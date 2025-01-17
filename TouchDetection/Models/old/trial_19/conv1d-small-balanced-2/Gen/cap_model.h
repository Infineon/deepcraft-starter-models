/*
* Imagimob Studio 5.1.1920+23251253412258875242be5d4844a74c53d9fafa
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 09/30/2024 15:27:12 UTC. Any changes will be lost.
* 
* Model ID  6885181a-1a57-430d-843b-03328ba32193
* 
* Memory    Size                      Efficiency
* Buffers   3840 bytes (RAM)          80 %
* State     496 bytes (RAM)           100 %
* Readonly  19464 bytes (Flash)       100 %
* 
* Backend              tensorflow
* Keras Version        2.15.0
* Backend Model Type   Sequential
* Backend Model Name   conv1d-small-balanced-2
* 
* Class Index | Symbol Label
* 0           | unlabelled
* 1           | touch
* 
* Layer                          Shape           Type       Function
* Sliding Window (data points)   [24,3]          float      dequeue
*    window_shape = [24,3]
*    stride = 30
*    buffer_multiplier = 2
* Input Layer                    [24,3]          float      dequeue
*    shape = [24,3]
* Convolution 1D                 [12,16]         float      dequeue
*    filters = 16
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 2
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,3,16]
* Batch Normalization            [12,16]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[16]
*    beta = float[16]
*    mean = float[16]
*    variance = float[16]
* Activation                     [12,16]         float      dequeue
*    activation = relu
*    trainable = True
* Convolution 1D                 [12,32]         float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,16,32]
* Convolution 1D                 [12,32]         float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,32,32]
* Batch Normalization            [12,32]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[32]
*    beta = float[32]
*    mean = float[32]
*    variance = float[32]
* Activation                     [12,32]         float      dequeue
*    activation = relu
*    trainable = True
* Max pooling 1D                 [6,32]          float      dequeue
*    pool_size = 2
*    strides = 2
*    padding = valid
*    trainable = True
* Global average pooling 1D      [32]            float      dequeue
*    trainable = True
* Dense                          [2]             float      dequeue
*    units = 2
*    use_bias = True
*    activation = linear
*    trainable = True
*    weight = float[32,2]
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

#ifndef _IMAI_CAP_CAP_MODEL_H_
#define _IMAI_CAP_CAP_MODEL_H_
#ifdef _MSC_VER
#pragma once
#endif

#include <stdint.h>

typedef struct {    
    char *name;
    double TP; // True Positive or Correct Positive Prediction
    double FN; // False Negative or Incorrect Negative Prediction
    double FP; // False Positive or Incorrect Positive Prediction
    double TN; // True Negative or Correct Negative Prediction
    double TPR; // True Positive Rate or Sensitivity, Recall
    double TNR; // True Negative Rate or Specificity, Selectivity
    double PPV; // Positive Predictive Value or Precision
    double NPV; // Negative Predictive Value
    double FNR; // False Negative Rate or Miss Rate
    double FPR; // False Positive Rate or Fall-Out
    double FDR; // False Discovery Rate
    double FOR; // False Omission Rate
    double F1S; // F1 Score
} IMAI_CAP_stats;

/*
* Tensorflow Test Set
* 
* (ACC) Accuracy 99.009 %
* (F1S) F1 Score 99.004 %
* 
* Name of class                                            (unlabelled)            touch
* (TP) True Positive or Correct Positive Prediction                5522             1771
* (FN) False Negative or Incorrect Negative Prediction                7               66
* (FP) False Positive or Incorrect Positive Prediction               66                7
* (TN) True Negative or Correct Negative Prediction                1771             5522
* (TPR) True Positive Rate or Sensitivity, Recall               99.87 %          96.41 %
* (TNR) True Negative Rate or Specificity, Selectivity          96.41 %          99.87 %
* (PPV) Positive Predictive Value or Precision                  98.82 %          99.61 %
* (NPV) Negative Predictive Value                               99.61 %          98.82 %
* (FNR) False Negative Rate or Miss Rate                         0.13 %           3.59 %
* (FPR) False Positive Rate or Fall-Out                          3.59 %           0.13 %
* (FDR) False Discovery Rate                                     1.18 %           0.39 %
* (FOR) False Omission Rate                                      0.39 %           1.18 %
* (F1S) F1 Score                                                99.34 %          97.98 %
*/


