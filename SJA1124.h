//--------------------------------------------------------------------------------------------
// This Header file provides the definitions for all control and status registers of the 1124 LIN controller
// THe initialization values for each of the control registers has been defined below and will be
// used in the initialization methods that will be provided along with this document
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
// Low Power mode
//*******************
// ** set MODE = 0x80
//********************
// The mode register (MODE) is used to reset the SJA1124 and to select Low Power mode.
// Operating modes are described in Section 6.2.
// Address | Bit 7 | Bit  6  | Bit 5  | Bit 4  | Bit 3  | Bit 2  | Bit 1  | Bit 0  |
//  00h    |  RST  |--------------------------- reserved------------------| LPMODE |
//  Default|   1   |    0    |   0    |   0    |    0   |    0   |    0   |    0   |

#define MODE_ADDR                            0x00
#define RESET_CNTRLER                        0b10000000   // reset device
#define LPMODE_LOW_PWR                       0b00000001    // Low Power mode
#define LPMODE_NORMAL                      	 0b00000000    // Normal Mode
//--------------------------------------------------------------------------------------------
//  *********************
// PLLCFG
// THe Zonal Controller will use a 1.832Mhz oscillator, therefore,
//*********************
// ** PLLCFG_ADDR = PLLMULT_20
//*********************
// Address  | Bit 7 | Bit  6  | Bit 5  | Bit 4  | Bit 3  | Bit 2  | Bit 1  | Bit 0 |
//  01h     | ------ reserved------------------| ------------PLLMULT ------------
//  Default |   1   |    0    |   0    |   0   |     1   |    0   |    1   |    0  |

#define PLLCFG_ADDR   0x1
#define PLLMULT_78    0x0 // fclk(PLL)in = 0.4 MHz to 0.5 MHz multiplication factor: M = 78
#define PLLMULT_78    0x0 // fclk(PLL)in = 0.4 MHz to 0.5 MHz multiplication factor: M = 78
#define PLLMULT_65    0x1 // fclk(PLL)in = 0.5 MHz to 0.7 MHz multiplication factor: M = 65
#define PLLMULT_39    0x2 // fclk(PLL)in = 0.7 MHz to 1.0 MHz multiplication factor: M = 39
#define PLLMULT_20    0x3 // fclk(PLL)in = 1.0 MHz to 1.4 MHz multiplication factor: M = 28
#define PLLMULT_20    0x4 // fclk(PLL)in = 1.4 MHz to 1.9 MHz multiplication factor: M = 20
#define PLLMULT_15    0x5 // fclk(PLL)in = 1.9 MHz to 2.6 MHz multiplication factor: M = 15
#define PLLMULT_11    0x6 // fclk(PLL)in = 2.6 MHz to 3.5 MHz multiplication factor: M = 11
#define PLLMULT_8_5   0x7 // fclk(PLL)in = 3.5 MHz to 4.5 MHz multiplication factor: M = 8.5
#define PLLMULT_6_4   0x8 // fclk(PLL)in = 4.5 MHz to 6.0 MHz multiplication factor: M = 6.4
#define PLLMULT_4_8   0x9 // fclk(PLL)in = 6.0 MHz to 8.0 MHz multiplication factor: M = 4.8
#define PLLMULT_3_9   0xA // fclk(PLL)in = 8.0 MHz to 10.0 MHz multiplicatin factor: M = 3.9

//--------------------------------------------------------------------------------------------
// INT 1  Enable Control Register
// Address  Bit 7 | Bit 6  | Bit 5  | Bit 4  | Bit 3  | Bit 2  | Bit 1  | Bit 0  |
//  02h     | ---------reserved---------------| L4WUIE | L3WUIE | L2WUIE | L1WUIE |
//  Default |   0  |    0   |   0    |   0    |    1   |    1   |    1   |    1   |

#define INT1EN_ADDR   0x2
#define L4WUIE_ON     0x1 // LIN 4 wake-up interrupt enable
#define L4WUIE_OFF    0x0 // LIN 4 wake-up interrupt disable
#define L3WUIE_ON     0x1 // LIN 3 wake-up interrupt enable
#define L3WUIE_OFF    0x0 // LIN 3 wake-up interrupt disable
#define L2WUIE_ON     0x1 // LIN 2 wake-up interrupt enable
#define L2WUIE_OFF    0x0 // LIN 2 wake-up interrupt disable
#define L1WUIE_ON     0x1 // LIN 1 wake-up interrupt enable
#define L1WUIE_OFF    0x0 // LIN 1 wake-up interrupt disable

//--------------------------------------------------------------------------------------------
// INT 2 Enable Control Register
// Address  | Bit 7 | Bit  6  | Bit 5  | Bit 4  | Bit 3  | Bit 2  | Bit 1  | Bit 0   |
//  03h     |----reserved-----| OTWIE  |PLLOLIE |PLLILIE |PLLIFFIE| SPIEIE | reserved|
//  Default |   0   |    0    |   0    |   0    |    0   |    0   |    0   |    0    |

#define INT2EN_ADDR   0x3

#define OTWIE_ON      0b00100000 // overtemperature warning interrupt enable
#define OTWIE_OFF            0x0 // overtemperature warning  interrupt disable
#define PLLOLIE_ON    0b00010000 // PLL out-of-lock interrupt enable
#define PLLOLIE_OFF          0x0 // PLL out-of-lock interrupt disable
#define PLLILIE_ON    0b00001000 // PLL in-lock  interrupt enable
#define PLLILIE_OFF          0x0 // PLL in-lock  interrupt disable
#define L1WUIE_ON     0b00000100 // PLL input frequency fail  interrupt enable
#define L1WUIE_OFF           0x0 // PLL input frequency fail  interrupt disable
#define SPIEIE_ON     0b00000010 // SPI error interrupt enable
#define SPIEIE_OFF           0x0 // SPI error interrupt disable

