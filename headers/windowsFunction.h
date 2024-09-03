#ifndef WINDOWS_FUNCTION_H
#define WINDOWS_FUNCTION_H

#include<windows.h>

#define WINDOW_CLASS_NAME "WindowClass"
#define APP_NAME "Basic Calc"
#define APP_WIDTH 145
#define APP_HEIGHT 243
#define APP_BACKGROUND_COLOR RGB(255,255,255)
#define DECIMAL_PRECISION 6

#define ID_BUTTON_9 101
#define ID_BUTTON_8 102
#define ID_BUTTON_7 103
#define ID_BUTTON_6 104
#define ID_BUTTON_5 105
#define ID_BUTTON_4 106
#define ID_BUTTON_3 107
#define ID_BUTTON_2 108
#define ID_BUTTON_1 109
#define ID_BUTTON_0 110

#define ID_BUTTON_PLUS 111
#define ID_BUTTON_MULTIPLY 112
#define ID_BUTTON_DIVIDE 113
#define ID_BUTTON_SUBTRACT 114
#define ID_BUTTON_EQUAL 115
#define ID_BUTTON_CLEAR 116
#define ID_NUM_ENTERED 117
#define ID_BUTTON_DOT 118
#define ID_BUTTON_CLEAR_SESSION 119
#define ID_BUTTON_BACKSPACE 120

LRESULT CALLBACK WindowProc(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam);
WNDCLASSA CreateWindowClass(const char *windowClassName, HINSTANCE windowHandle);
HWND CreateAppWindow(const char *windowClassName, const char *appName, unsigned short width, unsigned short height, HINSTANCE windowHandle);
HWND CreateButton(const char *buttonNum, unsigned short xPos, unsigned short yPos, unsigned short width, unsigned short height, HWND parentWindowHandle, int lParam);
void ShowNumInTextBox(HWND textWindowHandle, const char * number,  char * enteredNumBuffer, float * inputNum);
void ShowSymbolInTextBox(HWND textWindowHandle, const char * symbol, char * enterNumBuffer);
void ShowResultInTextBox(double * pNumber, HWND textBoxWindowHandle);
void ConsoleWindowVisibility(int isVisible);
#endif
