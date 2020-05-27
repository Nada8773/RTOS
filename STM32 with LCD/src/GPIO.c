/**
 * @file GPIO.c
 * @author Mariam El-Shakafi (mariam.elshakafi@gmail.com)
 * @brief This is the implementation for the GPIO driver
 * @version 0.1
 * @date 2020-04-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Std_Types.h"
#include "GPIO.h"


typedef struct
{
u32 CRL;
u32 CRH;
u32 IDR;
u32 ODR;
u32 BSRR;
u32 BRR;
u32 LCKR;
} GPIO_regMap;

/* Set masks */
#define GPIO_MODE_CNF_SETMASK    0x0000000F
#define GPIO_IS_CRL              0x000000FF
#define GPIO_IS_CRH              0x0000FF00


/**
 * @brief Initializes GPIO object for use
 * Note that you should enable clock for the peripheral before attempting to initialize
 *
 * @param gpioObj a GPIO_initStruct that states the proper configuration for the pin/pins
 *
 */
void GPIO_init(GPIO_initStruct* gpioObj)
{
  volatile GPIO_regMap* gpioBase = (volatile GPIO_regMap*)gpioObj->port;
  u32 gpioModSpeed = (gpioObj->speed) | ((gpioObj->mode)&GPIO_MODE_CNF_SETMASK);
  
  u8 bitPos = 0;
  u8 shiftVal = 0;
  /* Lower 8 pins */
  if((gpioObj->pin)&GPIO_IS_CRL)
  {
    for(bitPos = 0; bitPos < 8; bitPos++)
    {
      shiftVal = bitPos << 2;
      if((gpioObj->pin)&(1 << bitPos))
      {
        gpioBase->CRL &= ~(GPIO_MODE_CNF_SETMASK << shiftVal);
        gpioBase->CRL |= (gpioModSpeed << shiftVal);
        if((gpioObj->mode) == GPIO_INPUT_PULL_UP)
        {
          gpioBase->BSRR = (1 << bitPos);
        }
        else if ((gpioObj->mode) == GPIO_INPUT_PULL_DOWN)
        {
          gpioBase->BRR = (1 << bitPos);
        }
      }
    }
  }
  
  /* Upper 8 pins */
  if((gpioObj->pin)&GPIO_IS_CRH)
  {
    u32 shiftedPin = ((gpioObj->pin) >> 8);
    for(bitPos = 0; bitPos < 8; bitPos++)
    {
      shiftVal = bitPos << 2;
      if(shiftedPin&(1 << bitPos))
      {
        gpioBase->CRH &= ~(GPIO_MODE_CNF_SETMASK << shiftVal);
        gpioBase->CRH |= (gpioModSpeed << shiftVal);
        if((gpioObj->mode) == GPIO_INPUT_PULL_UP)
        {
          gpioBase->BSRR = (1 << (bitPos + 8));
        }
        else if ((gpioObj->mode) == GPIO_INPUT_PULL_DOWN)
        {
          gpioBase->BRR = (1 << (bitPos + 8));
        }
      }
    }
  }
}


/**
 * @brief Sets/ resets pin according to given val
 * 
 * @param gpioObj a GPIO_initStruct that has been already initialized using GPIO_init
 * @param val States whether to set or reset the given pin
 *        @arg GPIO_PIN_SET
 *        @arg GPIO_PIN_RESET
 * @param pin States the pin number
 *        @arg GPIO_PIN_0 
 *        @arg GPIO_PIN_1 
 *        @arg GPIO_PIN_2 
 *        @arg GPIO_PIN_3 
 *        @arg GPIO_PIN_4 
 *        @arg GPIO_PIN_5 
 *        @arg GPIO_PIN_6 
 *        @arg GPIO_PIN_7 
 *        @arg GPIO_PIN_8 
 *        @arg GPIO_PIN_9 
 *        @arg GPIO_PIN_10
 *        @arg GPIO_PIN_11
 *        @arg GPIO_PIN_12
 *        @arg GPIO_PIN_13
 *        @arg GPIO_PIN_14
 *        @arg GPIO_PIN_15
 *
 */
void GPIO_writePin(GPIO_initStruct* gpioObj, u8 val, u32 pin)
{
  GPIO_regMap* gpioBase = (GPIO_regMap*)gpioObj->port;
  switch(val)
  {
    case GPIO_PIN_SET:
      gpioBase->BSRR = pin;
    break;

    case GPIO_PIN_RESET:
      gpioBase->BRR = pin;
    break;
  }
}


/**
 * @brief Reads pin value
 * 
 * @param gpioObj a GPIO_initStruct that has been already initialized using GPIO_init
 *
 * @param pin States the pin number
 *        @arg GPIO_PIN_0 
 *        @arg GPIO_PIN_1 
 *        @arg GPIO_PIN_2 
 *        @arg GPIO_PIN_3 
 *        @arg GPIO_PIN_4 
 *        @arg GPIO_PIN_5 
 *        @arg GPIO_PIN_6 
 *        @arg GPIO_PIN_7 
 *        @arg GPIO_PIN_8 
 *        @arg GPIO_PIN_9 
 *        @arg GPIO_PIN_10
 *        @arg GPIO_PIN_11
 *        @arg GPIO_PIN_12
 *        @arg GPIO_PIN_13
 *        @arg GPIO_PIN_14
 *        @arg GPIO_PIN_15
 *
 * @return u8 Returns the value of the pin
 *        GPIO_PIN_SET
 *        GPIO_PIN_RESET
 */
u8 GPIO_readPin(GPIO_initStruct* gpioObj, u32 pin)
{
  u8 pinStat = 0;
  GPIO_regMap* gpioBase = (GPIO_regMap*)gpioObj->port;
  if((gpioBase->IDR)&pin)
  {
    pinStat = GPIO_PIN_SET;
  }
  else
  {
    pinStat = GPIO_PIN_RESET;
  }
  return pinStat;
}
