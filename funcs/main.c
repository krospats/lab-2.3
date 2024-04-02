
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include "func1.h"
#include "func2.h"

#define ERROR_FILE_OPEN -3

void main() {
	

	int continueFlag;
	do {
		int taskNumber;
		printf("choose task(1 or  2): - ");
		taskNumber = scan(1, 2);
		if (taskNumber == 1) task1();
		else if (taskNumber == 2)  task2();
		printf("\ndo you want to continue use this lab?(1 - yes, 2 - no) - ");
		continueFlag = scan(1, 2);
	} while (continueFlag == 1);
}