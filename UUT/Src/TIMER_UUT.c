/*
 * TIMER.c
 *
 *  Created on: 20 Nov 2022
 *      Author: shachar-ubuntu
 */

#include "../../UUT/Inc/TIMER_UUT.h"

/**
 * @brief the timer flag to be used by the program's callback function.
 * 		  if the Ethernet packet data request to use timer.
 */
tFlag timer_end = {.bit=TIMER_NOT_END};

/**
 * @brief elapsed timer callback function implementation, turn on timer flag.
 * 		  which indicates the timer ends.
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == BASIC_TIMER1_HANDLE)
	{
		timer_end.bit = TIMER_END;
	}
}

/**
 * @fn 		void timer_init(TIM_HandleTypeDef*, uint32_t, uint32_t)
 * @brief 	initialize and start the timer given with prescalar and period values
 * 		  	so the user will decide the time where the timer elapsed.
 *
 * @param htim 		the timer to init and start.
 * @param prescalar	the prescalar value.
 * @param periodq	the period value.
 */
void timer_init_start(TIM_HandleTypeDef *htim, uint32_t prescalar, uint32_t period)
{
	//TIM master configurations
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	//if the timer is defined
	if(htim == BASIC_TIMER1_HANDLE)
	{
		htim->Init.Prescaler = prescalar;
		htim->Init.Period = period;
		htim->Instance = BASIC_TIMER1;
		htim->Init.CounterMode = TIM_COUNTERMODE_UP;
		htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
		if (HAL_TIM_Base_Init(htim) != HAL_OK)
		{
			Error_Handler();
		}
		sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
		sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
		if (HAL_TIMEx_MasterConfigSynchronization(htim, &sMasterConfig) != HAL_OK)
		{
			Error_Handler();
		}

		// start the timer which is based interrupt.
		HAL_TIM_Base_Start_IT(BASIC_TIMER1_HANDLE);
	}
}
