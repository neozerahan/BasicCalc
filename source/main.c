#include <stdio.h>
#include <windef.h>
#include <windows.h>
#include <winuser.h>

#include "../headers/windowsFunction.h"
#include "../headers/utilities.h"
#include "../headers/calculator.h"

//GLOBAL WINDOWS HANDLES //
HWND globalMainWindow = {0};
HWND globalDisplayWindow = {0};
HWND globalResultWindow = {0};

//GLOBAL BUTTON HANDLES //

// NUMBER BUTTONS//
HWND globalButton09 = {0};
HWND globalButton08 = {0};
HWND globalButton07 = {0};
HWND globalButton06 = {0};
HWND globalButton05 = {0};
HWND globalButton04 = {0};
HWND globalButton03 = {0};
HWND globalButton02 = {0};
HWND globalButton01 = {0};
HWND globalButton00 = {0};

//OPERATOR BUTTONS//
HWND globalButtonPlus = {0};
HWND globalButtonMinus = {0};
HWND globalButtonEqual = {0};
HWND globalButtonMultiply = {0}; 
HWND globalButtonDivide = {0};
HWND globalButtonClear = {0};
HWND globalButtonClearSession = {0};
HWND globalButtonDot = {0};
HWND globalButtonBackSpace = {0};

// GLOBAL VARIABLES //

char enteredNumBuffer[10];
short int globalIsNumEntered = FALSE;
short int *pGlobalIsNumEntered = &globalIsNumEntered;

short int globalBufferSize = 0;
short int *pGlobalBufferSize = &globalBufferSize;

short int globalIsFirstNum = TRUE;
short int *pGlobalIsFirstNum = &globalIsFirstNum;

short int globalIsMinusSymbolBeforeNum = FALSE;
short int *pGlobalIsMinusSymbolBeforeNum = &globalIsNumEntered;

double globalResultNum = 0;
double * pGlobalResultNum = &globalResultNum;

float globalInputNum = 0;
float * pGlobalInputNum = &globalInputNum;

float globalNum02 = 0;
float * pGlobalNum02 = &globalNum02;

double globalNum01 = 0;
double * pGlobalNum01 = &globalNum01;

char lastInputtedOperator[0];

