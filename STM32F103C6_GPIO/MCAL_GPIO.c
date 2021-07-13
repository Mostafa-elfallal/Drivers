/*
 * MCAL_GPIO.c
 *
 *  Created on: Jul 12, 2021
 *      Author: Darsh
 */
#include "MCAL_GPIO.h"
/*
 * This function is used for getting the start position for every pin in the CRL or CRH registers
 * */
uint8_t getCRLHPos(uint8_t pinNumber)
{
	if(pinNumber < GPIO_PIN_8)
	{
		return	(pinNumber * 4);
	}
	else{
		return	((pinNumber - GPIO_PIN_8) * 4);
	}
}

/* * * * * * * * * * * * * * * * * * * * * *
 *	@Fn				-MCAL_GPIO_Init
 * 	@brief			-Initializes the GPIOx PINy according to specified parameters in PinConfig
 *	@param [in]		-GPIOx : pointer to  GPIO_t where x can be A ->> E to select the required peripheral
 *	@param [in]		-PinConfig : pointer to GPIO_PinConfig_t structure that contains
 *						the configuration of the pin
 *	@param [out]	-none
 *	@retval 		-none
 *	Note 			-none
 * * * * * * * * * * * * * * * * * * * * * */

void MCAL_GPIO_Init(GPIO_t * GPIOx ,GPIO_PinConfig_t * PinConfig)
{
	volatile uint32_t* configReg = NULL;

	configReg = (PinConfig->GPIO_PinNumber < GPIO_PIN_8)?	&GPIOx->CRL : &GPIOx->CRH;
	uint8_t RegVal = 0;
	//clear the 4bits
	(*configReg) &= ~( 0x0F << getCRLHPos(PinConfig->GPIO_PinNumber));
	//is it output ?
	if(PinConfig->GPIO_PinMode <= GPIO_MODE_OUTPUT_AF_OD)
	{
		RegVal = (PinConfig->GPIO_PinMode << 2) | (PinConfig->GPIO_OutputSpeed );
	}
	else
	{
		//it's input
		if(PinConfig->GPIO_PinMode != GPIO_MODE_INPUT_PU)
		{
			RegVal = (PinConfig->GPIO_PinMode) -4;	//4 is shift to separate ranges
			//o/p from 0 to 3 & i/p from 4 to D
			GPIOx->ODR &= ~((uint32_t)(1<< PinConfig->GPIO_PinNumber));
		}
		else{
			RegVal =(PinConfig->GPIO_PinMode) -5;		// PD is the same as PU here
			// so we removed shift and converted
			// it back to PU
			GPIOx->ODR |= (1<< (PinConfig->GPIO_PinNumber));
		}
	}
	(*configReg) |= (RegVal << getCRLHPos(PinConfig->GPIO_PinNumber));
}


/* * * * * * * * * * * * * * * * * * * * * *
 *	@Fn				-MCAL_GPIO_DeInit
 * 	@brief			-resets the GPIOx peripheral registers
 *	@param [in]		-GPIOx : pointer to  GPIO_t where x can be A ->> E to select the required peripheral
 *	@param [out]	-none
 *	@retval 		-none
 *	Note 			-none
 * * * * * * * * * * * * * * * * * * * * * */

void MCAL_GPIO_DeInit(GPIO_t * GPIOx)
{
	uint8_t Regval = (uint8_t)(((uint32_t)GPIOx >> 10)&0x0f);
	RCC->APB2RSTR |=  (uint32_t)(1<<Regval);
	RCC->APB2RSTR &= ~(uint32_t)(1<<Regval);
}


/* * * * * * * * * * * * * * * * * * * * * *
 *	@Fn				-MCAL_GPIO_ReadPin
 * 	@brief			-Read specific pin
 *	@param [in]		-GPIOx : pointer to  GPIO_t where x can be A ->> E to select the required peripheral
 *	@param [in]		-PinNumber : set the pin number according to @ref GPIO_PINS_DEFINES
 *	@param [out]	-the input on the specified pin
 *	@retval 		-uint8_t : unsigned 1 byte @ref GPIO_PIN_STATE_DEFINES
 *	Note 			-none
 * * * * * * * * * * * * * * * * * * * * * */
GPIO_PIN_STATE_t MCAL_GPIO_ReadPin(GPIO_t * GPIOx , GPIO_PINS_t PinNumber)
{
	GPIO_PIN_STATE_t bit;
	if((GPIOx->IDR & (1<<PinNumber)) != (uint32_t)GPIO_PIN_LOW){
		bit = GPIO_PIN_HIGH;
	}
	else{
		bit = GPIO_PIN_LOW;
	}
	return bit;
}

