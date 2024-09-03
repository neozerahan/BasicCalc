#include"../headers/utilities.h"
#include <stdio.h>


int CountDigitsOfNum(float value)
{
    int digitCount = 1;
    float tempNum = 0;

    tempNum = value;

    if (tempNum > 0)
    {
        while (tempNum >= 10)
        {
            tempNum = tempNum / 10;
            digitCount++;
        }
    }
    else
    {
        while (tempNum <= -10)
        {
            tempNum = tempNum / 10;
            digitCount++;
        }
    }
    printf("Digit Count : %d\n", digitCount);
    return digitCount;
}

short int CountLengthOfString(const char *string)
{
    short int count = 0;
    char character = '0';

    while(character !='\0')
    {
        character = string[count];
        if(character == '\0') break;
        count++;
   }
    printf("Count: %d\n", count);
    return count;
}

short int CountLenghtOfDecimalNumber (float number)
{
    short int digitCount = 0;   
    int tempNum = (int)number;
    float decimalNum = number - tempNum; 
    while(tempNum != 0)
    {
        tempNum /= 10; 
        digitCount++;
    }

    printf("Digit count = %d\n", digitCount);
    return digitCount;
}

void RemoveDecimalPointIfLastInBuffer(char * buffer)
{

    int i = 0;
    while(buffer[i] != '\0')
    {
        if ((buffer[i] == '.') & (buffer[i+1] == '\0'))
        {
            buffer[i] = '\0';
            printf("decimal point removed!");
            break;
        }
        i++;
    }
}

void ConvertToNegativeFloat(float * value)
{
    (*value) *= -1;
}
