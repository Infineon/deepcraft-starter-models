/*
* DEEPCRAFT Studio 5.4.2875.65534+8fc265c1e63e5f306a3b283716871dff38ff3a6d
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 05/07/2025 12:17:43 UTC. Any changes will be lost.
* 
* Model ID  816b0d47-62df-42c9-9cbb-fbf5f02a6f4d
* 
* Memory    Size                      Efficiency
* Buffers   48000 bytes (RAM)         80 %
* State     2608 bytes (RAM)          100 %
* Readonly  75212 bytes (Flash)       100 %
* 
* Backend              tensorflow
* Keras Version        2.15.0
* Backend Model Type   Sequential
* Backend Model Name   conv2d-medium-balanced-1
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
* Reshape                        [100,6,1]       float      dequeue
*    shape = [100,6,1]
*    trainable = True
* Convolution 2D                 [50,3,16]       float      dequeue
*    filters = 16
*    kernel_size = [3,3]
*    strides = [2,2]
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,3,1,16]
* Batch Normalization            [50,3,16]       float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 3
*    gamma = float[16]
*    beta = float[16]
*    mean = float[16]
*    variance = float[16]
* Activation                     [50,3,16]       float      dequeue
*    activation = relu
*    trainable = True
* Convolution 2D                 [50,3,16]       float      dequeue
*    filters = 16
*    kernel_size = [3,3]
*    strides = [1,1]
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,3,16,16]
* Convolution 2D                 [50,3,16]       float      dequeue
*    filters = 16
*    kernel_size = [3,3]
*    strides = [1,1]
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,3,16,16]
* Batch Normalization            [50,3,16]       float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 3
*    gamma = float[16]
*    beta = float[16]
*    mean = float[16]
*    variance = float[16]
* Activation                     [50,3,16]       float      dequeue
*    activation = relu
*    trainable = True
* Convolution 2D                 [50,3,32]       float      dequeue
*    filters = 32
*    kernel_size = [3,3]
*    strides = [1,1]
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,3,16,32]
* Convolution 2D                 [50,3,32]       float      dequeue
*    filters = 32
*    kernel_size = [3,3]
*    strides = [1,1]
*    padding = same
*    activation = linear
*    use_bias = False
*    trainable = True
*    weight = float[3,3,32,32]
* Batch Normalization            [50,3,32]       float      dequeue
*    epsilon = 0.001
*    trainable = True
*    scale = True
*    center = True
*    axis = 3
*    gamma = float[32]
*    beta = float[32]
*    mean = float[32]
*    variance = float[32]
* Activation                     [50,3,32]       float      dequeue
*    activation = relu
*    trainable = True
* Global average pooling 2D      [32]            float      dequeue
* Dense                          [3]             float      dequeue
*    units = 3
*    use_bias = True
*    activation = linear
*    trainable = True
*    weight = float[32,3]
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
* (ACC) Accuracy 89.279 %
* (F1S) F1 Score 89.385 %
* 
* Name of class                                            (unlabelled)           circle          shaking
* (TP) True Positive or Correct Positive Prediction                1642              820              561
* (FN) False Negative or Incorrect Negative Prediction              325               27               11
* (FP) False Positive or Incorrect Positive Prediction               26              183              154
* (TN) True Negative or Correct Negative Prediction                1393             2356             2660
* (TPR) True Positive Rate or Sensitivity, Recall               83.48 %          96.81 %          98.08 %
* (TNR) True Negative Rate or Specificity, Selectivity          98.17 %          92.79 %          94.53 %
* (PPV) Positive Predictive Value or Precision                  98.44 %          81.75 %          78.46 %
* (NPV) Negative Predictive Value                               81.08 %          98.87 %          99.59 %
* (FNR) False Negative Rate or Miss Rate                        16.52 %           3.19 %           1.92 %
* (FPR) False Positive Rate or Fall-Out                          1.83 %           7.21 %           5.47 %
* (FDR) False Discovery Rate                                     1.56 %          18.25 %          21.54 %
* (FOR) False Omission Rate                                     18.92 %           1.13 %           0.41 %
* (F1S) F1 Score                                                90.34 %          88.65 %          87.18 %
*/


