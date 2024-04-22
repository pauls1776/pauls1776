
#include "stub.h"

static uint32_t  g_One_ms_Timer_Tick_counter = 0;
static uint32_t  counter = 0;
extern uintptr_t g_context;
extern bool      TC6_HandleMacPhyInterrupt(uint8_t tc6instance);


  lpspi_state_t lpspi_1State;
  extern void PINS_ISR(void);
  static void LPSPI_DRV_MasterCompleteTransfer(uint32_t instance);
  void TC6NoIP_CB_OnEthernetReceive(int8_t idx, const uint8_t *pRx, uint16_t len);
  void TC6Stub_IntPinInterruptEnable(uint8_t idx, bool enableInt);

status_t LPSPI_DRV_MasterInit_Stub(uint32_t instance, lpspi_state_t * lpspiState, const lpspi_master_config_t * spiConfig);

//*************************************************************************
//* Pin Settings
// ******************************************************************************/
pin_settings_config_t spi_pin_mux[5U]= {
      {
        /* SIN pin */
        .base = PORTD,
        .pinPortIdx = 16,
        .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
        .passiveFilter = false,
        .driveSelect = PORT_LOW_DRIVE_STRENGTH,
        .mux = PORT_MUX_ALT4,
        .pinLock = false,
        .intConfig = PORT_DMA_INT_DISABLED,
        .clearIntFlag = false,
      },

      {
        /* SOUT pin */
        .base = PORTB,
        .pinPortIdx = 4,
        .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
        .passiveFilter = false,
        .driveSelect = PORT_LOW_DRIVE_STRENGTH,
        .mux = PORT_MUX_ALT3,
        .pinLock = false,
        .intConfig = PORT_DMA_INT_DISABLED,
        .clearIntFlag = false,
      },

      {
        /* SCK pin */
        .base = PORTD,
        .pinPortIdx = 15,
        .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
        .passiveFilter = false,
        .driveSelect = PORT_LOW_DRIVE_STRENGTH,
        .mux = PORT_MUX_ALT4,
        .pinLock = false,
        .intConfig = PORT_DMA_INT_DISABLED,
        .clearIntFlag = false,

      },

      {
        /* PCS0 pin */
        .base            = PORTB,
        .pinPortIdx      = 5,
        .pullConfig      = PORT_INTERNAL_PULL_NOT_ENABLED,
        .passiveFilter   = false,
        .driveSelect     = PORT_LOW_DRIVE_STRENGTH,
//        .mux             = PORT_MUX_ALT4,                // detach the Chip Select from the SPI hardrware logic so that I can be handled independantly 
        .mux             = PORT_MUX_AS_GPIO,
        .pinLock         = false,
        .intConfig       = PORT_DMA_INT_DISABLED,
        .clearIntFlag    = false,
        .gpioBase        = PTB,
        .direction       = GPIO_OUTPUT_DIRECTION,

      },
	  {
	    .base            = PORTD,                                           // Interrupt line from LAN8651 to MCU - Active low Falling Edge
	    .pinPortIdx      = 12U,
	    .pullConfig      = PORT_INTERNAL_PULL_NOT_ENABLED,
	    .driveSelect     = PORT_LOW_DRIVE_STRENGTH,
	    .passiveFilter   = false,
	    .mux             = PORT_MUX_AS_GPIO,
	    .pinLock         = false,
	    .intConfig       = PORT_INT_FALLING_EDGE,
	    .clearIntFlag    = false,
	    .gpioBase        = PTD,
	    .direction       = GPIO_INPUT_DIRECTION,
	    .digitalFilter   = false,
	    .initValue       = 0U,
	 }
    };


  const lpspi_master_config_t lpspi_0_MasterConfig0_stub = {
    .bitsPerSec =20000UL,
    .whichPcs = LPSPI_PCS0,
    .pcsPolarity = LPSPI_ACTIVE_LOW,
    .isPcsContinuous = false,
    .bitcount = 8U,
    .lpspiSrcClk = 8000000UL,
    .clkPhase = LPSPI_CLOCK_PHASE_2ND_EDGE,
    .clkPolarity = LPSPI_SCK_ACTIVE_LOW,
    .lsbFirst = false,
    .transferType = LPSPI_USING_INTERRUPTS,
    .rxDMAChannel = 0U,
    .txDMAChannel = 0U,
    .callback = NULL,
    .callbackParam = NULL
  };
