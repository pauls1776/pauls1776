/***********************************************************************************************************************
 * This file was generated by the S32 Config Tools. Any manual edits made to this file
 * will be overwritten if the respective S32 Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef lpuart_1_H
#define lpuart_1_H

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.5, Global macro not referenced.
 * The global macro will be used in function call of the module.
 *
 */
/*******************************************************************************
 * Included files 
 ******************************************************************************/
#include "lpuart_driver.h"

/*******************************************************************************
 * Definitions 
 ******************************************************************************/
#define INST_LPUART_1  2

extern lpuart_state_t lpUartState0;

/* External declaration of LPUART configuration structure */
extern const lpuart_user_config_t lpuart_0_InitConfig0;



#endif /* lpuart_1_H */
