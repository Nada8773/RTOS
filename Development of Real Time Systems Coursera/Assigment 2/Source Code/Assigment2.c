
/********************************************************************************
**  FILENAME     : Assigment2.c         			                           **
**  VERSION      : 1.0                                                         **
**  DATE         : 14 Sep 2020                                                 **
**  AUTHOR       : Nada Mohamed                                                **
**  Description  : "communicationtask" must send a simulated data packet every **
**                  200ms but is often blocked by matrixtask, fix this problem **
**                  without changing the functionality in the tasks.           **
*******************************************************************************/

#include <stdio.h>
#include <conio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

static void matrix_task();
static void communication_task();
static void prioritysettask();



#define SIZE 10
#define ROW SIZE
#define COL SIZE
#define FALSE 0
#define TRUE 1
#define HighestCommunicationPriority 4
#define LowestCommunicationPriority 2

int CommunicationTask = FALSE;
int MatrixTask = FALSE;
long CommunicationTaskTick=0;
long MatrixTaskTick=0;

/* Handlers for the tasks */
TaskHandle_t matrix_handle = NULL;
TaskHandle_t communication_handle = NULL;
TaskHandle_t priorityset_handle = NULL;


void main_task( void )
{

	xTaskCreate((pdTASK_CODE)matrix_task, (signed char *)"Matrix", 1000, NULL, 3, &matrix_handle);
	xTaskCreate((pdTASK_CODE)communication_task, (signed char *)"Communication", configMINIMAL_STACK_SIZE, NULL, 1, &communication_handle);
	xTaskCreate((pdTASK_CODE)prioritysettask, (signed char *)"priorityset", configMINIMAL_STACK_SIZE, NULL, 5, &priorityset_handle);


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

		MatrixTask = TRUE;
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
        MatrixTask = FALSE;
    	printf("Matrix Task Execution Time = %i ms \n",MatrixTaskTick * portTICK_PERIOD_MS);
		fflush(stdout);
		vTaskDelay(100);
	}
}

static void communication_task()
{
	while (1) {
		printf("Communication Task \n");
		fflush(stdout);

		CommunicationTask = TRUE;
		CommunicationTaskTick = 0;

		printf("Sending data...\n");
		fflush(stdout);
		vTaskDelay(100);
		printf("Data sent!\n");
		fflush(stdout);
		vTaskDelay(100);
		fflush(stdout);

		CommunicationTask = FALSE;
		printf("Communication Task Execution Time = %i\n",CommunicationTaskTick * portTICK_PERIOD_MS);
		fflush(stdout);
	}
}


static void prioritysettask()
{
	static int CommunicationTaskExecutionTime  = 0;
	CommunicationTaskExecutionTime = CommunicationTaskTick * portTICK_PERIOD_MS;
	printf("Priority Task\n");
	fflush(stdout);
	while (1)
	{
		CommunicationTaskExecutionTime  = CommunicationTaskTick * portTICK_PERIOD_MS;
		if( CommunicationTaskExecutionTime > 1000 )
			{
			/* Sets the priority of "communicationtask" to 4  */
				vTaskPrioritySet(communication_handle, HighestCommunicationPriority);
				printf("Communication Task Priority = 4\n");
				fflush(stdout);
			}
			else if( CommunicationTaskExecutionTime < 200 )
			{
				/* Sets the priority of "communicationtask" to 2 */
				vTaskPrioritySet(communication_handle, LowestCommunicationPriority);
				printf("Communication Task Priority = 2\n");
				fflush(stdout);
			}
		vTaskDelay(1000);
	}
}