// Call the SDK code that has been pulled into this file to do initialization. 
//
error_t spiInit(void)
{
  	/* Initialize LPSPI0 (Send)*/

 //   PINS_DRV_Init(5U, spi_pin_mux);
      PINS_DRV_Init(4U, spi_pin_mux);


	LPSPI_DRV_MasterInit_Stub(INST_LPSPI_1, &lpspi_1State, &lpspi_0_MasterConfig0_stub);

    /* Install PORTC_IRQn as PINS interrupt handler */
	INT_SYS_InstallHandler(PORTD_IRQn,&PINS_ISR,(isr_t *)0 );


	PINS_DRV_ClearPinIntFlagCmd(PORTD, (uint32_t) 12);
    INT_SYS_ClearPending(PORTD_IRQn);

  // INT_SYS_EnableIRQ(PORTD_IRQn);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSPI_GetVersionId
 * Description   : Configures the LPSPI for master or slave.
 *
 * Note that the LPSPI module must first be disabled before configuring this.
 *
 *END**************************************************************************/
status_t LPSPI_SetMasterSlaveMode_Stub(LPSPI_Type * base, lpspi_master_slave_mode_t mode)
{
    base->CFGR1 = (base->CFGR1 & (~LPSPI_CFGR1_MASTER_MASK)) | ((uint32_t)mode << LPSPI_CFGR1_MASTER_SHIFT);
    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSPI_SetPcsPolarityMode
 * Description   : Configures the desired LPSPI PCS polarity.
 *
 * This function allows the user to configure the polarity of a particular PCS signal.
 * Note that the LPSPI module must first be disabled before configuring this.
 *
 *END**************************************************************************/
status_t LPSPI_SetPcsPolarityMode_Stub(LPSPI_Type * base, lpspi_which_pcs_t whichPcs,
                                            lpspi_signal_polarity_t pcsPolarity)
{
    uint32_t cfgr1Value = 0;

    /* Clear the PCS polarity bit */
    cfgr1Value = (base->CFGR1) & (~((uint32_t)1U << (LPSPI_CFGR1_PCSPOL_SHIFT + (uint32_t)whichPcs)));

    /* Configure the PCS polarity bit according to the pcsPolarity setting */
    cfgr1Value |= (uint32_t)pcsPolarity << (LPSPI_CFGR1_PCSPOL_SHIFT + (uint32_t)whichPcs);

    base->CFGR1 = cfgr1Value;

    return STATUS_SUCCESS;

}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSPI_DRV_MasterConfigureBus
 * Description   : Configures the LPSPI port physical parameters to access a device on the bus when
 *                 the LSPI instance is configured for interrupt operation.
 *
 * In this function, the term "spiConfig" is used to indicate the SPI device for which the LPSPI
 * master is communicating. This is an optional function as the spiConfig parameters are
 * normally configured in the initialization function or the transfer functions, where these various
 * functions would call the configure bus function.
 * The user can pass in a different spiConfig structure to the transfer function which contains
 * the parameters for the SPI bus to allow for communication to a different SPI device
 * (the transfer function then calls this function). However, the user also has the option to call
 * this function directly especially to get the calculated baud rate, at which point they may pass
 * in NULL for the spiConfig structure in the transfer function (assuming they have called this
 * configure bus function first).
 * Implements : LPSPI_DRV_MasterConfigureBus_Activity
 *
 *END**************************************************************************/
status_t LPSPI_DRV_MasterConfigureBus_Stub(uint32_t instance,
                                            const lpspi_master_config_t * spiConfig,
                                            uint32_t * calculatedBaudRate)
{
    DEV_ASSERT(instance < LPSPI_INSTANCE_COUNT);
    DEV_ASSERT(spiConfig != NULL);
    DEV_ASSERT(g_lpspiStatePtr[instance] != NULL);
    /* Instantiate local variable of type lpspi_state_t and point to global state */
    lpspi_state_t * lpspiState = g_lpspiStatePtr[instance];
    LPSPI_Type *base = g_lpspiBase[instance];
    uint32_t baudRate;

    /* The Transmit Command Register (TCR) Prescale value is calculated as part of the baud rate
       calculation. The value is stored in the run-time state structure for later programming
       in the TCR. */
    uint32_t tcrPrescaleValue;

    /* First, per the spec, we need to disable the LPSPI module before setting the delay */

    if (LPSPI_Disable(base) != STATUS_SUCCESS)
    {
        /* If error is returned, the LPSPI is busy */
        return STATUS_ERROR;
    }

    /* Check the bitcount to make sure it falls within the boundary conditions */
    if ((spiConfig->bitcount < 8U) || (spiConfig->bitcount > 4096U))
    {
        return STATUS_ERROR;
    }

    /* Configure internal state structure for LPSPI */
    lpspiState->bitsPerFrame = spiConfig->bitcount;
    lpspiState->lpspiSrcClk = (uint32_t) 8000000; // spiConfig->lpspiSrcClk;
    lpspiState->isPcsContinuous = spiConfig->isPcsContinuous;
    lpspiState->lsb = spiConfig->lsbFirst;
    /* Save transfer type DMA/Interrupt */
    lpspiState->transferType = spiConfig->transferType;
    /* Update transfer status */
    lpspiState->isTransferInProgress = false;
    lpspiState->isBlocking = false;
    /* Calculate the bytes/frame for lpspiState->bytesPerFrame. */
    lpspiState->bytesPerFrame = (uint16_t)((lpspiState->bitsPerFrame + 7U) / 8U);
    /* Due to DMA limitations frames of 3 bytes/frame will be internally handled as 4 bytes/frame. */
    if (lpspiState->bytesPerFrame == 3U)
    {
        lpspiState->bytesPerFrame = 4U;
    }
    /* Due to some limitations all frames bigger than 4 bytes/frame must be composed only from 4 bytes chunks. */
    if (lpspiState->bytesPerFrame > 4U)
    {
        lpspiState->bytesPerFrame = (((lpspiState->bytesPerFrame - 1U) / 4U) + 1U) * 4U;
    }
    /* Store DMA channel number used in transfer */
    lpspiState->rxDMAChannel = spiConfig->rxDMAChannel;
    lpspiState->txDMAChannel = spiConfig->txDMAChannel;
    /* Store callback */
    lpspiState->callback = spiConfig->callback;
    lpspiState->callbackParam = spiConfig->callbackParam;
    /* Configure the desired PCS polarity */
    (void)LPSPI_SetPcsPolarityMode_Stub(base, spiConfig->whichPcs, spiConfig->pcsPolarity);
    /* Set up the baud rate */
    baudRate = LPSPI_SetBaudRate(base, spiConfig->bitsPerSec, spiConfig->lpspiSrcClk, &tcrPrescaleValue);
    /* Enable sampling point delay */
    LPSPI_SetSamplingPoint(base, true);
    /* Now, re-enable the LPSPI module */
    LPSPI_Enable(base);
    /* If the baud rate return is "0", it means there was an error */
    if (baudRate == (uint32_t)0)
    {
        return STATUS_ERROR;
    }
    /* If the user wishes to know the calculated baud rate, then pass it back */
    if (calculatedBaudRate != NULL)
    {
        *calculatedBaudRate = baudRate;
    }
    /* Write the TCR for this transfer. */
    lpspi_tx_cmd_config_t txCmdCfg =
    {
        .frameSize = lpspiState->bitsPerFrame,
        .width = LPSPI_SINGLE_BIT_XFER,
        .txMask = false,
        .rxMask = false,
        .contCmd = false,
        .contTransfer = spiConfig->isPcsContinuous,
        .byteSwap = false,
        .lsbFirst = spiConfig->lsbFirst,
        .whichPcs = spiConfig->whichPcs,
        .preDiv = tcrPrescaleValue,
        .clkPhase = spiConfig->clkPhase,
        .clkPolarity = spiConfig->clkPolarity
    };
    LPSPI_SetTxCommandReg(base, &txCmdCfg);
    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSPI_SetPinConfigMode
 * Description   : Configures the LPSPI SDO/SDI pin configuration mode.
 *
 * This function configures the pin mode of the LPSPI.
 * For the SDI and SDO pins, the user can configure these pins as follows:
 *  SDI is used for input data and SDO for output data.
 *  SDO is used for input data and SDO for output data.
 *  SDI is used for input data and SDI for output data.
 *  SDO is used for input data and SDI for output data.
 *
 * The user has the option to configure the output data as:
 *  Output data retains last value when chip select is de-asserted (default setting).
 *  Output data is tristated when chip select is de-asserted.
 *
 * Finally, the user has the option to configure the PCS[3:2] pins as:
 *  Enabled for PCS operation (default setting).
 *  Disabled - this is need if the user wishes to configure the LPSPI mode for 4-bit transfers
 *             where these pins will be used as I/O data pins.
 *
 * Note that the LPSPI module must first be disabled before configuring this.
 *
 *END**************************************************************************/
status_t LPSPI_SetPinConfigMode_Stub(LPSPI_Type * base,
                                          lpspi_pin_config_t pinCfg,
                                          lpspi_data_out_config_t dataOutConfig,
                                          bool pcs3and2Enable)
{
    uint32_t cfgr1Value = 0;

    cfgr1Value = base->CFGR1 &
                 ~(LPSPI_CFGR1_PINCFG_MASK|LPSPI_CFGR1_OUTCFG_MASK|LPSPI_CFGR1_PCSCFG_MASK);

    cfgr1Value |= ((uint32_t)(pinCfg) << LPSPI_CFGR1_PINCFG_SHIFT) |
                  ((uint32_t)(dataOutConfig) << LPSPI_CFGR1_OUTCFG_SHIFT) |
                  ((uint32_t)(!pcs3and2Enable) << LPSPI_CFGR1_PCSCFG_SHIFT);  /* enable = 0 */

    base->CFGR1 = cfgr1Value;

	return STATUS_SUCCESS;
}

/*!
 * @brief Gets FIFO sizes of the LPSPI module.
 *
 * @ param base Module base pointer of type LPSPI_Type.
 * @ param fifoSize The FIFO size passed back to the user
 */
static inline void LPSPI_GetFifoSizes_Stub(const LPSPI_Type * base, uint8_t * fifoSize)
{
    if (fifoSize != NULL)
    {
        *fifoSize = (uint8_t)(1U << ((base->PARAM & LPSPI_PARAM_TXFIFO_MASK) >> LPSPI_PARAM_TXFIFO_SHIFT));
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSPI_DRV_MasterInit
 * Description   : Initializes a LPSPI instance for interrupt driven master mode operation.
 *
 * This function uses an interrupt-driven method for transferring data.
 * In this function, the term "spiConfig" is used to indicate the SPI device for which the LPSPI
 * master is communicating.
 * This function initializes the run-time state structure to track the ongoing
 * transfers, un-gates the clock to the LPSPI module, resets the LPSPI module,
 * configures the IRQ state structure, enables the module-level interrupt to the core, and
 * enables the LPSPI module.
 * Implements : LPSPI_DRV_MasterInit_Activity
 *
 *END**************************************************************************/
status_t LPSPI_DRV_MasterInit_Stub(uint32_t instance, lpspi_state_t * lpspiState,
                                    const lpspi_master_config_t * spiConfig)
{
    DEV_ASSERT(instance < LPSPI_INSTANCE_COUNT);
    DEV_ASSERT(lpspiState != NULL);
    DEV_ASSERT(spiConfig != NULL);
    LPSPI_Type *base = g_lpspiBase[instance];
    status_t errorCode = STATUS_SUCCESS;
    uint32_t baudRate;

    /* The Transmit Command Register (TCR) Prescale value is calculated as part of the baud rate
       calculation. The value is stored in the run-time state structure for later programming
       in the TCR. */
    uint32_t tcrPrescaleValue;

    /* Save runtime structure pointers so irq handler can point to the correct state structure */
    g_lpspiStatePtr[instance] = lpspiState;
    /* Reset the LPSPI registers to their default state */
    LPSPI_Init(base);
    /* Set for master mode */
    (void)LPSPI_SetMasterSlaveMode_Stub(base, LPSPI_MASTER);
    /* Set Pin configuration such that SDO=out and SDI=in */
    (void)LPSPI_SetPinConfigMode_Stub(base, LPSPI_SDI_IN_SDO_OUT, LPSPI_DATA_OUT_RETAINED, true);
    /* Calculate the FIFO size for the LPSPI */
    LPSPI_GetFifoSizes_Stub(base, &(lpspiState->fifoSize));

    /* Configure bus for this device. If NULL is passed, we assume the caller has
     * preconfigured the bus and doesn't wish to re-configure it again for this transfer.
     * Do nothing for calculatedBaudRate. If the user wants to know the calculatedBaudRate
     * then they can call this function separately.
     */
    errorCode = LPSPI_DRV_MasterConfigureBus_Stub(instance, spiConfig, NULL);
    if (errorCode != STATUS_SUCCESS)
    {
        return errorCode;
    }
    /* When TX is null the value sent on the bus will be 0 */
    lpspiState->dummy = 0;
    /* Initialize the semaphore */
    errorCode = OSIF_SemaCreate(&(lpspiState->lpspiSemaphore), 0);
     DEV_ASSERT(errorCode == STATUS_SUCCESS);
    /* Enable the interrupt */
    INT_SYS_EnableIRQ(g_lpspiIrqId[instance]);
    /* Finally, enable LPSPI */
    LPSPI_Enable(base);
    baudRate = LPSPI_SetBaudRate(base, spiConfig->bitsPerSec, spiConfig->lpspiSrcClk, &tcrPrescaleValue);

    lpspi_tx_cmd_config_t txCmdCfg =
    {
        .frameSize = spiConfig->bitcount,  //lpspiState->bitsPerFrame,
        .width = LPSPI_SINGLE_BIT_XFER,
        .txMask = false,
        .rxMask = false,
        .contCmd = false,
        .contTransfer = spiConfig->isPcsContinuous,
        .byteSwap = false,
        .lsbFirst = spiConfig->lsbFirst,
        .whichPcs = spiConfig->whichPcs,
        .preDiv = tcrPrescaleValue,
        .clkPhase = spiConfig->clkPhase,
        .clkPolarity = spiConfig->clkPolarity
    };
    LPSPI_SetTxCommandReg(base, &txCmdCfg);
    return errorCode;
}

void spiAssertCs(void)
{
	//PINS_DRV_SetPins(PTB, (0u  <<  PIN_5));
	PINS_DRV_WritePin(PTB, 5, 0);
	//CS hold time
   	usleep(1);

}

void spiDeassertCs(void)
{
	//CS hold time
   	usleep(1);
//	PINS_DRV_SetPins(PTB, (1u  <<  PIN_5));
	PINS_DRV_WritePin(PTB, 5, 1);

	//CS hold time
   	usleep(1);
}


bool TC6_CB_OnSpiTransaction(uint8_t tc6instance, const uint8_t *pTx, uint8_t *pRx, uint16_t len, void *pGlobalTag)
{

	//Pull the CS pin low
	spiAssertCs();
    status_t error = STATUS_SUCCESS;

    //INT_SYS_DisableIRQ(PORTD_IRQn);
    error = LPSPI_DRV_MasterTransferBlocking(INST_LPSPI_1, pTx, pRx, len, 100U);
    //INT_SYS_EnableIRQ(PORTD_IRQn);

    //Pull the CS pin hi
	spiDeassertCs();
	return (error == STATUS_SUCCESS);
}

uint32_t TC6Regs_CB_GetTicksMs(void)

{
	return(g_One_ms_Timer_Tick_counter);

}

void FTM0_Ovf_Reload_IRQHandler(void)
{
    PINS_DRV_TogglePins(PORTD, (1 << 11U));
	PINS_DRV_WritePin(PTD, 11, (pins_level_type_t) (counter & 0x01) );

	counter++;
	g_One_ms_Timer_Tick_counter++;
	if (counter == 1000U)
    {
        counter = 0;
    }
    FTM_DRV_ClearStatusFlags(INST_FLEXTIMER_MC_1, (uint32_t)FTM_TIME_OVER_FLOW_FLAG);
}

void TC6Regs_CB_OnEvent(TC6_t *pInst, TC6Regs_Event_t event, void *pTag)
	{
	    TC6NoIP_t *lw = pTag;
	    bool reinit = false;
	    switch (event) {
	        case TC6Regs_Event_UnknownError:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]UnknownError" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_Transmit_Protocol_Error:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]Transmit_Protocol_Error" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_Transmit_Buffer_Overflow_Error:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]Transmit_Buffer_Overflow_Error" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_Transmit_Buffer_Underflow_Error:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]Transmit_Buffer_Underflow_Error" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_Receive_Buffer_Overflow_Error:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]Receive_Buffer_Overflow_Error" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_Loss_of_Framing_Error:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]Loss_of_Framing_Error" ESC_RESETCOLOR "\r\n", lw->idx);
	            reinit = true;
	            break;
	        case TC6Regs_Event_Header_Error:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]Header_Error" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_Reset_Complete:
	           // PRINT(ESC_CLEAR_LINE ESC_GREEN "[%d]Reset_Complete" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_PHY_Interrupt:
	           // PRINT(ESC_CLEAR_LINE ESC_GREEN "[%d]PHY_Interrupt" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_Transmit_Timestamp_Capture_Available_A:
	           // PRINT(ESC_CLEAR_LINE ESC_GREEN "[%d]Transmit_Timestamp_Capture_Available_A" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_Transmit_Timestamp_Capture_Available_B:
	           // PRINT(ESC_CLEAR_LINE ESC_GREEN "[%d]Transmit_Timestamp_Capture_Available_B" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_Transmit_Timestamp_Capture_Available_C:
	           // PRINT(ESC_CLEAR_LINE ESC_GREEN "[%d]Transmit_Timestamp_Capture_Available_C" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_Transmit_Frame_Check_Sequence_Error:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]Transmit_Frame_Check_Sequence_Error" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_Control_Data_Protection_Error:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]Control_Data_Protection_Error" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_RX_Non_Recoverable_Error:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]RX_Non_Recoverable_Error" ESC_RESETCOLOR "\r\n", lw->idx);
	            reinit = true;
	            break;
	        case TC6Regs_Event_TX_Non_Recoverable_Error:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]TX_Non_Recoverable_Error" ESC_RESETCOLOR "\r\n", lw->idx);
	            reinit = true;
	            break;
	        case TC6Regs_Event_FSM_State_Error:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]FSM_State_Error" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_SRAM_ECC_Error:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]SRAM_ECC_Error" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_Undervoltage:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]Undervoltage" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_Internal_Bus_Error:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]Internal_Bus_Error" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_TX_Timestamp_Capture_Overflow_A:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]TX_Timestamp_Capture_Overflow_A" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_TX_Timestamp_Capture_Overflow_B:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]TX_Timestamp_Capture_Overflow_B" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_TX_Timestamp_Capture_Overflow_C:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]TX_Timestamp_Capture_Overflow_C" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_TX_Timestamp_Capture_Missed_A:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]TX_Timestamp_Capture_Missed_A" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_TX_Timestamp_Capture_Missed_B:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]TX_Timestamp_Capture_Missed_B" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_TX_Timestamp_Capture_Missed_C:
	           // PRINT(ESC_CLEAR_LINE ESC_RED "[%d]TX_Timestamp_Capture_Missed_C" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_MCLK_GEN_Status:
	           // PRINT(ESC_CLEAR_LINE ESC_YELLOW "[%d]MCLK_GEN_Status" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_gPTP_PA_TS_EG_Status:
	           // PRINT(ESC_CLEAR_LINE ESC_YELLOW "g[%d]PTP_PA_TS_EG_Status" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_Extended_Block_Status:
	           // PRINT(ESC_CLEAR_LINE ESC_YELLOW "[%d]Extended_Block_Status" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_SPI_Err_Int:
	           // PRINT(ESC_CLEAR_LINE ESC_YELLOW "[%d]SPI_Err_Int" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_MAC_BMGR_Int:
	           // PRINT(ESC_CLEAR_LINE ESC_YELLOW "[%d]MAC_BMGR_Int" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_MAC_Int:
	           // PRINT(ESC_CLEAR_LINE ESC_YELLOW "[%d]MAC_Int" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_HMX_Int:
	           // PRINT(ESC_CLEAR_LINE ESC_YELLOW "[%d]HMX_Int" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_GINT_Mask:
	           // PRINT(ESC_CLEAR_LINE ESC_YELLOW "[%d]GINT_Mask" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_Chip_Error:
	           // PRINT(ESC_RED "[%d]Chip_error! Please contact microchip support for replacement" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	        case TC6Regs_Event_Unsupported_Hardware:
	           // PRINT(ESC_RED "[%d]Unsupported MAC-PHY hardware found" ESC_RESETCOLOR "\r\n", lw->idx);
	            break;
	    }
	    if (reinit) {
	        TC6Regs_Reinit(pInst);
	    }
	}

