# Model performance and validation report
**Source model:** conv1d-small-balanced-0.h5  
**Output directory:** Infineon/mtb_ml_models  
**Generated:** 2024-10-30 17:47:13

### Memory usage
| Model | Model memory | Scratch memory |
| :--- | :--- | :--- |
| float | 4,128 | 16,384 |
| int8x8 | 4,496 | 16,384 |

### Latency
| Layer | Cycles |
| :--- | :--- |
| CONV_2D | 20,847 |
| MAX_POOL_2D | 2,746 |
| MEAN | 13,635 |
| FULLY_CONNECTED | 1,541 |
| **TOTAL** | **38,769** |

### Validation
**Validation data source:** None
