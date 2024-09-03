#include <stdint.h>
#include <windows.h>
#include <stdio.h>

#include "../headers/resource.h"
#include "../headers/windowsFunction.h"
#include "../headers/utilities.h"

WNDCLASSA CreateWindowClass (const char * windowClassName, HINSTANCE windowHandle)
{
    WNDCLASSA windowClass = {0};

    HICON appIcon = LoadIconA(windowHandle, MAKEINTRESOURCE(APP_ICON));

    HBRUSH backgroundColor = CreateSolidBrush(APP_BACKGROUND_COLOR); 

    windowClass.lpszClassName = windowClassName;
    windowClass.hbrBackground = backgroundColor;
    windowClass.hInstance = windowHandle;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hIcon = appIcon;

    return windowClass;
}

HWND CreateAppWindow(const char * windowClassName, const char * appName, unsigned short width, 
        unsigned short height, HINSTANCE windowHandle)
{
    HWND mainWindow = CreateWindowExA(
        0,
        windowClassName,
        appName,
        WS_OVERLAPPED | WS_SYSMENU | WS_POPUPWINDOW | WS_CAPTION,
        100, 100, width, height,
        NULL, NULL, windowHandle, NULL);
    return mainWindow;
}

void ConsoleWindowVisibility(int isVisible)
{
    HWND consoleHandle = GetConsoleWindow();

    if (isVisible == FALSE)
    {
        ShowWindow(consoleHandle, SW_HIDE);
    }
}

HWND CreateButton(const char* buttonNum, unsigned short xPos,unsigned short yPos, 
        unsigned short width, unsigned short height, HWND parentWindowHandle, int buttonID)
{
    HWND button = {0};

    button = CreateWindowA(
        "Button",
        buttonNum,
        BS_VCENTER | BS_CENTER | WS_CHILD | WS_VISIBLE | WS_BORDER,
        xPos, yPos, width, height,
        parentWindowHandle,
        (HMENU)buttonID, NULL, NULL);

    if (button == NULL)
    {
        MessageBox(NULL, "Unable to create button!", "ERROR!", 0);
    }
    return button;
}

void ShowNumInTextBox(HWND textWindowHandle, const char * number, char * enteredNumBuffer, 
        float * inputNum)
{
    if (SetWindowTextA(textWindowHandle, number) == 0)
    {
        MessageBox(NULL, "Unable to get the window handle in ...", "ERROR!", 0);
    }
    else
    {
        strcat(enteredNumBuffer, number);
        SetWindowTextA(textWindowHandle, enteredNumBuffer);
        *inputNum = atof(enteredNumBuffer); 
        printf("Input Num (winFunc) = %f\n", *inputNum);
    }
}

void ShowSymbolInTextBox(HWND textWindowHandle, const char * symbol, char * enterNumBuffer)
{
    *enterNumBuffer = 0; 
    if (SetWindowTextA(textWindowHandle, symbol) == 0)
    {
        MessageBox(NULL, "Unable to set the text...", "ERROR!", 0);
    }
}

void ShowResultInTextBox(double * pNumber, HWND textBoxWindowHandle)
{
    int digitCount = CountDigitsOfNum(*pNumber);
    digitCount += DECIMAL_PRECISION; // count the base number + max 6 buffer-size for decimal...

    char buffer[digitCount]; // create a buffer to store the string to float...

    gcvt(*pNumber, digitCount, buffer); // converts the float to string in buffer...

    RemoveDecimalPointIfLastInBuffer(buffer);    

    SetWindowTextA(textBoxWindowHandle, buffer);
}