int APIENTRY WinMain(HINSTANCE windowHandle, HINSTANCE prevWindowHandle, PSTR cmdline, int cmdshow)
{

    WNDCLASSA windowClass = CreateWindowClass(WINDOW_CLASS_NAME, windowHandle);

    RegisterClassA(&windowClass);

    globalMainWindow = CreateAppWindow(WINDOW_CLASS_NAME, APP_NAME, APP_WIDTH, APP_HEIGHT, 
            windowHandle);

    if (globalMainWindow == NULL)
    {
        MessageBox(NULL, "Main window creation failed!", "ERROR!", 0);
        return 0;
    }

    //Disable/hide console window...
    ConsoleWindowVisibility(FALSE); 

    ShowWindow(globalMainWindow, cmdshow);

    MSG msg = {};

    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProc(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
            {
                globalDisplayWindow = CreateWindowA(
                        "STATIC",
                        "",
                        SS_RIGHT | WS_VISIBLE | WS_CHILD,
                        0,0, APP_WIDTH - 8, 20,
                        windowHandle,
                        NULL, NULL, NULL);

                if(globalDisplayWindow == 0)
                {
                    MessageBox(NULL, "Unable to create display window!", "ERROR!", 0);
                }

                globalResultWindow = CreateWindowA(
                        "STATIC",
                        "0",
                        SS_RIGHT | WS_VISIBLE | WS_CHILD,
                        0,20, APP_WIDTH - 8,  20,
                        windowHandle,
                        NULL, NULL, NULL);

                if(globalResultWindow == 0)
                {
                    MessageBox(NULL, "Unable to create display window!", "ERROR!", 0);
                }

                short int offset = 40;
                short int buttonSize = 35;

                //BUTTON 5TH ROW
                globalButton09 = CreateButton("9", APP_WIDTH - offset - (buttonSize * 0), 40, 
                        buttonSize, buttonSize, windowHandle, ID_BUTTON_9);

                globalButton08 = CreateButton("8", APP_WIDTH - offset - (buttonSize * 1), 40, 
                        buttonSize, buttonSize, windowHandle,   ID_BUTTON_8);

                globalButton07 = CreateButton("7", APP_WIDTH - offset - (buttonSize * 2), 40, 
                        buttonSize, buttonSize, windowHandle, ID_BUTTON_7);

                globalButtonPlus = CreateButton("+", APP_WIDTH - offset - (buttonSize * 3), 40, 
                        buttonSize, buttonSize, windowHandle, ID_BUTTON_PLUS);

                //BUTTON 4TH ROW
                globalButton06 = CreateButton("6", APP_WIDTH - offset - (buttonSize * 0), 40 + 
                        buttonSize, buttonSize, buttonSize, windowHandle, ID_BUTTON_6 );

                globalButton05 = CreateButton("5", APP_WIDTH - offset - (buttonSize * 1), 40 + 
                        buttonSize, buttonSize, buttonSize, windowHandle, ID_BUTTON_5 );

                globalButton04 = CreateButton("4", APP_WIDTH - offset - (buttonSize * 2), 40 + 
                        buttonSize, buttonSize, buttonSize, windowHandle, ID_BUTTON_4 );

                globalButtonMinus = CreateButton("-", APP_WIDTH - offset - (buttonSize * 3), 40 + 
                        buttonSize, buttonSize, buttonSize, windowHandle, ID_BUTTON_SUBTRACT);

                //BUTTON 3RD ROW 
                globalButton03 = CreateButton("3", APP_WIDTH - offset - (buttonSize * 0), 40 + 
                        (buttonSize * 2), buttonSize, buttonSize, windowHandle, ID_BUTTON_3 );

                globalButton02 = CreateButton("2", APP_WIDTH - offset - (buttonSize * 1), 40 + 
                        (buttonSize * 2), buttonSize, buttonSize, windowHandle, ID_BUTTON_2 );

                globalButton01 = CreateButton("1", APP_WIDTH - offset - (buttonSize * 2), 40 + 
                        (buttonSize * 2), buttonSize, buttonSize, windowHandle, ID_BUTTON_1 );

                globalButtonMultiply = CreateButton("*", APP_WIDTH - offset - (buttonSize * 3), 40 
                        + (buttonSize * 2), buttonSize, buttonSize, windowHandle, 
                        ID_BUTTON_MULTIPLY);

                //BUTTON 2ND ROw
                globalButtonBackSpace = CreateButton("<--", APP_WIDTH - offset - (buttonSize * 0), 40 + 
                        (buttonSize * 3), buttonSize, buttonSize, windowHandle, ID_BUTTON_BACKSPACE);

                globalButton00 = CreateButton("0", APP_WIDTH - offset - (buttonSize * 1), 40 + 
                        (buttonSize * 3), buttonSize, buttonSize, windowHandle, ID_BUTTON_0);

                globalButtonDivide = CreateButton("/", APP_WIDTH - offset - (buttonSize * 2), 40 + 
                        (buttonSize * 3), buttonSize, buttonSize, windowHandle, ID_BUTTON_DIVIDE);

                globalButtonClear = CreateButton("c", APP_WIDTH - offset - (buttonSize * 3), 40 + 
                        (buttonSize * 3), buttonSize, buttonSize, windowHandle, ID_BUTTON_CLEAR);

                //BUTTON 1ST ROw
                globalButtonClearSession = CreateButton("ce", APP_WIDTH - offset - (buttonSize * 3), 40 + 
                        (buttonSize * 4), buttonSize, buttonSize, windowHandle, 
                        ID_BUTTON_CLEAR_SESSION);

                globalButtonDot = CreateButton(".", APP_WIDTH - offset - (buttonSize * 2), 40 + 
                        (buttonSize * 4), buttonSize, buttonSize, windowHandle, ID_BUTTON_DOT);

                globalButtonEqual = CreateButton("=", APP_WIDTH - offset - (buttonSize * 1), 40 + 
                        (buttonSize * 4), buttonSize * 2, buttonSize, windowHandle, 
                        ID_BUTTON_EQUAL);

            }
            break;

        case WM_COMMAND:
            {
                switch (LOWORD(wParam))
                {
                    case ID_BUTTON_9:
                        (*pGlobalIsNumEntered) = TRUE;
                        ShowNumInTextBox(globalDisplayWindow, "9", enteredNumBuffer, pGlobalInputNum 
                                );
                        break;
                    case ID_BUTTON_8:
                        (*pGlobalIsNumEntered) = TRUE;
                        ShowNumInTextBox(globalDisplayWindow, "8", enteredNumBuffer, pGlobalInputNum 
                                );
                        break;

                    case ID_BUTTON_7:
                        (*pGlobalIsNumEntered) = TRUE;
                        ShowNumInTextBox(globalDisplayWindow, "7", enteredNumBuffer, pGlobalInputNum 
                                );
                        break;

                    case ID_BUTTON_6:
                        (*pGlobalIsNumEntered) = TRUE;
                        ShowNumInTextBox(globalDisplayWindow, "6", enteredNumBuffer, pGlobalInputNum);
                        break;

                    case ID_BUTTON_5:
                        (*pGlobalIsNumEntered) = TRUE;
                        ShowNumInTextBox(globalDisplayWindow, "5", enteredNumBuffer, pGlobalInputNum 
                                );
                        break;

                    case ID_BUTTON_4:
                        (*pGlobalIsNumEntered) = TRUE;
                        ShowNumInTextBox(globalDisplayWindow, "4", enteredNumBuffer, pGlobalInputNum 
                                );
                        break;

                    case ID_BUTTON_3:
                        (*pGlobalIsNumEntered) = TRUE;
                        ShowNumInTextBox(globalDisplayWindow, "3", enteredNumBuffer, pGlobalInputNum 
                                );
                        break;

                    case ID_BUTTON_2:
                        (*pGlobalIsNumEntered) = TRUE;
                        ShowNumInTextBox(globalDisplayWindow, "2", enteredNumBuffer, pGlobalInputNum);
                        break;

                    case ID_BUTTON_1:
                        (*pGlobalIsNumEntered) = TRUE;
                        ShowNumInTextBox(globalDisplayWindow, "1", enteredNumBuffer, pGlobalInputNum);
                        break;

                    case ID_BUTTON_0:
                        (*pGlobalIsNumEntered) = TRUE;
                        ShowNumInTextBox(globalDisplayWindow, "0", enteredNumBuffer, pGlobalInputNum);
                        break;

                    case ID_BUTTON_DOT:
                        (*pGlobalIsNumEntered) = TRUE;
                        ShowNumInTextBox(globalDisplayWindow, ".", enteredNumBuffer, pGlobalInputNum);
                        break;


                    case ID_BUTTON_PLUS:

                        // Check, if for the first time, minus '-' sign was pressed so that
                        // the number is subtracted instead of adding it as -x + y = -z...
                        // The way I approached this is by converting it to it's negative number... 
                        if(globalIsMinusSymbolBeforeNum == TRUE) 
                        {
                            globalIsFirstNum = FALSE;
                            ConvertToNegativeFloat(&globalInputNum); 
                        }

                        ProcessOperatorButton("+", pGlobalIsFirstNum, globalDisplayWindow, 
                                enteredNumBuffer, lastInputtedOperator, pGlobalIsNumEntered, 
                                pGlobalInputNum, pGlobalNum01, pGlobalNum02, pGlobalResultNum,
                                globalResultWindow);

                        globalIsMinusSymbolBeforeNum = FALSE;
                        break;

                    case ID_BUTTON_DIVIDE:
                        ProcessOperatorButton("/", pGlobalIsFirstNum, globalDisplayWindow, 
                                enteredNumBuffer, lastInputtedOperator, pGlobalIsNumEntered, 
                                pGlobalInputNum, pGlobalNum01, pGlobalNum02, pGlobalResultNum,
                                globalResultWindow);
                        break;

                    case ID_BUTTON_MULTIPLY:
                        ProcessOperatorButton("*", pGlobalIsFirstNum, globalDisplayWindow,  
                                enteredNumBuffer,lastInputtedOperator, pGlobalIsNumEntered, 
                                pGlobalInputNum, pGlobalNum01, pGlobalNum02, pGlobalResultNum,
                                globalResultWindow);
                        break;

                    case ID_BUTTON_SUBTRACT:

                        //If minus sign was pressed before any number, use it as a sign rather
                        //then a subtraction operator by subtracting the number with 0, 
                        //Example -->  if '-' was inputted along with 1 then ... 0 - 1= -1...
                        if(globalIsNumEntered == FALSE) 
                        {
                            globalIsFirstNum = FALSE;
                            globalIsMinusSymbolBeforeNum = TRUE;
                        }

                        ProcessOperatorButton("-", pGlobalIsFirstNum, globalDisplayWindow, 
                                enteredNumBuffer,  lastInputtedOperator, pGlobalIsNumEntered, 
                                pGlobalInputNum, pGlobalNum01, pGlobalNum02, pGlobalResultNum,
                                globalResultWindow);
                        break;

                    case ID_BUTTON_EQUAL:
                        if (*lastInputtedOperator == 0)
                        {
                            printf("Please enter a symbol!\n");
                            break;
                        }

                        if ((*pGlobalIsNumEntered) == TRUE)
                        {
                            CalculateNum(lastInputtedOperator,  pGlobalIsFirstNum, pGlobalInputNum, 
                                    pGlobalNum01, pGlobalNum02, pGlobalResultNum);

                            *lastInputtedOperator = 0;
                            ShowResultInTextBox(pGlobalResultNum, globalResultWindow);

                            //Insert '=' symbol followed by a null terminator...
                            enteredNumBuffer[0] = '=';
                            enteredNumBuffer[1] = '\0';

                            //Set the display text to '=' symbol....
                            SetWindowTextA(globalDisplayWindow, enteredNumBuffer);

                            *enteredNumBuffer = 0;
                            (*pGlobalIsNumEntered)= FALSE; 
                        }
                        break;

                    case ID_BUTTON_CLEAR:
                        printf("Clear Data!\n");
                        *pGlobalResultNum = 0;
                        *pGlobalNum01 = 0;
                        *pGlobalNum02 = 0;
                        *enteredNumBuffer = 0;
                        *pGlobalIsFirstNum = TRUE;
                        *pGlobalIsNumEntered = FALSE;
                        SetWindowTextA(globalDisplayWindow, enteredNumBuffer);
                        SetWindowTextA(globalResultWindow, enteredNumBuffer);
                        break;

                    case ID_BUTTON_CLEAR_SESSION: 
                        *enteredNumBuffer = 0;
                        *pGlobalInputNum = 0;
                        SetWindowTextA(globalDisplayWindow, enteredNumBuffer);
                        globalIsNumEntered = FALSE;
                        *lastInputtedOperator = 0;
                        break;

                    case ID_BUTTON_BACKSPACE:
                        {
                            int stringCount = CountLengthOfString(enteredNumBuffer);
                            if(stringCount == 0) 
                            {
                                printf("Nothing to clear!\n");
                                break;
                            }

                            //Remove the last character by replacing it with '\0'...
                            enteredNumBuffer[stringCount-1] = '\0';

                            SetWindowTextA(globalDisplayWindow, enteredNumBuffer);
                        }
                        break;
                }

            }
            break;

        case WM_CLOSE:
            DestroyWindow(windowHandle);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(windowHandle, msg, wParam, lParam);
    }
    return 0 ;
}
