/*
* Imagimob Studio 5.1.1920+23251253412258875242be5d4844a74c53d9fafa
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 10/01/2024 08:50:39 UTC. Any changes will be lost.
* 
* Model ID  bbac668b-543a-4138-afb7-0a9f07a6f33a
* 
* Memory    Size                      Efficiency
* State     508 bytes (RAM)           100 %
* 
* Backend              tensorflow
* Keras Version        2.15.0
* Backend Model Type   Sequential
* Backend Model Name   fanad-conv1d-small-speed-1
* 
* Class Index | Symbol Label
* 0           | unlabelled
* 1           | anomaly
* 
* Layer                          Shape           Type       Function
* Sliding Window (data points)   [25,3]          float      dequeue
*    window_shape = [25,3]
*    stride = 3
*    buffer_multiplier = 1
* 
* Exported functions:
* 
* int FANAD_PREP_dequeue(float *restrict data_out)
*    Description: Dequeue features. RET_SUCCESS (0) on success, RET_NODATA (-1) if no data is available, RET_NOMEM (-2) on internal memory error
*    Parameter data_out is Output of size float[25,3].
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
* (ACC) Accuracy 94.243 %
* (F1S) F1 Score 94.213 %
* 
* Name of class                                            (unlabelled)          anomaly
* (TP) True Positive or Correct Positive Prediction               14732            10493
* (FN) False Negative or Incorrect Negative Prediction              342             1199
* (FP) False Positive or Incorrect Positive Prediction             1199              342
* (TN) True Negative or Correct Negative Prediction               10493            14732
* (TPR) True Positive Rate or Sensitivity, Recall               97.73 %          89.75 %
* (TNR) True Negative Rate or Specificity, Selectivity          89.75 %          97.73 %
* (PPV) Positive Predictive Value or Precision                  92.47 %          96.84 %
* (NPV) Negative Predictive Value                               96.84 %          92.47 %
* (FNR) False Negative Rate or Miss Rate                         2.27 %          10.25 %
* (FPR) False Positive Rate or Fall-Out                         10.25 %           2.27 %
* (FDR) False Discovery Rate                                     7.53 %           3.16 %
* (FOR) False Omission Rate                                      3.16 %           7.53 %
* (F1S) F1 Score                                                95.03 %          93.16 %
*/


#define FANAD_PREP_TEST_AVG_ACC 0.942426959575581 // Accuracy
#define FANAD_PREP_TEST_AVG_F1S 0.9421275068234384 // F1 Score

#define FANAD_PREP_TEST_STATS { \
 {name: "(unlabelled)", TP: 14732, FN: 342, FP: 1199, TN: 10493, TPR: 0.9773119278227, TNR: 0.8974512487170, PPV: 0.9247379323331, NPV: 0.9684356252884, FNR: 0.0226880721772, FPR: 0.1025487512829, FDR: 0.0752620676668, FOR: 0.0315643747115, F1S: 0.9502983389775, }, \
 {name: "anomaly", TP: 10493, FN: 1199, FP: 342, TN: 14732, TPR: 0.8974512487170, TNR: 0.9773119278227, PPV: 0.9684356252884, NPV: 0.9247379323331, FNR: 0.1025487512829, FPR: 0.0226880721772, FDR: 0.0315643747115, FOR: 0.0752620676668, F1S: 0.9315931992719, }, \
}

#ifdef FANAD_PREP_STATS_ENABLED
static const FANAD_PREP_stats FANAD_PREP_test_stats[] = FANAD_PREP_TEST_STATS;
#endif

/*
* Tensorflow Train Set
* 
* (ACC) Accuracy 96.215 %
* (F1S) F1 Score 96.215 %
* 
* Name of class                                            (unlabelled)          anomaly
* (TP) True Positive or Correct Positive Prediction               30519            28687
* (FN) False Negative or Incorrect Negative Prediction             1071             1258
* (FP) False Positive or Incorrect Positive Prediction             1258             1071
* (TN) True Negative or Correct Negative Prediction               28687            30519
* (TPR) True Positive Rate or Sensitivity, Recall               96.61 %          95.80 %
* (TNR) True Negative Rate or Specificity, Selectivity          95.80 %          96.61 %
* (PPV) Positive Predictive Value or Precision                  96.04 %          96.40 %
* (NPV) Negative Predictive Value                               96.40 %          96.04 %
* (FNR) False Negative Rate or Miss Rate                         3.39 %           4.20 %
* (FPR) False Positive Rate or Fall-Out                          4.20 %           3.39 %
* (FDR) False Discovery Rate                                     3.96 %           3.60 %
* (FOR) False Omission Rate                                      3.60 %           3.96 %
* (F1S) F1 Score                                                96.32 %          96.10 %
*/


