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
#define SYS_CLK_FREQ 72000000

/**@brief the added value in the calculation of the timer time elapsed of period register*/
#define PERIOD_ADDED_VAL 1

/**@brief the added value in the calculation of the timer time elapsed of prescalar register*/
#define PRESCALAR_ADDED_VAL 1

/**@brief user costum prescalar value*/
#define USER_PRESCALAR	7199

/**@brief user costum period value*/
#define USER_PERIOD		9999

/**@brief true magic number for timer end flag*/
#define TIMER_END 1

/**@brief false magic number for timer end flag*/
#define TIMER_NOT_END 0

/**
 * @def COSTUM_BASIC_TIMER_HANDLE
 * @brief definition for better code readability.
 */
#define BASIC_TIMER1_HANDLE &htim7

/** @brief the define for the timer's value.*/
#define BASIC_TIMER1 TIM7
/* ******************************************************************************************************* */

/* **************************** Externs ****************************************************************** */
/**@brief the timer to be used. this timer used when the server request to test timer.*/
extern TIM_HandleTypeDef htim7;

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
* 		 	test the timer peripheral. this done by using delay which uses busy loop and count ticks
* 		 	after the interrupt timer started so the timer_end flag must be set before the delay ends
 * 		  	otherwise, it is not working correctly.
 * @param 	iterations		running the test number of iterations.
 * @return	t_status		running it number of iterations to if one of them fails return TEST_FAILED 0xff,
 * 							otherwise TEST_SUCCEED 0x01
 */
t_status TIMER_UUT(uint8_t iterations);
/* ******************************************************************************************************* */

#endif /* INC_TIMER_UUT_H_ */
