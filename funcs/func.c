#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int scan(int a, int b) {
	int number;
	while (scanf_s("%8d", &number) == 0 || getchar() != '\n' || number < a || number > b) {
		printf("\nincorrect input!");
		printf("\ntry again - ");
		rewind(stdin);
	}
	return number;
}