#define FANAD_PREP_TRAIN_AVG_ACC 0.9621516210286829 // Accuracy
#define FANAD_PREP_TRAIN_AVG_F1S 0.962148193705502 // F1 Score

#define FANAD_PREP_TRAIN_STATS { \
 {name: "(unlabelled)", TP: 30519, FN: 1071, FP: 1258, TN: 28687, TPR: 0.9660968660968, TNR: 0.9579896476874, PPV: 0.9604116184661, NPV: 0.9640096780697, FNR: 0.0339031339031, FPR: 0.0420103523125, FDR: 0.0395883815338, FOR: 0.0359903219302, F1S: 0.9632458535199, }, \
 {name: "anomaly", TP: 28687, FN: 1258, FP: 1071, TN: 30519, TPR: 0.9579896476874, TNR: 0.9660968660968, PPV: 0.9640096780697, NPV: 0.9604116184661, FNR: 0.0420103523125, FPR: 0.0339031339031, FDR: 0.0359903219302, FOR: 0.0395883815338, F1S: 0.9609902349965, }, \
}

#ifdef FANAD_PREP_STATS_ENABLED
static const FANAD_PREP_stats FANAD_PREP_train_stats[] = FANAD_PREP_TRAIN_STATS;
#endif

/*
* Tensorflow Validation Set
* 
* (ACC) Accuracy 93.592 %
* (F1S) F1 Score 93.599 %
* 
* Name of class                                            (unlabelled)          anomaly
* (TP) True Positive or Correct Positive Prediction                6225             8629
* (FN) False Negative or Incorrect Negative Prediction              457              560
* (FP) False Positive or Incorrect Positive Prediction              560              457
* (TN) True Negative or Correct Negative Prediction                8629             6225
* (TPR) True Positive Rate or Sensitivity, Recall               93.16 %          93.91 %
* (TNR) True Negative Rate or Specificity, Selectivity          93.91 %          93.16 %
* (PPV) Positive Predictive Value or Precision                  91.75 %          94.97 %
* (NPV) Negative Predictive Value                               94.97 %          91.75 %
* (FNR) False Negative Rate or Miss Rate                         6.84 %           6.09 %
* (FPR) False Positive Rate or Fall-Out                          6.09 %           6.84 %
* (FDR) False Discovery Rate                                     8.25 %           5.03 %
* (FOR) False Omission Rate                                      5.03 %           8.25 %
* (F1S) F1 Score                                                92.45 %          94.44 %
*/


#define FANAD_PREP_VALIDATION_AVG_ACC 0.9359208619494676 // Accuracy
#define FANAD_PREP_VALIDATION_AVG_F1S 0.9359853323106939 // F1 Score

#define FANAD_PREP_VALIDATION_STATS { \
 {name: "(unlabelled)", TP: 6225, FN: 457, FP: 560, TN: 8629, TPR: 0.9316073032026, TNR: 0.9390575688322, PPV: 0.9174649963154, NPV: 0.9497028395333, FNR: 0.0683926967973, FPR: 0.0609424311677, FDR: 0.0825350036845, FOR: 0.0502971604666, F1S: 0.9244820672755, }, \
 {name: "anomaly", TP: 8629, FN: 560, FP: 457, TN: 6225, TPR: 0.9390575688322, TNR: 0.9316073032026, PPV: 0.9497028395333, NPV: 0.9174649963154, FNR: 0.0609424311677, FPR: 0.0683926967973, FDR: 0.0502971604666, FOR: 0.0825350036845, F1S: 0.9443502051983, }, \
}

#ifdef FANAD_PREP_STATS_ENABLED
static const FANAD_PREP_stats FANAD_PREP_validation_stats[] = FANAD_PREP_VALIDATION_STATS;
#endif

#define FANAD_PREP_API_QUEUE

// All symbols in order
#define FANAD_PREP_SYMBOL_MAP {"unlabelled", "anomaly"}

// Model GUID (16 bytes)
#define FANAD_PREP_MODEL_ID {0x8b, 0x66, 0xac, 0xbb, 0x3a, 0x54, 0x38, 0x41, 0xaf, 0xb7, 0x0a, 0x9f, 0x07, 0xa6, 0xf3, 0x3a}

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

// data_out [25,3] (300 bytes)
#define FANAD_PREP_DATA_OUT_COUNT (75)
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
