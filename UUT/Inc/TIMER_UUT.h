/*
 * TIMER.h
 *
 *  Created on: 20 Nov 2022
 *      Author: shachar-ubuntu
 */

#ifndef INC_TIMER_UUT_H_
#define INC_TIMER_UUT_H_
#include "main.h"

/**@brief user costum prescalar value*/
#define USER_PRESCALAR	7199

/**@brief user costum period value*/
#define USER_PERIOD		9999

/**@brief true magic number for timer end flag*/
#define TIMER_END 1

/**@brief false magic number for timer end flag*/
#define TIMER_NOT_END 0

/**@brief the timer to be used. this timer used when the server request to test timer.*/
extern TIM_HandleTypeDef htim7;

/**
 * @def COSTUM_BASIC_TIMER_HANDLE
 * @brief definition for better code readability.
 */
#define BASIC_TIMER1_HANDLE &htim7

/** @brief the define for the timer's value.*/
#define BASIC_TIMER1 TIM7

/**
 * @brief Sets the alignment of all aggregate members to a specified byte boundary.
 * 		  If the byte boundary number is smaller than the natural alignment of a member,
 * 		  padding bytes are removed, thereby reducing the overall structure or union size.
 */
#pragma pack(1)
/**
 * @brief the timer flag struct to be used by program's callback function.
 * @var   bit - is a bit field defined to hold one bit so it will be 0 or 1 and nothing else.
 * 		  this is bit is turned on when timer elapsed to enable operation based upon a timer.
 */
typedef struct timer_flag {
	uint8_t bit:1;
} tFlag;
/** @brief @reset the packing to the previous packing*/
#pragma pack()

/**
 * @brief this is the for user programmer to see there is a timer flag to indicate timer ends.
 * 		  this flag is a timer_flag type. tFlag is an alias for timer_flag.
 */
extern tFlag timer_end;

/**
 * @fn void timer_init(TIM_HandleTypeDef*, uint32_t, uint32_t)
 * @brief initialize and start the timer given with prescalar and period values
 * 		  so the user will decide the time where the timer elapsed.
 *
 * @param htim 		the timer to init and start.
 * @param prescalar	the prescalar value.
 * @param periodq	the period value.
 */
void timer_init_start(TIM_HandleTypeDef *htim, uint32_t prescalar, uint32_t period);

#endif /* INC_TIMER_UUT_H_ */
