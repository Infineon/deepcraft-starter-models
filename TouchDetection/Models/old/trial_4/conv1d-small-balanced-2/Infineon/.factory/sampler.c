/*
* Imagimob Studio 5.1.1920+23251253412258875242be5d4844a74c53d9fafa
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 10/09/2024 16:36:14 UTC. Any changes will be lost.
* 
* Model ID  fe293fac-c0f8-4c8c-8ffa-f6f8c320f366
* 
* Memory    Size                      Efficiency
* State     1008 bytes (RAM)          100 %
* 
* Layer                          Shape           Type       Function
* Sliding Window (data points)   [50,3]          float      dequeue
*    window_shape = [50,3]
*    stride = 30
*    buffer_multiplier = 2
* 
* Exported functions:
* 
* int IMAI_dequeue(float *restrict data_out, float *restrict time_out)
*    Description: Dequeue features. RET_SUCCESS (0) on success, RET_NODATA (-1) if no data is available, RET_NOMEM (-2) on internal memory error
*    Parameter data_out is Output of size float[50,3].
*    Parameter time_out is Output of size float[2].
* 
* int IMAI_enqueue(const float *restrict data_in, const float *restrict time_in)
*    Description: Enqueue features. Returns SUCCESS (0) on success, else RET_NOMEM (-2) when low on memory.
*    Parameter data_in is Input of size float[6].
*    Parameter time_in is Input of size float[1].
* 
* void IMAI_init(void)
*    Description: Initializes buffers to initial state. This function also works as a reset function.
* 
* 
* Disclaimer:
*   The generated code relies on the optimizations done by the C compiler.
*   For example many for-loops of length 1 must be removed by the optimizer.
*   This can only be done if the functions are inlined and simplified.
*   Check disassembly if unsure.
*   tl;dr Compile using gcc with -O3 or -Ofast
*/

#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "sampler.h"

// Working memory
static int8_t _state[1008];

// Memory mapped buffers
#define _K5              ((int8_t *)(_state + 0x00000000))   // s8[1008] (1008 bytes) 

// Represents a Circular Buffer
// https://en.wikipedia.org/wiki/Circular_buffer
typedef struct
{
	char *buf;
	int size;		// total bytes allocated in *buf
	int used;		// current bytes used in buffer.
	int read;
	int write;
} cbuffer_t;

#define CBUFFER_SUCCESS 0
#define CBUFFER_NOMEM -1

// Initializes a cbuffer handle with given memory and size.
static inline void cbuffer_init(cbuffer_t *dest, void *mem, int size) {
	dest->buf = mem;
	dest->size = size;
	dest->used = 0;
	dest->read = 0;
	dest->write = 0;
}

// Returns the number of free bytes in buffer.
static inline int cbuffer_get_free(cbuffer_t *buf) {
	return buf->size - buf->used;
}

// Returns the number of used bytes in buffer.
static inline int cbuffer_get_used(cbuffer_t *buf) {
	return buf->used;
}

// Writes given data to buffer.
// Returns CBUFFER_SUCCESS or CBUFFER_NOMEM if out of memory.
static inline int cbuffer_enqueue(cbuffer_t *buf, const void *data, int data_size) {
	int free = cbuffer_get_free(buf);

	// Out of memory?
	if (free < data_size)
		return CBUFFER_NOMEM;

	// Is the data split in the end?
	if (buf->write + data_size > buf->size) {
		int first_size = buf->size - buf->write;
		memcpy(buf->buf + buf->write, data, first_size);
		memcpy(buf->buf, ((char *)data) + first_size, data_size - first_size);
	}
	else {
		memcpy(buf->buf + buf->write, data, data_size);
	}
	buf->write += data_size;
	if (buf->write >= buf->size)
		buf->write -= buf->size;

	buf->used += data_size;
	return CBUFFER_SUCCESS;
}

