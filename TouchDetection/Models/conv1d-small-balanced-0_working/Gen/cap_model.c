/*
* Imagimob Studio 5.1.1920+23251253412258875242be5d4844a74c53d9fafa
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 10/01/2024 02:16:13 UTC. Any changes will be lost.
* 
* Model ID  63d39a27-6a93-4634-a648-b9cf55ac7c6e
* 
* Memory    Size                      Efficiency
* Buffers   1440 bytes (RAM)          80 %
* State     496 bytes (RAM)           100 %
* Readonly  584 bytes (Flash)         100 %
* 
* Backend              tensorflow
* Keras Version        2.15.0
* Backend Model Type   Sequential
* Backend Model Name   conv1d-small-balanced-0
* 
* Class Index | Symbol Label
* 0           | unlabelled
* 1           | touch
* 
* Layer                          Shape           Type       Function
* Sliding Window (data points)   [24,3]          float      dequeue
*    window_shape = [24,3]
*    stride = 42
*    buffer_multiplier = 2
* Input Layer                    [24,3]          float      dequeue
*    shape = [24,3]
* Convolution 1D                 [12,12]         float      dequeue
*    filters = 12
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 2
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,3,12]
* Batch Normalization            [12,12]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[12]
*    beta = float[12]
*    mean = float[12]
*    variance = float[12]
* Activation                     [12,12]         float      dequeue
*    activation = relu
*    trainable = True
* Max pooling 1D                 [6,12]          float      dequeue
*    pool_size = 2
*    strides = 2
*    padding = valid
*    trainable = True
* Global average pooling 1D      [12]            float      dequeue
*    trainable = True
* Dense                          [2]             float      dequeue
*    units = 2
*    use_bias = True
*    activation = linear
*    trainable = True
*    weight = float[12,2]
*    bias = float[2]
* Activation                     [2]             float      dequeue
*    activation = softmax
*    trainable = True
* 
* Exported functions:
* 
* int IMAI_CAP_dequeue(float *restrict data_out)
*    Description: Dequeue features. RET_SUCCESS (0) on success, RET_NODATA (-1) if no data is available, RET_NOMEM (-2) on internal memory error
*    Parameter data_out is Output of size float[2].
* 
* int IMAI_CAP_enqueue(const float *restrict data_in)
*    Description: Enqueue features. Returns SUCCESS (0) on success, else RET_NOMEM (-2) when low on memory.
*    Parameter data_in is Input of size float[6].
* 
* void IMAI_CAP_init(void)
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

/*
* Tensorflow Test Set
* 
* (ACC) Accuracy 96.546 %
* (F1S) F1 Score 96.481 %
* 
* Name of class                                            (unlabelled)            touch
* (TP) True Positive or Correct Positive Prediction                3766             1321
* (FN) False Negative or Incorrect Negative Prediction                7              175
* (FP) False Positive or Incorrect Positive Prediction              175                7
* (TN) True Negative or Correct Negative Prediction                1321             3766
* (TPR) True Positive Rate or Sensitivity, Recall               99.81 %          88.30 %
* (TNR) True Negative Rate or Specificity, Selectivity          88.30 %          99.81 %
* (PPV) Positive Predictive Value or Precision                  95.56 %          99.47 %
* (NPV) Negative Predictive Value                               99.47 %          95.56 %
* (FNR) False Negative Rate or Miss Rate                         0.19 %          11.70 %
* (FPR) False Positive Rate or Fall-Out                         11.70 %           0.19 %
* (FDR) False Discovery Rate                                     4.44 %           0.53 %
* (FOR) False Omission Rate                                      0.53 %           4.44 %
* (F1S) F1 Score                                                97.64 %          93.56 %
*/

#include <float.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#include "cap_model.h"

// Working memory
static int8_t _buffer[1440];
static int8_t _state[496];