void TC6_CB_OnError(TC6_t *pInst, TC6_Error_t err, void *pGlobalTag)
{
    TC6NoIP_t *lw = pGlobalTag;
    bool reinit = false;
    switch (err) {
        case TC6Error_Succeeded:
            //PRINT(ESC_CLEAR_LINE ESC_GREEN "[%d]No error occurred" ESC_RESETCOLOR "\r\n", lw->idx);
            break;
        case TC6Error_NoHardware:
            //PRINT(ESC_CLEAR_LINE ESC_RED "[%d]MISO data implies that there is no MACPHY hardware available" ESC_RESETCOLOR "\r\n", lw->idx);
            reinit = true;
            break;
        case TC6Error_UnexpectedSv:
            //PRINT(ESC_CLEAR_LINE ESC_RED " [%d]Unexpected Start Valid Flag" ESC_RESETCOLOR "\r\n", lw->idx);
            break;
        case TC6Error_UnexpectedDvEv:
            //PRINT(ESC_CLEAR_LINE ESC_RED "[%d]Unexpected Data Valid or End Valid Flag" ESC_RESETCOLOR "\r\n", lw->idx);
            break;
        case TC6Error_BadChecksum:
            //PRINT(ESC_CLEAR_LINE ESC_RED "[%d]Checksum in footer is wrong" ESC_RESETCOLOR "\r\n", lw->idx);
            reinit = true;
            break;
        case TC6Error_UnexpectedCtrl:
            //PRINT(ESC_CLEAR_LINE ESC_RED "[%d]Unexpected control packet received" ESC_RESETCOLOR "\r\n", lw->idx);
            reinit = true;
            break;
        case TC6Error_BadTxData:
            //PRINT(ESC_CLEAR_LINE ESC_RED "[%d]Header Bad Flag received" ESC_RESETCOLOR "\r\n", lw->idx);
            reinit = true;
            break;
        case TC6Error_SyncLost:
            //PRINT(ESC_CLEAR_LINE ESC_RED "[%d]Sync Flag is no longer set" ESC_RESETCOLOR "\r\n", lw->idx);
            reinit = true;
            break;
        case TC6Error_SpiError:
            //PRINT(ESC_CLEAR_LINE ESC_RED "[%d]TC6 SPI Error" ESC_RESETCOLOR "\r\n", lw->idx);
            reinit = true;
            break;
        case TC6Error_ControlTxFail:
            //PRINT(ESC_CLEAR_LINE ESC_RED "[%d]TC6 Control Message Error" ESC_RESETCOLOR "\r\n", lw->idx);
            break;
        default:
            //PRINT(ESC_CLEAR_LINE ESC_RED "[%d]Unknown TC6 error occurred" ESC_RESETCOLOR "\r\n", lw->idx);
            break;
    }
    if (reinit) {
        TC6Regs_Reinit(pInst);
    }
}
void TC6_CB_OnRxEthernetPacket(TC6_t *pInst, bool success, uint16_t len, uint64_t *rxTimestamp, void *pGlobalTag)
{
    TC6NoIP_t *lw = pGlobalTag;
    TC6NoIP_CB_OnEthernetReceive(lw->idx, lw->tc.ethRxBuf, len);
}
#define UDP_PAYLOAD_OFFSET          (42)
#define BOARD_INSTANCES_MAX         (4)
typedef struct
{
    uint32_t packetCntCurrent;
    uint32_t packetCntTotal;
    uint32_t byteCntCurrent;
    uint32_t byteCntTotal;
    uint32_t previousVal;
    uint32_t errors;
} MainStats_t;

