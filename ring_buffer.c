/* Includes ------------------------------------------------------------------*/
#include <assert.h>
#include "ring_buffer.h"


bool RingBuffer_Init(RingBuffer *ringBuffer, char *dataBuffer, size_t dataBufferSize)
{
	assert(ringBuffer);
	assert(dataBuffer);
	assert(dataBufferSize > 0);

	if ((ringBuffer) && (dataBuffer) && (dataBufferSize > 0)) {
      ringBuffer->data_pointer = dataBuffer;
	  ringBuffer->buffer_size = dataBufferSize;
	  for(uint16_t i; i < ringBuffer->buffer_size;i++)
      {
          ringBuffer->data_pointer[i] = 0;
      }
      ringBuffer->startnr = 0;
      ringBuffer->endnr = 0;
      ringBuffer->counter = 0;
      return true;
	}

	return false;
}

bool RingBuffer_Clear(RingBuffer *ringBuffer)
{
	assert(ringBuffer);

	if (ringBuffer) {
        for(uint16_t i; i < ringBuffer->counter;i++)
        {
            ringBuffer->data_pointer[i] = 0;
        }
        ringBuffer->startnr = 0;
        ringBuffer->endnr = 0;
        ringBuffer->counter = 0;
        return true;
	}
	return false;
}

bool RingBuffer_IsEmpty(const RingBuffer *ringBuffer)
{
  assert(ringBuffer);
	if(ringBuffer->counter != 0)
        return false;

	return true;
}

size_t RingBuffer_GetLen(const RingBuffer *ringBuffer)
{
	assert(ringBuffer);

	if (ringBuffer) {
		return(ringBuffer->counter);
	}
	return 0;

}

size_t RingBuffer_GetCapacity(const RingBuffer *ringBuffer)
{
	assert(ringBuffer);

	if (ringBuffer) {
		return(ringBuffer->buffer_size);
	}
	return 0;
}


bool RingBuffer_PutChar(RingBuffer *ringBuffer, char c)
{
	assert(ringBuffer);

	if (ringBuffer) {
		if(ringBuffer->counter != ringBuffer->buffer_size)
        {
            ringBuffer->data_pointer[ringBuffer->startnr] = c;
            ringBuffer->startnr++;
            ringBuffer->startnr %= ringBuffer->buffer_size;
            ringBuffer->counter++;
            return true;
        }

	}
	return false;
}

bool RingBuffer_GetChar(RingBuffer *ringBuffer, char *c)
{
	assert(ringBuffer);
	assert(c);

  if ((ringBuffer) && (c)) {
		if(!RingBuffer_IsEmpty(ringBuffer))
        {
            *c = ringBuffer->data_pointer[ringBuffer->endnr];
            ringBuffer->endnr++;
            ringBuffer->endnr %= ringBuffer->buffer_size;
            ringBuffer->counter--;
            return true;
        }
	}
	return false;
}
