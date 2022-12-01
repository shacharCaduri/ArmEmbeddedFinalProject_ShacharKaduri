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
	if(htim == BASIC_TIMER1_HANDLE)
	{
		timer_end = TIMER_END;
	}
}

/**
 * @brief 	start the timer with prescalar and period values so the user will decide the time where the
 * 		  	timer elapsed, test if it is indeed working correctly if a the given time really passed.
 * 		 	test the timer peripheral. this done by using delay which uses busy loop and count ticks
 * 		 	after the interrupt timer started so the timer_end flag must be set before the delay ends
 * 		  	otherwise, it is not working correctly.
 */
t_status TIMER_UUT(uint8_t iterations)
{
	/* in ms */
	double timer_elaps_time = HAL_DELAY_TO_SEC_VAL*(double)(((*BASIC_TIMER1_HANDLE).Init.Prescaler+PRESCALAR_ADDED_VAL)*((*BASIC_TIMER1_HANDLE).Init.Period+PERIOD_ADDED_VAL))/TIM_CLK_FREQ;

	/* test phase */
	while(iterations)
	{
		/* start timer*/
		HAL_TIM_Base_Start_IT(BASIC_TIMER1_HANDLE);

		/* delay for checking the elapsing time of the timer. */
		HAL_Delay(timer_elaps_time+TIM_DEVIATION_VAL);

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
