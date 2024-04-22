/*
 * stub.h
 *
 *  Created on: Jan 19, 2024
 *      Author: praskumt
 */

#ifndef STUB_H_
#define STUB_H_

// GLoabl Includes
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include "error.h"
#include "StdTypes.h"

// device includes
#include "device_registers.h"
#include "pins_driver.h"
#include "lpspi_hw_access.h"
#include "ftm_common.h"
#include "peripherals_flexTimer_mc_1.h"
#include "peripherals_lpspi_1.h"
#include "tc6-regs.h"
#include "ftm_mc_driver.h"
#include "ftm_hw_access.h"
#include "tc6-regs.h"
#include "TC6.h"


#include "lpspi_master_driver.h"   // included in peripherals_lpspi_1.h
#include "lpspi_slave_driver.h"    // included in peripherals_lpspi_1.h
#include "lpspi_shared_function.h" // included in peripherals_lpspi_1.h
#endif

#include "pcc_hw_access.h"
#include "S32K146.h"

#define usleep(delay) {volatile uint32_t n = delay * 4; while(n > 0) n--;}
#define sleep(delay)  {volatile uint32_t n = delay * 4000; while(n > 0) n--;}
#ifndef FALSE
   #define FALSE 0
#endif

#ifndef TRUE
   #define TRUE 1
#endif



error_t spiInit(void);
void    spiAssertCs(void);
void    spiDeassertCs(void);
uint32_t spiTransfer(uint8_t data);

//SPI driver abstraction layer
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


 typedef void (*TC6NoIP_On_PlcaStatus)(int8_t idx, bool success, bool plcaStatus);

 struct pbuf {
 	/** next pbuf in singly linked pbuf chain */
 	struct pbuf *next;

 	/** pointer to the actual data in the buffer */
 	void *payload;

 	/**
 	 * total length of this buffer and all next buffers in chain
 	 * belonging to the same packet.
 	 *
 	 * For non-queue packet chains this is the invariant:
 	 * p->tot_len == p->len + (p->next? p->next->tot_len: 0)
 	 */
 	uint16_t tot_len;

 	/** length of this buffer */
 	uint16_t len;

 	/** pbuf_type as u8_t instead of enum to save space */
 	uint8_t /*pbuf_type*/ type;

 	/** misc flags */
 	uint8_t flags;

 	/**
 	 * the reference count always equals the number of pointers
 	 * that refer to this pbuf. This can be pointers from an application,
 	 * the stack itself, or pbuf->next pointers from a chain.
 	 */
 	uint16_t ref;
 };

// typedef struct TC6_t TC6_t;

 typedef struct
 {
     uint8_t      ethRxBuf[1516];
     uint8_t      mac[6];
     TC6_t       *tc6;
     struct pbuf *pbuf;
     TC6NoIP_On_PlcaStatus pStatusCallback;
     uint16_t     rxLen;
     bool         rxInvalid;
 } TC6Lib_t;

 typedef struct
 {
     TC6Lib_t  tc;
     uint32_t  magic;
     uint8_t   idx;
 } TC6NoIP_t;


 
 /* STUB_H_ */
