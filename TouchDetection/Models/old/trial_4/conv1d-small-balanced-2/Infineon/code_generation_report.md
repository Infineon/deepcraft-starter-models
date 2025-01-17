# Model performance and validation report
**Source model:** conv1d-small-balanced-2.h5  
**Output directory:** Infineon/mtb_ml_models  
**Generated:** 2024-10-10 00:36:35

### Memory usage
| Model | Model memory | Scratch memory |
| :--- | :--- | :--- |
| float | 24,416 | 16,384 |
| int8x8 | 12,560 | 16,384 |

### Latency
| Layer | Cycles |
| :--- | :--- |
| CONV_2D | 45,875 |
| CONV_2D | 153,383 |
| CONV_2D | 247,770 |
| MAX_POOL_2D | 11,068 |
| MEAN | 54,160 |
| FULLY_CONNECTED | 1,678 |
| **TOTAL** | **513,934** |

### Validation
**Validation data source:** None
