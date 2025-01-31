/*
* Imagimob Studio 5.1.1920+23251253412258875242be5d4844a74c53d9fafa
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 10/09/2024 09:03:04 UTC. Any changes will be lost.
* 
* Model ID  fe293fac-c0f8-4c8c-8ffa-f6f8c320f366
* 
* Memory    Size                      Efficiency
* Buffers   8000 bytes (RAM)          80 %
* State     808 bytes (RAM)           100 %
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
* Sliding Window (data points)   [50,3]          float      dequeue
*    window_shape = [50,3]
*    stride = 30
*    buffer_multiplier = 2
* Input Layer                    [50,3]          float      dequeue
*    shape = [50,3]
* Convolution 1D                 [25,16]         float      dequeue
*    filters = 16
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 2
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,3,16]
* Batch Normalization            [25,16]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[16]
*    beta = float[16]
*    mean = float[16]
*    variance = float[16]
* Activation                     [25,16]         float      dequeue
*    activation = relu
*    trainable = True
* Convolution 1D                 [25,32]         float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,16,32]
* Convolution 1D                 [25,32]         float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,32,32]
* Batch Normalization            [25,32]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[32]
*    beta = float[32]
*    mean = float[32]
*    variance = float[32]
* Activation                     [25,32]         float      dequeue
*    activation = relu
*    trainable = True
* Max pooling 1D                 [12,32]         float      dequeue
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
* (ACC) Accuracy 94.260 %
* (F1S) F1 Score 94.298 %
* 
* Name of class                                            (unlabelled)            touch
* (TP) True Positive or Correct Positive Prediction                8941             3655
* (FN) False Negative or Incorrect Negative Prediction              478              289
* (FP) False Positive or Incorrect Positive Prediction              289              478
* (TN) True Negative or Correct Negative Prediction                3655             8941
* (TPR) True Positive Rate or Sensitivity, Recall               94.93 %          92.67 %
* (TNR) True Negative Rate or Specificity, Selectivity          92.67 %          94.93 %
* (PPV) Positive Predictive Value or Precision                  96.87 %          88.43 %
* (NPV) Negative Predictive Value                               88.43 %          96.87 %
* (FNR) False Negative Rate or Miss Rate                         5.07 %           7.33 %
* (FPR) False Positive Rate or Fall-Out                          7.33 %           5.07 %
* (FDR) False Discovery Rate                                     3.13 %          11.57 %
* (FOR) False Omission Rate                                     11.57 %           3.13 %
* (F1S) F1 Score                                                95.89 %          90.50 %
*/


#define IMAI_CAP_TEST_AVG_ACC 0.9426027089725361 // Accuracy
#define IMAI_CAP_TEST_AVG_F1S 0.9429834018282393 // F1 Score

#define IMAI_CAP_TEST_STATS { \
 {name: "(unlabelled)", TP: 8941, FN: 478, FP: 289, TN: 3655, TPR: 0.9492515128994, TNR: 0.9267241379310, PPV: 0.9686890574214, NPV: 0.8843455117348, FNR: 0.0507484871005, FPR: 0.0732758620689, FDR: 0.0313109425785, FOR: 0.1156544882651, F1S: 0.9588717893720, }, \
 {name: "touch", TP: 3655, FN: 289, FP: 478, TN: 8941, TPR: 0.9267241379310, TNR: 0.9492515128994, PPV: 0.8843455117348, NPV: 0.9686890574214, FNR: 0.0732758620689, FPR: 0.0507484871005, FDR: 0.1156544882651, FOR: 0.0313109425785, F1S: 0.9050389996285, }, \
}

#ifdef IMAI_CAP_STATS_ENABLED
static const IMAI_CAP_stats IMAI_CAP_test_stats[] = IMAI_CAP_TEST_STATS;
#endif

/*
* Tensorflow Train Set
* 
* (ACC) Accuracy 94.089 %
* (F1S) F1 Score 94.117 %
* 
* Name of class                                            (unlabelled)            touch
* (TP) True Positive or Correct Positive Prediction               21473             9501
* (FN) False Negative or Incorrect Negative Prediction             1158              788
* (FP) False Positive or Incorrect Positive Prediction              788             1158
* (TN) True Negative or Correct Negative Prediction                9501            21473
* (TPR) True Positive Rate or Sensitivity, Recall               94.88 %          92.34 %
* (TNR) True Negative Rate or Specificity, Selectivity          92.34 %          94.88 %
* (PPV) Positive Predictive Value or Precision                  96.46 %          89.14 %
* (NPV) Negative Predictive Value                               89.14 %          96.46 %
* (FNR) False Negative Rate or Miss Rate                         5.12 %           7.66 %
* (FPR) False Positive Rate or Fall-Out                          7.66 %           5.12 %
* (FDR) False Discovery Rate                                     3.54 %          10.86 %
* (FOR) False Omission Rate                                     10.86 %           3.54 %
* (F1S) F1 Score                                                95.67 %          90.71 %
*/