// Advances the read pointer by given count.
// Returns CBUFFER_SUCCESS on success or CBUFFER_NOMEM if count is more than available data
static inline int cbuffer_advance(cbuffer_t *buf, int count) {
	int used = cbuffer_get_used(buf);

	if (count > used)
		return CBUFFER_NOMEM;

	buf->read += count;
	if (buf->read >= buf->size)
		buf->read -= buf->size;

	// Reset pointers to 0 if buffer is empty in order to avoid unwanted wrapps.
	if (buf->read == buf->write) {
		buf->read = 0;
		buf->write = 0;
	}

	buf->used -= count;
	return CBUFFER_SUCCESS;
}

// Reset instance (clear buffer)
static inline void cbuffer_reset(cbuffer_t *buf) {
	buf->read = 0;
	buf->write = 0;
	buf->used = 0;
}

// Copies given "count" bytes to the "dst" buffer without advancing the buffer read offset.
// Returns CBUFFER_SUCCESS on success or CBUFFER_NOMEM if count is more than available data.
static inline int cbuffer_copyto(cbuffer_t *buf, void *dst, int count, int offset) {
	
	if (count > cbuffer_get_used(buf))
		return CBUFFER_NOMEM;

	int a0 = buf->read + offset;
	if (a0 >= buf->size)
		a0 -= buf->size;

	int c0 = count;
	if (a0 + c0 > buf->size)
		c0 = buf->size - a0;
	
	memcpy(dst, buf->buf + a0, c0);
	
	int c1 = count - c0;

	if (c1 > 0)
		memcpy(((char *)dst) + c0, buf->buf, c1);

	return CBUFFER_SUCCESS;
}

// Returns a read pointer at given offset and  
// updates *can_read_bytes (if not NULL) with the number of bytes that can be read.
// 
// Note! Byte count written to can_read_bytes can be less than what cbuffer_get_used() returns.
// This happens when the read has to be split in two since it's a circular buffer.
static inline void *cbuffer_readptr(cbuffer_t* buf, int offset, int *can_read_bytes)
{
	int a0 = buf->read + offset;
	if (a0 >= buf->size)
		a0 -= buf->size;
	if (can_read_bytes != NULL)
	{
		int c0 = buf->used;
		if (a0 + c0 > buf->size)
			c0 = buf->size - a0;

		*can_read_bytes = c0;
	}
	return buf->buf + a0;
}

typedef struct {
	cbuffer_t data_buffer;			// Circular Buffer for features
	cbuffer_t time_buffer;			// Circular Buffer for timestamps. Contains min,max for each input chunk
	int input_size;					// Number of bytes in each input chunk
	int window_count;				// Number of input chunks in output window.
} fixwin_t;

typedef float timestamp_t;
#define TIMESTAMP_MAX FLT_MAX
#define TIMESTAMP_MIN (-FLT_MAX)

#ifdef _MSC_VER
static_assert(sizeof(fixwin_t) <= 64, "Data structure 'fixwin_t' is too big");
#endif

#define IPWIN_RET_SUCCESS 0
#define IPWIN_RET_NODATA -1
#define IPWIN_RET_NOMEM -2

