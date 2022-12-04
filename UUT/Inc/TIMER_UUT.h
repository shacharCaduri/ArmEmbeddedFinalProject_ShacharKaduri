/*
 * TIMER.h
 *
 *  Created on: 20 Nov 2022
 *      Author: shachar-ubuntu
 */

#ifndef INC_TIMER_UUT_H_
#define INC_TIMER_UUT_H_
#include "main.h"
#include "stm32f7xx_hal.h"
#include "../../UUT/Inc/ExtraTools.h"

/* ********************** Defines ************************************************************************ */
/**@brief the clock frequency the basic timer uses to calculate the time*/
#define TIM_CLK_FREQ 72000000

/**@brief the added value in the calculation of the timer time elapsed of period register*/
#define PERIOD_ADDED_VAL 1

/**@brief the added value in the calculation of the timer time elapsed of prescalar register*/
#define PRESCALAR_ADDED_VAL 1

/**@brief true magic number for timer end flag*/
#define TIMER_END 1

/**@brief false magic number for timer end flag*/
#define TIMER_NOT_END 0

/**
 * @def COSTUM_TIMER_HANDLE
 * @brief definition for better code readability.
 */
#define TIMER1_HANDLE (&htim3)

/**@brief value to turn timer elaps time to be into milliseconds */
#define TO_MILLISECONDS 1000

/**
 * @brief the value to be add to the hal delay so the timer flag surely will be set,
 * little above the timer's total time, measured in ms
 */
#define TIM_DEVIATION_VAL 100
/* ******************************************************************************************************* */

/* **************************** Externs ****************************************************************** */
/**@brief the timer to be used. this timer used when the server request to test timer.*/
extern TIM_HandleTypeDef htim3;

/**
 * @brief the timer flag to be used by the program's callback function.
 * 		  if the Ethernet packet data request to use timer.
 */
extern uint8_t timer_end;
/* ******************************************************************************************************* */

/* **************************** Functions **************************************************************** */
/**
 * @fn 		uint8_t TIMER_UUT(uint32_t prescalar, uint32_t period, uint8_t iterations)
 * @brief 	start the timer with prescalar and period values so the user will decide the time where the
 * 		  	timer elapsed, test if it is indeed working correctly if a the given time really passed.
* 		 	test the timer peripheral.
 * @param 	iterations		running the test number of iterations.
 * @return	t_status		running it number of iterations to if one of them fails return TEST_FAILED 0xff,
 * 							otherwise TEST_SUCCEED 0x01
 */
t_status TIMER_UUT(uint8_t iterations);
/* ******************************************************************************************************* */

#endif /* INC_TIMER_UUT_H_ */
