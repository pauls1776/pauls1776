/*
 * stub.h
 *
 *  Created on: Jan 19, 2024
 *      Author: praskumt
 */

#ifndef STUB_H_
#define STUB_H_
#define DONT_USE_SDK 0

// GLoabl Includes
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include "error.h"
#include "StdTypes.h"

#include "tc6-conf.h"
#include "tc6-regs.h"
#include "tc6-stub.h"
#include "tc6-noip.h"
#include "ftm_common.h"
#include "ftm_hw_access.h"
#include "peripherals_flexTimer_mc_1.h"

// device includes
#include "device_registers.h"
#include "pins_driver.h"
#include "lpspi_hw_access.h"
#include "lpspi_master_driver.h"
#include "peripherals_lpspi_1.h"
#include "pcc_hw_access.h"
#include "S32K146.h"

typedef enum
{
    FTM_MODE_NOT_INITIALIZED                    = 0x00U,    /*!< The driver is not initialized */
    FTM_MODE_INPUT_CAPTURE                      = 0x01U,    /*!< Input capture */
    FTM_MODE_OUTPUT_COMPARE                     = 0x02U,    /*!< Output compare */
    FTM_MODE_EDGE_ALIGNED_PWM                   = 0x03U,    /*!< Edge aligned PWM */
    FTM_MODE_CEN_ALIGNED_PWM                    = 0x04U,    /*!< Center aligned PWM */
    FTM_MODE_QUADRATURE_DECODER                 = 0x05U,    /*!< Quadrature decoder */
    FTM_MODE_UP_TIMER                           = 0x06U,    /*!< Timer with up counter */
    FTM_MODE_UP_DOWN_TIMER                      = 0x07U,    /*!< timer with up-down counter */
    FTM_MODE_EDGE_ALIGNED_PWM_AND_INPUT_CAPTURE = 0x08U,    /*!< Edge aligned PWM and input capture */
} ftm_config_mode_t;

status_t FTM_DRV_InitCounter(uint32_t instance, const ftm_timer_param_t * timer);
typedef struct
{
    ftm_config_mode_t mode;                 /*!< FTM mode */
    uint16_t initialValue;                  /*!< Initial counter value */
    uint16_t finalValue;                    /*!< Final counter value */
} ftm_timer_param_t;

error_t spiInit(void);
error_t spiSetMode(uint_t mode);
error_t spiSetBitrate(uint_t bitrate);
void spiAssertCs(void);
void spiDeassertCs(void);
uint32_t spiTransfer(uint8_t data);

//SPI driver abstraction layer
typedef error_t (*SpiInit)(void);
typedef error_t (*SpiSetMode)(uint_t mode);
typedef error_t (*SpiSetBitrate)(uint_t bitrate);
typedef void (*SpiAssertCs)(void);
typedef void (*SpiDeassertCs)(void);
typedef uint32_t (*SpiTransfer)(uint8_t data);

#define PIN_0     0
#define PIN_1     1
#define PIN_2     2
#define PIN_3     3
#define PIN_4     4
#define PIN_5     5
#define PIN_6     6
#define PIN_7     7
#define PIN_8     8
#define PIN_9     9
#define PIN_10    10
#define PIN_11    11
#define PIN_12    12
#define PIN_13    13
#define PIN_14    14
#define PIN_15    15
#define PIN_16    16
#define PIN_17    17
#define PIN_18    18
#define PIN_19    19

//**********************************************************************************
// Added for LAN8651_Driver.c to resolve references for the linker

//Store unaligned 32-bit integer (big-endian encoding)
#define STORE32BE(a, p) \
   ((uint8_t *)(p))[0] = ((uint32_t)(a) >> 24) & 0xFFU, \
   ((uint8_t *)(p))[1] = ((uint32_t)(a) >> 16) & 0xFFU, \
   ((uint8_t *)(p))[2] = ((uint32_t)(a) >> 8) & 0xFFU, \
   ((uint8_t *)(p))[3] = ((uint32_t)(a) >> 0) & 0xFFU

   #ifndef MIN
      #define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

//Load unaligned 32-bit integer (big-endian encoding)
#define LOAD32BE(p) ( \
   ((uint32_t)(((uint8_t *)(p))[0]) << 24) | \
   ((uint32_t)(((uint8_t *)(p))[1]) << 16) | \
   ((uint32_t)(((uint8_t *)(p))[2]) << 8) | \
   ((uint32_t)(((uint8_t *)(p))[3]) << 0))
/**
 * @brief SPI driver
 **/

typedef struct
{
   SpiInit init;
   SpiSetMode setMode;
   SpiSetBitrate setBitrate;
   SpiAssertCs assertCs;
   SpiDeassertCs deassertCs;
   SpiTransfer transfer;
} SpiDriver;

/**
 * @brief Structure describing a buffer that spans multiple chunks
 **/
typedef struct
{
   void *address;
   uint16_t length;
   uint16_t size;
} ChunkDesc;

typedef struct
{
   uint_t chunkCount;
   uint_t maxChunkCount;
   ChunkDesc chunk[3];
} NetBuffer;

 size_t netBufferGetLength(const NetBuffer *buffer);
 size_t netBufferRead(void *dest, const NetBuffer *src, size_t srcOffset, size_t length);
 //__mingw_bos_extern_ovr




#if 0
 static inline bool LPSPI_GetStatusFlag(const LPSPI_Type * base,
                                            lpspi_status_flag_t statusFlag)
 {
     return (bool)(((base->SR) >> (uint8_t)statusFlag) & 1U);
 }
 void * memcpy(void * __restrict__ __dst, const void * __restrict__ __src, size_t __n)
 {
   return __builtin___memcpy_chk(__dst, __src, __n, __mingw_bos(__dst, 0));
 }

//#define osMemcpy (p, value, length) (void) memcpy(p, value, length)

 //__mingw_bos_extern_ovr
 void * memset(void * __dst, int __val, size_t __n)
 {
   return __builtin___memset_chk(__dst, __val, __n, __mingw_bos(__dst, 0));
 }
//#define osMemset(p, value, length) (void) memset(p, value, length)

 #ifndef osMemset
   #include <string.h>
   #define osMemset(p, value, length) (void) memset(p, value, length)
#endif

//Copy block of memory
#ifndef osMemcpy
   #include <string.h>
   #define osMemcpy(dest, src, length) (void) memcpy(dest, src, length)
#endif

#endif

 error_t spiInit(void);
 typedef void (*TC6NoIP_On_PlcaStatus)(int8_t idx, bool success, bool plcaStatus);
 struct pbuf {
	 uint8_t test;
	 uint8_t test1;
	};

 typedef struct TC6_t TC6_t;

 typedef struct
 {
     uint8_t ethRxBuf[1516];
     uint8_t mac[6];
     TC6_t *tc6;
     struct pbuf *pbuf;
     TC6NoIP_On_PlcaStatus pStatusCallback;
     uint16_t rxLen;
     bool rxInvalid;
 } TC6Lib_t;

 typedef struct
 {
     TC6Lib_t tc;
     uint32_t magic;
     uint8_t idx;
 } TC6NoIP_t;
#endif /* STUB_H_ */