//--------------------------------------------------------------------------------------------
//Interrupt register 3 (INT 3) provides LIN commander controller status information.
//When set, LxEI bits indicate that a LIN error status interrupt has been generated (if
//enabled; see Section 6.10.7.2) and can be identified via the respective LES register (see
//Table 42). Bits LxSI are set to indicate that a LIN status interrupt has been generated
//(if enabled; see Section 6.10.7.3) in the associated LS register (see Table 43). INT 3
//is a read-only register. Interrupts are cleared by writing 1 to the associated LES or LS
//register.
// INT3EN Enable Control Register
// Address  | Bit 7 | Bit  6 | Bit 5  | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
//  04h     | L4EIE |  L3EIE | L2EIE  | L1EIE |L4SIE  | L3SIE | L2SIE | L1SIE |
//  Default |   0   |    0   |   0    |   0   |    0  |    0  |    0  |    0  |

#define INT3EN_ADDR   0x4

#define L4EIE_EN      0b10000000    // LIN 4 controller error interrupt enable
#define L3EIE_EN      0b01000000    // LIN 3 controller error interrupt enable
#define L2EIE_EN      0b00100000    // LIN 2 controller error interrupt enable
#define L1EIE_EN      0b00010000    // LIN 1 controller error interrupt enable

#define L4SIE_EN      0b00001000    // LIN 4 controller status interrupt enable
#define L3SIE_EN      0b00000100    // LIN 3 controller status interrupt enable
#define L2SIE_EN      0b00000010    // LIN 2 controller status interrupt enable
#define L1SIE_EN      0b00000001    // LIN 1 controller status interrupt enable
//--------------------------------------------------------------------------------------------

// INT1 Status Register
// Address  | Bit 7 | Bit  6  | Bit 5  | Bit 4  | Bit 3  | Bit 2  | Bit 1 | Bit 0 |
//  10h     | INITI |-------reserved------------| L4WUI  | L3WUI  | L2WUI | L1WUI |
//  Default |   1   |    0   |   0    |   0     |    0   |    0   |    0  |    0  |
#define INT1_STATUS_ADDR 0x10
#define INITI_MASK       0b10000000
#define L4WUI_MASK       0b00001000  // LIN 4 wake-up interrupt status mask
#define L3WUI_MASK       0b00000100  // LIN 3 wake-up interrupt status mask
#define L2WUI_MASK       0b00000010  // LIN 2 wake-up interrupt status mask
#define L1WUI_MASK       0b00000001  // LIN 1 wake-up interrupt status mask
//--------------------------------------------------------------------------------------------
// INT2 Status Register
// Interrupt status bits are cleared by writing 1; writing 0 has no effect.
// Address  | Bit 7 | Bit  6  | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
//  11h     |----reserved-----| OTWI  |PLLOLI |PLLILI |PLLIFFI| SPIEI | LPRFI |
//  Default |   0   |    0    |   0   |   0   |   0   |   0   |    0  |    0  |

#define INT2_STATUS_ADDR   0x11

#define OTWI_MASK      0b00100000  // overtemperature warning interrupt status
#define PLLOLI_MASK    0b00010000  // PLL out-of-lock interrupt status
#define PLLILI_MASK    0b00001000  // PLL in-lock interrupt status
#define L1WUI_MASK     0b00000100  // PLL input frequency fail interrupt status
#define SPIEI_MASK     0b00000010  // SPI error interrupt status
#define LPRFI_MASK     0b00000001  // low power request fail interrupt
//--------------------------------------------------------------------------------------------
// INT3EN Status Register
// Interrupts are cleared by writing 1 to the associated LES or LS register.
// Address  | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
//  12h     | L4EI  | L3EI  | L2EI  | L1EI  | L4SI  | L3SI  | L2SI  | L1SI  |
//  Default |   0   |    0  |   0   |   0   |   0   |   0   |    0  |    0  |
#define INT3EN_ADDR   0x12

#define L4EIE_MASK      0b10000000 // LIN 4 controller error interrupt status
#define L3EIE_MASK      0b01000000 // LIN 3 controller error interrupt status
#define L2EIE_MASK      0b00100000 // LIN 2 controller error interrupt status
#define L1EIE_MASK      0b00010000 // LIN 1 controller error interrupt status

#define L4SIE_MASK      0b00001000 // LIN 4 controller status interrupt
#define L3SIE_MASK      0b00000100 // LIN 3 controller status interrupt
#define L2SIE_MASK      0b00000010 // LIN 2 controller status interrupt
#define L1SIE_MASK      0b00000001 // LIN 1 controller status interrupt
//--------------------------------------------------------------------------------------------
// STATUS Register (Read only)
// Address  | Bit 7 | Bit 6   | Bit 5 | Bit 4   | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
//  13h     |----reserved-----|  OTW  |reserved | PLLIL | PLLIFF| -- reserved --|

#define STATUS_REG_ADDR   0x13

#define OTW_MASK            0b00100000  //overtemperature warning
#define PLLIL_MASK          0b00001000  // PLL lock status
#define PLL_IN_LOCK         0x1         // PLL in lock
#define PLL_NOT_IN_LOCK     0x0         // PLL Not in lock

#define PLLIFF_MASK         0b00000100  // PLL input frequency fail status
#define PLL_INPUT_FREQ_FAIL 0x1         // PLL input frequency failure (outside defined range)
#define PLL_INPUT_FREQ_OK   0x0         // PLL input frequency ok (within defined range)


