/*
* ImagiNet Compiler 5.1.1920+23251253412258875242be5d4844a74c53d9fafa
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 10/30/2024 09:47:13 UTC. Any changes will be lost.
* 
* Model ID  e60522e6-fb5c-4970-9fac-500bcf8d1833
* 
* Memory    Size                      Efficiency
* Buffers   360 bytes (RAM)           100 %
* State     16888 bytes (RAM)         100 %
* Readonly  4576 bytes (Flash)        100 %
* 
* Exported functions:
* 
*  @description: Try read data from model.
*  @param data_out Output features. Output float[2].
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*  int IMAI_dequeue(float *data_out);
* 
*  @description: Try write data to model.
*  @param data_in Input features. Input float[6].
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*  int IMAI_enqueue(const float *data_in);
* 
*  @description: Closes and flushes streams, free any heap allocated memory.
*  void IMAI_finalize(void);
* 
*  @description: Initializes buffers to initial state.
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*  int IMAI_init(void);
* 
* 
* Disclaimer:
*   The generated code relies on the optimizations done by the C compiler.
*   For example many for-loops of length 1 must be removed by the optimizer.
*   This can only be done if the functions are inlined and simplified.
*   Check disassembly if unsure.
*   tl;dr Compile using gcc with -O3 or -Ofast
*/

#include <stdint.h>
#include <string.h>
#include "mtb_ml_model.h"

#include "cap_model.h"

#ifdef __GNUC__
#define ALIGNED(x) __attribute__((aligned(x)))
#else
#define ALIGNED(x) __declspec(align(x))
#endif
// Working memory
static ALIGNED(16) int8_t _buffer[360];
static ALIGNED(16) int8_t _state[16888];

