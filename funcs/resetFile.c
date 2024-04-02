#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "func2.h"
#include "resetFile.h"


void resetFile() {
	FILE* file;
	file = fopen("database.txt", "w+");
	fclose(file);
	printf("DONE RESETTING FILE");
}