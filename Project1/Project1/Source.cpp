#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <windows.h>
#include <iostream>
#include <Shlwapi.h>
#include <tchar.h>
#include <cmath>
#include "CTD.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
#define WMAIN_CLASSNAME     "Calculator"
#define WMAIN_CAPTION       "Калькулятор"

TCHAR buf[256];

HINSTANCE hInstance;

int main(int nCmdShow) {
    HWND hConsole = GetConsoleWindow();
    ShowWindow(hConsole, SW_HIDE);
    HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);
    HWND hWnd;
    MSG msg;
    WNDCLASS wc;

    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = WMAIN_CLASSNAME;
    wc.lpszMenuName = NULL;

    if (!RegisterClass(&wc))
        return 1;

    hWnd = CreateWindow(WMAIN_CLASSNAME, WMAIN_CAPTION,WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 450, 419, HWND_DESKTOP, NULL, hInstance, 0);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND button[34], hEdit, hListBox;
    PAINTSTRUCT ps;
    HDC hdc;
    int i = 0;
    int count = 0, a = 0, b = 0;

    switch (message)
    {
    case WM_CREATE:
        hEdit = CreateWindow(("edit"), ("0"), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 6, 10, 415, 115, hWnd, (HMENU)ID_EDIT, hInstance, 0);
        button[0] = CreateWindow("button", "+", WS_VISIBLE | WS_CHILD, 185, 330, 55, 45, hWnd, (HMENU)ID_BUTTON_PL, hInstance, 0);
        button[1] = CreateWindow("button", "-", WS_VISIBLE | WS_CHILD, 185, 280, 55, 45, hWnd, (HMENU)ID_BUTTON_M, hInstance, 0);
        button[2] = CreateWindow("button", "*", WS_VISIBLE | WS_CHILD, 185, 230, 55, 45, hWnd, (HMENU)ID_BUTTON_ZV, hInstance, 0);
        button[3] = CreateWindow("button", "/", WS_VISIBLE | WS_CHILD, 185, 180, 55, 45, hWnd, (HMENU)ID_BUTTON_DEL, hInstance, 0);
        button[4] = CreateWindow("button", "AC", WS_VISIBLE | WS_CHILD, 125, 130, 55, 45, hWnd, (HMENU)ID_BUTTON_AC, hInstance, 0);
        button[5] = CreateWindow("button", "sqrt", WS_VISIBLE | WS_CHILD, 185, 130, 55, 45, hWnd, (HMENU)ID_BUTTON_PR, hInstance, 0);
        button[8] = CreateWindow("button", ".", WS_VISIBLE | WS_CHILD, 65, 330, 55, 45, hWnd, (HMENU)ID_BUTTON_DOT, hInstance, 0);
        button[9] = CreateWindow("button", "Решить", WS_VISIBLE | WS_CHILD, 125, 330, 55, 45, hWnd, (HMENU)ID_BUTTON_Decision, hInstance, 0);
        button[10] = CreateWindow("button", "0", WS_VISIBLE | WS_CHILD, 5, 330, 55, 45, hWnd, (HMENU)ID_BUTTON_0, hInstance, 0);
        button[11] = CreateWindow("button", "1", WS_VISIBLE | WS_CHILD, 5, 280, 55, 45, hWnd, (HMENU)ID_BUTTON_1, hInstance, 0);
        button[12] = CreateWindow("button", "2", WS_VISIBLE | WS_CHILD, 65, 280, 55, 45, hWnd, (HMENU)ID_BUTTON_2, hInstance, 0);
        button[13] = CreateWindow("button", "3", WS_VISIBLE | WS_CHILD, 125, 280, 55, 45, hWnd, (HMENU)ID_BUTTON_3, hInstance, 0);
        button[14] = CreateWindow("button", "4", WS_VISIBLE | WS_CHILD, 5, 230, 55, 45, hWnd, (HMENU)ID_BUTTON_4, hInstance, 0);
        button[15] = CreateWindow("button", "5", WS_VISIBLE | WS_CHILD, 65, 230, 55, 45, hWnd, (HMENU)ID_BUTTON_5, hInstance, 0);
        button[16] = CreateWindow("button", "6", WS_VISIBLE | WS_CHILD, 125, 230, 55, 45, hWnd, (HMENU)ID_BUTTON_6, hInstance, 0);
        button[17] = CreateWindow("button", "7", WS_VISIBLE | WS_CHILD, 5, 180, 55, 45, hWnd, (HMENU)ID_BUTTON_7, hInstance, 0);
        button[18] = CreateWindow("button", "8", WS_VISIBLE | WS_CHILD, 65, 180, 55, 45, hWnd, (HMENU)ID_BUTTON_8, hInstance, 0);
        button[19] = CreateWindow("button", "9", WS_VISIBLE | WS_CHILD, 125, 180, 55, 45, hWnd, (HMENU)ID_BUTTON_9, hInstance, 0);
        button[20] = CreateWindow("button", "^", WS_VISIBLE | WS_CHILD, 245, 130, 55, 45, hWnd, (HMENU)ID_BUTTON_POW, hInstance, 0);
        button[21] = CreateWindow("button", "sin", WS_VISIBLE | WS_CHILD, 245, 180, 55, 45, hWnd, (HMENU)ID_BUTTON_SIN, hInstance, 0);
        button[22] = CreateWindow("button", "cos", WS_VISIBLE | WS_CHILD, 245, 230, 55, 45, hWnd, (HMENU)ID_BUTTON_COS, hInstance, 0);
        button[23] = CreateWindow("button", "tan", WS_VISIBLE | WS_CHILD, 245, 280, 55, 45, hWnd, (HMENU)ID_BUTTON_TAN, hInstance, 0);
        button[24] = CreateWindow("button", "|x|", WS_VISIBLE | WS_CHILD, 305, 130, 55, 45, hWnd, (HMENU)ID_BUTTON_ABS, hInstance, 0);
        button[25] = CreateWindow("button", "ctg", WS_VISIBLE | WS_CHILD, 245, 330, 55, 45, hWnd, (HMENU)ID_BUTTON_AT, hInstance, 0);
        button[26] = CreateWindow("button", "Обычный режим", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON , 303, 230, 130, 45, hWnd, (HMENU)ID_BUTTON_OP1, hInstance, 0);
        button[27] = CreateWindow("button", "Квадратное ур.", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 305, 280, 130, 45, hWnd, (HMENU)ID_BUTTON_OP2, hInstance, 0);
        button[28] = CreateWindow("button", "Линейное ур.", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 305, 330, 130, 45, hWnd, (HMENU)ID_BUTTON_OP3, hInstance, 0);
        button[29] = CreateWindow("button", "(", WS_VISIBLE | WS_CHILD, 5, 130, 55, 45, hWnd, (HMENU)ID_BUTTON_LEFT, hInstance, 0);
        button[30] = CreateWindow("button", ")", WS_VISIBLE | WS_CHILD, 65, 130, 55, 45, hWnd, (HMENU)ID_BUTTON_RIGHT, hInstance, 0);
        button[31] = CreateWindow("button", "log(2)", WS_VISIBLE | WS_CHILD, 305, 180, 55, 45, hWnd, (HMENU)ID_BUTTON_LOG, hInstance, 0);
        button[33] = CreateWindow("button", "Pi", WS_VISIBLE | WS_CHILD, 365, 180, 55, 45, hWnd, (HMENU)ID_BUTTON_PI, hInstance, 0);
        button[34] = CreateWindow("button", "e", WS_VISIBLE | WS_CHILD, 365, 130, 55, 45, hWnd, (HMENU)ID_BUTTON_E, hInstance, 0);
        SendMessage(button[26], BM_SETCHECK, BST_CHECKED, 0);
        break;
       

    case WM_COMMAND:
        if ((LOWORD(wParam) == ID_BUTTON_0) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == TEXT('0') && 0 == buf[1])*buf = 0;
            StrCat(buf, TEXT("0"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_1) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == TEXT('0') && 0 == buf[1])*buf = 0;
            StrCat(buf, TEXT("1"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_2) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1])*buf = 0;
            StrCat(buf, TEXT("2"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_3) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1])*buf = 0;
            StrCat(buf, TEXT("3"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_4) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1])*buf = 0;
            StrCat(buf, TEXT("4"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_5) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1])*buf = 0;
            StrCat(buf, TEXT("5"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_6) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1])*buf = 0;
            StrCat(buf, TEXT("6"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_7) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1])*buf = 0;
            StrCat(buf, TEXT("7"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_8) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1])*buf = 0;
            StrCat(buf, TEXT("8"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_9) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == '0' && 0 == buf[1])*buf = 0;
            StrCat(buf, TEXT("9"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_PL) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("+"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_M) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("-"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_ZV) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("*"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_DEL) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("/"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_Decision) && (HIWORD(wParam) == BN_CLICKED))
        {
            if (IsDlgButtonChecked(hWnd, ID_BUTTON_OP1) !=0)
            {
                GetWindowText(hEdit, buf, sizeof(buf));
                SetWindowText(hEdit, Option1(buf));
            }
            else if (IsDlgButtonChecked(hWnd, ID_BUTTON_OP2) != 0)
            {
                GetWindowText(hEdit, buf, sizeof(buf));
                SetWindowText(hEdit, Option2(buf));
            }
            else if (IsDlgButtonChecked(hWnd, ID_BUTTON_OP3) != 0)
            {
                GetWindowText(hEdit, buf, sizeof(buf));
                SetWindowText(hEdit, Option3(buf));
            }
        }
        if ((LOWORD(wParam) == ID_BUTTON_DOT) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("."));
            SetWindowText(hEdit, buf);
        }
        if ((LOWORD(wParam) == ID_BUTTON_AC) && (HIWORD(wParam) == BN_CLICKED))
        {
            if (IsDlgButtonChecked(hWnd, ID_BUTTON_OP1) != 0)
            {
                SetWindowText(hEdit, TEXT("0"));
                buf[0] = 0;
            }
            if (IsDlgButtonChecked(hWnd, ID_BUTTON_OP2) != 0)
            {
                SetWindowText(hEdit, TEXT(""));
                buf[0] = 0;
                StrCat(buf, TEXT("()*x^2+()*x+()=0"));
                SetWindowText(hEdit, buf);
            }
            if (IsDlgButtonChecked(hWnd, ID_BUTTON_OP3) != 0)
            {
                SetWindowText(hEdit, TEXT(""));
                buf[0] = 0;
                StrCat(buf, TEXT("()*x+()=0"));
                SetWindowText(hEdit, buf);
            }
        }

        if ((LOWORD(wParam) == ID_BUTTON_PR) && (HIWORD(wParam) == BN_CLICKED))
        {    
            if (*buf == '0' && 0 == buf[1])*buf = 0;
            StrCat(buf, TEXT("sqrt"));
            SetWindowText(hEdit, buf);
        }
        if ((LOWORD(wParam) == ID_BUTTON_POW) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("^"));
            SetWindowText(hEdit, buf);
        }
        if ((LOWORD(wParam) == ID_BUTTON_SIN) && (HIWORD(wParam) == BN_CLICKED))
        {
            if (*buf == '0' && 0 == buf[1])*buf = 0;
            StrCat(buf, TEXT("sin"));
            SetWindowText(hEdit, buf);
        }
        if ((LOWORD(wParam) == ID_BUTTON_COS) && (HIWORD(wParam) == BN_CLICKED))
        {
            if (*buf == '0' && 0 == buf[1])*buf = 0;
            StrCat(buf, TEXT("cos"));
            SetWindowText(hEdit, buf);
        }
        if ((LOWORD(wParam) == ID_BUTTON_TAN) && (HIWORD(wParam) == BN_CLICKED))
        {
            if (*buf == '0' && 0 == buf[1])*buf = 0;
            StrCat(buf, TEXT("tan"));
            SetWindowText(hEdit, buf);
        }
        if ((LOWORD(wParam) == ID_BUTTON_ABS) && (HIWORD(wParam) == BN_CLICKED))
        {
            if (*buf == '0' && 0 == buf[1])*buf = 0;
            StrCat(buf, TEXT("|"));
            SetWindowText(hEdit, buf);
        }
        if ((LOWORD(wParam) == ID_BUTTON_AT) && (HIWORD(wParam) == BN_CLICKED))
        {
            if (*buf == '0' && 0 == buf[1])*buf = 0;
            StrCat(buf, TEXT("ctg"));
            SetWindowText(hEdit, buf);
        }
        if ((LOWORD(wParam) == ID_BUTTON_OP1) && (HIWORD(wParam) == BN_CLICKED))
        {
            SetWindowText(hEdit, TEXT("0"));
            buf[0] = 0;
        }
        if ((LOWORD(wParam) == ID_BUTTON_OP2) && (HIWORD(wParam) == BN_CLICKED))
        {
            SetWindowText(hEdit, TEXT(""));
            buf[0] = 0;
            StrCat(buf, TEXT("()*x^2+()*x+()=0"));
            SetWindowText(hEdit, buf);
        }
        if ((LOWORD(wParam) == ID_BUTTON_OP3) && (HIWORD(wParam) == BN_CLICKED))
        {
            SetWindowText(hEdit, TEXT(""));
            buf[0] = 0;
            StrCat(buf, TEXT("()*x+()=0"));
            SetWindowText(hEdit, buf);
        }
        if ((LOWORD(wParam) == ID_BUTTON_LEFT) && (HIWORD(wParam) == BN_CLICKED))
        {
            if (*buf == '0' && 0 == buf[1])*buf = 0;
            
            StrCat(buf, TEXT("("));
            SetWindowText(hEdit, buf);
        }
        if ((LOWORD(wParam) == ID_BUTTON_RIGHT) && (HIWORD(wParam) == BN_CLICKED))
        {
            if (*buf == '0' && 0 == buf[1])*buf = 0;
            
            StrCat(buf, TEXT(")"));
            SetWindowText(hEdit, buf);
        }
        if ((LOWORD(wParam) == ID_BUTTON_LOG) && (HIWORD(wParam) == BN_CLICKED))
        {
            if (*buf == '0' && 0 == buf[1])*buf = 0;

            StrCat(buf, TEXT("log"));
            SetWindowText(hEdit, buf);
        }
        if ((LOWORD(wParam) == ID_BUTTON_PI) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == TEXT('0') && 0 == buf[1])*buf = 0;
            StrCat(buf, TEXT("3.14"));
            SetWindowText(hEdit, buf);
        }
        if ((LOWORD(wParam) == ID_BUTTON_E) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            if (*buf == TEXT('0') && 0 == buf[1])*buf = 0;
            StrCat(buf, TEXT("2.71"));
            SetWindowText(hEdit, buf);
        }

        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}