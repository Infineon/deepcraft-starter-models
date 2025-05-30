/*
* DEEPCRAFT Studio 5.4.2875.65534+8fc265c1e63e5f306a3b283716871dff38ff3a6d
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 05/07/2025 12:01:01 UTC. Any changes will be lost.
* 
* Model ID  aaf08b58-54e2-4c6e-b096-33d0f69a3aed
* 
* Memory    Size                      Efficiency
* Buffers   16000 bytes (RAM)         80 %
* State     2608 bytes (RAM)          100 %
* Readonly  94540 bytes (Flash)       100 %
* 
* Backend              tensorflow
* Keras Version        2.15.0
* Backend Model Type   Sequential
* Backend Model Name   conv1d-medium-balanced-3
* 
* Class Index | Symbol Label
* 0           | unlabelled
* 1           | circle
* 2           | shaking
* 
* Layer                          Shape           Type       Function
* Sliding Window (data points)   [100,6]         float      dequeue
*    window_shape = [100,6]
*    stride = 60
*    buffer_multiplier = 1
* Contextual Window (Sliding Window) [100,6]         float      dequeue
*    contextual_length_sec = 2
*    prediction_freq = 5
* Input Layer                    [100,6]         float      dequeue
*    shape = [100,6]
* Convolution 1D                 [50,16]         float      dequeue
*    filters = 16
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 2
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,6,16]
* Batch Normalization            [50,16]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[16]
*    beta = float[16]
*    mean = float[16]
*    variance = float[16]
* Activation                     [50,16]         float      dequeue
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
*    weight = float[3,16,32]
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
* Convolution 1D                 [25,64]         float      dequeue
*    filters = 64
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,32,64]
* Convolution 1D                 [25,64]         float      dequeue
*    filters = 64
*    kernel_size = 3
*    dilation_rate = 1
*    strides = 1
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,64,64]
* Batch Normalization            [25,64]         float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 2
*    gamma = float[64]
*    beta = float[64]
*    mean = float[64]
*    variance = float[64]
* Activation                     [25,64]         float      dequeue
*    activation = relu
*    trainable = True
* Max pooling 1D                 [12,64]         float      dequeue
*    pool_size = 2
*    strides = 2
*    padding = valid
*    trainable = True
* Global average pooling 1D      [64]            float      dequeue
*    trainable = True
* Dense                          [3]             float      dequeue
*    units = 3
*    use_bias = True
*    activation = linear
*    trainable = True
*    weight = float[64,3]
*    bias = float[3]
* Activation                     [3]             float      dequeue
*    activation = softmax
*    trainable = True
* 
* Exported functions:
* 
* int IMAI_dequeue(float *restrict data_out)
*    Description: Dequeue features. RET_SUCCESS (0) on success, RET_NODATA (-1) if no data is available, RET_NOMEM (-2) on internal memory error
*    Parameter data_out is Output of size float[3].
* 
* int IMAI_enqueue(const float *restrict data_in)
*    Description: Enqueue features. Returns SUCCESS (0) on success, else RET_NOMEM (-2) when low on memory.
*    Parameter data_in is Input of size float[2,3].
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

#ifndef _IMAI_MODEL_H_
#define _IMAI_MODEL_H_
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
} IMAI_stats;

/*
* Tensorflow Test Set
* 
* (ACC) Accuracy 87.980 %
* (F1S) F1 Score 88.072 %
* 
* Name of class                                            (unlabelled)           circle          shaking
* (TP) True Positive or Correct Positive Prediction                1621              831              527
* (FN) False Negative or Incorrect Negative Prediction              346               16               45
* (FP) False Positive or Incorrect Positive Prediction               53              222              132
* (TN) True Negative or Correct Negative Prediction                1366             2317             2682
* (TPR) True Positive Rate or Sensitivity, Recall               82.41 %          98.11 %          92.13 %
* (TNR) True Negative Rate or Specificity, Selectivity          96.26 %          91.26 %          95.31 %
* (PPV) Positive Predictive Value or Precision                  96.83 %          78.92 %          79.97 %
* (NPV) Negative Predictive Value                               79.79 %          99.31 %          98.35 %
* (FNR) False Negative Rate or Miss Rate                        17.59 %           1.89 %           7.87 %
* (FPR) False Positive Rate or Fall-Out                          3.74 %           8.74 %           4.69 %
* (FDR) False Discovery Rate                                     3.17 %          21.08 %          20.03 %
* (FOR) False Omission Rate                                     20.21 %           0.69 %           1.65 %
* (F1S) F1 Score                                                89.04 %          87.47 %          85.62 %
*/


