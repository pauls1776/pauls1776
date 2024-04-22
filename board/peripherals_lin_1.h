/***********************************************************************************************************************
 * This file was generated by the S32 Config Tools. Any manual edits made to this file
 * will be overwritten if the respective S32 Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef lin_1_H
#define lin_1_H

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
#include "stddef.h"
#include "lin_driver.h"

/*******************************************************************************
 * Definitions 
 ******************************************************************************/

/*! @brief Device instance number */
#define INST_LIN1  (1U)

/*******************************************************************************
 * Global variables 
 ******************************************************************************/

/*! @brief LIN State structure */
extern lin_state_t lin0_State;

/*! @brief Extern LIN user configuration structure */
/*! @brief Extern LIN configuration lin0_InitConfig0 */
extern lin_user_config_t lin0_InitConfig0;



#endif /* lin_1_H */