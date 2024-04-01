#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "func2.h"
#include "deleteLogic.h"


void deleteLogic(student* students) {
	int amountOfStudents = getAmountOfStudents();
	students = getStudents(students, amountOfStudents);
	int index = 0;
	int* deletedIndexes = findaddNotDeletedStudentsFile(students, amountOfStudents, &index);
	addNotDeletedStudentsFile(students, amountOfStudents, deletedIndexes, index);
	printf("DONE DELETING STUDENTS\n\n");
}

int* findaddNotDeletedStudentsFile(student* students, int amountOfStudents, int* index) {
	int* deletedStudents = mallocWithoutNull(0);
	float avgScore = 0;
	for (int i = 0; i < amountOfStudents; i++) {
		if (students[i].eventDate[students[i].amountOfEvents - 1].event == ENROLLMENT || students[i].eventDate[students[i].amountOfEvents - 1].event == RECOVERY) {
			for (int j = 0; j < students[i].amountOfSubjects; j++) {
				avgScore += students[i].markSubject[j].mark;
			}
			avgScore = avgScore / students[i].amountOfSubjects;
			if (avgScore < 5) {
				(*index)++;
				deletedStudents = reallocWithoutNull(deletedStudents, (*index) * sizeof(int));
				deletedStudents[(*index) - 1] = i;

			}
		}
	}
	return deletedStudents;
}

void addNotDeletedStudentsFile(student* students, int amountOfStudents, int* deletedStudents, int index) {
	FILE* file = fopen("database.txt", "w+");
	int k = 0;
	for (int i = 0; i < amountOfStudents; i++) {
		if (k < index && deletedStudents[k] == i) {
			k++;
			continue;
		}
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