//--------------------------------------------------------------------------------------------
// LIN communication  registers	LCOM1
// LIN high-speed mode can be enabled to support baud rates higher than 20 kBd (see
// section Section 6.2.3.4) via bits LxHS in the LIN commander controller communication
// register 1 (LCOM1). Pin TMF can be enabled per LIN channel via bits LxTMFE for
// synchronous LIN header transmission (see Section 6.4).
// LIN header transmission can be synchronized across multiple SJA1124 devices. A rising
// edge on pin TMF triggers the start of a synchronous LIN header transmission (when the
// function is enabled). The minimum LOW and HIGH TMF pulse widths needed to trigger
// transmission are, respectively, ttmf(L) and ttmf(H).
// Note: once LIN header transmission has been triggered via pin TMF, additional
// TMF trigger pulses should not be applied until the LIN frame transmission has been
// completed. Otherwise, a second LIN frame transmission might be triggered in error.
// Synchronous LIN frame transmission is enabled for a LIN channel by setting the relevant
// LxTMFE bit in the LCOM1 register (Table 25).
// If synchronous LIN header transmission is only needed for one SJA1124 device, it can
// be enabled per LIN channel via bits LxHTRQ in the LCOM2 register (Table 26). Pin TMF
// does not need to be activated in this case.
// Note: after setting bit LxHTRQ, it should not be set again until LIN frame transmission
// has been completed. Otherwise, a second LIN frame transmission might be triggered in
// error.
// Address | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3  | Bit 2  | Bit 1  | Bit 0  |
//  20h    | L4HS  | L3HS  | L2HS  | L1HS  | L4TMFE | L3TMFE | L2HTRQ | L1HTRQ |
//  Default|   0   |    0  |   0   |   0   |    0   |    0   |    0   |    0   |

#define LCOM1_ADDR   0x20
#define LIN4_HI_SPD_MASK      0b10000000  // LIN 4 high-speed mode
#define LIN3_HI_SPD_MASK      0b01000000  // LIN 3 high-speed mode
#define LIN2_HI_SPD_MASK      0b00100000  // LIN 2 high-speed mode
#define LIN1_HI_SPD_MASK      0b00010000  // LIN 1 high-speed mode
#define ENABLE_HI_SPEED       1
#define DISABLE_HI_SPEED      0

#define LIN4_TRANS_FRM_EN      0b00001000    // LIN 4 transmit frame input (TMF) enable
#define LIN3_TRANS_FRM_EN      0b00000100    // LIN 3 transmit frame input (TMF) enable
#define LIN2_TRANS_FRM_EN      0b00000010    // LIN 2 transmit frame input (TMF) enable
#define LIN1_TRANS_FRM_EN      0b00000001    // LIN 1 transmit frame input (TMF) enable

//--------------------------------------------------------------------------------------------
//LIN communication  register 2
// Bits LxHTRQ in table LCOM2 are used to initiate LIN header transmission.
// Address | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3  | Bit 2  | Bit 1  | Bit 0  |
//  21h    | ---------reserved-------------| L4HTRQ | L3HTRQ | L2HTRQ | L1HTRQ |
//  Default| ---------reserved-------------|    0   |    0   |    0   |    0   |
// ************************************
// set LCOM2_ADDR = LIN1_HEADER_TRANS_REQ
// **********************************

#define LCOM2_ADDR   0x21
#define LIN4_HEADER_TRANS_REQ  0b00001000    // LIN 4 header transmission request
#define LIN3_HEADER_TRANS_REQ  0b00000100    // LIN 3 header transmission request
#define LIN2_HEADER_TRANS_REQ  0b00000010    // LIN 2 header transmission request
#define LIN1_HEADER_TRANS_REQ  0b00000001    // LIN 1 header transmission request


//------------------------------------------------------------
// LIN channel send frame registers

// LIN configuration registers 1
// LIN configuration register 1 (LCFG1) is used to select the operating mode, configure the
// LIN commander break length and to enable/disable the hardware checksum.
// Address          | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3  | Bit 2    | Bit 1  | Bit 0  |
//  30h 60h 90h C0h | CCD   | ---------------MBL ------------| reserved | SLEEP  | INIT   |
//  Default         |   0   |    0  |   0   |   0   |    0   |    0     |    1   |    0   |
// ************************************
// set LCFG1 = HW_CHK_SUM_ENABLE + LCFG1_MBL_10BITS +  LIN_NORMAL_MODE + LIN_INIT_MODE = 0x02
// **********************************

#define LIN1_LCFG1       0x30
#define LIN2_LCFG1       0x60
#define LIN3_LCFG1       0x90
#define LIN4_LCFG1       0xC0
#define LCFG1_CHK_CAL_MASK 0b10000000  // checksum calculation mask
#define HW_CHK_SUM_DISABLE 0b10000000  // Disable Hardware checksum calculation
#define HW_CHK_SUM_ENABLE         0x0  // Enable Hardware checksum calculation

#define LCFG1_MBL_MASK   0b01111000 // LIN commander break length
#define LCFG1_MBL_10BITS (0x0 < 3)  // Break length = 10 Bits
#define LCFG1_MBL_11BITS (0x1 < 3)  // Break length = 11 Bits
#define LCFG1_MBL_12BITS (0x2 < 3)  // Break length = 12 Bits
#define LCFG1_MBL_13BITS (0x3 < 3)  // Break length = 13 Bits
#define LCFG1_MBL_14BITS (0x4 < 3)  // Break length = 14 Bits
#define LCFG1_MBL_15BITS (0x5 < 3)  // Break length = 15 Bits
#define LCFG1_MBL_16BITS (0x6 < 3)  // Break length = 16 Bits
#define LCFG1_MBL_17BITS (0x7 < 3)  // Break length = 17 Bits
#define LCFG1_MBL_18BITS (0x8 < 3)  // Break length = 18 Bits
#define LCFG1_MBL_19BITS (0x8 < 3)  // Break length = 19 Bits
#define LCFG1_MBL_20BITS (0xA < 3)  // Break length = 20 Bits
#define LCFG1_MBL_21BITS (0xB < 3)  // Break length = 21 Bits
#define LCFG1_MBL_22BITS (0xC < 3)  // Break length = 22 Bits
#define LCFG1_MBL_23BITS (0xD < 3)  // Break length = 23 Bits
#define LCFG1_MBL_36BITS (0xE < 3)  // Break length = 36 Bits
#define LCFG1_MBL_50BITS (0xF < 3)  // Break length = 50 Bits

