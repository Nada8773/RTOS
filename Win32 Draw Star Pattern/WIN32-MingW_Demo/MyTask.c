
/* Standard includes. */
#include <stdio.h>
#include <conio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

#define MAX_NUM   7
static int first_run=0;

#define   NULL  ((void*)0)
TaskHandle_t myTaskHandle =NULL ;
static int counter = 0;
void Task_5ms ()
{
	while(1)
	{
		if(counter == MAX_NUM)
		{
			printf("\t Task 1 is running \n");
			counter=0;
			first_run=0;
		}

		if(counter == 0 && first_run == 0)
		{
			printf("Tringle2 \t");
		}
		else
		{
			/* Draw one row of star pattern */
			for (int j = counter; j < MAX_NUM-1; j++)
			{
				printf(" ");
			}
			for (int k = 0; k < 2*counter + 1; k++)
			{
				printf("*");
			}
		}
		printf("\t\t\t");

		vTaskDelay(5);  /* 5ms */
	}
}


void Task_10ms ()
{
	//printf("\b \b \b \b \b \b \b");
	while(1)
	{


		if(counter == 0 && first_run == 0)
		{
			printf("Tringle1 \n");
			first_run =1;
		}
		//if(counter==0)printf("\t");

		else
		{
			if(counter==0)printf("\t");


			/* Draw one row of star pattern */
			for (int j = counter; j < MAX_NUM-1; j++)
			{
				printf(" ");
			}
			for (int k = 0; k < 2*counter + 1; k++)
			{
				printf("*");
			}
			counter++;
			printf("\n");
			if(counter == MAX_NUM)
			{
				printf("\nTask 2 is running\t");
			}

		}
		vTaskDelay(5);  /* 5ms */
	}
}


void main_task( void )
{


	xTaskCreate(Task_5ms, "task1", 200 ,(void*)0 ,tskIDLE_PRIORITY , &myTaskHandle);
	xTaskCreate(Task_10ms, "task2", 200 ,(void*)0 ,tskIDLE_PRIORITY , &myTaskHandle);

	vTaskStartScheduler();

	while(1)
	{

	}
}
