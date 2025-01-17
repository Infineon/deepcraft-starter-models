/*
* Imagimob Studio 5.1.1920+23251253412258875242be5d4844a74c53d9fafa
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 10/10/2024 08:17:23 UTC. Any changes will be lost.
* 
* Model ID  4a6039f9-31ee-4e23-8df7-6fca5b38c3c6
* 
* Memory    Size                      Efficiency
* Buffers   14000 bytes (RAM)         91 %
* State     1408 bytes (RAM)          100 %
* Readonly  26248 bytes (Flash)       100 %
* 
* Backend              tensorflow
* Keras Version        2.15.0
* Backend Model Type   Sequential
* Backend Model Name   conv1d-small-balanced-3
* 
* Class Index | Symbol Label
* 0           | unlabelled
* 1           | touch
* 
* Layer                          Shape           Type       Function
* Sliding Window (data points)   [100,3]         float      dequeue
*    window_shape = [100,3]
*    stride = 60
*    buffer_multiplier = 2
* Input Layer                    [100,3]         float      dequeue
*    shape = [100,3]
* Convolution 1D                 [50,32]         float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 2
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,3,32]
* Batch Normalization            [50,32]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[32]
*    beta = float[32]
*    mean = float[32]
*    variance = float[32]
* Activation                     [50,32]         float      dequeue
*    activation = relu
*    trainable = True
* Convolution 1D                 [50,32]         float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,32,32]
* Convolution 1D                 [50,32]         float      dequeue
*    filters = 32
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,32,32]
* Batch Normalization            [50,32]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[32]
*    beta = float[32]
*    mean = float[32]
*    variance = float[32]
* Activation                     [50,32]         float      dequeue
*    activation = relu
*    trainable = True
* Max pooling 1D                 [25,32]         float      dequeue
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
* (ACC) Accuracy 86.611 %
* (F1S) F1 Score 86.501 %
* 
* Name of class                                            (unlabelled)            touch
* (TP) True Positive or Correct Positive Prediction                4051             1687
* (FN) False Negative or Incorrect Negative Prediction              377              510
* (FP) False Positive or Incorrect Positive Prediction              510              377
* (TN) True Negative or Correct Negative Prediction                1687             4051
* (TPR) True Positive Rate or Sensitivity, Recall               91.49 %          76.79 %
* (TNR) True Negative Rate or Specificity, Selectivity          76.79 %          91.49 %
* (PPV) Positive Predictive Value or Precision                  88.82 %          81.73 %
* (NPV) Negative Predictive Value                               81.73 %          88.82 %
* (FNR) False Negative Rate or Miss Rate                         8.51 %          23.21 %
* (FPR) False Positive Rate or Fall-Out                         23.21 %           8.51 %
* (FDR) False Discovery Rate                                    11.18 %          18.27 %
* (FOR) False Omission Rate                                     18.27 %          11.18 %
* (F1S) F1 Score                                                90.13 %          79.18 %
*/


#define IMAI_CAP_TEST_AVG_ACC 0.8661132075471698 // Accuracy
#define IMAI_CAP_TEST_AVG_F1S 0.8650141664419435 // F1 Score

#define IMAI_CAP_TEST_STATS { \
 {name: "(unlabelled)", TP: 4051, FN: 377, FP: 510, TN: 1687, TPR: 0.9148599819331, TNR: 0.7678652708238, PPV: 0.8881824161368, NPV: 0.8173449612403, FNR: 0.0851400180668, FPR: 0.2321347291761, FDR: 0.1118175838631, FOR: 0.1826550387596, F1S: 0.9013238402491, }, \
 {name: "touch", TP: 1687, FN: 510, FP: 377, TN: 4051, TPR: 0.7678652708238, TNR: 0.9148599819331, PPV: 0.8173449612403, NPV: 0.8881824161368, FNR: 0.2321347291761, FPR: 0.0851400180668, FDR: 0.1826550387596, FOR: 0.1118175838631, F1S: 0.7918329030743, }, \
}

#ifdef IMAI_CAP_STATS_ENABLED
static const IMAI_CAP_stats IMAI_CAP_test_stats[] = IMAI_CAP_TEST_STATS;
#endif

/*
* Tensorflow Train Set
* 
* (ACC) Accuracy 84.246 %
* (F1S) F1 Score 84.152 %
* 
* Name of class                                            (unlabelled)            touch
* (TP) True Positive or Correct Positive Prediction                9137             4612
* (FN) False Negative or Incorrect Negative Prediction             1123             1448
* (FP) False Positive or Incorrect Positive Prediction             1448             1123
* (TN) True Negative or Correct Negative Prediction                4612             9137
* (TPR) True Positive Rate or Sensitivity, Recall               89.05 %          76.11 %
* (TNR) True Negative Rate or Specificity, Selectivity          76.11 %          89.05 %
* (PPV) Positive Predictive Value or Precision                  86.32 %          80.42 %
* (NPV) Negative Predictive Value                               80.42 %          86.32 %
* (FNR) False Negative Rate or Miss Rate                        10.95 %          23.89 %
* (FPR) False Positive Rate or Fall-Out                         23.89 %          10.95 %
* (FDR) False Discovery Rate                                    13.68 %          19.58 %
* (FOR) False Omission Rate                                     19.58 %          13.68 %
* (F1S) F1 Score                                                87.67 %          78.20 %
*/


