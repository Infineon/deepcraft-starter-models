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


#define IMAI_CAP_TEST_AVG_ACC 0.9654583412412222 // Accuracy
#define IMAI_CAP_TEST_AVG_F1S 0.9648070323488258 // F1 Score

#define IMAI_CAP_TEST_STATS { \
 {name: "(unlabelled)", TP: 3766, FN: 7, FP: 175, TN: 1321, TPR: 0.9981447124304, TNR: 0.8830213903743, PPV: 0.9555950266429, NPV: 0.9947289156626, FNR: 0.0018552875695, FPR: 0.1169786096256, FDR: 0.0444049733570, FOR: 0.0052710843373, F1S: 0.9764065335753, }, \
 {name: "touch", TP: 1321, FN: 175, FP: 7, TN: 3766, TPR: 0.8830213903743, TNR: 0.9981447124304, PPV: 0.9947289156626, NPV: 0.9555950266429, FNR: 0.1169786096256, FPR: 0.0018552875695, FDR: 0.0052710843373, FOR: 0.0444049733570, F1S: 0.9355524079320, }, \
}

#ifdef IMAI_CAP_STATS_ENABLED
static const IMAI_CAP_stats IMAI_CAP_test_stats[] = IMAI_CAP_TEST_STATS;
#endif

/*
* Tensorflow Train Set
* 
* (ACC) Accuracy 97.193 %
* (F1S) F1 Score 97.151 %
* 
* Name of class                                            (unlabelled)            touch
* (TP) True Positive or Correct Positive Prediction               15404             5127
* (FN) False Negative or Incorrect Negative Prediction               50              543
* (FP) False Positive or Incorrect Positive Prediction              543               50
* (TN) True Negative or Correct Negative Prediction                5127            15404
* (TPR) True Positive Rate or Sensitivity, Recall               99.68 %          90.42 %
* (TNR) True Negative Rate or Specificity, Selectivity          90.42 %          99.68 %
* (PPV) Positive Predictive Value or Precision                  96.59 %          99.03 %
* (NPV) Negative Predictive Value                               99.03 %          96.59 %
* (FNR) False Negative Rate or Miss Rate                         0.32 %           9.58 %
* (FPR) False Positive Rate or Fall-Out                          9.58 %           0.32 %
* (FDR) False Discovery Rate                                     3.41 %           0.97 %
* (FOR) False Omission Rate                                      0.97 %           3.41 %
* (F1S) F1 Score                                                98.11 %          94.53 %
*/


#define IMAI_CAP_TRAIN_AVG_ACC 0.9719276652149215 // Accuracy
#define IMAI_CAP_TRAIN_AVG_F1S 0.9715100861751294 // F1 Score

#define IMAI_CAP_TRAIN_STATS { \
 {name: "(unlabelled)", TP: 15404, FN: 50, FP: 543, TN: 5127, TPR: 0.9967645916914, TNR: 0.9042328042328, PPV: 0.9659497084091, NPV: 0.9903418968514, FNR: 0.0032354083085, FPR: 0.0957671957671, FDR: 0.0340502915908, FOR: 0.0096581031485, F1S: 0.9811152511066, }, \
 {name: "touch", TP: 5127, FN: 543, FP: 50, TN: 15404, TPR: 0.9042328042328, TNR: 0.9967645916914, PPV: 0.9903418968514, NPV: 0.9659497084091, FNR: 0.0957671957671, FPR: 0.0032354083085, FDR: 0.0096581031485, FOR: 0.0340502915908, F1S: 0.9453305061307, }, \
}

#ifdef IMAI_CAP_STATS_ENABLED
static const IMAI_CAP_stats IMAI_CAP_train_stats[] = IMAI_CAP_TRAIN_STATS;
#endif

/*
* Tensorflow Validation Set
* 
* (ACC) Accuracy 97.659 %
* (F1S) F1 Score 97.643 %
* 
* Name of class                                            (unlabelled)            touch
* (TP) True Positive or Correct Positive Prediction                3508             1499
* (FN) False Negative or Incorrect Negative Prediction               20              100
* (FP) False Positive or Incorrect Positive Prediction              100               20
* (TN) True Negative or Correct Negative Prediction                1499             3508
* (TPR) True Positive Rate or Sensitivity, Recall               99.43 %          93.75 %
* (TNR) True Negative Rate or Specificity, Selectivity          93.75 %          99.43 %
* (PPV) Positive Predictive Value or Precision                  97.23 %          98.68 %
* (NPV) Negative Predictive Value                               98.68 %          97.23 %
* (FNR) False Negative Rate or Miss Rate                         0.57 %           6.25 %
* (FPR) False Positive Rate or Fall-Out                          6.25 %           0.57 %
* (FDR) False Discovery Rate                                     2.77 %           1.32 %
* (FOR) False Omission Rate                                      1.32 %           2.77 %
* (F1S) F1 Score                                                98.32 %          96.15 %
*/


#define IMAI_CAP_VALIDATION_AVG_ACC 0.9765944997074313 // Accuracy
#define IMAI_CAP_VALIDATION_AVG_F1S 0.9764254334651012 // F1 Score

#define IMAI_CAP_VALIDATION_STATS { \
 {name: "(unlabelled)", TP: 3508, FN: 20, FP: 100, TN: 1499, TPR: 0.9943310657596, TNR: 0.9374609130706, PPV: 0.9722838137472, NPV: 0.9868334430546, FNR: 0.0056689342403, FPR: 0.0625390869293, FDR: 0.0277161862527, FOR: 0.0131665569453, F1S: 0.9831838565022, }, \
 {name: "touch", TP: 1499, FN: 100, FP: 20, TN: 3508, TPR: 0.9374609130706, TNR: 0.9943310657596, PPV: 0.9868334430546, NPV: 0.9722838137472, FNR: 0.0625390869293, FPR: 0.0056689342403, FDR: 0.0131665569453, FOR: 0.0277161862527, F1S: 0.9615137908915, }, \
}

#ifdef IMAI_CAP_STATS_ENABLED
static const IMAI_CAP_stats IMAI_CAP_validation_stats[] = IMAI_CAP_VALIDATION_STATS;
#endif

#define IMAI_CAP_API_QUEUE

// All symbols in order
#define IMAI_CAP_SYMBOL_MAP {"unlabelled", "touch"}

// Model GUID (16 bytes)
#define IMAI_CAP_MODEL_ID {0x27, 0x9a, 0xd3, 0x63, 0x93, 0x6a, 0x34, 0x46, 0xa6, 0x48, 0xb9, 0xcf, 0x55, 0xac, 0x7c, 0x6e}

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

#define IMAI_CAP_KEY_MAX (19)



// Return codes
#define IMAI_CAP_RET_SUCCESS 0
#define IMAI_CAP_RET_NODATA -1
#define IMAI_CAP_RET_NOMEM -2

// Exported methods
int IMAI_CAP_dequeue(float *restrict data_out);
int IMAI_CAP_enqueue(const float *restrict data_in);
void IMAI_CAP_init(void);

#endif /* _IMAI_CAP_CAP_MODEL_H_ */
