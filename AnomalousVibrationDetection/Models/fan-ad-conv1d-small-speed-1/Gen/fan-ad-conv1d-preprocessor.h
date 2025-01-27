/*
* Imagimob Studio 4.8.1397+ec7f68f457701b125b40ecb6a3e43a64ab83bbf6
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 06/14/2024 07:50:02 UTC. Any changes will be lost.
* 
* Model ID  9ad1ca69-9d30-4be6-8a30-3f5ae6392ddf
* 
* Memory    Size                      Efficiency
* State     808 bytes (RAM)           100 %
* 
* Backend              tensorflow
* Keras Version        2.15.0
* Backend Model Type   Sequential
* Backend Model Name   fan-ad-conv1d-small-speed-1
* 
* Class Index | Symbol Label
* 0           | unlabelled
* 1           | anomaly
* 
* Layer                          Shape           Type       Function
* Sliding Window (data points)   [50,3]          float      dequeue
*    window_shape = [50,3]
*    stride = 3
*    buffer_multiplier = 1
* 
* Exported functions:
* 
* int FANAD_PREP_dequeue(float *restrict data_out)
*    Description: Dequeue features. RET_SUCCESS (0) on success, RET_NODATA (-1) if no data is available, RET_NOMEM (-2) on internal memory error
*    Parameter data_out is Output of size float[50,3].
* 
* int FANAD_PREP_enqueue(const float *restrict data_in)
*    Description: Enqueue features. Returns SUCCESS (0) on success, else RET_NOMEM (-2) when low on memory.
*    Parameter data_in is Input of size float[3].
* 
* void FANAD_PREP_init(void)
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

#ifndef _FANAD_PREP_FAN_AD_CONV1D_PREPROCESSOR_H_
#define _FANAD_PREP_FAN_AD_CONV1D_PREPROCESSOR_H_
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
} FANAD_PREP_stats;

/*
* Tensorflow Test Set
* 
* (ACC) Accuracy 94.449 %
* (F1S) F1 Score 94.392 %
* 
* Name of class                                            (unlabelled)          anomaly
* (TP) True Positive or Correct Positive Prediction               10006             6447
* (FN) False Negative or Incorrect Negative Prediction               62              905
* (FP) False Positive or Incorrect Positive Prediction              905               62
* (TN) True Negative or Correct Negative Prediction                6447            10006
* (TPR) True Positive Rate or Sensitivity, Recall               99.38 %          87.69 %
* (TNR) True Negative Rate or Specificity, Selectivity          87.69 %          99.38 %
* (PPV) Positive Predictive Value or Precision                  91.71 %          99.05 %
* (NPV) Negative Predictive Value                               99.05 %          91.71 %
* (FNR) False Negative Rate or Miss Rate                         0.62 %          12.31 %
* (FPR) False Positive Rate or Fall-Out                         12.31 %           0.62 %
* (FDR) False Discovery Rate                                     8.29 %           0.95 %
* (FOR) False Omission Rate                                      0.95 %           8.29 %
* (F1S) F1 Score                                                95.39 %          93.02 %
*/


#define FANAD_PREP_TEST_AVG_ACC 0.9444890929965557 // Accuracy
#define FANAD_PREP_TEST_AVG_F1S 0.9439163569207383 // F1 Score

#define FANAD_PREP_TEST_STATS { \
 {name: "(unlabelled)", TP: 10006, FN: 62, FP: 905, TN: 6447, TPR: 0.9938418752483, TNR: 0.8769042437431, PPV: 0.9170561818348, NPV: 0.9904747273006, FNR: 0.0061581247516, FPR: 0.1230957562568, FDR: 0.0829438181651, FOR: 0.0095252726993, F1S: 0.9539062872396, }, \
 {name: "anomaly", TP: 6447, FN: 905, FP: 62, TN: 10006, TPR: 0.8769042437431, TNR: 0.9938418752483, PPV: 0.9904747273006, NPV: 0.9170561818348, FNR: 0.1230957562568, FPR: 0.0061581247516, FDR: 0.0095252726993, FOR: 0.0829438181651, F1S: 0.9302359137147, }, \
}

#ifdef FANAD_PREP_STATS_ENABLED
static const FANAD_PREP_stats FANAD_PREP_test_stats[] = FANAD_PREP_TEST_STATS;
#endif

/*
* Tensorflow Train Set
* 
* (ACC) Accuracy 96.595 %
* (F1S) F1 Score 96.588 %
* 
* Name of class                                            (unlabelled)          anomaly
* (TP) True Positive or Correct Positive Prediction               24450            20087
* (FN) False Negative or Incorrect Negative Prediction              301             1269
* (FP) False Positive or Incorrect Positive Prediction             1269              301
* (TN) True Negative or Correct Negative Prediction               20087            24450
* (TPR) True Positive Rate or Sensitivity, Recall               98.78 %          94.06 %
* (TNR) True Negative Rate or Specificity, Selectivity          94.06 %          98.78 %
* (PPV) Positive Predictive Value or Precision                  95.07 %          98.52 %
* (NPV) Negative Predictive Value                               98.52 %          95.07 %
* (FNR) False Negative Rate or Miss Rate                         1.22 %           5.94 %
* (FPR) False Positive Rate or Fall-Out                          5.94 %           1.22 %
* (FDR) False Discovery Rate                                     4.93 %           1.48 %
* (FOR) False Omission Rate                                      1.48 %           4.93 %
* (F1S) F1 Score                                                96.89 %          96.24 %
*/


#define FANAD_PREP_TRAIN_AVG_ACC 0.9659487713362396 // Accuracy
#define FANAD_PREP_TRAIN_AVG_F1S 0.9658805113822986 // F1 Score