// Parameters
static const uint32_t _K5[] = {
    0xbceea861, 0x3c72ab0f, 0xbc7788a4, 0x3c2a53c6, 0xbc34f36f, 0xbca3b660, 0x3ad525c1, 0x3ae9a147, 
    0x3d109341, 0xba456f22, 0x3b1fea1a, 0xbc4dbfd4, 0xbb9c392a, 0x3c0fba40, 0xbc94336b, 0xbad6a72d, 
    0x3bb52d55, 0xbc0ab16e, 0x3bde72c9, 0xbc0bd4e2, 0xbc7c8e32, 0x3b4fbc81, 0x3bca8272, 0xbcbcdc97, 
    0x3a61dd18, 0x3b082ea5, 0xbc1b6f40, 0xbc87c37e, 0x3be4e0c1, 0xbc512740, 0xbc291db9, 0x3d3da418, 
    0xbc88a735, 0xbb60376a, 0xbb0ca64a, 0x3c7673ca, 0x3b62501e, 0x3987dc87, 0x3bac1280, 0x3a5aaf81, 
    0xbb38695f, 0x3b77e1cf, 0xbacd11c6, 0x3b95fd46, 0xb9bf0424, 0x3b592e8d, 0x39842d97, 0x3b5cc731, 
    0x3a1f5139, 0xbbd24c77, 0x3b700352, 0x3a582020, 0x3b150fde, 0xbb087bc2, 0x3aa12cfe, 0xbbd61b67, 
    0xbbe0b444, 0xbb5c983d, 0x3b9d92fb, 0xbc09734d, 0x3b23cedb, 0xba928691, 0xbba1e55d, 0x3b3200a0, 
    0x3aa5b860, 0x3b3627d7, 0x3b2b3a4d, 0x3b167a67, 0x3bd96993, 0x3a54ed23, 0xbb64fef9, 0x3b0b8752, 
    0xb8885d82, 0x3ab02673, 0x3b0a987e, 0x3aa5c786, 0xbb0bb6ee, 0x3b7f5aac, 0x3b24da2e, 0x39ec9c5b, 
    0xb90138d8, 0xbc4351d8, 0x3c0019db, 0xbc6a0fae, 0xbbaa902d, 0x3aa67660, 0xbc304340, 0x3af2013e, 
    0x3ae17882, 0x3c889150, 0xbbc35dc4, 0x3ba7cf3a, 0xbc2c0824, 0xbc177806, 0x3bc4b6f5, 0xbb5e023e, 
    0xba97d938, 0x3b6d6f42, 0x3b28bccf, 0xba1f39f0, 0x3b0d5559, 0x3b16f4d3, 0x3a83b792, 0xbb30768b, 
    0x3b2727b9, 0x3ad3d070, 0x3ac0a1de, 0x3a27a34a
};

static const uint32_t _K8[] = {
    0x41756bea, 0xc0f8b0c6, 0xc11c5bf6, 0xc1c1d7d6, 0xc0b20a95, 0xbf629085, 0x4093a91c, 0xc119a38a, 
    0xc07e7544, 0x40ec82a2, 0x40847cdf, 0xc038c70f
};

static const uint32_t _K14[] = {
    0x3f56b4e1, 0x3fb6315a, 0x3fc98a83, 0xc022a040, 0xbf2a0eb8, 0xbf13aa48, 0x3e8efb6c, 0x3f5ac90b, 
    0xbee2eb13, 0x3f77c2e2, 0x3f80fc6f, 0xbed54c95, 0xbf6fd0bc, 0xbf600c05, 0xbfad7e66, 0x3ffc0599, 
    0x3f32d322, 0x3dda252b, 0xbedae150, 0xbfb60f49, 0x3f2ba0de, 0xbf3e25f7, 0xbf14c57e, 0x3edb6a2d
};

static const uint32_t _K16[] = {
    0xbd29f724, 0x3d29f71a
};

