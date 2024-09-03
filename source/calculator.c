#include "../headers/calculator.h"
#include <stdio.h>
#include "../headers/utilities.h"
#include "../headers/windowsFunction.h"

void CalculateNum(char * symbol, short int * pGlobalIsFirstNum, float * pGlobalInputNum, 
        double * pGlobalNum01, float * pGlobalNum02 , double * pGlobalResultNum)
{
    if(*pGlobalIsFirstNum == TRUE)
    {
        *pGlobalNum01 = *pGlobalInputNum;
    }
    else
    {
        *pGlobalNum02 = *pGlobalInputNum;
    }

    switch(symbol[0])
    {
    case '+':
        printf("Add\n");
        *pGlobalResultNum = *pGlobalNum01 + *pGlobalNum02;
        printf("%f = %f + %f\n", *pGlobalResultNum, *pGlobalNum01, *pGlobalNum02);
        *pGlobalNum01 = *pGlobalResultNum;
        printf("Num01: %f\n", *pGlobalNum01);
        *pGlobalIsFirstNum = FALSE;
        break;
    case '-':
        printf("Subtract\n");
        if (*pGlobalIsFirstNum == TRUE)
        {
            *pGlobalResultNum = *pGlobalNum01;
            *pGlobalNum01 = *pGlobalResultNum;
            printf("Result: %f\n", *pGlobalResultNum);
        }
        else
        {
            *pGlobalResultNum = (*pGlobalNum01) - (*pGlobalNum02);
            printf("%f = %f - %f\n", *pGlobalResultNum, *pGlobalNum01, *pGlobalNum02);
            *pGlobalNum01 = *pGlobalResultNum;
            printf("Num01: %f\n", *pGlobalNum01);
        }
       *pGlobalIsFirstNum = FALSE;
        break;
    case '*':
        printf("Multiply\n");
        // don't multiply the first number when inputted...
        if (*pGlobalIsFirstNum == TRUE)
        {
            *pGlobalResultNum = *pGlobalNum01;
            *pGlobalNum01 = *pGlobalResultNum;
        }
        else
        {
            *pGlobalResultNum = (*pGlobalNum01) * (*pGlobalNum02);
            printf("%f = %f * %f\n", *pGlobalResultNum, *pGlobalNum01, *pGlobalNum02);
            *pGlobalNum01 = *pGlobalResultNum;
            printf("Num01: %f\n", *pGlobalNum01);
        }
       *pGlobalIsFirstNum = FALSE;
        break;
    case '/':
        printf("Divide\n");
        if (*pGlobalIsFirstNum == TRUE)
        {
            *pGlobalResultNum = *pGlobalNum01;
            *pGlobalIsFirstNum = FALSE;
        }
        else if( *pGlobalNum02 == 0)
        {
            *pGlobalResultNum = 0;
            *pGlobalNum01 = *pGlobalResultNum;
            *pGlobalIsFirstNum = TRUE;
        }
        else
        {
            *pGlobalResultNum = (*pGlobalNum01) / (*pGlobalNum02);
            printf("%f = %f / %f\n", *pGlobalResultNum, *pGlobalNum01, *pGlobalNum02);
            *pGlobalNum01 = *pGlobalResultNum;
            printf("Num01: %f\n", *pGlobalNum01);
            *pGlobalIsFirstNum = FALSE;
        }
        break;
    default:
        printf("No operation");
        break;
    }
}

void ProcessOperatorButton(char * symbol, short int *pGlobalIsFirstNum, HWND globalDisplayWindow, 
        char * enteredNumBuffer, char * lastInputtedOperator,  short int *pGlobalIsNumEntered, 
        float * pGlobalInputNum, double *pGlobalNum01, float * pGlobalNum02,double * pGlobalResultNum, 
        HWND globalResultWindow)
{
    ShowSymbolInTextBox(globalDisplayWindow, symbol, enteredNumBuffer);
    lastInputtedOperator[0] = *symbol;
    if ((*pGlobalIsNumEntered) == TRUE)
    {
        CalculateNum(symbol, pGlobalIsFirstNum, pGlobalInputNum, pGlobalNum01, pGlobalNum02, 
                pGlobalResultNum);
        ShowResultInTextBox(pGlobalResultNum, globalResultWindow);
        (*pGlobalIsNumEntered) = FALSE;
    }
}
