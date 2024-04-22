/***********************************************************************************************************************
 * This file was generated by the S32 Configuration Tools. Any manual edits made to this file
 * will be overwritten if the respective S32 Configuration Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v10.0
processor: S32K146
package_id: S32K146_LQFP100
mcu_data: s32sdk_s32k1xx_rtm_403
processor_version: 0.0.0
functionalGroups:
- name: BOARD_InitPeripherals
  UUID: a6d43dcb-893a-49cd-9d9d-0bb26ff0f05b
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Included files 
 ******************************************************************************/
#include "peripherals_adc_config_1.h"

/*******************************************************************************
 * adc_config_1 initialization code
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'adc_config_1'
- type: 'adc_config'
- mode: 'general'
- custom_name_enabled: 'false'
- type_id: 'adc'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'ADC_0'
- config_sets:
  - adc:
    - adcConverterCfg:
      - 0:
        - name: 'adc_config_1_ConvConfig0'
        - readonly: 'true'
        - clockDivide: 'ADC_CLK_DIVIDE_4'
        - sampleTime: '255'
        - resolution: 'ADC_RESOLUTION_12BIT'
        - inputClock: 'ADC_CLK_ALT_1'
        - trigger: 'ADC_TRIGGER_SOFTWARE'
        - pretriggerSel: 'ADC_PRETRIGGER_SEL_PDB'
        - triggerSel: 'ADC_TRIGGER_SEL_PDB'
        - dmaEnable: 'false'
        - voltageRef: 'ADC_VOLTAGEREF_VREF'
        - continuousConvEnable: 'false'
        - supplyMonitoringEnable: 'false'
    - adcCompareCfg: []
    - adcAverageCfg: []
    - adcChanCfg: []
    - quick_selection: 'dv_adc'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.7, External variable could be made static.
 * The external variables will be used in other source files in application code.
 *
 */

const adc_converter_config_t adc_config_1_ConvConfig0 = {
  .clockDivide = ADC_CLK_DIVIDE_4,
  .sampleTime = 255U,
  .resolution = ADC_RESOLUTION_12BIT,
  .inputClock = ADC_CLK_ALT_1,
  .trigger = ADC_TRIGGER_SOFTWARE,
  .pretriggerSel = ADC_PRETRIGGER_SEL_PDB,
  .triggerSel = ADC_TRIGGER_SEL_PDB,
  .dmaEnable = false,
  .voltageRef = ADC_VOLTAGEREF_VREF,
  .continuousConvEnable = false,
  .supplyMonitoringEnable = false
};


