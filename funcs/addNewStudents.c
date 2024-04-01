#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "func2.h"
#include "addNewStudents.h"
student* addNewStudent(student* students) {

	char buffer[128];
	char string[11];
	int moreEvents = 1;
	int j = 0;

	students = reallocWithoutNull(students, 1 * sizeof(student));
	students[0].studentId = getId();

	students[0].name = getName(buffer);
	students[0].surName = getSurName(buffer);
	students[0].lastName = getLastName(buffer);


	students[0].amountOfSubjects = getAmountOfSubjects();
	students[0].markSubject = mallocWithoutNull(students[0].amountOfSubjects * sizeof(marks));
	for (int i = 0; i < students[0].amountOfSubjects; i++) {
		students[0].markSubject[i].subject = getUniqueSubject(students, 0, i);
		students[0].markSubject[i].mark = getMark();
	}
	students[0].eventDate = mallocWithoutNull(sizeof(events));
	students[0].amountOfEvents = 0;

	do {
		students[0].amountOfEvents++;
		students[0].eventDate = reallocWithoutNull(students[0].eventDate, students[0].amountOfEvents * sizeof(events));
		if (j == 0) students[0].eventDate[j].event = ENROLLMENT;
		else if ((j % 2) == 1) students[0].eventDate[j].event = DROPOUT;
		else students[0].eventDate[j].event = RECOVERY;

		students[0].eventDate[j].date = getDate(students, j, string);

		printf("\ndo you want to add more events?(1 - yes, 0 - no) ");
		moreEvents = scan(0, 1);
		j++;
	} while (moreEvents);



	return students;
}
int getId() {
	int number = 0;
	FILE* file = fopen("database.txt", "r");
	int amountOfStudents = getAmountOfStudents();
	number = checkOnUnique(number, amountOfStudents, file);
	fclose(file);
	return number;
}
int checkOnUnique(int number, int amountOfStudents, FILE* file) {
	int fileNumber = 0;
	char letter;
	while (1) {
		fseek(file, 0, SEEK_SET);
		int sameFlag = 0;
		printf("\nenter student id:(1 - 10000000) ");
		number = scan(1, 10000000);
		for (int i = 0; i < amountOfStudents; i++) {
			fscanf(file, "%d", &fileNumber);
			do {
				fscanf(file, "%c", &letter);
			} while (letter != '\n');
			if (fileNumber == number) {
				i = amountOfStudents;
				sameFlag = 1;
			}
		}
		if (sameFlag == 0) 	return number;
		else {
			printf("this id isnt unique!");
			printUsedIds(amountOfStudents);
		}
	}
}
void printUsedIds(int amountOfStudents) {
	int fileNumber = 0;
	char letter = ' ';
	FILE* file = fopen("database.txt", "r");
	printf("\n used ids: ");
	for (int i = 0; i < amountOfStudents; i++) {
		fscanf(file, "%d", &fileNumber);
		printf("%d ", fileNumber);
		do {
			fscanf(file, "%c", &letter);
		} while (letter != '\n');
	}
	printf("\n");
}
char* getName(char buffer[128]) {
	char* arrayOfChars;
	printf("\nenter name: ");
	buffer = fgets(buffer, 128, stdin);
	buffer[strlen(buffer) - 1] = '\0';
	arrayOfChars = mallocWithoutNull(strlen(buffer) + 1);
	strcpy(arrayOfChars, buffer);
	return arrayOfChars;
}

char* getSurName(char buffer[128]) {
	char* arrayOfChars;
	printf("\nenter surname: ");
	buffer = fgets(buffer, 128, stdin);
	buffer[strlen(buffer) - 1] = '\0';
	arrayOfChars = mallocWithoutNull(strlen(buffer) + 1);
	strcpy(arrayOfChars, buffer);
	return arrayOfChars;
}

char* getLastName(char buffer[128]) {
	char* arrayOfChars;
	printf("\nenter last name: ");
	buffer = fgets(buffer, 128, stdin);
	arrayOfChars = mallocWithoutNull(strlen(buffer) + 1);
	buffer[strlen(buffer) - 1] = '\0';
	strcpy(arrayOfChars, buffer);
	return arrayOfChars;
}

int getAmountOfSubjects() {
	int number;
	printf("\nenter amount of subjects:(1 - 20) ");
	number = scan(1, 20);
	return number;
}

char* getSubject(char buffer[128]) {
	char* arrayOfChars;
	printf("\nenter subject:");
	buffer = fgets(buffer, 128, stdin);
	buffer[strlen(buffer) - 1] = '\0';
	arrayOfChars = mallocWithoutNull(strlen(buffer) + 1);
	strcpy(arrayOfChars, buffer);
	return arrayOfChars;
}
char* getUniqueSubject(student* students, int i, int j) {
	char buffer[128];
	while (1) {

		int isUnique = 0;
		char* arrayOfChars = getSubject(buffer);
		for (int k = j - 1; k >= 0; k--) {
			if (strcmp(arrayOfChars, students[i].markSubject[k].subject) == 0) {
				isUnique = 1;
				k = -1;
			}

		}
		if (isUnique == 1) printf("\nthis subject isnt unique");
		else if (isUnique == 0) return arrayOfChars;
	}

}

