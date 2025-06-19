/*
* DEEPCRAFT Studio 5.5.3120.65534+525b8a9a633807a1867cf244cbe9400f1fe0f639
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 06/18/2025 14:05:34 UTC. Any changes will be lost.
* 
* Memory    Size                      Efficiency
* Buffers   6152 bytes (RAM)          100 %
* State     7480 bytes (RAM)          100 %
* Readonly  2216 bytes (Flash)        100 %
* 
* Layer                          Shape           Type       Function
* Sliding Window (data points)   [512]           float      dequeue
*    window_shape = [512]
*    stride = 160
*    buffer_multiplier = 1
* Hamming smoothing              [512]           float      dequeue
*    sym = True
* Real Discrete Fourier Transform [257,2]         float      dequeue
*    axis = 0
* Frobenius norm                 [257]           float      dequeue
*    axis = 0
* Mel Filterbank                 [40]            float      dequeue
*    num_filters = 40
*    sample_rate = 16000
*    f_low = 25
*    f_high = 8000
*    htk = True
*    librosa = False
* Clip                           [40]            float      dequeue
*    min = 0.000316227766016
*    max = 3.40282347E+38
* Logarithm                      [40]            float      dequeue
*    base = 0
* 
* Exported functions:
* 
* int IMAI_dequeue(float *restrict data_out, float *restrict time_out)
*    Description: Dequeue features. RET_SUCCESS (0) on success, RET_NODATA (-1) if no data is available, RET_NOMEM (-2) on internal memory error
*    Parameter data_out is Output of size float[40].
*    Parameter time_out is Output of size float[2].
* 
* int IMAI_enqueue(const float *restrict data_in, const float *restrict time_in)
*    Description: Enqueue features. Returns SUCCESS (0) on success, else RET_NOMEM (-2) when low on memory.
*    Parameter data_in is Input of size float[1].
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

#ifndef _IMAI_SAMPLER_H_
#define _IMAI_SAMPLER_H_
#ifdef _MSC_VER
#pragma once
#endif

#include <stdint.h>
#define IMAI_API_QUEUE_TIME

// First nibble is bit encoding, second nibble is number of bytes
#define IMAGINET_TYPES_NONE	(0x0)
#define IMAGINET_TYPES_FLOAT32	(0x14)
#define IMAGINET_TYPES_FLOAT64	(0x18)
#define IMAGINET_TYPES_INT8	(0x21)
#define IMAGINET_TYPES_INT16	(0x22)
#define IMAGINET_TYPES_INT32	(0x24)
#define IMAGINET_TYPES_INT64	(0x28)
#define IMAGINET_TYPES_QDYN8	(0x31)
#define IMAGINET_TYPES_QDYN16	(0x32)
#define IMAGINET_TYPES_QDYN32	(0x34)

// data_in [1] (4 bytes)
#define IMAI_DATA_IN_COUNT (1)
#define IMAI_DATA_IN_TYPE float
#define IMAI_DATA_IN_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_DATA_IN_SCALE (1)
#define IMAI_DATA_IN_OFFSET (0)
#define IMAI_DATA_IN_IS_QUANTIZED (0)

// time_in [1] (4 bytes)
#define IMAI_TIME_IN_COUNT (1)
#define IMAI_TIME_IN_TYPE float
#define IMAI_TIME_IN_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_TIME_IN_SCALE (1)
#define IMAI_TIME_IN_OFFSET (0)
#define IMAI_TIME_IN_IS_QUANTIZED (0)

// data_out [40] (160 bytes)
#define IMAI_DATA_OUT_COUNT (40)
#define IMAI_DATA_OUT_TYPE float
#define IMAI_DATA_OUT_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_DATA_OUT_SCALE (1)
#define IMAI_DATA_OUT_OFFSET (0)
#define IMAI_DATA_OUT_IS_QUANTIZED (0)

// time_out [2] (8 bytes)
#define IMAI_TIME_OUT_COUNT (2)
#define IMAI_TIME_OUT_TYPE float
#define IMAI_TIME_OUT_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_TIME_OUT_SCALE (1)
#define IMAI_TIME_OUT_OFFSET (0)
#define IMAI_TIME_OUT_IS_QUANTIZED (0)

#define IMAI_KEY_MAX (16)



// Return codes
#define IMAI_RET_SUCCESS 0
#define IMAI_RET_NODATA -1
#define IMAI_RET_NOMEM -2

// Exported methods
int IMAI_dequeue(float *restrict data_out, float *restrict time_out);
int IMAI_enqueue(const float *restrict data_in, const float *restrict time_in);
void IMAI_init(void);

#endif /* _IMAI_SAMPLER_H_ */
