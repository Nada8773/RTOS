
/********************************************************************************
 **  FILENAME     : Assigment4.c         			                           **
 **  VERSION      : 1.0                                                         **
 **  DATE         : 30 Sep 2020                                                 **
 **  AUTHOR       : Nada Mohamed                                                **
 **  Description  : handle aperiodic jobs.                                      **
 *******************************************************************************/

#include <stdio.h>
#include <conio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

static void matrix_task();
static void aperiodic_task();

#define SIZE 10
#define ROW SIZE
#define COL SIZE

/* Handlers for the tasks */
TaskHandle_t matrix_handle = NULL;
TaskHandle_t aperiodic_handle = NULL;
TimerHandle_t xTimers = NULL;

int MatrixTask = FALSE;
long MatrixTaskTick=0;
int AperiodicTask = FALSE;
long AperiodTaskTick = 0;

/* A variable to hold a count of the number of times the timer expires. */
long lExpireCounters = 0;
void vTimerCallback(TimerHandle_t pxTimer)
{
	printf("Timer callback!\n");
	AperiodTaskTick=0;

	xTaskCreate((pdTASK_CODE)aperiodic_task, (signed char *)"Aperiodic", configMINIMAL_STACK_SIZE, NULL, 3, &aperiodic_handle);
	long lArrayIndex;
	const long xMaxExpiryCountBeforeStopping = 10;
	/* Optionally do something if the pxTimer parameter is NULL. */
	configASSERT(pxTimer);
	/* Increment the number of times that pxTimer has expired. */
	lExpireCounters += 1;
	/* If the timer has expired 10 times then stop it from running. */
	if (lExpireCounters == xMaxExpiryCountBeforeStopping) {
		/* Do not use a block time if calling a timer API function from a
		timer callback function, as doing so could cause a deadlock! */
		xTimerStop(pxTimer, 0);
	}
}
void main_task( void )
{


	xTimers = xTimerCreate
			(/* Just a text name, not used by the RTOS
                     kernel. */
					"Timer",
					/* The timer period in ticks, must be
                     greater than 0. */
					pdMS_TO_TICKS(5000),
					/* The timers will auto-reload themselves
                     when they expire. */
					pdTRUE,
					/* The ID is used to store a count of the
                     number of times the timer has expired, which
                     is initialised to 0. */
					( void * ) 0,
					/* Each timer calls the same callback when
                     it expires. */
					vTimerCallback
			);
	if( xTimers == NULL )
	{
		/* The timer was not created. */
		printf("The timer was not created\n");
	}
	else
	{
		 /* Start the timer.  No block time is specified, and
		             even if one was it would be ignored because the RTOS
		             scheduler has not yet been started. */
		             if( xTimerStart( xTimers, 0 ) != pdPASS )
		             {
		                 /* The timer could not be set into the Active
		                 state. */
		         		printf("The timer Fail \n");

		             }
	}

	xTaskCreate((pdTASK_CODE)matrix_task, (signed char *)"Matrix", 1000, NULL, 3, &matrix_handle);

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
		printf("matrix task started !\n");

		MatrixTaskTick = 0;

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

      	printf("Matrix Task Execution Time = %i ms \n",MatrixTaskTick);
	    fflush(stdout);
	    MatrixTaskTick=0;
		vTaskDelay(100);
	}
}
static void aperiodic_task()
{
	TickType_t initial = xTaskGetTickCount();
	printf("Aperiodic task started!\n");
	fflush(stdout);
	long i;
	for (i = 0; i<1000000000; i++); //Dummy workload
	printf("Aperiodic task done!\n");
	fflush(stdout);

	printf("Response Time is : %d\n",xTaskGetTickCount() - initial);
	fflush(stdout);

	vTaskDelete(aperiodic_handle);
}