#define FANAD_PREP_TRAIN_STATS { \
 {name: "(unlabelled)", TP: 24450, FN: 301, FP: 1269, TN: 20087, TPR: 0.9878388751969, TNR: 0.9405787600674, PPV: 0.9506590458415, NPV: 0.9852364135766, FNR: 0.0121611248030, FPR: 0.0594212399325, FDR: 0.0493409541584, FOR: 0.0147635864233, F1S: 0.9688924113334, }, \
 {name: "anomaly", TP: 20087, FN: 1269, FP: 301, TN: 24450, TPR: 0.9405787600674, TNR: 0.9878388751969, PPV: 0.9852364135766, NPV: 0.9506590458415, FNR: 0.0594212399325, FPR: 0.0121611248030, FDR: 0.0147635864233, FOR: 0.0493409541584, F1S: 0.9623898045228, }, \
}

#ifdef FANAD_PREP_STATS_ENABLED
static const FANAD_PREP_stats FANAD_PREP_train_stats[] = FANAD_PREP_TRAIN_STATS;
#endif

/*
* Tensorflow Validation Set
* 
* (ACC) Accuracy 90.009 %
* (F1S) F1 Score 90.119 %
* 
* Name of class                                            (unlabelled)          anomaly
* (TP) True Positive or Correct Positive Prediction               10903             4926
* (FN) False Negative or Incorrect Negative Prediction             1130              627
* (FP) False Positive or Incorrect Positive Prediction              627             1130
* (TN) True Negative or Correct Negative Prediction                4926            10903
* (TPR) True Positive Rate or Sensitivity, Recall               90.61 %          88.71 %
* (TNR) True Negative Rate or Specificity, Selectivity          88.71 %          90.61 %
* (PPV) Positive Predictive Value or Precision                  94.56 %          81.34 %
* (NPV) Negative Predictive Value                               81.34 %          94.56 %
* (FNR) False Negative Rate or Miss Rate                         9.39 %          11.29 %
* (FPR) False Positive Rate or Fall-Out                         11.29 %           9.39 %
* (FDR) False Discovery Rate                                     5.44 %          18.66 %
* (FOR) False Omission Rate                                     18.66 %           5.44 %
* (F1S) F1 Score                                                92.54 %          84.87 %
*/


#define FANAD_PREP_VALIDATION_AVG_ACC 0.900090981462527 // Accuracy
#define FANAD_PREP_VALIDATION_AVG_F1S 0.9011890527586455 // F1 Score

#define FANAD_PREP_VALIDATION_STATS { \
 {name: "(unlabelled)", TP: 10903, FN: 1130, FP: 627, TN: 4926, TPR: 0.9060915814842, TNR: 0.8870880605078, PPV: 0.9456201214223, NPV: 0.8134081902245, FNR: 0.0939084185157, FPR: 0.1129119394921, FDR: 0.0543798785776, FOR: 0.1865918097754, F1S: 0.9254339430463, }, \
 {name: "anomaly", TP: 4926, FN: 627, FP: 1130, TN: 10903, TPR: 0.8870880605078, TNR: 0.9060915814842, PPV: 0.8134081902245, NPV: 0.9456201214223, FNR: 0.1129119394921, FPR: 0.0939084185157, FDR: 0.1865918097754, FOR: 0.0543798785776, F1S: 0.8486519080024, }, \
}

#ifdef FANAD_PREP_STATS_ENABLED
static const FANAD_PREP_stats FANAD_PREP_validation_stats[] = FANAD_PREP_VALIDATION_STATS;
#endif

#define FANAD_PREP_API_QUEUE

// All symbols in order
#define FANAD_PREP_SYMBOL_MAP {"unlabelled", "anomaly"}

// Model GUID (16 bytes)
#define FANAD_PREP_MODEL_ID {0x69, 0xca, 0xd1, 0x9a, 0x30, 0x9d, 0xe6, 0x4b, 0x8a, 0x30, 0x3f, 0x5a, 0xe6, 0x39, 0x2d, 0xdf}

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

// data_in [3] (12 bytes)
#define FANAD_PREP_DATA_IN_COUNT (3)
#define FANAD_PREP_DATA_IN_TYPE float
#define FANAD_PREP_DATA_IN_TYPE_ID IMAGINET_TYPES_FLOAT32
#define FANAD_PREP_DATA_IN_SCALE (1)
#define FANAD_PREP_DATA_IN_OFFSET (0)
#define FANAD_PREP_DATA_IN_IS_QUANTIZED (0)

// data_out [50,3] (600 bytes)
#define FANAD_PREP_DATA_OUT_COUNT (150)
#define FANAD_PREP_DATA_OUT_TYPE float
#define FANAD_PREP_DATA_OUT_TYPE_ID IMAGINET_TYPES_FLOAT32
#define FANAD_PREP_DATA_OUT_SCALE (1)
#define FANAD_PREP_DATA_OUT_OFFSET (0)
#define FANAD_PREP_DATA_OUT_IS_QUANTIZED (0)

#define FANAD_PREP_KEY_MAX (3)



// Return codes
#define FANAD_PREP_RET_SUCCESS 0
#define FANAD_PREP_RET_NODATA -1
#define FANAD_PREP_RET_NOMEM -2

// Exported methods
int FANAD_PREP_dequeue(float *restrict data_out);
int FANAD_PREP_enqueue(const float *restrict data_in);
void FANAD_PREP_init(void);

#endif /* _FANAD_PREP_FAN_AD_CONV1D_PREPROCESSOR_H_ */