#define IMAI_CAP_TEST_AVG_ACC 0.9900896008688569 // Accuracy
#define IMAI_CAP_TEST_AVG_F1S 0.9900350257972635 // F1 Score

#define IMAI_CAP_TEST_STATS { \
 {name: "(unlabelled)", TP: 5522, FN: 7, FP: 66, TN: 1771, TPR: 0.9987339482727, TNR: 0.9640718562874, PPV: 0.9881889763779, NPV: 0.9960629921259, FNR: 0.0012660517272, FPR: 0.0359281437125, FDR: 0.0118110236220, FOR: 0.0039370078740, F1S: 0.9934334802554, }, \
 {name: "touch", TP: 1771, FN: 66, FP: 7, TN: 5522, TPR: 0.9640718562874, TNR: 0.9987339482727, PPV: 0.9960629921259, NPV: 0.9881889763779, FNR: 0.0359281437125, FPR: 0.0012660517272, FDR: 0.0039370078740, FOR: 0.0118110236220, F1S: 0.9798063623789, }, \
}

#ifdef IMAI_CAP_STATS_ENABLED
static const IMAI_CAP_stats IMAI_CAP_test_stats[] = IMAI_CAP_TEST_STATS;
#endif

/*
* Tensorflow Train Set
* 
* (ACC) Accuracy 99.045 %
* (F1S) F1 Score 99.040 %
* 
* Name of class                                            (unlabelled)            touch
* (TP) True Positive or Correct Positive Prediction               22796             6453
* (FN) False Negative or Incorrect Negative Prediction               46              236
* (FP) False Positive or Incorrect Positive Prediction              236               46
* (TN) True Negative or Correct Negative Prediction                6453            22796
* (TPR) True Positive Rate or Sensitivity, Recall               99.80 %          96.47 %
* (TNR) True Negative Rate or Specificity, Selectivity          96.47 %          99.80 %
* (PPV) Positive Predictive Value or Precision                  98.98 %          99.29 %
* (NPV) Negative Predictive Value                               99.29 %          98.98 %
* (FNR) False Negative Rate or Miss Rate                         0.20 %           3.53 %
* (FPR) False Positive Rate or Fall-Out                          3.53 %           0.20 %
* (FDR) False Discovery Rate                                     1.02 %           0.71 %
* (FOR) False Omission Rate                                      0.71 %           1.02 %
* (F1S) F1 Score                                                99.39 %          97.86 %
*/


#define IMAI_CAP_TRAIN_AVG_ACC 0.9904507128102672 // Accuracy
#define IMAI_CAP_TRAIN_AVG_F1S 0.9904016998664785 // F1 Score

#define IMAI_CAP_TRAIN_STATS { \
 {name: "(unlabelled)", TP: 22796, FN: 46, FP: 236, TN: 6453, TPR: 0.9979861658348, TNR: 0.9647181940499, PPV: 0.9897533865925, NPV: 0.9929219879981, FNR: 0.0020138341651, FPR: 0.0352818059500, FDR: 0.0102466134074, FOR: 0.0070780120018, F1S: 0.9938527270349, }, \
 {name: "touch", TP: 6453, FN: 236, FP: 46, TN: 22796, TPR: 0.9647181940499, TNR: 0.9979861658348, PPV: 0.9929219879981, NPV: 0.9897533865925, FNR: 0.0352818059500, FPR: 0.0020138341651, FDR: 0.0070780120018, FOR: 0.0102466134074, F1S: 0.9786169244767, }, \
}

#ifdef IMAI_CAP_STATS_ENABLED
static const IMAI_CAP_stats IMAI_CAP_train_stats[] = IMAI_CAP_TRAIN_STATS;
#endif

