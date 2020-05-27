
/* Library */
#include "STD_TYPES.h"
#include "delay.h"

/* MCAL */
#include "RCC.h"
#include "GPIO.h"

/* HAL */
#include "CLCD_interface.h"

/* Kernel */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"


/* Task Priority*/
#define TASK1_PRIORITY		(2)
#define TASK2_PRIORITY		(1)


/* Private Function Prototype */
static void Task_1( void *pvParameters );
static void Task_2( void *pvParameters );

/* Global Variable */
SemaphoreHandle_t xSemaphore;

/*********************************** main ****************/
int main(void)
{
	/* RCC */
	RCC_SetClock( RCC_CR_HSE ,ON);
	Select_SystemClock(RCC_CFGR_SW_HSE);
	RCC_EnablePeripheral_APB2(RCC_APB2ENR_IOPAEN_PORTA);

	/* GPIO LCD PINs OUTPUT MODE */
	for(u8 idx=0 ; idx <11 ;idx++)
	{
		DIO_SetPinMode('A',idx ,0b0010);
	}

	/* LCD */
	CLCD_voidInitialize(); /* Initialize LCD */
	CLCD_Clear();          /* Clear LCD */

	xSemaphore = xSemaphoreCreateCounting( 1, 1 );

	/* Create Task 1 */
	xTaskCreate( Task_1, "Task_1", 100, NULL, TASK1_PRIORITY, NULL );

	/* Create Task 2 */
	xTaskCreate( Task_2, "Task_2", 100, NULL, TASK2_PRIORITY, NULL );

	/* Start Scheduler */
	vTaskStartScheduler();
	while(1)
	{

	}
}

/*********************************** Task1 ****************/
static void Task_1( void *pvParameters )
{
	while(1)
	{
		if(xSemaphoreTake( xSemaphore, 10000 )== pdTRUE ) /* Take Semaphore */
		{
			CLCD_Clear();  /* Clear LCD */
			CLCD_voidWriteString("Task1"); /* Display Data in LCD */
			_delay_ms(3000);              /* delay 3sec */
		}
		xSemaphoreGive(xSemaphore);  /* Release Semaphore */
		vTaskDelay(2000);    /* waiting 2 sec*/
	}
}

/*********************************** Task2 ****************/
static void Task_2( void *pvParameters )
{
	while(1)
	{
		if(xSemaphoreTake( xSemaphore, 10000 )== pdTRUE )  /* Take Semaphore */
		{
			CLCD_Clear(); /* Clear LCD */
			CLCD_voidWriteString("Task2");  /* Display Data in LCD */
			_delay_ms(1000);  /* delay 1sec */
		}
		xSemaphoreGive(xSemaphore);   /* Release Semaphore */
		vTaskDelay(2000);   /* waiting 2 sec*/
	}
}