// Parameters
static const uint32_t _K4[] = {
    0x0000001c, 0x334c4654, 0x00200014, 0x0018001c, 0x00100014, 0x0000000c, 0x00040008, 0x00000014, 
    0x0000001c, 0x0000009c, 0x000000f4, 0x00000338, 0x00000348, 0x0000111c, 0x00000003, 0x00000001, 
    0x00000010, 0x000a0000, 0x000c0010, 0x00040008, 0x0000000a, 0x0000000c, 0x0000001c, 0x00000048, 
    0x0000000f, 0x76726573, 0x5f676e69, 0x61666564, 0x00746c75, 0x00000001, 0x00000004, 0xffffff8c, 
    0x00000010, 0x00000004, 0x00000017, 0x766e6f63, 0x732d6431, 0x6c6c616d, 0x6c61622d, 0x65636e61, 
    0x00302d64, 0x00000001, 0x00000004, 0xfffffcba, 0x00000004, 0x00000007, 0x75706e69, 0x00325f74, 
    0x00000002, 0x00000034, 0x00000004, 0xffffffdc, 0x00000013, 0x00000004, 0x00000013, 0x564e4f43, 
    0x49535245, 0x4d5f4e4f, 0x44415445, 0x00415441, 0x000c0008, 0x00040008, 0x00000008, 0x00000012, 
    0x00000004, 0x00000013, 0x5f6e696d, 0x746e7572, 0x5f656d69, 0x73726576, 0x006e6f69, 0x00000014, 
    0x00000240, 0x00000238, 0x00000218, 0x000001f8, 0x000001dc, 0x000001c8, 0x000001b0, 0x00000188, 
    0x00000148, 0x000000cc, 0x000000c4, 0x000000bc, 0x000000b4, 0x000000ac, 0x000000a4, 0x0000009c, 
    0x00000094, 0x0000008c, 0x0000006c, 0x00000004, 0xfffffd7e, 0x00000004, 0x00000058, 0x0000000c, 
    0x000e0008, 0x00040008, 0x00000008, 0x00000010, 0x00000028, 0x00060000, 0x00040008, 0x00000006, 
    0x00000004, 0x00000001, 0x000003eb, 0x000a0000, 0x000c0010, 0x00040008, 0x0000000a, 0x00000002, 
    0x00000002, 0x00000004, 0x00000006, 0x34312e32, 0x0000312e, 0xfffffde2, 0x00000004, 0x00000010, 
    0x34312e31, 0x0000302e, 0x00000000, 0x00000000, 0xfffff180, 0xfffff184, 0xfffff188, 0xfffff18c, 
    0xfffff190, 0xfffff194, 0xfffff198, 0xfffff19c, 0xfffffe1e, 0x00000004, 0x0000006c, 0x25ca3597, 
    0x0606b8d8, 0xa811fb7f, 0xf5813edf, 0xd125c527, 0x812211ab, 0xd3cc0b05, 0x7fe4dd13, 0x29faf7d2, 
    0x147f0654, 0x6fda5bbc, 0x430542f7, 0x1048810c, 0x9d13d72d, 0x8149cd98, 0x34b5ef26, 0x2c323518, 
    0x29bd107f, 0x29452cfe, 0x0f527fbb, 0x933ca5fc, 0x0eae0ad8, 0x3eb87f0d, 0xd7499081, 0xe31f2cf2, 
    0x812f6d66, 0x1e454c78, 0xfffffe96, 0x00000004, 0x00000030, 0x00002481, 0xffffdbea, 0xffffdc65, 
    0xffffd40a, 0xffffa700, 0xfffff46b, 0x00002e34, 0xffff866e, 0xffffaa49, 0x0000253e, 0x0000211f, 
    0xffffa5ee, 0xfffffed2, 0x00000004, 0x00000018, 0x814f472a, 0x2b0ee3df, 0xeb3230ea, 0x62bcd4d1, 
    0xb9eb0523, 0x15e3db22, 0xfffffef6, 0x00000004, 0x00000008, 0xffffff75, 0x0000008b, 0xffffff0a, 
    0x00000004, 0x00000004, 0x00000001, 0xffffff1a, 0x00000004, 0x0000000c, 0x00000001, 0x00000006, 
    0x0000000c, 0xffffff32, 0x00000004, 0x00000010, 0x00000001, 0x0000000c, 0x00000001, 0x0000000c, 
    0xffffff4e, 0x00000004, 0x00000010, 0x00000001, 0x00000001, 0x00000018, 0x00000003, 0xfffff2ec, 
    0xfffff2f0, 0x0000000f, 0x52494c4d, 0x6e6f4320, 0x74726576, 0x002e6465, 0x00000001, 0x00000014, 
    0x000e0000, 0x00140018, 0x000c0010, 0x00040008, 0x0000000e, 0x00000014, 0x0000001c, 0x000001f0, 
    0x000001f4, 0x000001f8, 0x00000004, 0x6e69616d, 0x00000000, 0x00000008, 0x000001b4, 0x00000158, 
    0x00000124, 0x000000d0, 0x000000ac, 0x00000078, 0x00000040, 0x00000004, 0xfffffed2, 0x0000001c, 
    0x09000000, 0x0000001c, 0x00000020, 0x00000005, 0x00060000, 0x00040008, 0x00000006, 0x3f800000, 
    0x00000001, 0x00000010, 0x00000001, 0x0000000f, 0xffffff0a, 0x00000014, 0x08000000, 0x00000010, 
    0x00000014, 0x00000004, 0xfffff3b8, 0x00000001, 0x0000000f, 0x00000003, 0x0000000e, 0x00000006, 
    0x00000005, 0xffffff3e, 0x00000014, 0x1b000000, 0x00000010, 0x00000014, 0x00000003, 0xfffff3ec, 
    0x00000001, 0x0000000e, 0x00000002, 0x0000000d, 0x00000004, 0xffffff12, 0x00000008, 0x0000000c, 
    0x00000001, 0x0000000d, 0x00000002, 0x0000000c, 0x00000003, 0xffffff8e, 0x00000024, 0x05000000, 
    0x00000034, 0x00000038, 0x00000002, 0x000e0000, 0x00170018, 0x000c0010, 0x00040008, 0x0000000e, 
    0x00000002, 0x00000001, 0x00000002, 0x00000001, 0x01000000, 0x00000001, 0x0000000c, 0x00000001, 
    0x0000000b, 0xffffff82, 0x00000008, 0x0000000c, 0x00000001, 0x0000000b, 0x00000002, 0x0000000a, 
    0x00000002, 0x000e0000, 0x00140018, 0x000c0010, 0x0004000b, 0x0000000e, 0x00000020, 0x01000000, 
    0x00000028, 0x0000002c, 0x00000001, 0x0010000c, 0x000c0000, 0x00070008, 0x0000000c, 0x01000000, 
    0x00000001, 0x00000002, 0x00000001, 0x0000000a, 0x00000003, 0x00000009, 0x00000008, 0x00000007, 
    0x000a0000, 0x0000000c, 0x00040008, 0x0000000a, 0x00000008, 0x0000000c, 0x00000001, 0x00000009, 
    0x00000002, 0x00000000, 0x00000001, 0x00000001, 0x00000010, 0x00000001, 0x00000000, 0x00000011, 
    0x00000b38, 0x00000ab0, 0x00000a4c, 0x000009ec, 0x00000980, 0x000008f0, 0x0000086c, 0x00000760, 
    0x000005ac, 0x00000518, 0x0000034c, 0x000002c0, 0x00000234, 0x000001a8, 0x00000124, 0x00000070, 
    0x00000004, 0xfffff522, 0x01000000, 0x00000014, 0x00000030, 0x00000011, 0x09000000, 0x00000044, 
    0xfffff50c, 0x00000008, 0x00000010, 0x00000001, 0xffffff80, 0xffffffff, 0x00000001, 0x3b800000, 
    0x00000019, 0x74617453, 0x6c756665, 0x74726150, 0x6f697469, 0x4364656e, 0x3a6c6c61, 0x00000030, 
    0x00000002, 0x00000001, 0x00000002, 0xfffff58a, 0x01000000, 0x00000014, 0x00000034, 0x00000010, 
    0x09000000, 0x0000008c, 0xfffff574, 0x00000008, 0x00000014, 0x00000001, 0xfffffff1, 0xffffffff, 
    0x00000000, 0x00000001, 0x3dd62f77, 0x0000005e, 0x65646f6d, 0x2f315f6c, 0x766e6f63, 0x732d6431, 
    0x6c6c616d, 0x6c61622d, 0x65636e61, 0x2f302d64, 0x6579616c, 0x2f355f72, 0x4d74614d, 0x6d3b6c75, 
    0x6c65646f, 0x632f315f, 0x31766e6f, 0x6d732d64, 0x2d6c6c61, 0x616c6162, 0x6465636e, 0x6c2f302d, 
    0x72657961, 0x422f355f, 0x41736169, 0x00006464, 0x00000002, 0x00000001, 0x00000002, 0xfffff63a, 
    0x01000000, 0x00000014, 0x00000034, 0x0000000f, 0x09000000, 0x0000005c, 0xfffff624, 0x00000008, 
    0x00000014, 0x00000001, 0xffffff80, 0xffffffff, 0x00000000, 0x00000001, 0x3c7553c8, 0x0000002c, 
    0x65646f6d, 0x2f315f6c, 0x766e6f63, 0x732d6431, 0x6c6c616d, 0x6c61622d, 0x65636e61, 0x2f302d64, 
    0x6579616c, 0x2f345f72, 0x6e61654d, 0x00000000, 0x00000002, 0x00000001, 0x0000000c, 0xfffff6ba, 
    0x01000000, 0x00000014, 0x00000034, 0x0000000e, 0x09000000, 0x00000060, 0xfffff6a4, 0x00000008, 
    0x00000014, 0x00000001, 0xffffff80, 0xffffffff, 0x00000000, 0x00000001, 0x3d2ec5a3, 0x00000030, 
    0x65646f6d, 0x2f315f6c, 0x766e6f63, 0x732d6431, 0x6c6c616d, 0x6c61622d, 0x65636e61, 0x2f302d64, 
    0x6579616c, 0x2f335f72, 0x65757153, 0x31657a65, 0x00000000, 0x00000003, 0x00000001, 0x00000006, 
    0x0000000c, 0xfffff742, 0x01000000, 0x00000014, 0x00000034, 0x0000000d, 0x09000000, 0x0000005c, 
    0xfffff72c, 0x00000008, 0x00000014, 0x00000001, 0xffffff80, 0xffffffff, 0x00000000, 0x00000001, 
    0x3d2ec5a3, 0x0000002f, 0x65646f6d, 0x2f315f6c, 0x766e6f63, 0x732d6431, 0x6c6c616d, 0x6c61622d, 
    0x65636e61, 0x2f302d64, 0x6579616c, 0x2f335f72, 0x5078614d, 0x006c6f6f, 0x00000004, 0x00000001, 
    0x00000006, 0x00000001, 0x0000000c, 0xfffff7ca, 0x01000000, 0x00000014, 0x00000030, 0x0000000c, 
    0x09000000, 0x0000005c, 0xfffff7b4, 0x00000008, 0x00000010, 0x00000001, 0xffffff80, 0xffffffff, 
    0x00000001, 0x3d2ec5a3, 0x00000033, 0x65646f6d, 0x2f315f6c, 0x766e6f63, 0x732d6431, 0x6c6c616d, 
    0x6c61622d, 0x65636e61, 0x2f302d64, 0x6579616c, 0x2f335f72, 0x61707845, 0x6944646e, 0x0031736d, 
    0x00000004, 0x00000001, 0x0000000c, 0x00000001, 0x0000000c, 0xfffff852, 0x01000000, 0x00000014, 
    0x00000034, 0x0000000b, 0x09000000, 0x0000019c, 0xfffff83c, 0x00000008, 0x00000014, 0x00000001, 
    0xffffff80, 0xffffffff, 0x00000000, 0x00000001, 0x3d2ec5a3, 0x0000016e, 0x65646f6d, 0x2f315f6c, 
    0x766e6f63, 0x732d6431, 0x6c6c616d, 0x6c61622d, 0x65636e61, 0x2f302d64, 0x6579616c, 0x2f325f72, 
    0x756c6552, 0x646f6d3b, 0x315f6c65, 0x6e6f632f, 0x2d643176, 0x6c616d73, 0x61622d6c, 0x636e616c, 
    0x302d6465, 0x79616c2f, 0x315f7265, 0x7461622f, 0x6f6e6863, 0x612f6d72, 0x315f6464, 0x646f6d3b, 
    0x315f6c65, 0x6e6f632f, 0x2d643176, 0x6c616d73, 0x61622d6c, 0x636e616c, 0x302d6465, 0x79616c2f, 
    0x305f7265, 0x6e6f432f, 0x2f443176, 0x65757153, 0x3b657a65, 0x65646f6d, 0x2f315f6c, 0x766e6f63, 
    0x732d6431, 0x6c6c616d, 0x6c61622d, 0x65636e61, 0x2f302d64, 0x6579616c, 0x2f315f72, 0x63746162, 
    0x726f6e68, 0x756d2f6d, 0x3b315f6c, 0x65646f6d, 0x2f315f6c, 0x766e6f63, 0x732d6431, 0x6c6c616d, 
    0x6c61622d, 0x65636e61, 0x2f302d64, 0x6579616c, 0x2f315f72, 0x63746162, 0x726f6e68, 0x756d2f6d, 
    0x6f6d3b6c, 0x5f6c6564, 0x6f632f31, 0x6431766e, 0x616d732d, 0x622d6c6c, 0x6e616c61, 0x2d646563, 
    0x616c2f30, 0x5f726579, 0x61622f31, 0x6e686374, 0x2f6d726f, 0x3b627573, 0x65646f6d, 0x2f315f6c, 
    0x766e6f63, 0x732d6431, 0x6c6c616d, 0x6c61622d, 0x65636e61, 0x2f302d64, 0x6579616c, 0x2f305f72, 
    0x766e6f43, 0x00004431, 0x00000004, 0x00000001, 0x00000001, 0x0000000c, 0x0000000c, 0xfffffa1a, 
    0x01000000, 0x00000014, 0x00000030, 0x0000000a, 0x09000000, 0x00000064, 0xfffffa04, 0x00000008, 
    0x00000010, 0x00000001, 0xffffff80, 0xffffffff, 0x00000001, 0x40bcfcfd, 0x0000003a, 0x65646f6d, 
    0x2f315f6c, 0x766e6f63, 0x732d6431, 0x6c6c616d, 0x6c61622d, 0x65636e61, 0x2f302d64, 0x6579616c, 
    0x2f305f72, 0x766e6f43, 0x452f4431, 0x6e617078, 0x6d694464, 0x00003173, 0x00000004, 0x00000001, 
    0x00000001, 0x00000018, 0x00000003, 0xfffffaaa, 0x01000000, 0x00000014, 0x000000b8, 0x00000009, 
    0x09000000, 0x00000184, 0xfffffa94, 0x00000008, 0x0000006c, 0x0000000c, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000000c, 
    0x3991b6ae, 0x39155e27, 0x393e5948, 0x39bf225c, 0x382d6d5b, 0x3853f45f, 0x388a885d, 0x385b1fd2, 
    0x3800aeb3, 0x3909a497, 0x38ad62ea, 0x37b1da3e, 0x000000d3, 0x65646f6d, 0x2f315f6c, 0x766e6f63, 
    0x732d6431, 0x6c6c616d, 0x6c61622d, 0x65636e61, 0x2f302d64, 0x6579616c, 0x2f315f72, 0x63746162, 
    0x726f6e68, 0x756d2f6d, 0x3b315f6c, 0x65646f6d, 0x2f315f6c, 0x766e6f63, 0x732d6431, 0x6c6c616d, 
    0x6c61622d, 0x65636e61, 0x2f302d64, 0x6579616c, 0x2f305f72, 0x766e6f43, 0x532f4431, 0x65657571, 
    0x6d3b657a, 0x6c65646f, 0x632f315f, 0x31766e6f, 0x6d732d64, 0x2d6c6c61, 0x616c6162, 0x6465636e, 
    0x6c2f302d, 0x72657961, 0x622f315f, 0x68637461, 0x6d726f6e, 0x6c756d2f, 0x646f6d3b, 0x315f6c65, 
    0x6e6f632f, 0x2d643176, 0x6c616d73, 0x61622d6c, 0x636e616c, 0x302d6465, 0x79616c2f, 0x305f7265, 
    0x6e6f432f, 0x00443176, 0x00000004, 0x0000000c, 0x00000001, 0x00000003, 0x00000003, 0xfffffc5a, 
    0x01000000, 0x00000014, 0x000000b8, 0x00000008, 0x02000000, 0x000000e8, 0xfffffc44, 0x00000008, 
    0x0000006c, 0x0000000c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x0000000c, 0x3ad7244f, 0x3a5c8982, 0x3a8c85ad, 0x3b0d1a1e, 
    0x398007b2, 0x399c78ec, 0x39cc8a17, 0x39a1c3ea, 0x393dfeed, 0x3a4b39ca, 0x39fffff9, 0x39034c08, 
    0x00000035, 0x65646f6d, 0x2f315f6c, 0x766e6f63, 0x732d6431, 0x6c6c616d, 0x6c61622d, 0x65636e61, 
    0x2f302d64, 0x6579616c, 0x2f315f72, 0x63746162, 0x726f6e68, 0x75732f6d, 0x00000062, 0x00000001, 
    0x0000000c, 0xfffffd62, 0x01000000, 0x00000014, 0x00000034, 0x00000007, 0x09000000, 0x0000005c, 
    0xfffffd4c, 0x00000008, 0x00000014, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 
    0x3ca3e810, 0x0000002e, 0x65646f6d, 0x2f315f6c, 0x766e6f63, 0x732d6431, 0x6c6c616d, 0x6c61622d, 
    0x65636e61, 0x2f302d64, 0x6579616c, 0x2f355f72, 0x4d74614d, 0x00006c75, 0x00000002, 0x00000002, 
    0x0000000c, 0xfffffde2, 0x01000000, 0x00000014, 0x00000034, 0x00000006, 0x02000000, 0x0000006c, 
    0xfffffdcc, 0x00000008, 0x00000014, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 
    0x399d12bc, 0x0000003e, 0x65646f6d, 0x2f315f6c, 0x766e6f63, 0x732d6431, 0x6c6c616d, 0x6c61622d, 
    0x65636e61, 0x2f302d64, 0x6579616c, 0x2f355f72, 0x73616942, 0x2f646441, 0x64616552, 0x69726156, 
    0x656c6261, 0x0000704f, 0x00000001, 0x00000002, 0xfffffe6e, 0x01000000, 0x00000014, 0x00000014, 
    0x00000005, 0x02000000, 0x0000004c, 0xfffffedc, 0x0000003e, 0x65646f6d, 0x2f315f6c, 0x766e6f63, 
    0x732d6431, 0x6c6c616d, 0x6c61622d, 0x65636e61, 0x2f302d64, 0x6579616c, 0x2f345f72, 0x6e61654d, 
    0x6465722f, 0x69746375, 0x695f6e6f, 0x6369646e, 0x00007365, 0x00000000, 0xfffffed6, 0x01000000, 
    0x00000014, 0x00000014, 0x00000004, 0x02000000, 0x0000003c, 0xffffff44, 0x0000002f, 0x65646f6d, 
    0x2f315f6c, 0x766e6f63, 0x732d6431, 0x6c6c616d, 0x6c61622d, 0x65636e61, 0x2f302d64, 0x6579616c, 
    0x2f335f72, 0x65757153, 0x00657a65, 0x00000001, 0x00000003, 0xffffff32, 0x01000000, 0x00000014, 
    0x00000014, 0x00000003, 0x02000000, 0x00000040, 0xffffffa0, 0x00000032, 0x65646f6d, 0x2f315f6c, 
    0x766e6f63, 0x732d6431, 0x6c6c616d, 0x6c61622d, 0x65636e61, 0x2f302d64, 0x6579616c, 0x2f335f72, 
    0x61707845, 0x6944646e, 0x0000736d, 0x00000001, 0x00000004, 0xffffff92, 0x01000000, 0x00000018, 
    0x00000018, 0x00000002, 0x02000000, 0x0000004c, 0x00040004, 0x00000004, 0x00000039, 0x65646f6d, 
    0x2f315f6c, 0x766e6f63, 0x732d6431, 0x6c6c616d, 0x6c61622d, 0x65636e61, 0x2f302d64, 0x6579616c, 
    0x2f305f72, 0x766e6f43, 0x452f4431, 0x6e617078, 0x6d694464, 0x00000073, 0x00000001, 0x00000004, 
    0x00160000, 0x0018001c, 0x00100017, 0x0008000c, 0x00000000, 0x00070000, 0x00000016, 0x01000000, 
    0x00000020, 0x0000003c, 0x00000001, 0x09000000, 0x00000050, 0x000c000c, 0x00000000, 0x00040008, 
    0x0000000c, 0x00000008, 0x00000010, 0x00000001, 0xffffff80, 0xffffffff, 0x00000001, 0x40bcfcfd, 
    0x00000019, 0x76726573, 0x5f676e69, 0x61666564, 0x5f746c75, 0x75706e69, 0x3a325f74, 0x00000030, 
    0x00000003, 0x00000001, 0x00000018, 0x00000003, 0x00000006, 0x00000080, 0x00000060, 0x00000040, 
    0x0000002c, 0x00000018, 0x00000004, 0xffffffc0, 0x00000019, 0x00000002, 0x19000000, 0xffffffd0, 
    0x00000009, 0x00000004, 0x09000000, 0xffffffe0, 0x00000028, 0x00000002, 0x28000000, 0xfffffff0, 
    0x00000011, 0x00000002, 0x11000000, 0x0010000c, 0x0000000f, 0x00040008, 0x0000000c, 0x00000003, 
    0x00000003, 0x03000000, 0x000c000c, 0x0000000b, 0x00040000, 0x0000000c, 0x00000016, 0x16000000
};