#define IMAI_CAP_TRAIN_AVG_ACC 0.9408869987849332 // Accuracy
#define IMAI_CAP_TRAIN_AVG_F1S 0.941165444104495 // F1 Score

#define IMAI_CAP_TRAIN_STATS { \
 {name: "(unlabelled)", TP: 21473, FN: 1158, FP: 788, TN: 9501, TPR: 0.9488312491714, TNR: 0.9234133540674, PPV: 0.9646017699115, NPV: 0.8913594145792, FNR: 0.0511687508285, FPR: 0.0765866459325, FDR: 0.0353982300884, FOR: 0.1086405854207, F1S: 0.9566515192016, }, \
 {name: "touch", TP: 9501, FN: 788, FP: 1158, TN: 21473, TPR: 0.9234133540674, TNR: 0.9488312491714, PPV: 0.8913594145792, NPV: 0.9646017699115, FNR: 0.0765866459325, FPR: 0.0511687508285, FDR: 0.1086405854207, FOR: 0.0353982300884, F1S: 0.9071033034179, }, \
}

#ifdef IMAI_CAP_STATS_ENABLED
static const IMAI_CAP_stats IMAI_CAP_train_stats[] = IMAI_CAP_TRAIN_STATS;
#endif

/*
* Tensorflow Validation Set
* 
* (ACC) Accuracy 93.074 %
* (F1S) F1 Score 93.069 %
* 
* Name of class                                            (unlabelled)            touch
* (TP) True Positive or Correct Positive Prediction                6456             4456
* (FN) False Negative or Incorrect Negative Prediction              384              428
* (FP) False Positive or Incorrect Positive Prediction              428              384
* (TN) True Negative or Correct Negative Prediction                4456             6456
* (TPR) True Positive Rate or Sensitivity, Recall               94.39 %          91.24 %
* (TNR) True Negative Rate or Specificity, Selectivity          91.24 %          94.39 %
* (PPV) Positive Predictive Value or Precision                  93.78 %          92.07 %
* (NPV) Negative Predictive Value                               92.07 %          93.78 %
* (FNR) False Negative Rate or Miss Rate                         5.61 %           8.76 %
* (FPR) False Positive Rate or Fall-Out                          8.76 %           5.61 %
* (FDR) False Discovery Rate                                     6.22 %           7.93 %
* (FOR) False Omission Rate                                      7.93 %           6.22 %
* (F1S) F1 Score                                                94.08 %          91.65 %
*/


#define IMAI_CAP_VALIDATION_AVG_ACC 0.9307403616513136 // Accuracy
#define IMAI_CAP_VALIDATION_AVG_F1S 0.9306946909971708 // F1 Score

#define IMAI_CAP_VALIDATION_STATS { \
 {name: "(unlabelled)", TP: 6456, FN: 384, FP: 428, TN: 4456, TPR: 0.9438596491228, TNR: 0.9123669123669, PPV: 0.9378268448576, NPV: 0.9206611570247, FNR: 0.0561403508771, FPR: 0.0876330876330, FDR: 0.0621731551423, FOR: 0.0793388429752, F1S: 0.9408335762168, }, \
 {name: "touch", TP: 4456, FN: 428, FP: 384, TN: 6456, TPR: 0.9123669123669, TNR: 0.9438596491228, PPV: 0.9206611570247, NPV: 0.9378268448576, FNR: 0.0876330876330, FPR: 0.0561403508771, FDR: 0.0793388429752, FOR: 0.0621731551423, F1S: 0.9164952694364, }, \
}

#ifdef IMAI_CAP_STATS_ENABLED
static const IMAI_CAP_stats IMAI_CAP_validation_stats[] = IMAI_CAP_VALIDATION_STATS;
#endif

#define IMAI_CAP_API_QUEUE

// All symbols in order
#define IMAI_CAP_SYMBOL_MAP {"unlabelled", "touch"}

// Model GUID (16 bytes)
#define IMAI_CAP_MODEL_ID {0xac, 0x3f, 0x29, 0xfe, 0xf8, 0xc0, 0x8c, 0x4c, 0x8f, 0xfa, 0xf6, 0xf8, 0xc3, 0x20, 0xf3, 0x66}

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
