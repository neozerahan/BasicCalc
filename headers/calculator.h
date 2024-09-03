#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <windows.h>

void CalculateNum(char * symbol, short int * pGlobalIsFirstNum, float * pGlobalInputNum,
        double * pGlobalNum01, float * pGlobalNum02 , double * pGlobalResultNum);

void ProcessOperatorButton(char * symbol, short int *pGlobalIsFirstNum, HWND globalDisplayWindow,  
        char * enteredNumBuffer,char * lastInputtedOperator,  short int *pGlobalIsNumEntered, 
        float * pGlobalInputNum,double *pGlobalNum01, float * pGlobalNum02, double * pGlobalResultNum, 
        HWND globalResultWindow);
#endif
