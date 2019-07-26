#include "cli.h"
#include "usart.h"
#include <string.h>
#include <ctype.h>
#include "stm32f4xx_hal.h"

// head of CLI command list
static CLI_CommandItem *head = NULL;

// char buffer where command will be stored
static char commandBuffer[100];

uint8_t i = 0;

/**
 * This function searches the CLI command list and tries to find a descriptor for the provided command.
 * The command format is case-insensitive.
 * Returns pointer to @ref CLI_MenuItem structure if given command was found in the CLI command list.
 *
 * @param command pointer to command (string)
 *
 * @retval pointer to @ref CLI_MenuItem structure desrcibing the command, if command was found
 * @retval NULL if the given command does not match any command regitstered in the CLI command list 
 */
static CLI_CommandItem* CLI_GetMenuItemByCommandName(char *command);

/**
 * @bref This function is responsible for collecting the command reading in from USART.
 *
 * This function should check wether the USART interface has some new data. If it does
 * this function reads new characters and stores them in a command buffer. This function
 * is also responsible for providing echo of the input characters back to the buffer.
 *
 * The function exits when:
 * - no more characters are available to read from USART - the function returns false
 * - new line was detected - this function returns true
 *
 * @retval true if command was collected
 * @retval false if command is yet incomplete
 */
static bool CLI_StoreCommand(void);

/**
 * @brief This function converts string to a lowercase
 *
 * @param dst pointer where converted null terminated string will be stored
 * @param src pointer to string which will be converted
 */
static void CLI_StringToUpper(char *dst, const char *src);
	
	
	
void CLI_Proc(void){
	
	if(CLI_StoreCommand() && strlen(commandBuffer)){
		char *args;
		args = strchr(commandBuffer, ' ');
		if(args!=NULL){
				*args='\0';
				args++; 
		}
		CLI_StringToUpper(commandBuffer,commandBuffer);
		CLI_CommandItem * item = CLI_GetMenuItemByCommandName(commandBuffer);
		if(item){
			item->callback(args);
		} else {
			if (0 == strcmp(commandBuffer,"?")) {
				USART_WriteString("\n\r");
				CLI_PrintAllCommands();
			}
		}
	}
}

bool CLI_AddCommand(CLI_CommandItem *item){
	if(item->callback==NULL||item->commandName==NULL){
	return false;
	}
	if(head==NULL){
		head=item;}
	else{
		CLI_CommandItem *temp = head;
		while(!(temp->next == NULL)){
			temp = temp->next;
		}
		temp->next = item;
		
	}
	return true;
	
}

void CLI_PrintAllCommands(void){
	CLI_CommandItem *temp = head;
	while(temp!=NULL)
	{
		USART_WriteString(temp->commandName);
		USART_WriteString("\n\r");	
		temp = temp->next;
	}
}

CLI_CommandItem* CLI_GetMenuItemByCommandName(char *command){
	CLI_CommandItem* item;
	item = head;
	while(item != NULL && strcmp(item->commandName, command)){
		item = item->next;
	}
	
	return item;
};

void CLI_StringToUpper(char *dst, const char *src){
	int i = 0;
	while(*(src+i)){
	*(dst+i)=toupper(*(src+i));
		i++;
	}
}

bool CLI_StoreCommand(){
	
	char c;
	static int index;
	
	if(USART_GetChar(&c)){
		USART_PutChar(c);
		if(c=='\n'||c=='\r'){
			commandBuffer[index] = 0;
			index = 0;
			USART_WriteString("\n\r");
			return true;
		}
		else if(c == 127)
		{
			if (index > 0) {
				index--;
			}
		}
		else
		{
			commandBuffer[index++] = c;
		}
	}
	
	return false;
}