#define IMAI_TEST_AVG_ACC 0.892793857058476 // Accuracy
#define IMAI_TEST_AVG_F1S 0.8938525752385881 // F1 Score

#define IMAI_TEST_STATS { \
 {name: "(unlabelled)", TP: 1642, FN: 325, FP: 26, TN: 1393, TPR: 0.8347737671581, TNR: 0.9816772374911, PPV: 0.9844124700239, NPV: 0.8108265424912, FNR: 0.1652262328418, FPR: 0.0183227625088, FDR: 0.0155875299760, FOR: 0.1891734575087, F1S: 0.9034387895460, }, \
 {name: "circle", TP: 820, FN: 27, FP: 183, TN: 2356, TPR: 0.9681227863046, TNR: 0.9279243796770, PPV: 0.8175473579262, NPV: 0.9886697440201, FNR: 0.0318772136953, FPR: 0.0720756203229, FDR: 0.1824526420737, FOR: 0.0113302559798, F1S: 0.8864864864864, }, \
 {name: "shaking", TP: 561, FN: 11, FP: 154, TN: 2660, TPR: 0.9807692307692, TNR: 0.9452736318407, PPV: 0.7846153846153, NPV: 0.9958816922500, FNR: 0.0192307692307, FPR: 0.0547263681592, FDR: 0.2153846153846, FOR: 0.0041183077499, F1S: 0.8717948717948, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_test_stats[] = IMAI_TEST_STATS;
#endif

/*
* Tensorflow Train Set
* 
* (ACC) Accuracy 95.832 %
* (F1S) F1 Score 95.829 %
* 
* Name of class                                            (unlabelled)           circle          shaking
* (TP) True Positive or Correct Positive Prediction                3750             3156             1947
* (FN) False Negative or Incorrect Negative Prediction              281               64               40
* (FP) False Positive or Incorrect Positive Prediction               71              158              156
* (TN) True Negative or Correct Negative Prediction                5136             5860             7095
* (TPR) True Positive Rate or Sensitivity, Recall               93.03 %          98.01 %          97.99 %
* (TNR) True Negative Rate or Specificity, Selectivity          98.64 %          97.37 %          97.85 %
* (PPV) Positive Predictive Value or Precision                  98.14 %          95.23 %          92.58 %
* (NPV) Negative Predictive Value                               94.81 %          98.92 %          99.44 %
* (FNR) False Negative Rate or Miss Rate                         6.97 %           1.99 %           2.01 %
* (FPR) False Positive Rate or Fall-Out                          1.36 %           2.63 %           2.15 %
* (FDR) False Discovery Rate                                     1.86 %           4.77 %           7.42 %
* (FOR) False Omission Rate                                      5.19 %           1.08 %           0.56 %
* (F1S) F1 Score                                                95.52 %          96.60 %          95.21 %
*/


#define IMAI_TRAIN_AVG_ACC 0.9583243126217796 // Accuracy
#define IMAI_TRAIN_AVG_F1S 0.9582885103890261 // F1 Score

#define IMAI_TRAIN_STATS { \
 {name: "(unlabelled)", TP: 3750, FN: 281, FP: 71, TN: 5136, TPR: 0.9302902505581, TNR: 0.9863645093143, PPV: 0.9814184768385, NPV: 0.9481262691526, FNR: 0.0697097494418, FPR: 0.0136354906856, FDR: 0.0185815231614, FOR: 0.0518737308473, F1S: 0.9551706571574, }, \
 {name: "circle", TP: 3156, FN: 64, FP: 158, TN: 5860, TPR: 0.9801242236024, TNR: 0.9737454303755, PPV: 0.9523234761617, NPV: 0.9891964888588, FNR: 0.0198757763975, FPR: 0.0262545696244, FDR: 0.0476765238382, FOR: 0.0108035111411, F1S: 0.9660238751147, }, \
 {name: "shaking", TP: 1947, FN: 40, FP: 156, TN: 7095, TPR: 0.9798691494715, TNR: 0.9784857261067, PPV: 0.9258202567760, NPV: 0.9943938332165, FNR: 0.0201308505284, FPR: 0.0215142738932, FDR: 0.0741797432239, FOR: 0.0056061667834, F1S: 0.9520782396088, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_train_stats[] = IMAI_TRAIN_STATS;
#endif

/*
* Tensorflow Validation Set
* 
* (ACC) Accuracy 84.497 %
* (F1S) F1 Score 84.696 %
* 
* Name of class                                            (unlabelled)           circle          shaking
* (TP) True Positive or Correct Positive Prediction                1464              763              629
* (FN) False Negative or Incorrect Negative Prediction              382              123               19
* (FP) False Positive or Incorrect Positive Prediction               65              217              242
* (TN) True Negative or Correct Negative Prediction                1469             2277             2490
* (TPR) True Positive Rate or Sensitivity, Recall               79.31 %          86.12 %          97.07 %
* (TNR) True Negative Rate or Specificity, Selectivity          95.76 %          91.30 %          91.14 %
* (PPV) Positive Predictive Value or Precision                  95.75 %          77.86 %          72.22 %
* (NPV) Negative Predictive Value                               79.36 %          94.87 %          99.24 %
* (FNR) False Negative Rate or Miss Rate                        20.69 %          13.88 %           2.93 %
* (FPR) False Positive Rate or Fall-Out                          4.24 %           8.70 %           8.86 %
* (FDR) False Discovery Rate                                     4.25 %          22.14 %          27.78 %
* (FOR) False Omission Rate                                     20.64 %           5.12 %           0.76 %
* (F1S) F1 Score                                                86.76 %          81.78 %          82.82 %
*/


#define IMAI_VALIDATION_AVG_ACC 0.8449704142011835 // Accuracy
#define IMAI_VALIDATION_AVG_F1S 0.8469614367392944 // F1 Score

#define IMAI_VALIDATION_STATS { \
 {name: "(unlabelled)", TP: 1464, FN: 382, FP: 65, TN: 1469, TPR: 0.7930660888407, TNR: 0.9576271186440, PPV: 0.9574885546108, NPV: 0.7936250675310, FNR: 0.2069339111592, FPR: 0.0423728813559, FDR: 0.0425114453891, FOR: 0.2063749324689, F1S: 0.8675555555555, }, \
 {name: "circle", TP: 763, FN: 123, FP: 217, TN: 2277, TPR: 0.8611738148984, TNR: 0.9129911788291, PPV: 0.7785714285714, NPV: 0.94875, FNR: 0.1388261851015, FPR: 0.0870088211708, FDR: 0.2214285714285, FOR: 0.05125, F1S: 0.8177920685959, }, \
 {name: "shaking", TP: 629, FN: 19, FP: 242, TN: 2490, TPR: 0.9706790123456, TNR: 0.9114202049780, PPV: 0.7221584385763, NPV: 0.9924272618573, FNR: 0.0293209876543, FPR: 0.0885797950219, FDR: 0.2778415614236, FOR: 0.0075727381426, F1S: 0.8281764318630, }, \
}

#ifdef IMAI_STATS_ENABLED
static const IMAI_stats IMAI_validation_stats[] = IMAI_VALIDATION_STATS;
#endif

#define IMAI_API_QUEUE

// All symbols in order
#define IMAI_SYMBOL_MAP {"unlabelled", "circle", "shaking"}

// Model GUID (16 bytes)
#define IMAI_MODEL_ID {0x47, 0x0d, 0x6b, 0x81, 0xdf, 0x62, 0xc9, 0x42, 0x9c, 0xbb, 0xfb, 0xf5, 0xf0, 0x2a, 0x6f, 0x4d}

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

#define IMAI_KEY_MAX (35)



// Return codes
#define IMAI_RET_SUCCESS 0
#define IMAI_RET_NODATA -1
#define IMAI_RET_NOMEM -2

// Exported methods
int IMAI_dequeue(float *restrict data_out);
int IMAI_enqueue(const float *restrict data_in);
void IMAI_init(void);

#endif /* _IMAI_MODEL_H_ */
