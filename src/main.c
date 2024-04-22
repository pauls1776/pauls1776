/*!
** Copyright 2020 NXP
** @file main.c
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup main_module main module documentation
**  @{
*/
/* MODULE main */


/* Including necessary configuration files. */
#include "sdk_project_config.h"
#include <string.h>
#include <stdio.h>
#include "S32K146.h"
#include "pcc_hw_access.h"
#include "clock_S32K1xx.h"
#include "stub.h"


volatile int exit_code = 0;
/* User includes */


static   TC6_t * g_TC6_instance_ptr;
extern void IntHandler(uintptr_t context);

#define TIMEOUT 100000U

//Ethernet interface configuration
#define APP_IF_NAME              "eth0"
#define APP_HOST_NAME            "coap-client-demo"
#define APP_MAC_ADDR             "00-AB-CD-EF-28-60"

#define APP_USE_DHCP_CLIENT ENABLED
#define APP_IPV4_HOST_ADDR       "192.168.0.20"
#define APP_IPV4_SUBNET_MASK     "255.255.255.0"
#define APP_IPV4_DEFAULT_GATEWAY "192.168.0.254"
#define APP_IPV4_PRIMARY_DNS     "8.8.8.8"
#define APP_IPV4_SECONDARY_DNS   "8.8.4.4"

#define APP_USE_SLAAC ENABLED
#define APP_IPV6_LINK_LOCAL_ADDR "fe80::2860"
#define APP_IPV6_PREFIX          "2001:db8::"
#define APP_IPV6_PREFIX_LENGTH         64
#define APP_IPV6_GLOBAL_ADDR     "2001:db8::2860"
#define APP_IPV6_ROUTER          "fe80::1"
#define APP_IPV6_PRIMARY_DNS     "2001:4860:4860::8888"
#define APP_IPV6_SECONDARY_DNS   "2001:4860:4860::8844"

void PINS_ISR(void);
void PINS_ISR(void)
{
  PINS_DRV_ClearPinIntFlagCmd(PORTD, (uint32_t) 12);

  //  TC6_HandleMacPhyInterrupt(TC6_GetInstance(context));  // context being the TC6_t * originally returned by TC6_Init()
  TC6_HandleMacPhyInterrupt((uint8_t) 0);  // context being the TC6_t * originally returned by TC6_Init()
}

static void BSP_init(void)
{
    ftm_state_t  state;
    status_t stat;

	stat = CLOCK_DRV_Init(&clockMan1_InitConfig0);
    //CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT, g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);

    //CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

	stat = PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);
    /* Install PORTC_IRQn as PINS interrupt handler */
    /* Initialize FTM */
#if 1
	FTM_DRV_Init(INST_FLEXTIMER_MC_1, &flexTimer_mc_1_InitConfig_0, &state);

    /* Initialize counter */
    FTM_DRV_InitCounter(INST_FLEXTIMER_MC_1, &flexTimer_mc_1_TimerConfig_0);

    /* Start Counter */
    FTM_DRV_CounterStart(INST_FLEXTIMER_MC_1);
#endif

    spiInit();
    ENABLE_INTERRUPTS();
    //DISABLE_INTERRUPTS();

}

/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
static TC6NoIP_t g_stub_var = {0};

uint32_t g_csr;
S32_SysTick_MemMapPtr S32_SysTick_MemMapPtr_new;

int main(void)
{

    S32_SysTick_MemMapPtr_new = S32_SysTick;
	uint32_t  wait;
    uint32_t  counter = 0;

	//(PORTD, (uint32_t) 12);

	BSP_init();

    static uint8_t buffer_data0[] =
    {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x70, 0xb3, /* ......p. */
        0xd5, 0x77, 0xf0, 0x00, 0x08, 0x00, 0x45, 0x00, /* .w.*..E. */
        0x00, 0x22, 0x37, 0x57, 0x00, 0x00, 0x80, 0x11, /* ."7W.... */
        0x00, 0x00, 0xc0, 0xa8, 0x00, 0xde, 0xc0, 0xa8, /* .F...... */
        0x00, 0xff, 0x86, 0xc9, 0x86, 0xc9, 0x00, 0x0e, /* ........ */
        0x00, 0x00, 0x01, 0xCD, 0xCD, 0xCD, 0xCD, 0xCD  /* f....... */
    };


     g_TC6_instance_ptr = TC6_Init(&g_stub_var);
	 while (g_TC6_instance_ptr == (TC6_t * )NULL);
	 const uint8_t PLCA_node_id = 1;
	 uint8_t mac[6] =  {0x070U, 0xB3U,0xD5U, 0x77U, 0xF0U, PLCA_node_id};

#if 0
	 while ( TC6Regs_Init( g_TC6_instance_ptr,  NULL,  mac, TRUE,  PLCA_node_id,  (uint8_t) 8, (uint8_t) 0, (uint8_t) 0x80,  FALSE,  FALSE,  FALSE) ==0);
	 while(!TC6Regs_GetInitDone(g_TC6_instance_ptr))
	 {
	           //  TC6_Service(TC6_Instance, true);  // this is for asynchronous processing of the LAN driver  - we have choose the synchronous driver
	  }

#endif
	 for(;;)
    {
    	for (wait=0;wait<100000;wait++)
    	{ }
    	counter= 10000;

        g_csr = S32_SysTick_MemMapPtr_new->CSR;
        S32_SysTick->CSR =  S32_SysTick_CSR_ENABLE(0);
        g_csr = S32_SysTick_MemMapPtr_new->CSR;
        S32_SysTick->CSR =  S32_SysTick_CSR_ENABLE(1);
        g_csr = S32_SysTick_MemMapPtr_new->CSR;

       error_t error;
      // TC6_Service(TC6_Instance, FALSE);   // this call would be needed for the asynchronous driver
       TC6Regs_CheckTimers();
       TC6_HandleMacPhyInterrupt( 0 ); // this is to be deleted
       if (counter >= 10000)
       {
       	counter = 0;
       	TC6_SendRawEthernetPacket(g_TC6_instance_ptr, buffer_data0, (uint16_t) sizeof(buffer_data0), (uint8_t) 0 );

       }

    }
 return exit_code;

}