// Memory mapped buffers
#define _K4              ((int8_t *)_K4)                     // s8[4576] (4576 bytes)
#define _K2              ((int8_t *)(_state + 0x00000000))   // s8[496] (496 bytes)
#define _K3              ((int8_t *)(_state + 0x000001f8))   // s8[16384] (16384 bytes)
#define _K7              ((int8_t *)(_state + 0x000001f0))   // s8[8] (8 bytes)
#define _K1              ((float *)(_buffer + 0x00000000))   // f32[24,3] (288 bytes)
#define _K6              ((int8_t *)(_buffer + 0x00000120))  // s8[72] (72 bytes)

#define IPWIN_RET_SUCCESS 0
#define IPWIN_RET_NODATA -1
#define IPWIN_RET_ERROR -2
#define IPWIN_RET_STREAMEND -3

// Represents a Circular Buffer
// https://en.wikipedia.org/wiki/Circular_buffer
typedef struct
{
	char *buf;
	int size;		// total bytes allocated in *buf
	int used;		// current bytes used in buffer.
	int read;
	int write;
} cbuffer_t;

#define CBUFFER_SUCCESS 0
#define CBUFFER_NOMEM -1

// Initializes a cbuffer handle with given memory and size.
static inline void cbuffer_init(cbuffer_t *dest, void *mem, int size) {
	dest->buf = mem;
	dest->size = size;
	dest->used = 0;
	dest->read = 0;
	dest->write = 0;
}