// Memory mapped buffers
#define _K14             ((float *)_K14)                     // f32[2,12] (96 bytes) 
#define _K16             ((float *)_K16)                     // f32[2] (8 bytes) 
#define _K5              ((float *)_K5)                      // f32[12,3,3] (432 bytes) 
#define _K8              ((float *)_K8)                      // f32[12] (48 bytes) 
#define _K3              ((int8_t *)(_state + 0x00000000))   // s8[496] (496 bytes) 
#define _K10             ((float *)(_buffer + 0x00000000))   // f32[12,12] (576 bytes) 
#define _K12             ((float *)(_buffer + 0x00000240))   // f32[6,12] (288 bytes) 
#define _K13             ((float *)(_buffer + 0x00000000))   // f32[12] (48 bytes) 
#define _K15             ((float *)(_buffer + 0x00000030))   // f32[2] (8 bytes) 
#define _K17             ((float *)(_buffer + 0x00000000))   // f32[2] (8 bytes) 
#define _K2              ((float *)(_buffer + 0x00000000))   // f32[24,3] (288 bytes) 
#define _K4              ((float *)(_buffer + 0x00000120))   // f32[12,12] (576 bytes) 
#define _K6              ((float *)(_buffer + 0x00000360))   // f32[12,12] (576 bytes) 

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
	int input_size;					// Number of bytes in each input chunk
	int window_count;				// Number of input chunks in output window.
} fixwin_t;

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
* @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1) is no data is available.
*/
static inline int fixwin_dequeuef32(void* restrict handle, void* restrict dst, int stride_count)
{
	fixwin_t* fep = (fixwin_t*)handle;

	const int stride_bytes = stride_count * fep->input_size;
	const int size = fep->window_count * fep->input_size;
	if (cbuffer_get_used(&fep->data_buffer) >= size) {
		if (cbuffer_copyto(&fep->data_buffer, dst, size, 0) != 0)
			return IPWIN_RET_NOMEM;

		if (cbuffer_advance(&fep->data_buffer, stride_bytes) != 0)
			return IPWIN_RET_NOMEM;

		return IPWIN_RET_SUCCESS;
	}
	return IPWIN_RET_NODATA;
}

static inline float mac_f32(const float* restrict a, const float* restrict b, int count)
{
	float sum = 0;
	for (int i = 0; i < count; i++) {
		sum += *a++ * *b++;
	}
	return sum;
}

static inline void conv1d_flat_f32(
	const float* restrict input,
	const float* restrict weight,
	float* restrict output,
	int top,
	int bottom,
	int n_output_rows,
	int filters,
	int strides,
	int kernel_size)
{
	for (int i = 0; i < n_output_rows; i++) {
		const float* wp = weight;		// Weight matrix
		const float* bp = input;		// Input matrix
		const int step = i * strides;	// Row size
		int len = kernel_size;			// Normally do one kernel

		int skip = top - step;			// Pad top?
		if (skip > 0) {
			len -= skip;				// Trim kernel length
			wp += skip;					// Advance kernel
		}
		else {						// No top padding,
			bp -= skip;					// Rollback input
		}

		skip = step + len - bottom;		// Pad bottom?
		if (skip > 0)
			len -= skip;				// Just cut the kernel at end

		float* op = output + i * filters;
		for (int j = 0; j < filters; j++) {
			*op++ = mac_f32(wp + j * kernel_size, bp, len);
		}
	}
}

static inline void add_f32(
	const float* restrict a,
	const float* restrict b,
	int l, int g1, int m, int g2, int r,
	float* restrict output)
{
	int index = 0;
	for (int x = 0; x < l; x++) {
		for (int i = 0; i < g1; i++) {
			for (int y = 0; y < m; y++) {
				for (int j = 0; j < g2; j++) {
					for (int z = 0; z < r; z++) {
						output[index] = a[index] + b[x * m * r + y * r + z];
						index++;
					}
				}
			}
		}
	}
}

static inline void relu_f32(const float* restrict x, int count, float* restrict result)
{
	for (int i = 0; i < count; i++) {
		const float value = *x++;
		*result++ = value > 0 ? value : 0;
	}
}

static inline float maxpool1d_f32_max(const float *restrict x, int ncols, int pool_size)
{
    float max = -FLT_MAX;
    for (int i = 0; i < pool_size; i++) {
        const float value = *(x + i * ncols);
        if (value > max)
            max = value;
    }
    return max;
}