#define LCFG1_MODE_SELECT 0b00000010       // LIN mode select
#define LIN_SLEEP_MODE    0b00000010
#define LIN_NORMAL_MODE   0
#define LCFG1_INIT_MASK   0b00000001       // LIN initialization Request
#define LIN_INIT_MODE     0b00000001
//------------------------------------------------------------

//LIN configuration registers 2
// Address          | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3  | Bit 2 | Bit 1 | Bit 0 |
// 31h 61h 91h C1h  | TBDE  | IOBE  | -------------------reserved--------------------|
//  Default         |   0   |    0  |   0   |   0   |   0   |   0    |    0  |    0  |

#define LIN1_LCFG2 	    0x31
#define LIN2_LCFG2 	    0x61
#define LIN3_LCFG2 	    0x91
#define LIN4_LCFG2 	    0xC1
#define LCFG2_TBDE_MASK      0b10000000 // 2-bit delimiter mask
#define LCFG2_2BIT_DELIM     0x1        // 2-bit delimiter
#define LCFG2_IOBE_MASK      0b01000000 // idle on bit error mask
#define LCFG2_BIT_ERR_RST    0x1        // bit error resets LIN state machine
#define LCFG2_NO_BIT_ERR_RST 0x0        // bit error does not resets LIN state machine
//------------------------------------------------------------

// LIN idle timeout control register
// Address          | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3  | Bit 2 | Bit 1|  Bit 0   |
// 32h 22h 92h C2h  |  -------------------reserved-------------------|  IOT | reserved |
//  Default         |   0   |    0  |   0   |   0   |   0   |   0    |   1  |    0     |

#define LIN1_LITC      0x32
#define LIN2_LITC      0x22
#define LIN3_LITC      0x92
#define LIN4_LITC      0xC2
#define LCFG2_IOT_MASK         0b00000010  // idle on timeout mask
#define LCFG2_IDLE_TIMEOUT_RST 0b00000010  // idle on timeout resets LIN state machine
//------------------------------------------------------------

// LIN global control register
// The LIN global control register (LGC) provides the option to extend the number of stop
// bits (STOP) and to initiate a soft reset (SR).
// STOP determines the number of stop bits in the transmitted data. The STOP bit is
// configured for all fields (Delimiter, Sync, ID, Checksum and payload). Setting bit SR to
// 1 executes a soft reset of the LIN commander controller (FSMs, timers, status and error
// registers) without modifying the configuration registers. All LS and LES status bits are
// reset by a soft reset.
// Address          | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3  | Bit 2 | Bit 1  |  Bit 0 |
// 33h 63h 93h C3h  |  -------------------reserved-------------------|  STOP  |    SR  |
//  Default         |   0   |    0  |   0   |   0   |   0   |   0    |   0    |    0   |

#define LIN1_LGC       0x33
#define LIN2_LGC       0x63
#define LIN3_LGC       0x93
#define LIN4_LGC       0xC3

#define LCFG2_STOPBIT_MASK  0b00000010  // stop bit configuration
#define LCFG2_2STOP_BITS           0x1  // 2 stop bits
#define LCFG2_1STOP_BIT            0x0  // 1 stop bit

#define LCFG2_SR_MASK       0b00000001  // LIN controller soft reset control
#define LCFG2_SOFT_RESET_EN        0x1  // perform soft reset
#define LCFG2_NO_SOFT_RESET        0x0  // perform soft reset

//--------------------------------------------------------------------------------------------

// LIN global control register
// The RTO field in the LIN response timeout control register (LRTC) defines the time limit
// for receiving the complete LIN frame response (including checksum). The time base for
// the timeout timer is bit time tbit, the nominal time required to transmit one bit.
// The timer starts at the end of the LIN frame header (i.e. at the end of the stop bit of the
// protected identifier field).
//     Tresponse_max = RTO x (DFL + 2) x Tbit = RTO/10 x Tresponse_min
// Address          | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3  | Bit 2 | Bit 1 |  Bit 0 |
// 34h 64h 94h C4h  |  -------------------reserved--| ---------------RTO -----------  |
// Default          |   0   |    0  |   0   |   0   |   1  |   1    |   1    |    0   |
// ************************
// Baud Rate expected = 10,000
// Tbit = 1/10000 = 100 usec
// Tresponse_max = 14 * 100 usec * ((8 bytes -1) + 2) = 12.6 msec
//*************************
#define LIN1_LRTC         0x34
#define LIN2_LRTC         0x64
#define LIN3_LRTC         0x94
#define LIN4_LRTC         0xC4
#define LCFG2_RTO_MASK    0x0F  // response timeout time - The reset value is 0Eh = 14, corresponding to tRESPONSE_MAX = 1.4 x tRESPONSE_MIN
//--------------------------------------------------------------------------------------------

