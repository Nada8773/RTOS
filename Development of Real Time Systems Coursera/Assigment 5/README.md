## Overview

In the last assignment you will implement your own scheduler in SimSo.
This is done by adding a new multi-core scheduler plug-in as a python file and integrating 
this into SimSo. We will learn that it is possible to implement any kind of scheduler 
in this environment which can be useful for your future research! 
Then we will also implement inter-task communication in practice in FreeRTOS by using 
message queues.

#### 1. Simulation assignment

The assignment is to modify a real-time simulator to verify feasibility of a set of tasks.

- Modify the python code in P_RM.py to use firstfit instead of the current algorithm.

- Hint: Instead of scheduling the task to the CPU with the lowest utilization chose the first one which has a lower utilization 
  than Urm(x+1) where x is the already scheduled tasks on the CPU

- Hint2: have a look at the def packer(self) function in the file P_RM.py

- Schedule the following task set on three processors using your modified algorithm.

  T1(2,1) T2(2.5,0.1) T3(3,1) T4(4,1) T5(4.5,0.1) T6(5,1) T7(6,1) T8(7,1) T9(8,1) T10(8.5,0.1) T11(9,1)

#### 2. Programming assignment

- Create a task "matrixtask" containing the following functionality:
```
*)pvPortMalloc(ROW * sizeof(double*));
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
		vTaskDelay(100);
	}
}

```
- Create a queue and send the content of (double **)c to the queue in matrixtask with before the vTaskDelay() 
  call (hint: place the c variable in a struct). (More information Here).

- Create a reader task which reads the content of the queue in case there is something in the queue.

- In case the queue has some content it should save the data in a local (double **) variable.

- Print out the content of the (double **)c variable in case the content is updated.
 The data transferred from c should be a 10x10 matrix with the value 390 in each slot.