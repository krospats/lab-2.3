#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "func2.h"
#include "printStudents.h"


void printStudents(student* students) {
	int amountOfStudents = getAmountOfStudents();
	if (amountOfStudents == 0) printf("\nthere is no students in file!");
	else {
		FILE* file = fopen("database.txt", "r+");
		fseek(file, 0, SEEK_SET);
		for (int i = 0; i < amountOfStudents; i++) {
			students = getStudent(students, file);
			printStudent(students);
		}

		fclose(file);
	}
}
student* getStudent(student* students, FILE* file) {
	char buffer[128];
	char date[11];

	students = reallocWithoutNull(students, 1 * sizeof(student));
	int number = 0;
	students[0].studentId = getNumberFile(file);
	students[0].name = getStringFile(file);
	students[0].surName = getStringFile(file);

	students[0].lastName = getStringFile(file);
	students[0].amountOfSubjects = getNumberFile(file);
	students[0].markSubject = mallocWithoutNull(students[0].amountOfSubjects * sizeof(marks));
	for (int j = 0; j < students[0].amountOfSubjects; j++) {
		students[0].markSubject[j].subject = getStringFile(file);
		students[0].markSubject[j].mark = getNumberFile(file);
	}
	students[0].amountOfEvents = getNumberFile(file);
	students[0].eventDate = mallocWithoutNull(students[0].amountOfEvents * sizeof(events));
	for (int j = 0; j < students[0].amountOfEvents; j++) {
		fseek(file, 1, SEEK_CUR);
		students[0].eventDate[j].event = getNumberFile(file);
		students[0].eventDate[j].date = getStringFile(file);
	}
	fscanf(file, "\n");
	return students;

}
void printStudent(student* students) {

	printf("\n--------------------------------------\n");
	printf("student id: %d\n", students[0].studentId);
	printf("dtudent name: %s %s %s\n\n", students[0].name, students[0].surName, students[0].lastName);

	printf("MARKS:\n");
	for (int j = 0; j < students[0].amountOfSubjects; j++) {
		printf("\n %s %d", students[0].markSubject[j].subject, students[0].markSubject[j].mark);
	}
	printf("\n\nEVENTS:\n");
	for (int j = 0; j < students[0].amountOfEvents; j++) {
		if (students[0].eventDate[j].event == ENROLLMENT) printf("\nEnrollment: ");
		else if (students[0].eventDate[j].event % 2 == DROPOUT) printf("\nDropout: ");
		else printf("\nRecovery: ");

		printf("%s ", students[0].eventDate[j].date);
	}
	printf("\n--------------------------------------\n");
}