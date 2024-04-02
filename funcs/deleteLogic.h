#pragma once


void deleteLogic(student* students);
int* findaddNotDeletedStudentsFile(student* students, int amountOfStudents, int* index);
void addNotDeletedStudentsFile(student* students, int amountOfStudents, int* deletedStudents, int index);