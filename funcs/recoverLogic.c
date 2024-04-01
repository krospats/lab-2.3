#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "func2.h"
#include "recoverLogic.h"


void recoverLogic(student* students, int amountOfStudents) {
	amountOfStudents = getAmountOfStudents();
	students = getStudents(students, amountOfStudents);
	recoverStudents(students, amountOfStudents);
	addAllStudentsFile(students, amountOfStudents);
	printf("DONE RECOVERING STUDENTS\n\n");
}

student* recoverStudents(student* students, int amountOfStudents) {
	float avgScore = 0;
	for (int i = 0; i < amountOfStudents; i++) {
		if (students[i].eventDate[students[i].amountOfEvents - 1].event == DROPOUT) {
			for (int j = 0; j < students[i].amountOfSubjects; j++) {
				avgScore += students[i].markSubject[j].mark;
			}
			avgScore = avgScore / students[i].amountOfSubjects;
			if (avgScore >= 7) {
				students[i].amountOfEvents++;
				students[i].eventDate = reallocWithoutNull(students[i].eventDate, students[i].amountOfEvents * sizeof(events));
				students[i].eventDate[students[i].amountOfEvents - 1].event = 2;
				students[i].eventDate[students[i].amountOfEvents - 1].date = malloc(10);
				strcpy(students[i].eventDate[students[i].amountOfEvents - 1].date, students[i].eventDate[students[i].amountOfEvents - 2].date);
			}
		}
	}
}

int addAllStudentsFile(student* students, int amountOfStudents) {
	FILE* file = fopen("database.txt", "w+");
	for (int i = 0; i < amountOfStudents; i++) {
		fprintf(file, "%d ", students[i].studentId);

		fprintf(file, "%s ", students[i].name);
		fprintf(file, "%s ", students[i].surName);
		fprintf(file, "%s ", students[i].lastName);

		fprintf(file, "%d ", students[i].amountOfSubjects);


		for (int j = 0; j < students[i].amountOfSubjects; j++) {
			fprintf(file, "%s ", students[i].markSubject[j].subject);
			fprintf(file, "%d ", students[i].markSubject[j].mark);
		}
		fprintf(file, "%d ", students[i].amountOfEvents);

		for (int j = 0; j < students[i].amountOfEvents; j++) {
			fprintf(file, "%d ", students[i].eventDate[j].event);
			fprintf(file, "%s ", students[i].eventDate[j].date);
		}
		fprintf(file, "\n");
	}


	fclose(file);
}