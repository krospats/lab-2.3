#include <stdio.h>
#include "func.h"
#include "func1.h"


struct point
{
    unsigned int mantiss : 23;
    unsigned int something : 8;
    unsigned  sign : 1;

};

union code
{
    float number;
    struct point p;

};

int task1()
{
    int continueCheck;
    do {
       float number = getResult();
        number = findingIntPart(number);
        printResult(number);
        printf("\ndo you want to continue use this program(1 - yes, 2 - no) - ");
        continueCheck = scan(1, 2);
    } while (continueCheck % 2);
   
}
void printResult(float number){
    printf("\nnumber is %f", number);
    rewind(stdin);
}
float getResult() {
    printf("\nnumber(-2^23, 2^23): ");
    float check = limitNumber();
    float number = scanFloat(-1 * check, check);
    return number;
}
float limitNumber() {
    float maxNumber = 1;
    for (int i = 0; i < 23; i++) {
        maxNumber *= 2;
    }
    return maxNumber;
}
float findingIntPart(float number) {
    int check;

    union code c;
    struct point center = { 0 };
    c.p = center;
    c.number = number;
        int exp = c.p.something - 127;
        if (exp < 0) {
            c.p.something = 0;
        }
        else if (23 - exp > 0) {
            c.p.mantiss = c.p.mantiss >> 23 - exp;
            c.p.mantiss = c.p.mantiss << 23 - exp;
        }
        return c.number;
}

float abs(float number) {
    if (number < 0) number *= -1;
    return number;
}
float scanFloat(float a, float b) {
    float number;
    while (scanf_s("%f", &number) == 0 || getchar() != '\n' || number < a || number > b) {
        printf("\nincorrect input!");
        printf("\ntry again - ");

        rewind(stdin);
    }
    return number;
}