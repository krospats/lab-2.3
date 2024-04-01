#pragma once
enum event {
	ENROLLMENT,
	DROPOUT,
	RECOVERY
	
};
typedef struct markSubjects {
	int mark;
	char* subject;
}marks;

typedef struct eventDates {
	int event;
	char* date;
}events;

typedef struct Students {
	int studentId;
	char* name;
	char* surName;
	char* lastName;
	int amountOfSubjects;
	marks* markSubject;
	int amountOfEvents;
	events* eventDate;
}student;

void task2();
void createFile();
int chooseActionFunc();
void switchAction(int chooseAction, student* students, int amountOfStudents);
void* reallocWithoutNull(void* inputPtr, unsigned newSize);
void* mallocWithoutNull(unsigned size);
int getAmountOfStudents();
student* getStudents(student* students, int amountOfStudents);
int getNumberFile(FILE* file);
char* getStringFile(FILE* file);





















void resetFile();











