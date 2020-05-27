/**
 * @file GPIO.h
 * @author Mariam El-Shakafi (mariam.elshakafi@gmail.com)
 * @brief This is the user interface for the GPIO driver
 * @version 0.1
 * @date 2020-04-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */


#ifndef GPIO_H
#define GPIO_H


/**
 * @brief GPIO initialization structure
 * This should be configured using proper macros before calling GPIO_init API
 *
 */
typedef struct
{
u32 port;
u32 pin;
u32 speed;
u32 mode;
} GPIO_initStruct;


/******** Masks used for GPIO_initStruct parameters *******/

/**
 * @brief GPIO configuration for port parameter
 * 
 */
#define GPIO_PORTA           (0x40010800)
#define GPIO_PORTB           (0x40010C00)
#define GPIO_PORTC           (0x40011000)


/**
 * @brief GPIO configuration for pin parameter
 * 
 */ 
#define GPIO_PIN_0                 0x0001
#define GPIO_PIN_1                 0x0002
#define GPIO_PIN_2                 0x0004
#define GPIO_PIN_3                 0x0008
#define GPIO_PIN_4                 0x0010
#define GPIO_PIN_5                 0x0020
#define GPIO_PIN_6                 0x0040
#define GPIO_PIN_7                 0x0080
#define GPIO_PIN_8                 0x0100
#define GPIO_PIN_9                 0x0200
#define GPIO_PIN_10                0x0400
#define GPIO_PIN_11                0x0800
#define GPIO_PIN_12                0x1000
#define GPIO_PIN_13                0x2000
#define GPIO_PIN_14                0x4000
#define GPIO_PIN_15                0x8000

/**
 * @brief GPIO configuration for speed parameter
 * 
 */
#define GPIO_INPUT              0x00000000
#define GPIO_OUTPUT_10MHZ       0x00000001
#define GPIO_OUTPUT_2MHZ        0x00000002
#define GPIO_OUTPUT_50MHZ       0x00000003

/**
 * @brief GPIO configuration for mode parameter
 * 
 */
#define GPIO_INPUT_ANALOG       0x00000000
#define GPIO_INPUT_FLOAT        0x00000004
#define GPIO_INPUT_PULL_UP      0x00000018
#define GPIO_INPUT_PULL_DOWN    0x00000028
#define GPIO_OUTPUT_GP_PP       0x00000000
#define GPIO_OUTPUT_GP_OD       0x00000004
#define GPIO_OUTPUT_AF_PP       0x00000008
#define GPIO_OUTPUT_AF_OD       0x0000000c


/******** Masks used for val input in GPIO_writePin() API *******/
#define GPIO_PIN_SET                     1
#define GPIO_PIN_RESET                   0


/**
 * @brief Initializes GPIO object for use
 * Note that you should enable clock for the peripheral before attempting to initialize
 *
 * @param gpioObj a GPIO_initStruct that states the proper configuration for the pin/pins
 *
 */
extern void GPIO_init(GPIO_initStruct* gpioObj);

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
extern void GPIO_writePin(GPIO_initStruct* gpioObj, u8 val, u32 pin);

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
extern u8 GPIO_readPin(GPIO_initStruct* gpioObj, u32 pin);

#endif
