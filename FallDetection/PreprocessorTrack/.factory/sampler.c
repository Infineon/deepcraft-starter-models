/*
* DEEPCRAFT Studio 5.3.2105.65534+97a4ad90a36f682f20d4081ed5623ff9ee9cc55f
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 11/19/2024 9:02:59 AM UTC. Any changes will be lost.
* 
* Layer                          Shape           Type       Function
* Scale                          [6]             float      compute
*    scale = 0.125
* 
* Exported functions:
* 
* void IMAI_compute(const float *restrict data_in, float *restrict data_out)
*    Description: Compute a forward pass
*    Parameter data_in is Input of size float[6].
*    Parameter data_out is Output of size float[6].
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

#include <stdint.h>

#include "sampler.h"

// Working memory

static inline void scale_f32(
	const float* restrict x,
	int count,
	float scale,
	float* restrict output)
{
	for (int i = 0; i < count; i++) {
		output[i] = x[i] * scale;
	}
}

#define __RETURN_ERROR(_exp) do { int __ret = (_exp); if(__ret < 0) return __ret; } while(0)
#define __RETURN_ERROR_BREAK_EMPTY(_exp) {  int __ret = (_exp); if(__ret == -1) break; if(__ret < 0) return __ret;  } 

void IMAI_compute(const float *restrict data_in, float *restrict data_out) {    
    scale_f32(data_in, 6, 0.125, data_out);
}

void IMAI_init(void) {    
}

