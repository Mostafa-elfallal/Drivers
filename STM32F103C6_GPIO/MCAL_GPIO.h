/*
 * MCAL_GPIO.h
 *
 *  Created on: Jul 12, 2021
 *      Author: Darsh
 */

#ifndef INC_MCAL_GPIO_H_
#define INC_MCAL_GPIO_H_

/* * * * * * * * * * * * * * * * * * * * * *
 *
 * INCLUDES
 *
 * * * * * * * * * * * * * * * * * * * * * */

#include <stm32f103c6.h>
//==================================================================================


/* * * * * * * * * * * * * * * * * * * * * *
 *
 * CONFIGURATION REFERENCES
 *
 * * * * * * * * * * * * * * * * * * * * * */

/* * * * *
 * @ref GPIO_PINS_DEFINES
 * * * * */
typedef enum
{
 	GPIO_PIN_0		=		((uint8_t)0x00),	/*	Pin 0 is selected	*/
	GPIO_PIN_1		=		((uint8_t)0x01),	/*	Pin 1 is selected	*/
	GPIO_PIN_2		=		((uint8_t)0x02),	/*	Pin 2 is selected	*/
	GPIO_PIN_3		=		((uint8_t)0x03),	/*	Pin 3 is selected	*/
 	GPIO_PIN_4		=		((uint8_t)0x04),	/*	Pin 4 is selected	*/
 	GPIO_PIN_5		=		((uint8_t)0x05),	/*	Pin 5 is selected	*/
 	GPIO_PIN_6		=		((uint8_t)0x06),	/*	Pin 6 is selected	*/
	GPIO_PIN_7		=		((uint8_t)0x07),	/*	Pin 7 is selected	*/
 	GPIO_PIN_8		=		((uint8_t)0x08),	/*	Pin 8 is selected	*/
 	GPIO_PIN_9		=		((uint8_t)0x09),	/*	Pin 9 is selected	*/
 	GPIO_PIN_10		=		((uint8_t)0x0A),	/*	Pin 10 is selected	*/
 	GPIO_PIN_11		=		((uint8_t)0x0B),	/*	Pin 11 is selected	*/
	GPIO_PIN_12		=		((uint8_t)0x0C),	/*	Pin 12 is selected	*/
	GPIO_PIN_13		=		((uint8_t)0x0D),	/*	Pin 13 is selected	*/
	GPIO_PIN_14		=		((uint8_t)0x0E),	/*	Pin 14 is selected	*/
	GPIO_PIN_15		=		((uint8_t)0x0F)		/*	Pin 15 is selected	*/
}GPIO_PINS_t;

/* * * * *
 * @ref GPIO_MODE_DEFINES
 * * * * */
typedef enum
{
	GPIO_MODE_OUTPUT_PP		=	((uint8_t)0x000),	/*	output push-pull mode				*/
	GPIO_MODE_OUTPUT_OD		=	((uint8_t)0x001),	/*	output open-drain mode				*/
	GPIO_MODE_OUTPUT_AF_PP	=	((uint8_t)0x002),	/*	output alternate push-pull mode		*/
	GPIO_MODE_OUTPUT_AF_OD	=	((uint8_t)0x003),	/*	output alternate open-drain mode	*/

	GPIO_MODE_ANALOG		=	((uint8_t)0x004),	/*	analog mode							*/
	GPIO_MODE_INPUT_FLO		=	((uint8_t)0x008),	/*	input floating mode					*/
	GPIO_MODE_INPUT_PD		=	((uint8_t)0x00C),	/*	input with pull down mode			*/
	GPIO_MODE_INPUT_PU		=	((uint8_t)0x00D)	/*	input with pull up mode				*/
}GPIO_MODE_t;



/* * * * *
 * @ref GPIO_OUTPUTSPEED_DEFINES
 * * * * */
typedef enum
{
	GPIO_OUTPUTSPEED10M		=	((uint8_t)0x001),	/*	output mode	max speed 10 M		*/
	GPIO_OUTPUTSPEED2M		=	((uint8_t)0x002),	/*	output mode	max speed 2 M		*/
	GPIO_OUTPUTSPEED50M		=	((uint8_t)0x003)	/*	output mode	max speed 50 M		*/
}GPIO_OUTPUTSPEED_t;

/* * * * *
 * @ref GPIO_PIN_STATE_DEFINES
 * * * * */
typedef enum
{
	GPIO_PIN_HIGH		=		((uint8_t)1),
 	GPIO_PIN_LOW		=		((uint8_t)0),
}GPIO_PIN_STATE_t;

/* * * * *
 * @ref GPIO_LOCK_FEEDBACK_DEFINES
 * * * * */

typedef enum
{
	GPIO_LOCK_DONE		=		((uint8_t)1),
	GPIO_LOCK_ERROR		=		((uint8_t)0),
}GPIO_LOCK_FEEDBACK_t;


/* * * * * * * * * * * * * * * * * * * * * *
 *
 * TYPE DEFINITIONS		(STRUCTURES)
 *
 * * * * * * * * * * * * * * * * * * * * * */

typedef struct
{
	GPIO_PINS_t 		GPIO_PinNumber;		//Specifies the GPIO pin to be configured
											//This parameter must be a value of @ref GPIO_PINS_DEFINES

	GPIO_MODE_t			GPIO_PinMode;		//specifies the operating mode of the selected pin
											//This must be a value of @ref GPIO_MODE_DEFINES

	GPIO_OUTPUTSPEED_t	GPIO_OutputSpeed;	//Specifies the speed of the pin in case of being output
											//This parameter must be a value of @ref GPIO_OUTPUTSPEED_DEFINES
}GPIO_PinConfig_t;



/* * * * * * * * * * * * * * * * * * * * * *
 *
 * APIs Supported by "MCAL GPIO DRIVER"
 *
 * * * * * * * * * * * * * * * * * * * * * */


void MCAL_GPIO_Init(GPIO_t * GPIOx ,GPIO_PinConfig_t * PinConfig);
void MCAL_GPIO_DeInit(GPIO_t * GPIOx);

GPIO_PIN_STATE_t MCAL_GPIO_ReadPin(GPIO_t * GPIOx , GPIO_PINS_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_t * GPIOx);

void MCAL_GPIO_WritePin(GPIO_t * GPIOx , GPIO_PINS_t PinNumber , GPIO_PIN_STATE_t Value);
void MCAL_GPIO_WritePort(GPIO_t * GPIOx, uint16_t Value);

void MCAL_GPIO_TogglePin(GPIO_t * GPIOx , GPIO_PINS_t PinNumber);

GPIO_LOCK_FEEDBACK_t MCAL_GPIO_LockPin(GPIO_t * GPIOx , GPIO_PINS_t PinNumber);
#endif /* INC_MCAL_GPIO_H_ */