//The LIN baud rate is specified as an unsigned fixed-point number. The mantissa is coded
//as a 16-bit integer value (IBR) and the fraction is coded as a 4-bit fractional value (FBR).
//IBR is split between two registers: the LIN baud rate generator MSB register (LBRM;
//Table 33) contains the 8 most significant bits; the LIN baud rate generator LSB register
//(LBRL; Table 34) contains the 8 least significant bits.
//FBR is defined in the LIN fractional register (LFR; Table 32).
//The output frequency of the baud rate generator is 16 times the baud rate. The input
//frequency of the baud rate generator is the PLL output clock frequency fclk(PLL)out.
//The baud rate can be calculated from the following formula:
// The baud rate deviation (ΔBR) from the nominal baud rate (BRnom) depends on the PLL
// output clock frequency and the nominal baud rate. The baud rate deviation (ΔBR) can be
// calculated from the nominal baud rate (BRnom) using the following equation
// LIN fractional register
// Address          | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3  | Bit 2    | Bit 1  |  Bit 0 |
// 35h 65h 95h C5h  |  -------------------reserved--| ---------------FBR ---------------  |
// Default          |   0   |    0  |   0   |   0   |   1  |   1    |   1    |    0   |
// ********************************************************************
// baudrate = Fclk(PLLOUT) / (16 * IBR) + FBR)  = 65 * 500000/ ((16 * IBR) + FBR)) = 20000
//                                              = 32500000 /20000 = (16 * IBR) + FBR = 1625 /16 = IBR + FBR/16 = 101.56  ||
//                                               IBR = 101 = 0x65
//                                               LIN1_BAUD_RATE_MSB_B1 (LBRM) = 0x00
//                                               LIN1_BAUD_RATE_MSB_B0 (LBRL) = 0x65
//                                               LIN1_BAUD_FRACTION (FBR) = 3.5 = 4
// ********************************************************************

#define LIN1_BAUD_FRACTION       0x35
#define LIN2_BAUD_FRACTION       0x65
#define LIN3_BAUD_FRACTION       0x95
#define LIN4_BAUD_FRACTION       0xC5
#define LCFG2_FRCTION_BAUD_RATE_MASK    0x0F  // fractional baud rate
//------------------------------------------------------------

// LIN baud rate generator LBRM register
// Address          | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3  | Bit 2 | Bit 1 |  Bit 0 |
// 36h 66h 96h C6h  |  --------------------------IBR[15:7]--------------------------  |
// Default          |   0   |    0  |   0   |   0   |   0   |   0    |   0   |    0   |
#define LIN1_BAUD_RATE_MSB_B1      0x36
#define LIN2_BAUD_RATE_MSB_B1      0x66
#define LIN3_BAUD_RATE_MSB_B1      0x96
#define LIN4_BAUD_RATE_MSB_B1      0xC6
//------------------------------------------------------------

// LIN baud rate generator LBRL  MSB register
// Address          | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2  | Bit 1 |  Bit 0 |
// 37h 67h 97h C7h  |  --------------------------IBR[7:0]---------------------------- |
// Default          |   0   |    0  |   0   |   0   |   0   |   0    |   0   |    0   |
#define LIN1_BAUD_RATE_MSB_B0      0x37
#define LIN2_BAUD_RATE_MSB_B0      0x67
#define LIN3_BAUD_RATE_MSB_B0      0x97
#define LIN4_BAUD_RATE_MSB_B0      0xC7

//------------------------------------------------------------

// LIN commander interrupt enable register
// The LIN interrupt enable register (LIE) is used to enable the LIN commander controller
// interrupt sources. The status of the interrupts can be read from the LIN error status
// register (LES) and LIN status register (LS).
// Address           | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3    | Bit 2 | Bit 1 | Bit 0  |
//   38h 68h 98h C8h | SZIE  | TOIE  | BEIE  | CEIE  | reserved | DRIE  | DTIE  | FEIE   |
//    Default        |   0   |    0  |   0   |   0   |   0      |   0   |   0   |    0   |

#define LIN1_INTR_EN   0x38
#define LIN2_INTR_EN   0x68
#define LIN3_INTR_EN   0x98
#define LIN4_INTR_EN   0xC8

#define LSZIE_EN     0b10000000  // stuck-at-zero interrupt enable; generated when SZF flag in LES register (Table 42; bit 7) is set
#define TOIE_EN      0b01000000  // timeout interrupt enable; generated when TOF flag in LES register (Table 42; bit 6) is set
#define BEIE_EN      0b00100000  // bit error interrupt enable; generated when BEF flag in LES register (Table 42; bit 5) is set
#define CEIE_EN      0b00010000  // checksum error interrupt enable; generated when CEF flag in LES register (Table 42; bit 4) is set

#define DRIE_EN      0b00000100  // data reception complete interrupt enable; generated when DRF flag in LS register (Table 43, bit 1) is set
#define DTIE_EN      0b00000010  // data transmission complete interrupt enable; generated when DTF flag in LS register (Table 43, bit 1) is set
#define FEIE_EN      0b00000001  // frame error interrupt enable; generated when FEF flag in LES register (Table 42; bit 0) is set
//------------------------------------------------------------

// LIN control registers (LC)
// A wake-up request is generated by writing the wake-up character to LIN buffer data
// register 1 (LBD1; see Section 6.10.6.5) and setting bit WURQ to 1. The data written to
// LBDx is transmitted when WURQ is set. The current LIN frame transmission can be
// aborted by setting bit ARBQ. A LIN header transmission is initiated by setting bit HTRQ.
// If bit DIR in register LBC is set (see Table 38), the LIN frame response transmission
// follows automatically.
// Address   LC      | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3  | Bit 2 | Bit 1 | Bit 0  |
//   39h 69h 99h C9h | ------- reserved -----| WURQ  | --reserved --- | ABRQ  | HTRQ   |
//    Default        |   0   |    0  |   0   |   0   |   0      |  0  |   0   |    0   |
// **************************
// LIN1_INTR_EN = WAKE_UP_REQ + HEADER_RX_REQ
// **************************
#define LIN1_INTR_EN   0x39
#define LIN2_INTR_EN   0x69
#define LIN3_INTR_EN   0x99
#define LIN4_INTR_EN   0xC9

#define WAKE_UP_REQ    0b00010000  // abort the current transmission or wake-up; aborts at the end of current bit
#define ABORT_TX_WAKE  0b00000010  // abort the current transmission or wake-up; aborts at the end of current bit
#define HEADER_RX_REQ  0b00000001  // Generate LIN header transmission

