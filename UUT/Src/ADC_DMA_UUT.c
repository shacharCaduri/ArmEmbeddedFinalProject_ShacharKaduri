/*
 * ADC_DMA_UUT.c
 *
 *  Created on: Nov 27, 2022
 *      Author: shachar-ubuntu
 */

#include "../../UUT/Inc/ADC_DMA_UUT.h"
#include <string.h> // for strcmp

/**@brief holding the actual value got by the adc. */
uint32_t adc_value = INIT_TO_ZERO;

/**@brief the flag of the adc when interrupt ISR called */
uint8_t adc_callback_flag = ADC_FLAG_RESET;

/**@brief the complete convertion callback function this implentations */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if(hadc == ADC_HANDLE_ADDR)
	{
		/* just set the callback to indicate CPU convertion completed */
		adc_callback_flag = ADC_FLAG_SET;
	}
}

/**
 * @brief	the adc under unit tests function, the funtion checks if the adc value got is the expected value.
 * 			the expected value is according to which the ADC peripheral connected to.
 */
t_status ADC_UUT_DMA(uint8_t iterations)
{
	/* start the dma functionality */
	HAL_ADC_Start_DMA(ADC_HANDLE_ADDR, &adc_value, (uint32_t)ADC_NUM_OF_SAMPLES);

	/* the status to check the functions in the iterations */
	HAL_StatusTypeDef status = HAL_ERROR;

	while(iterations)
	{

		/* start ADC convertion */
		status = HAL_ADC_Start(ADC_HANDLE_ADDR);

		/* check if start correctly */
		if(status != HAL_OK)
		{
			return TEST_FAILED;
		}

		/* check callback complete flag */
		if(wait_till_flag_set_or_timeout(&adc_callback_flag, ADC_TIMEOUT, ADC_DMA_TIME) != WAIT_STATUS_OK)
		{
			return TEST_FAILED;
		}
		else
		{
			/* check if ADC expected value is between the deviation allowed ADC_VAL +/- DEVIATION if it is continue to next iteration */
			if(! (ADC_EXPECTED_VALUE - ADC_DEVIATION <= adc_value && adc_value <= ADC_EXPECTED_VALUE + ADC_DEVIATION ))
			{
				/* reset the callback flag */
				adc_callback_flag = ADC_FLAG_RESET;
				return TEST_FAILED;
			}
			/* reset the callback flag */
			adc_callback_flag = ADC_FLAG_RESET;

		}

		--iterations;
	}

	/* if all iterations passed return TEST passed successfully */
	return TEST_SUCCEED;
}
