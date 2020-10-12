
/********************************************************************************
 **  FILENAME     : Assigment5.c         			                           **
 **  VERSION      : 1.0                                                         **
 **  DATE         : 13 Oct 2020                                                 **
 **  AUTHOR       : Nada Mohamed                                                **
 **  Description  : Send Data Throught Queue.                                      **
 *******************************************************************************/

#include <stdio.h>
#include <conio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"



static void matrix_task();
static void Receiver_Task();

/* Handlers for the tasks */
TaskHandle_t matrix_handle = NULL;
TaskHandle_t Receiver_handle = NULL;

QueueHandle_t xQueue ;

#define SIZE 10
#define ROW SIZE
#define COL SIZE

struct AMessage
{
	double **c;
}xMessage;


void main_task( void )
{

	xTaskCreate((pdTASK_CODE)matrix_task, (signed char *)"Matrix", 1000, NULL, 3, &matrix_handle);

	xTaskCreate((pdTASK_CODE)Receiver_Task, (signed char *)"Receiver", 1000, NULL, 2, &Receiver_handle);

	/* Create a queue capable of containing 10 * 10 unsigned double values. */
	xQueue = xQueueCreate( 10 * 10, sizeof(xMessage) );

	if( xQueue == NULL )
	{
		/* Queue was not created and must not be used. */
		printf("Queue was not created\n");
	}
	// This starts the real-time scheduler
	vTaskStartScheduler();

	while(1)
	{

	}
}




static void matrix_task()
{
	int i;
	double **a = (double **)pvPortMalloc(ROW * sizeof(double*));
	for (i = 0; i < ROW; i++) a[i] = (double *)pvPortMalloc(COL * sizeof(double));
	double **b = (double **)pvPortMalloc(ROW * sizeof(double*));
	for (i = 0; i < ROW; i++) b[i] = (double *)pvPortMalloc(COL * sizeof(double));
	double **c = (double **)pvPortMalloc(ROW * sizeof(double*));
	for (i = 0; i < ROW; i++) c[i] = (double *)pvPortMalloc(COL * sizeof(double));

	double sum = 0.0;
	int j, k, l;

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			a[i][j] = 1.5;
			b[i][j] = 2.6;
		}
	}

	while (1) {
		/*
		 * In an embedded systems, matrix multiplication would block the CPU for a long time
		 * but since this is a PC simulator we must add one additional dummy delay.
		 */
		long simulationdelay;
		for (simulationdelay = 0; simulationdelay<1000000000; simulationdelay++)
			;
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				c[i][j] = 0.0;
			}
		}

		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				sum = 0.0;
				for (k = 0; k < SIZE; k++) {
					for (l = 0; l<10; l++) {
						sum = sum + a[i][k] * b[k][j];
					}
				}
				c[i][j] = sum;
			}
		}



		xMessage.c = (double **)pvPortMalloc(ROW * sizeof(double*));
		for (i = 0; i < ROW; i++) xMessage.c[i] = \
				(double *)pvPortMalloc(COL * sizeof(double));
		for (i = 0; i < SIZE; i++)
		{
			for (j = 0; j < SIZE; j++)
			{
				xMessage.c[i][j] = c[i][j];
				c[i][j] = 0.0;
			}
		}

		printf("Send Data \n");
		fflush(stdout);

		if( xQueueSend( xQueue,  ( void * ) &xMessage, ( TickType_t ) 10 ) != pdPASS )
		{
			/* Failed to post the message, even after 10 ticks. */
			printf("Failed to post the message, even after 10 ticks\n");

		}
		vTaskDelay(100);
	}
}

static void Receiver_Task()
{
	struct AMessage ReceivedValue;

	for( ;; )
	{
		if(xQueue != NULL)
		{
			if (xQueueReceive( xQueue, &ReceivedValue, ( TickType_t ) 10 ) == pdPASS)
			{
				for (int i = 0; i < SIZE; i++)
				{
					for (int j = 0; j < SIZE; j++)
					{
						printf("Received Data = %f \n",ReceivedValue.c[i][j]);
					    fflush(stdout);
					}
				}
			}
		}

		vTaskDelay(100);
	}
}
