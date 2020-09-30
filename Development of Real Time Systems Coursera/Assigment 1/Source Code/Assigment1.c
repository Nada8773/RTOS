#include <stdio.h>
#include <conio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

void Task1_100ms();
void Task2_500ms();



TaskHandle_t myTaskHandle =NULL ;

#define TASK1_STACKSIZE  1000
#define TASK2_STACKSIZE  100
#define TASK1_PRIORITY   3
#define TASK2_PRIORITY   1


void main_task( void )
{


	xTaskCreate(Task1_100ms, "task1", TASK1_STACKSIZE, NULL, TASK1_PRIORITY , &myTaskHandle);
	xTaskCreate(Task2_500ms, "task2", TASK2_STACKSIZE, NULL, TASK2_PRIORITY , &myTaskHandle);

	vTaskStartScheduler();

	while(1)
	{

	}
}

void Task1_100ms()
{
	while(1)
	{
		printf("This is task 1 \n");

		vTaskDelay(100);  /* 100ms */
	}
}


void Task2_500ms()
{
	while(1)
	{
		printf("This is task 2 \n");

		vTaskDelay(500);  /* 500ms */
	}
}
