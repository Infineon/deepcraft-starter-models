# Model performance and validation report
**Source model:** fan-ad-conv1d-small-speed-1.h5  
**Output directory:** Infineon/mtb_ml_models  
**Generated:** 2024-09-20 14:44:23

### Memory usage
| Model | Model memory | Scratch memory |
| :--- | :--- | :--- |
| float | 12,204 | 16,384 |

### Latency
| Layer | Cycles |
| :--- | :--- |
| CONV_2D | 76,875 |
| CONV_2D | 203,623 |
| CONV_2D | 203,623 |
| MAX_POOL_2D | 11,682 |
| MEAN | 27,216 |
| FULLY_CONNECTED | 1,304 |
| **TOTAL** | **524,322** |

### Validation
**Validation data source:** None