/*
* Tensorflow Validation Set
* 
* (ACC) Accuracy 99.484 %
* (F1S) F1 Score 99.483 %
* 
* Name of class                                            (unlabelled)            touch
* (TP) True Positive or Correct Positive Prediction                5209             1922
* (FN) False Negative or Incorrect Negative Prediction               12               25
* (FP) False Positive or Incorrect Positive Prediction               25               12
* (TN) True Negative or Correct Negative Prediction                1922             5209
* (TPR) True Positive Rate or Sensitivity, Recall               99.77 %          98.72 %
* (TNR) True Negative Rate or Specificity, Selectivity          98.72 %          99.77 %
* (PPV) Positive Predictive Value or Precision                  99.52 %          99.38 %
* (NPV) Negative Predictive Value                               99.38 %          99.52 %
* (FNR) False Negative Rate or Miss Rate                         0.23 %           1.28 %
* (FPR) False Positive Rate or Fall-Out                          1.28 %           0.23 %
* (FDR) False Discovery Rate                                     0.48 %           0.62 %
* (FOR) False Omission Rate                                      0.62 %           0.48 %
* (F1S) F1 Score                                                99.65 %          99.05 %
*/


#define IMAI_CAP_VALIDATION_AVG_ACC 0.9948381696428571 // Accuracy
#define IMAI_CAP_VALIDATION_AVG_F1S 0.994832733647165 // F1 Score

#define IMAI_CAP_VALIDATION_STATS { \
 {name: "(unlabelled)", TP: 5209, FN: 12, FP: 25, TN: 1922, TPR: 0.9977015897337, TNR: 0.9871597329224, PPV: 0.9952235384027, NPV: 0.9937952430196, FNR: 0.0022984102662, FPR: 0.0128402670775, FDR: 0.0047764615972, FOR: 0.0062047569803, F1S: 0.9964610234337, }, \
 {name: "touch", TP: 1922, FN: 25, FP: 12, TN: 5209, TPR: 0.9871597329224, TNR: 0.9977015897337, PPV: 0.9937952430196, NPV: 0.9952235384027, FNR: 0.0128402670775, FPR: 0.0022984102662, FDR: 0.0062047569803, FOR: 0.0047764615972, F1S: 0.9904663746457, }, \
}

#ifdef IMAI_CAP_STATS_ENABLED
static const IMAI_CAP_stats IMAI_CAP_validation_stats[] = IMAI_CAP_VALIDATION_STATS;
#endif

#define IMAI_CAP_API_QUEUE

// All symbols in order
#define IMAI_CAP_SYMBOL_MAP {"unlabelled", "touch"}

// Model GUID (16 bytes)
#define IMAI_CAP_MODEL_ID {0x1a, 0x18, 0x85, 0x68, 0x57, 0x1a, 0x0d, 0x43, 0x84, 0x3b, 0x03, 0x32, 0x8b, 0xa3, 0x21, 0x93}

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

// data_in [6] (24 bytes)
#define IMAI_CAP_DATA_IN_COUNT (6)
#define IMAI_CAP_DATA_IN_TYPE float
#define IMAI_CAP_DATA_IN_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_CAP_DATA_IN_SCALE (1)
#define IMAI_CAP_DATA_IN_OFFSET (0)
#define IMAI_CAP_DATA_IN_IS_QUANTIZED (0)

// data_out [2] (8 bytes)
#define IMAI_CAP_DATA_OUT_COUNT (2)
#define IMAI_CAP_DATA_OUT_TYPE float
#define IMAI_CAP_DATA_OUT_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_CAP_DATA_OUT_SCALE (1)
#define IMAI_CAP_DATA_OUT_OFFSET (0)
#define IMAI_CAP_DATA_OUT_IS_QUANTIZED (0)

#define IMAI_CAP_KEY_MAX (28)



// Return codes
#define IMAI_CAP_RET_SUCCESS 0
#define IMAI_CAP_RET_NODATA -1
#define IMAI_CAP_RET_NOMEM -2

// Exported methods
int IMAI_CAP_dequeue(float *restrict data_out);
int IMAI_CAP_enqueue(const float *restrict data_in);
void IMAI_CAP_init(void);

#endif /* _IMAI_CAP_CAP_MODEL_H_ */