//------------------------------------------------------------
// LIN buffer identifier registers
// The LIN buffer identifier registers contain the LIN frame identifiers.
//  Address  LSTATE     | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3  | Bit 2 | Bit 1 | Bit 0  |
//   3Ah, 6Ah, 9Ah, CAh | --- reserved- |----------------- ID --------------- ------------|
//***************************
//  LIN1_ID = 0b00101010
//***************************
#define LIN1_ID   0x3A
#define LIN2_ID   0x6A
#define LIN3_ID   0x9A
#define LIN4_ID   0xCA

//------------------------------------------------------------
// LIN buffer identifier registers
// The LIN buffer control registers are used to configure the LIN checksum version (classic
// or enhanced), the LIN message response direction (from commander to responder or
// vice versa) and the data field length (number of data bytes to be transferred).
//  Address  LSTATE     | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3  | Bit 2 | Bit 1 | Bit 0  |
//   3Bh, 6Bh, 9Bh, CBh | ------ reserved------ |--------DFL ------------|  DIR  |  CCS   |
//***************************
//  LIN1_BUF_CTRL = 0b0001111
//***************************

#define LIN1_BUF_CTRL   0x3B
#define LIN2_BUF_CTRL   0x6B
#define LIN3_BUF_CTRL   0x9B
#define LIN4_BUF_CTRL   0xCB


//------------------------------------------------------------
// LIN State registers
//  Address  LSTATE  | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3    | Bit 2 | Bit 1 | Bit 0  |
//   4Fh 7Fh AFh DFh | RXBSY | ------- reserved----- |----------------- LINS ------------|

#define LIN1_LSTATE   0x4F
#define LIN2_LSTATE   0x7F
#define LIN3_LSTATE   0xAF
#define LIN4_LSTATE   0xDF

#define RXBSY_MASK     0b10000000 // receiver busy flag
#define RX_ONGOING     0x1        // reception ongoing
#define RX_IDLE        0x0        // reception Idle
#define LINSTATE_MASK  0x0F       // LIN State

uint8 LIN1_State;
uint8 LIN2_State;
uint8 LIN3_State;
uint8 LIN4_State;

#define SLEEP         0x00       // Sleep Mode
#define INIT          0x01       // receiver busy flag
#define IDLE          0x02       // receiver busy flag
#define SYNC_BRK_TX   0x03       // receiver busy flag
#define SYNC_DELIM_TX 0x04       // receiver busy flag
#define SYNC_FIELD_TX 0x05       // receiver busy flag
#define ID_TX         0x06       // receiver busy flag
#define HEADER_TX     0x07       // receiver busy flag
#define RX_ONGOING    0x08       // receiver busy flag
#define CHECKSUM_TXRX 0x09       // receiver busy flag
//------------------------------------------------------------


// The LIN error status registers (LES) contains a number of interrupt sources.
// If a dominant pulse lasts for 100 bits or more, bit SZF is set. If the same dominant pulse
// persists, subsequent SZF settings will be 87 bit times apart (instead of 100 bit times).
// An interrupt is generated (bit LxEI in INT3 = 1; see Table 23) if bits SZIE in LIE (see
// Table 35) and LxEIE in INT3EN (see Table 20) are set to enable the interrupt
// The TOF error flag is set when the response timeout value (RTO) is exceeded. The LIN
// state machine resets to Idle state when this bit and bit IOT in LITC (Table 29) are set. An
// LxEI interrupt is generated if bit TOIE in LIE and LxEIE in INT3EN are set.
// The BEF error flag is set in transmission mode when the value read back from the
// bus is different from the value transmitted. Bit error is not checked during break field
// transmission. Transmission of the frame is stopped after the corrupted bit is detected
// if the IOBE bit in LCFG2 (Table 28) is set. If IOBE is reset, the transmitter continues
// to transmit in spite of the bit error. An LxEI interrupt is generated if bit BEIE in LIE and
// LxEIE in INT3EN are set.
// The CEF error flag is set when the checksum computed by hardware does not match the
// received checksum. The received frame is discarded and the LIN commander controller
// returns to idle state. An LxEI interrupt is generated if bits CEIE in LIE and LxEIE in
// INT3EN are set.
// The FEF error flag is set when a dominant state is sampled on a stop bit of the currently
// received character (sync field, identifier field, data field, checksum field). The received
// frame is discarded and the LIN commander controller returns to idle state. An LxEI
// interrupt is generated if bits FEIE in LIE and LxEIE in INT3EN are set.
//
// LIN error status registers
//  Address         | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3    | Bit 2 | Bit 1 | Bit 0  |
//  50h 80h B0h E0h | SZF   | TOF   | BEF   | CEF   | -------reserved--------  | FEF    |
#define LIN1_ERROR_STAT 	  0x50
#define LIN2_ERROR_STAT 	  0x80
#define LIN3_ERROR_STAT 	  0xB0
#define LIN4_ERROR_STAT 	  0xE0

#define SZF_MASK     0b10000000 // stuck-at-zero timeout error detected
#define TOF_MASK     0b01000000 // timeout interrupt error detected
#define BEF_MASK     0b00100000 // bit error flag
#define CEF_MASK     0b00010000 // checksum error flag

#define FEF_MASK     0b00000001 // framing error (invalid stop bit) detected
//------------------------------------------------------------

// LIN  status registers
// The LIN status registers (LS) reflect the status of the LIN frame transmission. It contains
// two LIN frame transfer status interrupt sources.
//  Address         | Bit 7    | Bit 6  | Bit 5 | Bit 4 | Bit 3    | Bit 2 | Bit 1 | Bit 0    |
//  51h 81h B1h E1h | reserved | DRBNE  | -------reserved-------   | DRF   | DTF   | reserved |
#define LIN1_STATUS  	    	  0x51
#define LIN2_STATUS  	    	  0x81
#define LIN3_STATUS  	    	  0xB1
#define LIN4_STATUS  	    	  0xE1
#define DATA_BUF_NOT_EMPTY_MASK   0b01000000 // data reception buffer not empty flag
#define FIRST_BYTE_RX     	   	  1
#define DATA_RX_CMP_MASK  	   	  0b00000100 // data reception complete flag
#define DATA_RX_CMP       	   	  1
#define DATA_TX_CMP_MASK  	   	  0b00000010 // data transmission complete flag
#define DATA_TX_CMP               1
//-------------------------------------------------------------------------------------------------