// Returns the number of free bytes in buffer.
static inline int cbuffer_get_free(cbuffer_t *buf) {
	return buf->size - buf->used;
}

// Returns the number of used bytes in buffer.
static inline int cbuffer_get_used(cbuffer_t *buf) {
	return buf->used;
}

// Writes given data to buffer.
// Returns CBUFFER_SUCCESS or CBUFFER_NOMEM if out of memory.
static inline int cbuffer_enqueue(cbuffer_t *buf, const void *data, int data_size) {
	int free = cbuffer_get_free(buf);

	// Out of memory?
	if (free < data_size)
		return CBUFFER_NOMEM;

	// Is the data split in the end?
	if (buf->write + data_size > buf->size) {
		int first_size = buf->size - buf->write;
		memcpy(buf->buf + buf->write, data, first_size);
		memcpy(buf->buf, ((char *)data) + first_size, data_size - first_size);
	}
	else {
		memcpy(buf->buf + buf->write, data, data_size);
	}
	buf->write += data_size;
	if (buf->write >= buf->size)
		buf->write -= buf->size;

	buf->used += data_size;
	return CBUFFER_SUCCESS;
}

// Advances the read pointer by given count.
// Returns CBUFFER_SUCCESS on success or CBUFFER_NOMEM if count is more than available data
static inline int cbuffer_advance(cbuffer_t *buf, int count) {
	int used = cbuffer_get_used(buf);

	if (count > used)
		return CBUFFER_NOMEM;

	buf->read += count;
	if (buf->read >= buf->size)
		buf->read -= buf->size;

	// Reset pointers to 0 if buffer is empty in order to avoid unwanted wrapps.
	if (buf->read == buf->write) {
		buf->read = 0;
		buf->write = 0;
	}

	buf->used -= count;
	return CBUFFER_SUCCESS;
}

