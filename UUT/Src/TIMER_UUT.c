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
uint8_t timer_end = TIMER_NOT_END;

/**
 * @brief elapsed timer callback function implementation, turn on timer flag.
 * 		  which indicates the timer ends.
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIMER1_HANDLE->Instance)
	{

		timer_end = TIMER_END;
	}
}


/**
 * @brief 	start the timer with prescalar and period values so the user will decide the time where the
 * 		  	timer elapsed, test if it is indeed working correctly if a the given time really passed.
 * 		 	test the timer peripheral.
 */
t_status TIMER_UUT(uint8_t iterations)
{
	/* in ms */
	double timer_elaps_time = TO_MILLISECONDS*(double)(((*TIMER1_HANDLE).Init.Prescaler+PRESCALAR_ADDED_VAL)*
			((*TIMER1_HANDLE).Init.Period+PERIOD_ADDED_VAL))/TIM_CLK_FREQ;

	/* get the tick value in milliseconds at the start of our timer */
	uint32_t start = INIT_TO_ZERO;

	/* get the tick value in milliseconds at the end of our timer */
	uint32_t end = INIT_TO_ZERO;

	/* test phase */
	while(iterations)
	{
		start = HAL_GetTick();

		/* enable timer interrupt to start (as time defined) */
		HAL_TIM_Base_Start_IT(TIMER1_HANDLE);
		timer_end = TIMER_NOT_END;

		/* wait for flag to be turn on */
		while(timer_end != TIMER_END)
		{

			/* ******** code to stop it from running forever in case it would happen ******** */
			end = HAL_GetTick();
			if((end-start) > (timer_elaps_time+TIM_DEVIATION_VAL))
			{
				/* stops the timer */
				HAL_TIM_Base_Stop_IT(TIMER1_HANDLE);

				timer_end = TIMER_NOT_END;

				return TEST_FAILED;
			}
			/* ****************************************************************************** */
		}
		/* stops the timer */
		HAL_TIM_Base_Stop_IT(TIMER1_HANDLE);
		timer_end = TIMER_NOT_END;

		end = HAL_GetTick();

		if(timer_elaps_time-TIM_DEVIATION_VAL <= end-start && end-start <= timer_elaps_time + TIM_DEVIATION_VAL)
		{
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
			--iterations;
			continue;
		}
		else {
			return TEST_FAILED;
		}

	}

	return TEST_SUCCEED;
}