// LIN  checksum field registers
// When the LIN commander controller is transmitting the LIN frame response fields (DIR =
// 1), the checksum value to be transmitted onto the LIN bus is stored in the LCF register.
// When the LIN commander controller is receiving the response fields (DIR = 0), the
// checksum received from the responder is stored in the LCF register.
// If the checksum calculation disable bit (CCD) in LIN configuration register 1 (LCFG1) is
// 0, LCF is read only. If CCD is logic 1, write access to the LCF register is enabled and the
// checksum must be allocated by the microcontroller.
// The LCF checksum data can be accessed via two addresses to support send frame and
// get status requests via a single SPI access. The register mapping is listed in Table 8
// (LCF; 3Ch, 6Ch, 9Ch, CCh) and Table 9 (LCF; 52h, 82h, B2h, E2h). For example, the
// LCF register addresses of LIN channel 2 are 6Ch and 82h.
//  Address         | Bit 7    | Bit 6  | Bit 5 | Bit 4 | Bit 3  | Bit 2 | Bit 1 | Bit 0  |
//  52h 82h B2h E2h | -----------------------------CF----------------------------------   |

#define LIN1_CHKSUM   0x52
#define LIN2_CHKSUM   0x82
#define LIN3_CHKSUM   0xB2
#define LIN4_CHKSUM	  0xE2
//-------------------------------------------------------------------------------------------------

// // LIN buffer data registers
// The LIN buffer data registers are used to allocate LIN data bytes for LIN
// transmission or to read LIN bytes after a LIN message response has been received.
// Each register can be accessed via two addresses to support send frame and get status
// requests via a single SPI access. The register mapping is listed in Table 8 (LBD1 to
// LBD8; 3D to 44h, 6D to 74h, 9D to A4h, CD to D4h) and Table 9 (LBD1 to LBD8; 53 to
// 5Ah, 83 to 8Ah, B3 to BAh, E3 to EAh). For example, the LBD2 register addresses of LIN
// channel 3 are 9Eh and B4h.
//
// Address               | Bit 7    | Bit 6  | Bit 5 | Bit 4 | Bit 3  | Bit 2 | Bit 1 | Bit 0  |
//  53h 83h B3h E3h LBD1 | -----------------------------DATA0----------------------------------|
//  54h 84h B4h E4h LBD2 | -----------------------------DATA1----------------------------------|
//  55h 85h B5h E5h LBD3 | -----------------------------DATA2----------------------------------|
//  56h 86h B6h E6h LBD4 | -----------------------------DATA3----------------------------------|
//  57h 87h B7h E7h LBD5 | -----------------------------DATA4----------------------------------|
//  58h 88h B8h E8h LBD6 | -----------------------------DATA5----------------------------------|
//  59h 89h B9h E9h LBD7 | -----------------------------DATA6----------------------------------|
//  5Ah 8Ah BAh EAh LBD8 | -----------------------------DATA7----------------------------------|
// A LIN frame transmission is initiated by setting the LIN header transmission request bit
// (HTRQ) in the LIN control register (LC; Table 36). On receiving a header transmission
// request, the LIN commander controller transmits a LIN frame header, which includes
// break, sync and protected identifier fields. Depending on the state of the data direction
// bit (DIR) in the LIN buffer control register (LBC; Table 38), the LIN commander controller
// either transmits the LIN frame response (DIR = 1: LIN commander transmits, LIN
// responder receives) or expects to receive the LIN frame response from a LIN responder
// (DIR = 0: LIN responder transmits; LIN commander receives).
// When the LIN commander controller transmits the LIN frame response, the data fields
// stored in the LIN buffer data registers (LBDx; see Table 40) are transmitted automatically.
// The data field length (DFL) to be transmitted is configured in the LBC register. Finally, the
// checksum is transmitted. Depending on the CCD bit in the LIN configuration 1 register
// (LCFG1; Table 27), the checksum is either hardware-generated or needs to be stored in
// the LIN checksum field register (LCF; Table 39) by the user. If the checksum is generated
// automatically, the checksum type (enhanced or classic) can be configured via the CCS
// bit in the LBC register.
// Once LIN header transmission begins, the user should not modify register bits in the LIN
// buffer identifier (LBI; Table 37) and LIN buffer control (LBC; Table 38) registers until the
// frame transmission has been completed. The transmitted LIN frame identifier and data
// are also received by the LIN commander controller and copied, respectively, to LBI and LBDx.

uint8 LIN1_Data_Frame[8];
uint8 LIN2_Data_Frame[8];
uint8 LIN3_Data_Frame[8];
uint8 LIN4_Data_Frame[8];

#define	LIN1_LBD1	  0x53
#define LIN1_LBD2	  0x54
#define LIN1_LBD3	  0x55
#define LIN1_LBD4	  0x56
#define LIN1_LBD5	  0x57
#define LIN1_LBD6	  0x58
#define LIN1_LBD7	  0x59
#define LIN1_LBD8	  0x5A

#define	LIN2_LBD1	  0x83
#define LIN2_LBD2	  0x84
#define LIN2_LBD3	  0x85
#define LIN2_LBD4	  0x86
#define LIN2_LBD5	  0x87
#define LIN2_LBD6	  0x88
#define LIN2_LBD7	  0x89
#define LIN2_LBD8	  0x8A

#define	LIN3_LBD1	  0xB3
#define LIN3_LBD2	  0xB4
#define LIN3_LBD3	  0xB5
#define LIN3_LBD4	  0xB6
#define LIN3_LBD5	  0xB7
#define LIN3_LBD6	  0xB8
#define LIN3_LBD7	  0xB9
#define LIN3_LBD8	  0xBA