// Reset instance (clear buffer)
static inline void cbuffer_reset(cbuffer_t *buf) {
	buf->read = 0;
	buf->write = 0;
	buf->used = 0;
}

// Copies given "count" bytes to the "dst" buffer without advancing the buffer read offset.
// Returns CBUFFER_SUCCESS on success or CBUFFER_NOMEM if count is more than available data.
static inline int cbuffer_copyto(cbuffer_t *buf, void *dst, int count, int offset) {
	
	if (count > cbuffer_get_used(buf))
		return CBUFFER_NOMEM;

	int a0 = buf->read + offset;
	if (a0 >= buf->size)
		a0 -= buf->size;

	int c0 = count;
	if (a0 + c0 > buf->size)
		c0 = buf->size - a0;
	
	memcpy(dst, buf->buf + a0, c0);
	
	int c1 = count - c0;

	if (c1 > 0)
		memcpy(((char *)dst) + c0, buf->buf, c1);

	return CBUFFER_SUCCESS;
}

// Returns a read pointer at given offset and  
// updates *can_read_bytes (if not NULL) with the number of bytes that can be read.
// 
// Note! Byte count written to can_read_bytes can be less than what cbuffer_get_used() returns.
// This happens when the read has to be split in two since it's a circular buffer.
static inline void *cbuffer_readptr(cbuffer_t* buf, int offset, int *can_read_bytes)
{
	int a0 = buf->read + offset;
	if (a0 >= buf->size)
		a0 -= buf->size;
	if (can_read_bytes != NULL)
	{
		int c0 = buf->used;
		if (a0 + c0 > buf->size)
			c0 = buf->size - a0;

		*can_read_bytes = c0;
	}
	return buf->buf + a0;
}

