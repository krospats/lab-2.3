#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "func2.h"
#include "addNewStudents.h"
#include "deleteLogic.h"
#include "printStudents.h"
#include "recoverLogic.h"
#include "resetFile.h"



//add student
//print students
//delete students
//recover students
//reset file
//close program


void task2() {
	int amountOfStudents = 0;
	createFile();
	while (1) {
		student* students = mallocWithoutNull(1);


		int chooseAction = chooseActionFunc();
		if (chooseAction == 6) return;
		switchAction(chooseAction, students, amountOfStudents);
		printf("\n\n\n\n");
	}
}
void createFile() {
	FILE* file;
	if (file = fopen("database.txt", "r+") == NULL) {
		file = fopen("database.txt", "a");
		fclose(file);
	}
}
void switchAction(int chooseAction, student* students, int amountOfStudents) {
	switch (chooseAction) {
	case 1:
		students = addNewStudent(students);
		addToFile(students);
		break;
	case 2:
		printStudents(students);
		break;
	case 3:
		deleteLogic(students);
		break;
	case 4:
		recoverLogic(students, amountOfStudents);
		break;
	case 5:
		resetFile();
		break;
	}
}

int chooseActionFunc() {
	printf("choose action:\n 1 - add student\n 2 - print students\n 3 - delete bad students\n 4 - recover good students\n 5 - reset file\n 6 - close program");
	printf("\nACTION - ");
	int chooseAction = scan(1, 6);
	printf("\033[0d\033[2J");
	return chooseAction;
}



void* mallocWithoutNull(unsigned size) {
	void* returnArr = NULL;
	int counter = 0;

	while (1) {
		returnArr = (int*)malloc(size);
		if (returnArr != NULL) return returnArr;

		counter++;
		if (counter > 50) exit(-1);
	}

}

void* reallocWithoutNull(void* inputPtr, unsigned newSize) {
	int counter = 0;

	while (1) {
		inputPtr = (void*)realloc(inputPtr, newSize);
		if (inputPtr != NULL) return inputPtr;

		counter++;
		if (counter > 50) exit(-1);
	}
	return NULL;
}


student* getStudents(student* students, int amountOfStudents) {
	char buffer[128];
	char date[11];
	FILE* file = fopen("database.txt", "r+");
	fseek(file, 0, SEEK_SET);
	students = reallocWithoutNull(students, amountOfStudents * sizeof(student));
	for (int i = 0; i < amountOfStudents; i++) {
		int number = 0;
		students[i].studentId = getNumberFile(file);
		students[i].name = getStringFile(file);
		students[i].surName = getStringFile(file);

		students[i].lastName = getStringFile(file);
		students[i].amountOfSubjects =  getNumberFile(file);
		students[i].markSubject = mallocWithoutNull(students[i].amountOfSubjects * sizeof(marks));
		for (int j = 0; j < students[i].amountOfSubjects; j++) {
			students[i].markSubject[j].subject = getStringFile(file);
			students[i].markSubject[j].mark = getNumberFile(file);
		}
		students[i].amountOfEvents = getNumberFile(file);
		students[i].eventDate = mallocWithoutNull(students[i].amountOfEvents * sizeof(events));
		for (int j = 0; j < students[i].amountOfEvents; j++) {
			fseek(file, 1, SEEK_CUR);
			students[i].eventDate[j].event = getNumberFile(file);
			students[i].eventDate[j].date = getStringFile(file); 
		}
		fscanf(file, "\n");
	}
	fclose(file);
	return students;
}
int getAmountOfStudents() {
	FILE* file= fopen("database.txt", "r");
	char letter;
	int counter = 0;
	while (1) {
		letter = fgetc(file);
		if (letter == '\n') counter++;
		if (letter == EOF) return counter;
	}
	
}
int getNumberFile(FILE* file) {
	int number;
	fscanf(file, "%d", &number);
	return number;
}
char* getStringFile(FILE* file) {
	char buffer[128];
	char* arrayOfChars;
	
	fscanf(file, "%s", buffer);
	for (int i = 0; i < strlen(buffer); i++) {
		if (buffer[i] == 15) buffer[i] = ' ';
	}
	arrayOfChars = mallocWithoutNull(strlen(buffer) + 1);

	strcpy(arrayOfChars, buffer);
	return arrayOfChars;
}






