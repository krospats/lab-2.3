#pragma once



student* addNewStudent(student* students);
int getId();
char* getName(char buffer[128]);
char* getSurName(char buffer[128]);
char* getLastName(char buffer[128]);
int getAmountOfSubjects();
char* getSubject(char buffer[128]);
int getMark();
char* getDate(student* students, int j, char string[11]);
void addToFile(student* students);
int checkOnUnique(int number, int amountOfStudents, FILE* file);
void printUsedIds(int amountOfStudents);
char* getUniqueSubject(student* students, int i, int j);
int getRightDate(char string[11]);
int isDateFunc(char buffer[11]);
long getDay(char string[11]);
long getMonth(char string[11]);
long getYear(char string[11]);
int dateCheck(long day, long month, long year);
int isBiggerThanPreviousDate(student* students, int j, char string[11]);