typedef struct {
	cbuffer_t data_buffer;			// Circular Buffer for features
	int input_size;					// Number of bytes in each input chunk
	int window_count;				// Number of input chunks in output window.
} fixwin_t;

#ifdef _MSC_VER
static_assert(sizeof(fixwin_t) <= 64, "Data structure 'fixwin_t' is too big");
#endif

/*
* Try to dequeue a window.
*
* @param handle Pointer to an initialized handle.
* @param dst Pointer where to write window.
* @param stride_count Number of items (of size handle->input_size) to stride window.
* @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1) is no data is available.
*/
static inline int fixwin_dequeue(void* restrict handle, void* restrict dst, int stride_count)
{
	fixwin_t* fep = (fixwin_t*)handle;

	const int stride_bytes = stride_count * fep->input_size;
	const int size = fep->window_count * fep->input_size;
	if (cbuffer_get_used(&fep->data_buffer) >= size) {
		if (cbuffer_copyto(&fep->data_buffer, dst, size, 0) != 0)
			return IPWIN_RET_ERROR;

		if (cbuffer_advance(&fep->data_buffer, stride_bytes) != 0)
			return IPWIN_RET_ERROR;

		return IPWIN_RET_SUCCESS;
	}
	return IPWIN_RET_NODATA;
}