typedef struct
{
    MainStats_t stats[BOARD_INSTANCES_MAX];
    uint32_t    nextStat;
    uint32_t    nextBeaconCheck;
    uint32_t    nextLed;
    uint32_t    iperfTx;
    int8_t      idxNoIp;
    bool        button1;
    bool        button2;
    bool        gotBeaconState;
    bool        lastBeaconState;
    bool        txBusy;
    bool        allowTxStress;
} MainLocal_t;

static MainLocal_t m;

void TC6NoIP_CB_OnEthernetReceive(int8_t idx, const uint8_t *pRx, uint16_t len)
{
    if (len >= (UDP_PAYLOAD_OFFSET + 5)) {
        uint16_t i = UDP_PAYLOAD_OFFSET;
        uint8_t idx = pRx[i++];
        if (idx < BOARD_INSTANCES_MAX) {
            uint32_t val = 0;
            uint32_t previous = m.stats[idx].previousVal;
            val |= pRx[i++] << 24;
            val |= pRx[i++] << 16;
            val |= pRx[i++] << 8;
            val |= pRx[i++];

            if (previous) {
                if ((previous + 1) != val) {
                    m.stats[idx].errors++;
                }
            }
            m.stats[idx].previousVal = val;

            m.stats[idx].byteCntCurrent += len;
            m.stats[idx].byteCntTotal += len;
            m.stats[idx].packetCntCurrent++;
            m.stats[idx].packetCntTotal++;
        }
    }
}