#define IMAI_CAP_TRAIN_AVG_ACC 0.8424632352941176 // Accuracy
#define IMAI_CAP_TRAIN_AVG_F1S 0.8415209465094878 // F1 Score

#define IMAI_CAP_TRAIN_STATS { \
 {name: "(unlabelled)", TP: 9137, FN: 1123, FP: 1448, TN: 4612, TPR: 0.8905458089668, TNR: 0.7610561056105, PPV: 0.8632026452527, NPV: 0.8041848299912, FNR: 0.1094541910331, FPR: 0.2389438943894, FDR: 0.1367973547472, FOR: 0.1958151700087, F1S: 0.8766610698009, }, \
 {name: "touch", TP: 4612, FN: 1448, FP: 1123, TN: 9137, TPR: 0.7610561056105, TNR: 0.8905458089668, PPV: 0.8041848299912, NPV: 0.8632026452527, FNR: 0.2389438943894, FPR: 0.1094541910331, FDR: 0.1958151700087, FOR: 0.1367973547472, F1S: 0.7820262823230, }, \
}

#ifdef IMAI_CAP_STATS_ENABLED
static const IMAI_CAP_stats IMAI_CAP_train_stats[] = IMAI_CAP_TRAIN_STATS;
#endif

/*
* Tensorflow Validation Set
* 
* (ACC) Accuracy 85.680 %
* (F1S) F1 Score 85.632 %
* 
* Name of class                                            (unlabelled)            touch
* (TP) True Positive or Correct Positive Prediction                2772             2218
* (FN) False Negative or Incorrect Negative Prediction              316              518
* (FP) False Positive or Incorrect Positive Prediction              518              316
* (TN) True Negative or Correct Negative Prediction                2218             2772
* (TPR) True Positive Rate or Sensitivity, Recall               89.77 %          81.07 %
* (TNR) True Negative Rate or Specificity, Selectivity          81.07 %          89.77 %
* (PPV) Positive Predictive Value or Precision                  84.26 %          87.53 %
* (NPV) Negative Predictive Value                               87.53 %          84.26 %
* (FNR) False Negative Rate or Miss Rate                        10.23 %          18.93 %
* (FPR) False Positive Rate or Fall-Out                         18.93 %          10.23 %
* (FDR) False Discovery Rate                                    15.74 %          12.47 %
* (FOR) False Omission Rate                                     12.47 %          15.74 %
* (F1S) F1 Score                                                86.92 %          84.17 %
*/


#define IMAI_CAP_VALIDATION_AVG_ACC 0.8567994505494505 // Accuracy
#define IMAI_CAP_VALIDATION_AVG_F1S 0.8563226786084296 // F1 Score

#define IMAI_CAP_VALIDATION_STATS { \
 {name: "(unlabelled)", TP: 2772, FN: 316, FP: 518, TN: 2218, TPR: 0.8976683937823, TNR: 0.8106725146198, PPV: 0.8425531914893, NPV: 0.8752959747434, FNR: 0.1023316062176, FPR: 0.1893274853801, FDR: 0.1574468085106, FOR: 0.1247040252565, F1S: 0.8692380056444, }, \
 {name: "touch", TP: 2218, FN: 518, FP: 316, TN: 2772, TPR: 0.8106725146198, TNR: 0.8976683937823, PPV: 0.8752959747434, NPV: 0.8425531914893, FNR: 0.1893274853801, FPR: 0.1023316062176, FDR: 0.1247040252565, FOR: 0.1574468085106, F1S: 0.8417457305502, }, \
}

#ifdef IMAI_CAP_STATS_ENABLED
static const IMAI_CAP_stats IMAI_CAP_validation_stats[] = IMAI_CAP_VALIDATION_STATS;
#endif

#define IMAI_CAP_API_QUEUE

// All symbols in order
#define IMAI_CAP_SYMBOL_MAP {"unlabelled", "touch"}

// Model GUID (16 bytes)
#define IMAI_CAP_MODEL_ID {0xf9, 0x39, 0x60, 0x4a, 0xee, 0x31, 0x23, 0x4e, 0x8d, 0xf7, 0x6f, 0xca, 0x5b, 0x38, 0xc3, 0xc6}

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