static inline void mtb_model_int8_f32(const void* handle, const float* restrict src, int src_count, float* restrict dst, int dst_count, int8_t* tmp)
{
	mtb_ml_model_t* model = *(mtb_ml_model_t**)handle;

	int in_offset = model->input_zero_point;
	float in_scale = model->input_scale;
	 
	for (int i = 0; i < src_count; i++) {
		float value = (src[i] / in_scale) + in_offset;
		if (value > 127)
			tmp[i] = 127;
		else if (value < -128)
			tmp[i] = -128;
		else
			tmp[i] = (int8_t)value;
	}

	mtb_ml_model_run(model, tmp);
	
	int out_offset = model->output_zero_point;
	float out_scale = model->output_scale;
	int8_t* out_data = model->output;
	for (int i = 0; i < dst_count; i++) {
		dst[i] = (out_data[i] - out_offset) * out_scale;
	}
}

/**
 * Enqueue handle->input_size values from given *data pointer to internal window buffer.
 *
 * @param handle Pointer to an initialized handle.
 * @param data Data to enqueue.
 * @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_ERROR (-2) if internal buffer is out of memory.
 */
static inline int fixwin_enqueue(void* restrict handle, const void* restrict data)
{
	fixwin_t* fep = (fixwin_t*)handle;

	if (cbuffer_enqueue(&fep->data_buffer, data, fep->input_size) != 0)
		return IPWIN_RET_ERROR;

	return IPWIN_RET_SUCCESS;
}

static inline void mtb_model_free(const void* handle)
{
	mtb_ml_model_t* model = *(mtb_ml_model_t**)handle;
	mtb_ml_model_deinit(model);
}

/**
* Initializes a fixwin sampler handle.
*
* @param handle Pointer to a preallocated memory area of fixwin_handle_size() bytes to initialize.
*
* @param input_size Number of bytes to enqueue.
* @param window_count Number of items (of size input_size) in each window
*/
static inline void fixwin_init(void* restrict handle, int input_size, int window_count)
{
	fixwin_t* fep = (fixwin_t*)handle;
	fep->input_size = input_size;
	fep->window_count = window_count;

	char* mem = ((char*)handle) + sizeof(fixwin_t);

	int data_buffer = input_size * window_count;
	
	cbuffer_init(&fep->data_buffer, mem, data_buffer);
}