void TC6_CB_OnRxEthernet(TC6_t *pInst, const uint8_t *pRx, uint16_t offset, uint16_t len, void *pGlobalTag)
{
    TC6NoIP_t *lw = pGlobalTag;
    if ((offset + len) < sizeof(lw->tc.ethRxBuf)) {
        memcpy(&lw->tc.ethRxBuf[offset], pRx, len);
    }
}


void TC6_CB_OnIntPinInterruptEnable(uint8_t tc6instance, bool enableInt)
{
    TC6Stub_IntPinInterruptEnable(tc6instance, enableInt);
}

void TC6_CB_OnNeedService(TC6_t *pInst, void *pGlobalTag)
{
}

void TC6Stub_IntPinInterruptEnable(uint8_t idx, bool enableInt)
{
    //ASSERT(idx < TC6_MAX_INSTANCES);
    if (enableInt)
    {
        INT_SYS_EnableIRQ(PORTD_IRQn);
    }
    else
    {
        INT_SYS_DisableIRQ(PORTD_IRQn);
    }
}

 void TC6_CB_OnRxEthernetSlice(TC6_t *pInst, const uint8_t *pRx, uint16_t offset, uint16_t len, void *pGlobalTag)
{
    TC6NoIP_t *lw = pGlobalTag;
    if ((offset + len) < sizeof(lw->tc.ethRxBuf)) {
        memcpy(&lw->tc.ethRxBuf[offset], pRx, len);
    }
}