#define IMAI_TEST_AVG_ACC 0.8797991730655641 // Accuracy
#define IMAI_TEST_AVG_F1S 0.8807154556770832 // F1 Score

#define IMAI_TEST_STATS { \
 {name: "(unlabelled)", TP: 1621, FN: 346, FP: 53, TN: 1366, TPR: 0.8240976105744, TNR: 0.9626497533474, PPV: 0.9683393070489, NPV: 0.7978971962616, FNR: 0.1759023894255, FPR: 0.0373502466525, FDR: 0.0316606929510, FOR: 0.2021028037383, F1S: 0.8904147212304, }, \
 {name: "circle", TP: 831, FN: 16, FP: 222, TN: 2317, TPR: 0.9811097992916, TNR: 0.9125640015754, PPV: 0.7891737891737, NPV: 0.9931418774110, FNR: 0.0188902007083, FPR: 0.0874359984245, FDR: 0.2108262108262, FOR: 0.0068581225889, F1S: 0.8747368421052, }, \
 {name: "shaking", TP: 527, FN: 45, FP: 132, TN: 2682, TPR: 0.9213286713286, TNR: 0.9530916844349, PPV: 0.7996965098634, NPV: 0.9834983498349, FNR: 0.0786713286713, FPR: 0.0469083155650, FDR: 0.2003034901365, FOR: 0.0165016501650, F1S: 0.8562144597887, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_test_stats[] = IMAI_TEST_STATS;
#endif

/*
* Tensorflow Train Set
* 
* (ACC) Accuracy 93.364 %
* (F1S) F1 Score 93.344 %
* 
* Name of class                                            (unlabelled)           circle          shaking
* (TP) True Positive or Correct Positive Prediction                3651             3184             1790
* (FN) False Negative or Incorrect Negative Prediction              380               36              197
* (FP) False Positive or Incorrect Positive Prediction              120              332              161
* (TN) True Negative or Correct Negative Prediction                5087             5686             7090
* (TPR) True Positive Rate or Sensitivity, Recall               90.57 %          98.88 %          90.09 %
* (TNR) True Negative Rate or Specificity, Selectivity          97.70 %          94.48 %          97.78 %
* (PPV) Positive Predictive Value or Precision                  96.82 %          90.56 %          91.75 %
* (NPV) Negative Predictive Value                               93.05 %          99.37 %          97.30 %
* (FNR) False Negative Rate or Miss Rate                         9.43 %           1.12 %           9.91 %
* (FPR) False Positive Rate or Fall-Out                          2.30 %           5.52 %           2.22 %
* (FDR) False Discovery Rate                                     3.18 %           9.44 %           8.25 %
* (FOR) False Omission Rate                                      6.95 %           0.63 %           2.70 %
* (F1S) F1 Score                                                93.59 %          94.54 %          90.91 %
*/


#define IMAI_TRAIN_AVG_ACC 0.9336436458107815 // Accuracy
#define IMAI_TRAIN_AVG_F1S 0.9334399166403476 // F1 Score

#define IMAI_TRAIN_STATS { \
 {name: "(unlabelled)", TP: 3651, FN: 380, FP: 120, TN: 5087, TPR: 0.9057305879434, TNR: 0.9769541002496, PPV: 0.9681782020684, NPV: 0.9304920431680, FNR: 0.0942694120565, FPR: 0.0230458997503, FDR: 0.0318217979315, FOR: 0.0695079568319, F1S: 0.9359138682389, }, \
 {name: "circle", TP: 3184, FN: 36, FP: 332, TN: 5686, TPR: 0.9888198757763, TNR: 0.9448321701561, PPV: 0.9055745164960, NPV: 0.9937084935337, FNR: 0.0111801242236, FPR: 0.0551678298438, FDR: 0.0944254835039, FOR: 0.0062915064662, F1S: 0.9453681710213, }, \
 {name: "shaking", TP: 1790, FN: 197, FP: 161, TN: 7090, TPR: 0.9008555611474, TNR: 0.9777961660460, PPV: 0.9174782162993, NPV: 0.9729655550981, FNR: 0.0991444388525, FPR: 0.0222038339539, FDR: 0.0825217837006, FOR: 0.0270344449018, F1S: 0.9090909090909, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_train_stats[] = IMAI_TRAIN_STATS;
#endif

/*
* Tensorflow Validation Set
* 
* (ACC) Accuracy 83.343 %
* (F1S) F1 Score 83.427 %
* 
* Name of class                                            (unlabelled)           circle          shaking
* (TP) True Positive or Correct Positive Prediction                1411              845              561
* (FN) False Negative or Incorrect Negative Prediction              435               41               87
* (FP) False Positive or Incorrect Positive Prediction               91              306              166
* (TN) True Negative or Correct Negative Prediction                1443             2188             2566
* (TPR) True Positive Rate or Sensitivity, Recall               76.44 %          95.37 %          86.57 %
* (TNR) True Negative Rate or Specificity, Selectivity          94.07 %          87.73 %          93.92 %
* (PPV) Positive Predictive Value or Precision                  93.94 %          73.41 %          77.17 %
* (NPV) Negative Predictive Value                               76.84 %          98.16 %          96.72 %
* (FNR) False Negative Rate or Miss Rate                        23.56 %           4.63 %          13.43 %
* (FPR) False Positive Rate or Fall-Out                          5.93 %          12.27 %           6.08 %
* (FDR) False Discovery Rate                                     6.06 %          26.59 %          22.83 %
* (FOR) False Omission Rate                                     23.16 %           1.84 %           3.28 %
* (F1S) F1 Score                                                84.29 %          82.97 %          81.60 %
*/


#define IMAI_VALIDATION_AVG_ACC 0.8334319526627219 // Accuracy
#define IMAI_VALIDATION_AVG_F1S 0.8342652316547178 // F1 Score

#define IMAI_VALIDATION_STATS { \
 {name: "(unlabelled)", TP: 1411, FN: 435, FP: 91, TN: 1443, TPR: 0.7643553629469, TNR: 0.9406779661016, PPV: 0.9394141145139, NPV: 0.7683706070287, FNR: 0.2356446370530, FPR: 0.0593220338983, FDR: 0.0605858854860, FOR: 0.2316293929712, F1S: 0.8428912783751, }, \
 {name: "circle", TP: 845, FN: 41, FP: 306, TN: 2188, TPR: 0.9537246049661, TNR: 0.8773055332798, PPV: 0.7341442224152, NPV: 0.9816061013907, FNR: 0.0462753950338, FPR: 0.1226944667201, FDR: 0.2658557775847, FOR: 0.0183938986092, F1S: 0.8296514482081, }, \
 {name: "shaking", TP: 561, FN: 87, FP: 166, TN: 2566, TPR: 0.8657407407407, TNR: 0.9392386530014, PPV: 0.7716643741403, NPV: 0.9672069355446, FNR: 0.1342592592592, FPR: 0.0607613469985, FDR: 0.2283356258596, FOR: 0.0327930644553, F1S: 0.816, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_validation_stats[] = IMAI_VALIDATION_STATS;
#endif

#define IMAI_API_QUEUE

// All symbols in order
#define IMAI_SYMBOL_MAP {"unlabelled", "circle", "shaking"}

// Model GUID (16 bytes)
#define IMAI_MODEL_ID {0x58, 0x8b, 0xf0, 0xaa, 0xe2, 0x54, 0x6e, 0x4c, 0xb0, 0x96, 0x33, 0xd0, 0xf6, 0x9a, 0x3a, 0xed}

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

// data_in [2,3] (24 bytes)
#define IMAI_DATA_IN_COUNT (6)
#define IMAI_DATA_IN_TYPE float
#define IMAI_DATA_IN_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_DATA_IN_SCALE (1)
#define IMAI_DATA_IN_OFFSET (0)
#define IMAI_DATA_IN_IS_QUANTIZED (0)

// data_out [3] (12 bytes)
#define IMAI_DATA_OUT_COUNT (3)
#define IMAI_DATA_OUT_TYPE float
#define IMAI_DATA_OUT_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_DATA_OUT_SCALE (1)
#define IMAI_DATA_OUT_OFFSET (0)
#define IMAI_DATA_OUT_IS_QUANTIZED (0)

#define IMAI_KEY_MAX (39)



// Return codes
#define IMAI_RET_SUCCESS 0
#define IMAI_RET_NODATA -1
#define IMAI_RET_NOMEM -2

// Exported methods
int IMAI_dequeue(float *restrict data_out);
int IMAI_enqueue(const float *restrict data_in);
void IMAI_init(void);

#endif /* _IMAI_MODEL_H_ */