int mtb_init(const void *handle, int8_t* model_bin, unsigned int model_size, int8_t* arena_buffer, int arena_size) {
	
	mtb_ml_model_t** model_obj = (mtb_ml_model_t**)handle;
	
	mtb_ml_model_bin_t model = { "model", (uint8_t*)model_bin, model_size, arena_size };
	mtb_ml_model_buffer_t buffer = { (uint8_t*)arena_buffer, arena_size };
	if (mtb_ml_model_init(&model, &buffer, model_obj) != CY_RSLT_SUCCESS)
		return IPWIN_RET_ERROR;

	return 0;
}

#define __RETURN_ERROR(_exp) do { int __ret = (_exp); if(__ret < 0) return __ret; } while(0)
#define __RETURN_ALWAYS(_exp) return (_exp)
#define __RETURN_ERROR_BREAK_EMPTY(_exp) {  int __ret = (_exp); if(__ret == -1) break; if(__ret < 0) return __ret;  } 

/*
* Try read data from model.
* 
*  @param data_out Output features. Output float[2].
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*/
int IMAI_dequeue(float *restrict data_out) {    
    __RETURN_ERROR(fixwin_dequeue(_K2, _K1, 7));
    mtb_model_int8_f32(_K7, _K1, 72, data_out, 2, _K6);
    return 0;
}

/*
* Try write data to model.
* 
*  @param data_in Input features. Input float[6].
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*/
int IMAI_enqueue(const float *restrict data_in) {    
    __RETURN_ERROR(fixwin_enqueue(_K2, data_in));
    return 0;
}

/*
* Closes and flushes streams, free any heap allocated memory.
* 
*/
void IMAI_finalize(void) {    
    mtb_model_free(_K7);
}

/*
* Initializes buffers to initial state.
* 
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*/
int IMAI_init(void) {    
    fixwin_init(_K2, 24, 12);
    __RETURN_ERROR(mtb_init(_K7, _K4, 4576, _K3, 16384));
    return 0;
}

#ifdef IMAI_REFLECTION

static IMAI_api_def _IMAI_api_def = {
    api_ver: 1,
    id: {0xe6, 0x22, 0x05, 0xe6, 0x5c, 0xfb, 0x70, 0x49, 0x9f, 0xac, 0x50, 0x0b, 0xcf, 0x8d, 0x18, 0x33},
    api_type: IMAI_API_TYPE_QUEUE,
    prefix: "IMAI_",
    buffer_mem: {
        size: 360,
        peak_usage: 360,
    },
    static_mem: {
        size: 16888,
        peak_usage: 16888,
    },
    readonly_mem: {
        size: 4576,
        peak_usage: 4576,
    },
    func_count: 4,
    func_list: (IMAI_func_def[]) {
        {
            name: "IMAI_dequeue",
            description: "Try read data from model.",
            fn_ptr: IMAI_dequeue,
            attrib: 3,
            param_count: 1,
            param_list: (IMAI_param_def[]) {
                {
                    name: "data_out",
                    attrib: IMAI_PARAM_OUTPUT,
                    rank: 1,
                    shape: (IMAI_shape_dim[]) {
                        {
                            name: "Labels",
                            size: 2,
                            labels: (label_text_t[]) { "unlabelled","touch" },
                        },
                    },
                    count: 2,
                    type_id: IMAGINET_TYPES_FLOAT32,
                    frequency: 14.163865546218487,
                    shift: 0,
                    scale: 1,
                    offset: 0,
                },
            },
        },
        {
            name: "IMAI_enqueue",
            description: "Try write data to model.",
            fn_ptr: IMAI_enqueue,
            attrib: 3,
            param_count: 1,
            param_list: (IMAI_param_def[]) {
                {
                    name: "data_in",
                    attrib: IMAI_PARAM_INPUT,
                    rank: 1,
                    shape: (IMAI_shape_dim[]) {
                        {
                            name: "",
                            size: 6,
                        },
                    },
                    count: 6,
                    type_id: IMAGINET_TYPES_FLOAT32,
                    frequency: 99.1470588235294,
                    shift: 0,
                    scale: 1,
                    offset: 0,
                },
            },
        },
        {
            name: "IMAI_finalize",
            description: "Closes and flushes streams, free any heap allocated memory.",
            fn_ptr: IMAI_finalize,
            attrib: 10,
            param_count: 0,
            param_list: (IMAI_param_def[]) {
            },
        },
        {
            name: "IMAI_init",
            description: "Initializes buffers to initial state.",
            fn_ptr: IMAI_init,
            attrib: 7,
            param_count: 0,
            param_list: (IMAI_param_def[]) {
            },
        },
    },
};

IMAI_api_def *IMAI_api(void) {
    return &_IMAI_api_def;
}

#endif /* IMAI_REFLECTION */

