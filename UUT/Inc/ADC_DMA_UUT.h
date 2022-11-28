/*
 * ADC_DMA_UUT.h
 *
 *  Created on: Nov 27, 2022
 *      Author: shachar-ubuntu
 */

#ifndef INC_ADC_DMA_UUT_H_
#define INC_ADC_DMA_UUT_H_
#include "main.h"
#include "stm32f7xx_hal.h"
#include "../../UUT/Inc/ExtraTools.h"

/* ***************** Defines ***************************************************************************** */
/**@brief the ADC value expected at the end of each iteration in the UUT function. */
#define ADC_EXPECTED_VALUE 4096

/**
 * @brief the ADC deviation is +- (Number Defined here) assuming its enough for our value to be between
 * those limits.
 */
#define ADC_DEVIATION 80

/**@brief the ADC flag value for false callback function did not called */
#define ADC_FLAG_RESET 0

/**@brief the ADC flag value for false callback function did not called */
#define ADC_FLAG_SET 1

/**@brief the handle address of the the ADC peripheral. */
#define ADC_HANDLE_ADDR &hadc1

/**@brief the ADC value which state which ADC peripheral is it in the start ADC function */
#define ADC_TO_TEST ADC1

/**@brief the synchronization needed for the ADC flag to be set so the CPU will check it and it'll be SET */
#define ADC_SYNC_TIME HAL_Delay(0.1)

/**@brief define the number samples of the data until returned from ADC (callback function) */
#define ADC_NUM_OF_SAMPLES 1
/* ******************************************************************************************************* */

/* ****************************** Externs **************************************************************** */
/**@brief holding the actual value got by the ADC. */
extern uint32_t adc_value;

/**@brief the flag of the adc when interrupt ISR called */
extern uint8_t adc_callback_flag;

/**@brief the handle of the ADC peripheral */
extern ADC_HandleTypeDef hadc1;
/* ******************************************************************************************************* */

/* ****************************  Functions *************************************************************** */
/**
 * @name	t_status ADC_UUT_DMA(uint8_t iterations)
 * @brief	the adc under unit tests function, the funtion checks if the adc value got is the expected value.
 * 			the expected value is according to which the ADC peripheral connected to.
 * @param 	iterations	the number of times to check this test.
 * @return	return TEST_SUCCEED 0x01 if test pass, otherwise TEST_FAILED 0xff. if one of the iterations fails
 * 			the whole test fails and returning TEST_FAILED if all tests iterations passed at the end return
 * 			TEST_SUCCEED 0x01.
 */
t_status ADC_UUT_DMA(uint8_t iterations);
/* ******************************************************************************************************* */

#endif /* INC_ADC_DMA_UUT_H_ */