int getMark() {
	int number;
	printf("\nenter mark:(0 - 10) ");
	number = scan(0, 10);
	return number;
}
char* getDate(student* students, int j, char string[11]) {
	int sum;
	char* date = mallocWithoutNull(10);
	do {
		if (students[(0)].eventDate[j].event == ENROLLMENT)   printf("\nchoose enrollment date(dd.mm.yyyy): ");
		else if (students[(0)].eventDate[j].event == DROPOUT)   printf("\nchoose dropout date(dd.mm.yyyy): ");
		else if (students[(0)].eventDate[j].event == RECOVERY)   printf("\nchoose recovery date(dd.mm.yyyy): ");
		string = fgets(string, 11, stdin);
		rewind(stdin);
		int isDate = isDateFunc(string);
		int isRightDate = getRightDate(string);
		int isBigger = isBiggerThanPreviousDate(students, j, string);
		if (isDate == 1 || isBigger == 1 || isRightDate == 1) sum = 1;
		else sum = 0;
	} while (sum);
	strcpy(date, string);
	return date;

}
long getDay(char string[11]) {
	char day[2];
	day[0] = string[0]; day[1] = string[1];
	long dayInt = strtol(day, NULL, 10);
	return dayInt;
}
long getMonth(char string[11]) {
	char month[2];
	month[0] = string[3]; month[1] = string[4];
	long monthInt = strtol(month, NULL, 10);
	return monthInt;
}
long getYear(char string[11]) {
	char year[4];

	year[0] = string[6]; year[1] = string[7]; year[2] = string[8]; year[3] = string[9];
	long yearInt = strtol(year, NULL, 10);
	return yearInt;
}
int getRightDate(char string[11]) {
	long day = getDay(string);
	long month = getMonth(string);
	long year = getYear(string);
	int isRightDate = dateCheck(day, month, year);

	return isRightDate;
}
int dateCheck(long day, long month, long year) {
	if ((month % 2 == 1 && month >= 1 && month <= 7) || (month % 2 == 0 && month >= 8 && month <= 12) && (day >= 1 && day <= 31)) return 0;
	if ((month == 4 || month == 6 || month == 9 || month == 11) && (day >= 1 && day <= 30)) return 0;
	if (month == 2 && (day >= 1 && day <= 28)) return 0;
	if (month == 2 && day == 29 && year % 4 == 0 && year % 100 != 0) return 0;
	if (month == 2 && day == 29 && year % 100 == 0 && year % 400 == 0) return 0;
	printf("\ndate need to be correct");
	return 1;
}
int isDateFunc(char buffer[11]) {
	for (int i = 0; i < 10; i++) {
		if (i == 2 || i == 5) i++;
		if (!(buffer[i] >= '0' && buffer[i] <= '9')) {
			printf("\nincorrect input(dd.mm.yyyy needed");
			return 1;
		}
	}
	if (buffer[2] == '.' && buffer[5] == '.') return 0;
	else return 1;
}
int isBiggerThanPreviousDate(student* students, int j, char string[11]) {
	char buffer1[11];
	if (j >= 1) {
		strcpy(buffer1, students[0].eventDate[j - 1].date);
		long day1 = getDay(buffer1);
		long month1 = getMonth(buffer1);
		long year1 = getYear(buffer1);
		long day2 = getDay(string);
		long month2 = getMonth(string);
		long year2 = getYear(string);
		if ((year2 - year1) * 366 + (month2 - month1) * 31 + day2 - day1 >= 0) return 0;
		printf("\nyour date needs to be higher than %s", buffer1);
		return 1;
	}
	return 0;
}
void addToFile(student* students) {
	FILE* file = fopen("database.txt", "r+");
	fseek(file, 0, SEEK_END);

	fprintf(file, "%d ", students[0].studentId);

	fprintf(file, "%s ", students[0].name);
	fprintf(file, "%s ", students[0].surName);
	fprintf(file, "%s ", students[0].lastName);

	fprintf(file, "%d ", students[0].amountOfSubjects);


	for (int j = 0; j < students[0].amountOfSubjects; j++) {
		fprintf(file, "%s ", students[0].markSubject[j].subject);
		fprintf(file, "%d ", students[0].markSubject[j].mark);
	}
	fprintf(file, "%d ", students[0].amountOfEvents);

	for (int j = 0; j < students[0].amountOfEvents; j++) {
		fprintf(file, "%d ", students[0].eventDate[j].event);
		fprintf(file, "%s ", students[0].eventDate[j].date);
	}
	fprintf(file, "\n");
	fclose(file);

}