#define	LIN4_LBD1	  0xE3
#define LIN4_LBD2	  0xE4
#define LIN4_LBD3	  0xE5
#define LIN4_LBD4	  0xE6
#define LIN4_LBD5	  0xE7
#define LIN4_LBD6	  0xE8
#define LIN4_LBD7	  0xE9
#define LIN4_LBD8	  0xEA

//-------------------------------------------------------------------------------------------------
// LIN commander pull-up configuration register (MCFG)
// The SJA1124A contains Multiple Time Programmable (MTP) non-volatile memory (NVM)
// cells that allow the default configuration of the LIN commander pull-up to be programmed
// (the NVM registers are read-only in the SJA1124B).
// Programming of the NVM cells is performed in two steps. First, the required values are
// written to the LIN commander pull-up configuration register and, if necessary, the NVM
// status register (Table 12 and Table 13). The CRC value is then written to the NVM CRC
// register (Table 14). If the CRC value is correct, programming is confirmed. Otherwise, the
// operation is aborted. A system reset is generated after a successful NVM programming
// cycle. Note that the NVM cells cannot be read while they are being programmed.
// During NVM programming, the supply voltage must remain within the battery supply
// voltage operating range.
// After an NVM programming cycle has been completed, the non-volatile memory is
// protected against overwriting. Factory preset values, indicated by '*',
// Each LIN channel has a LIN dominant timeout function. This function switches off the
// relevant LIN commander termination resistor, Rcommander or Rcommander(lp), if the LIN
// bus level remains dominant for longer than tto(dom)LIN. LIN termination resistor Rresponder
// remains active as pull-up when Rcommander or Rcommander(lp) is switched off.
// Once the LIN bus level is recessive again, the LIN commander termination is switched on
// and the LIN dominant timeout timer is reset.
// The SJA1124A LIN commander termination is SPI-configurable and consists of a diode and a pull-up resistor of 900 Ω to 1100 Ω, as specified in LIN 2.x,
// ISO 17987-4:2016 (12 V LIN) and SAE J2602-1.
// The SJA1124B LIN commander termination is fixed and consists of a diode and a pull-up resistor of 900 Ω to 1010 Ω.

// Address MCFG | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3    | Bit 2 | Bit 1 | Bit 0  |
//   F0h        | ----M4CFG---  | ----- M3CFG --|----- M2CFG ------|-------M1CFG--- |
#define CMD_TERM_CFG_M4_MASK   0b11000000 // commander termination configuration channel 4
#define CMD_TERM_CFG_M3_MASK   0b00110000 // commander termination configuration channel 3
#define CMD_TERM_CFG_M2_MASK   0b00001100 // commander termination configuration channel 2
#define CMD_TERM_CFG_M1_MASK   0b00000011 // commander termination configuration channel 1

#define	OFF_NORM_LP               0x00  // Off in all states (i.e. terminated with Rresponder)
#define	Rcmd_In_NORM_Off_LP       0x01  // Rcommander in Normal mode and off in Low Power mode; terminated with Rresponder in Low Power mode
#define	Rcmd_In_NORM_RcmdLP_in_LP 0x02  // Rcommander in Normal mode and Rcommander(lp) in Low Power mode (default)
#define	Rcmd_In_NORM_LP           0x03  // Rcommander in Normal and Low Power modes.
//-------------------------------------------------------------------------------------------------

// NVM status register (MMTPS)
// Address MMTPS | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3    | Bit 2 | Bit 1 | Bit 0  |
//   F1h         |  DFR  |  FRS  |----------------------WRCNTS---------------------- |
#define DISABLE_FACT_RESTORE_MASK   0b10000000 // enable/disable facory restore (MTPNVM lock)
#define FACT_RESTORE_ON             0x1        // factory restore function enabled
#define FACT_RESTORE_OFF            0x0        // factory restore function disabled

#define WRITE_COUNT_STAT_MASK       0b000111111 // enable/disable facory restore (MTPNVM lock)
//-------------------------------------------------------------------------------------------------
// NVM CRC control register
// The cyclic redundancy check value stored in the NVM CRC control register (MCFGCRC,
// see Table 14) is calculated using the data written to registers MCFG (address F0h) and
// MMTPS (address F1h).
// The CRC value is calculated using the data representation shown in Figure 7 and the
// modulo-2 division with the generator polynomial: X8 + X5 + X3 +X2 + X + 1. The result of
// this operation must be bitwise inverted.

//******************************************************
// RESTORING FACTORY DEFAULTS
// Factory preset values are restored by writing 00h to register MCFG (Table 12) and then
// writing a correct CRC value to register MCFGCRC (Table 14). A minimum delay of
// tidl(SPI)MTPNVM must be inserted between the two write operations.
// The factory restore operation will be aborted if:
// • the write operation to MCFGCRC starts before the MTPNV SPI idle time (tidl(SPI)MTPNVM) has elapsed.
// • any SPI register access is initiated between the MCFG and MCFGCRC write operations
// • Factory restore is disabled (DFR = 1)
// The SJA1124 performs a system reset after the factory preset values have been restored.
//******************************************************

// Address MCFGCRC | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3    | Bit 2 | Bit 1 | Bit 0  |
//   F2h           |  -------------------------CRC------------------------------------ |
#define	NVM_CRC    0xF2    // cyclic redundancy check control (read/write)

//-------------------------------------------------------------------------------------------------
// Address MTPCS | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3    | Bit 2 | Bit 1 | Bit 0  |
//   FEh         |  -------------------------MTPCS------------------------------------ |
#define	MTPCS    0xFE
//------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Address MTPCS | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3    | Bit 2 | Bit 1 | Bit 0  |
//   FEh         | --Reserved -- |-------------------- ID  ------------------------- |
#define	LIN_DEVICE_ID    0xFF