/*
* Try to dequeue a window.
*
* @param handle Pointer to an initialized handle.
* @param dst Pointer where to write window.
* @param stride_count Number of items (of size handle->input_size) to stride window.
* @param time pointer to float[2] array where to write min and max timestamp.
* @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1) is no data is available.
*/
static inline int fixwin_dequeuef32(void* restrict handle, void* restrict dst, int stride_count, void* restrict time)
{
	fixwin_t* fep = (fixwin_t*)handle;

	const int win_count = fep->window_count;
	const int size = win_count * fep->input_size;
	if (cbuffer_get_used(&fep->data_buffer) >= size) {
		if (cbuffer_copyto(&fep->data_buffer, dst, size, 0) != 0)
			return IPWIN_RET_NOMEM;
		
		if (cbuffer_advance(&fep->data_buffer, stride_count * fep->input_size) != 0)
			return IPWIN_RET_NOMEM;

		if (fep->time_buffer.used < win_count * 2 * sizeof(timestamp_t))
			return IPWIN_RET_NOMEM;

		timestamp_t min = TIMESTAMP_MAX;
		timestamp_t max = TIMESTAMP_MIN;
		cbuffer_t* time_buf = &fep->time_buffer;
		for(int i = 0; i < win_count * 2; i++)
		{			
			const timestamp_t value = *(timestamp_t*)cbuffer_readptr(time_buf, i * sizeof(timestamp_t), NULL);
			if (value > max)
				max = value;
			if (value < min)
				min = value;
		}
		((timestamp_t *)time)[0] = min;
		((timestamp_t *)time)[1] = max;
		
		if (cbuffer_advance(time_buf, stride_count * 2 * sizeof(timestamp_t)) != 0)
			return IPWIN_RET_NOMEM;
		
		return IPWIN_RET_SUCCESS;
	}
	return IPWIN_RET_NODATA;
}

/**
 * Enqueue handle->input_size values from given *data pointer to internal window buffer.
 *
 * @param handle Pointer to an initialized handle.
 * @param data Data to enqueue.
 * @param time Pointer to time_count timestamps.
 * @param time_count Number of float values in *time pointer
 * @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NOMEM (-2) if internal buffer is out of memory.
 */
static inline int fixwin_enqueuef32(void* restrict handle, const void* restrict data, const void* restrict time, int time_count)
{
	fixwin_t* fep = (fixwin_t*)handle;

	if (cbuffer_enqueue(&fep->data_buffer, data, fep->input_size) != 0)
		return IPWIN_RET_NOMEM;

	timestamp_t min = TIMESTAMP_MAX;
	timestamp_t max = TIMESTAMP_MIN;
	for (int i = 0; i < time_count; i++)
	{
		const float value = ((timestamp_t *)time)[i];
		if (value > max)
			max = value;
		if (value < min)
			min = value;
	}

	if (cbuffer_enqueue(&fep->time_buffer, &min, sizeof(timestamp_t)) != 0)
		return IPWIN_RET_NOMEM;
	if (cbuffer_enqueue(&fep->time_buffer, &max, sizeof(timestamp_t)) != 0)
		return IPWIN_RET_NOMEM;

	return IPWIN_RET_SUCCESS;
}

/**
* Initializes a fixwin sampler handle.
*
* @param handle Pointer to a preallocated memory area of fixwin_handle_size() bytes to initialize.
*
* @param input_size Number of bytes to enqueue.
* @param window_count Number of items (of size input_size) in each window
*/
static inline void fixwin_initf32(void* restrict handle, int input_size, int window_count)
{
	fixwin_t* fep = (fixwin_t*)handle;
	fep->input_size = input_size;
	fep->window_count = window_count;
	
	char* mem = ((char*)handle) + sizeof(fixwin_t);

	int data_buffer = input_size * window_count;
	int time_buffer = 2 * window_count * sizeof(timestamp_t);	// 2 = min,max
	
	cbuffer_init(&fep->data_buffer, mem, data_buffer);	
	cbuffer_init(&fep->time_buffer, mem + data_buffer, time_buffer);
}

#define __RETURN_ERROR(_exp) do { int __ret = (_exp); if(__ret < 0) return __ret; } while(0)
#define __RETURN_ERROR_BREAK_EMPTY(_exp) {  int __ret = (_exp); if(__ret == -1) break; if(__ret < 0) return __ret;  } 

int IMAI_dequeue(float *restrict data_out, float *restrict time_out) {    
    __RETURN_ERROR(fixwin_dequeuef32(_K5, data_out, 5, time_out));
    return 0;
}

int IMAI_enqueue(const float *restrict data_in, const float *restrict time_in) {    
    __RETURN_ERROR(fixwin_enqueuef32(_K5, data_in, time_in, 1));
    return 0;
}

void IMAI_init(void) {    
    fixwin_initf32(_K5, 24, 25);
}