/* * * * * * * * * * * * * * * * * * * * * *
 *	@Fn				-MCAL_GPIO_ReadPort
 * 	@brief			-Read specific port
 *	@param [in]		-GPIOx : pointer to  GPIO_t where x can be A ->> E to select the required peripheral
 *	@param [out]	-the input on the specified port
 *	@retval 		-uint8_t : unsigned 2 byte
 *	Note 			-none
 * * * * * * * * * * * * * * * * * * * * * */
uint16_t MCAL_GPIO_ReadPort(GPIO_t * GPIOx)
{
	uint16_t PortVal = (uint16_t)GPIOx->IDR;
	return PortVal;
}

/* * * * * * * * * * * * * * * * * * * * * *
 *	@Fn				-MCAL_GPIO_WritePin
 * 	@brief			-write a value on a specific pin
 *	@param [in]		-GPIOx : pointer to  GPIO_t where x can be A ->> E to select the required peripheral
 *	@param [in]		-PinNumber : set the pin number according to @ref GPIO_PINS_DEFINES
 *	@param [in]		-Value : the value to be written on the pin @ref GPIO_PIN_STATE_DEFINES
 *	@param [out]	-none
 *	@retval 		-none
 *	Note 			-none
 * * * * * * * * * * * * * * * * * * * * * */
void MCAL_GPIO_WritePin(GPIO_t * GPIOx , GPIO_PINS_t PinNumber , GPIO_PIN_STATE_t Value)
{
	if(Value != GPIO_PIN_LOW){
		GPIOx->ODR |= (uint32_t)(1<<PinNumber);
	}
	else{
		GPIOx->ODR &= ~((uint32_t)(1<<PinNumber));
	}
}

/* * * * * * * * * * * * * * * * * * * * * *
 *	@Fn				-MCAL_GPIO_WritePort
 * 	@brief			-write a value on a specific pin
 *	@param [in]		-GPIOx : pointer to  GPIO_t where x can be A ->> E to select the required peripheral
 *	@param [in]		-Value : the value to be written on the port
 *	@param [out]	-none
 *	@retval 		-none
 *	Note 			-The configuration will be frozen
 * * * * * * * * * * * * * * * * * * * * * */
void MCAL_GPIO_WritePort(GPIO_t * GPIOx, uint16_t Value)
{
	GPIOx->ODR = (uint32_t)Value;
}

/* * * * * * * * * * * * * * * * * * * * * *
 *	@Fn				-MCAL_GPIO_TogglePin
 * 	@brief			-Toggles specific pin
 *	@param [in]		-GPIOx : pointer to  GPIO_t where x can be A ->> E to select the required peripheral
 *	@param [in]		-PinNumber : set the pin number according to @ref GPIO_PINS_DEFINES
 *	@param [out]	-none
 *	@retval 		-none
 *	Note 			-none
 * * * * * * * * * * * * * * * * * * * * * */
void MCAL_GPIO_TogglePin(GPIO_t * GPIOx , GPIO_PINS_t PinNumber)
{
	GPIOx->ODR ^= ((uint32_t)(1<<PinNumber));
}

/* * * * * * * * * * * * * * * * * * * * * *
 *	@Fn				-MCAL_GPIO_LockPin
 * 	@brief			-Locks specific pin
 *	@param [in]		-GPIOx : pointer to  GPIO_t where x can be A ->> E to select the required peripheral
 *	@param [in]		-PinNumber : set the pin number according to @ref GPIO_PINS_DEFINES
 *	@param [out]	-none
 *	@retval 		-uint8_t value according to @ref GPIO_LOCK_FEEDBACK_DEFINES
 *	Note 			-the return is DONE if it's successfully locked or ERROR if not
 * * * * * * * * * * * * * * * * * * * * * */
GPIO_LOCK_FEEDBACK_t MCAL_GPIO_LockPin(GPIO_t * GPIOx , GPIO_PINS_t PinNumber)
{
	volatile uint32_t temp = (1<<16) | (1<< PinNumber);
	GPIOx->LCKR = temp;
	GPIOx->LCKR = (1<< PinNumber);
	GPIOx->LCKR = temp;
	temp = GPIOx->LCKR;
	if((uint32_t)(GPIOx->LCKR & ( 1 << 16)))
	{
		return GPIO_LOCK_DONE;
	}
	else{
		return GPIO_LOCK_ERROR;
	}
}

