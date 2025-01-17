# Model performance and validation report
**Source model:** conv1d-small-balanced-2.h5  
**Output directory:** Infineon/mtb_ml_models  
**Generated:** 2024-10-02 13:18:57

### Memory usage
| Model | Model memory | Scratch memory |
| :--- | :--- | :--- |
| float | 24,416 | 16,384 |
| int8x8 | 12,560 | 16,384 |

### Latency
| Layer | Cycles |
| :--- | :--- |
| CONV_2D | 24,546 |
| CONV_2D | 76,150 |
| CONV_2D | 121,455 |
| MAX_POOL_2D | 5,385 |
| MEAN | 29,221 |
| FULLY_CONNECTED | 1,678 |
| **TOTAL** | **258,435** |

### Validation
**Validation data source:** None
