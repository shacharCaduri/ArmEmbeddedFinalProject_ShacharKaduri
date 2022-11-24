/*
 * TIMER.c
 *
 *  Created on: 20 Nov 2022
 *      Author: shachar-ubuntu
 */

#include "../../UUT/Inc/TIMER_UUT.h"
#include "../../UUT/Inc/MAIN_UUT.h"

/**
 * @brief the timer flag to be used by the program's callback function.
 * 		  if the Ethernet packet data request to use timer.
 */
uint8_t timer_end = TIMER_NOT_END;

/**
 * @brief elapsed timer callback function implementation, turn on timer flag.
 * 		  which indicates the timer ends.
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == BASIC_TIMER1_HANDLE)
	{
		timer_end = TIMER_END;
	}
}

/**
 * @fn uint8_t TIMER_UUT(uint32_t prescalar, uint32_t period, uint8_t iterations)
 * @brief initialize and start the timer with prescalar and period values
 * 		  so the user will decide the time where the timer elapsed, test if it
 * 		  is indeed working correctly if a the given time really passed.
 * 		  test the timer peripheral. this done by using delay which uses busy loop and count ticks
 * 		  after the interrupt timer started so the timer_end flag must be set before the delay ends
 * 		  otherwise, it is not working correctly.
 * @param 	prescalar		the prescalar value.
 * @param 	period			the period value.
 * @param 	iterations		running the test number of iterations.
 * @return	running it number of iterations to if one of them fails return TEST_FAILED 0xff, otherwise TEST_SUCCEED 0x01
 */
uint8_t TIMER_UUT(/*uint32_t prescalar, uint32_t period,*/ uint8_t iterations)
{
//	//TIM master configurations
//	TIM_MasterConfigTypeDef sMasterConfig = INIT_ALL_ZERO;
	double timer_elaps_time = (double)(((*BASIC_TIMER1_HANDLE).Init.Prescaler+PRESCALAR_ADDED_VAL)*((*BASIC_TIMER1_HANDLE).Init.Period+PERIOD_ADDED_VAL))/SYS_CLK_FREQ;
//
//	/* initialize timer with given params */
//	(*BASIC_TIMER1_HANDLE).Init.Prescaler = prescalar;
//	(*BASIC_TIMER1_HANDLE).Init.Period = period;
//	(*BASIC_TIMER1_HANDLE).Instance = BASIC_TIMER1;
//	(*BASIC_TIMER1_HANDLE).Init.CounterMode = TIM_COUNTERMODE_UP;
//	(*BASIC_TIMER1_HANDLE).Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
//	if (HAL_TIM_Base_Init(BASIC_TIMER1_HANDLE) != HAL_OK)
//	{
//		Error_Handler();
//	}
//	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
//	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//	if (HAL_TIMEx_MasterConfigSynchronization(BASIC_TIMER1_HANDLE, &sMasterConfig) != HAL_OK)
//	{
//		Error_Handler();
//	}


	/* test phase */
	while(iterations)
	{
		/* start timer*/
		HAL_TIM_Base_Start_IT(BASIC_TIMER1_HANDLE);

		/* delay for checking the elapsing time of the timer. */
		HAL_Delay(timer_elaps_time);

		if(timer_end != TIMER_END)
		{
			/* stops the timer */
			HAL_TIM_Base_Stop_IT(BASIC_TIMER1_HANDLE);

			timer_end = TIMER_NOT_END;

			return TEST_FAILED;
		}

		/* stops the timer */
		HAL_TIM_Base_Stop_IT(BASIC_TIMER1_HANDLE);

		timer_end = TIMER_NOT_END;

		--iterations;
	}
	return TEST_SUCCEED;
}