static inline void maxpool1d_f32_row(const float* restrict x, int pool_size, int ncols, float* restrict result)
{
    for (int i = 0; i < ncols; i++) {
        const float* xp = x + i;
        *result++ = maxpool1d_f32_max(xp, ncols, pool_size);
    }
}

static inline void maxpool1d_valid_f32(
    const float* restrict input,
    int pool_size,
    int strides,
    int ncols,
    int n_output_rows,
    float* restrict result)
{
    int input_pointer_step = ncols * strides;

    for (int i = 0; i < n_output_rows; i++) {
        const float* input_current = input + (i * input_pointer_step);
        float* rp = result + (i * ncols);
        maxpool1d_f32_row(input_current, pool_size, ncols, rp);
    }
}

static inline float _globav1d_f32_mean(const float *restrict x, int nchannel, int nsteps)
{
	float mean = 0.0;
	for (int i = 0; i < nsteps; i++) {
		const float value = *(x + i * nchannel);
		mean = mean + value;
	}
	mean = mean/(float)nsteps;
	return mean;
}

static inline void globav1d_f32(const float *restrict x, int nsteps, int nchannel, float *restrict result)
{
	// Loop over all channels
	for (int i = 0; i < nchannel; i++) {
		const float* xp = x + i;
		*result++ = _globav1d_f32_mean(xp, nchannel, nsteps);
	}
}

static inline void dott_f32(const float *restrict a, const float *restrict b, float *restrict out, int d0, int d1, int d2)
{
	for (int i = 0; i < d2; i++) {
		float* op = out;
		for (int j = 0; j < d1; j++) {
			*op++ = mac_f32(a + j * d0, b, d0);
		}
		out += d1;
		b += d0;
	}
}

static inline void softmax_f32(const float* restrict x, int count, float* restrict result)
{
	float sum = 0;
	for (int i = 0; i < count; i++) {
		float value = expf(x[i]);
		sum += value;
		result[i] = value;
	}
	for (int i = 0; i < count; i++) {
		result[i] /= sum;
	}
}

/**
 * Enqueue handle->input_size values from given *data pointer to internal window buffer.
 *
 * @param handle Pointer to an initialized handle.
 * @param data Data to enqueue.
 * @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NOMEM (-2) if internal buffer is out of memory.
 */
static inline int fixwin_enqueuef32(void* restrict handle, const void* restrict data)
{
	fixwin_t* fep = (fixwin_t*)handle;

	if (cbuffer_enqueue(&fep->data_buffer, data, fep->input_size) != 0)
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
	
	cbuffer_init(&fep->data_buffer, mem, data_buffer);
}

#define __RETURN_ERROR(_exp) do { int __ret = (_exp); if(__ret < 0) return __ret; } while(0)
#define __RETURN_ERROR_BREAK_EMPTY(_exp) {  int __ret = (_exp); if(__ret == -1) break; if(__ret < 0) return __ret;  } 

int IMAI_CAP_dequeue(float *restrict data_out) {    
    __RETURN_ERROR(fixwin_dequeuef32(_K3, _K2, 7));
    conv1d_flat_f32(_K2, _K5, _K4, 0, 72, 12, 12, 6, 9);
    add_f32(_K4, _K8, 1, 1, 1, 12, 12, _K6);
    relu_f32(_K6, 144, _K10);
    maxpool1d_valid_f32(_K10, 2, 2, 12, 6, _K12);
    globav1d_f32(_K12, 6, 12, _K13);
    dott_f32(_K14, _K13, _K15, 12, 2, 1);
    add_f32(_K15, _K16, 1, 1, 1, 1, 2, _K17);
    softmax_f32(_K17, 2, data_out);
    return 0;
}

int IMAI_CAP_enqueue(const float *restrict data_in) {    
    __RETURN_ERROR(fixwin_enqueuef32(_K3, data_in));
    return 0;
}

void IMAI_CAP_init(void) {    
    fixwin_initf32(_K3, 24, 12);
}

