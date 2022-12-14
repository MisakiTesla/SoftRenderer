#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Wunder Renderer";

    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
            0,                              // Optional window styles.
            CLASS_NAME,                     // Window class
            L"Miha SoftRender",    // Window text
            WS_OVERLAPPEDWINDOW,            // Window style

            // Size and position 窗口位置
//            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            500, 300, 600, 600,
            NULL,       // Parent window
            NULL,       // Menu
            hInstance,  // Instance handle
            NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
//    MessageBox(hwnd, TEXT("Hi哈哈"), TEXT("Hihh哈哈"), 0);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_COPY:
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            SetBkMode(hdc,TRANSPARENT);//设置背景透明

            HBRUSH hbrBlack = CreateSolidBrush(RGB(0,0,0));
            HBRUSH hbrWhite = CreateSolidBrush(RGB(255,255,255));
            FillRect(hdc, &ps.rcPaint, hbrBlack);

            RECT rect;
            rect.top = 0L;
            rect.left = ps.rcPaint.left;
            rect.right = ps.rcPaint.right;
            rect.bottom = rect.top + 100;
            SetTextColor(hdc, RGB(0,255,0));

            DrawText(hdc,L"Miha SoftRender",-1, &rect, DT_CENTER);
//            FillRect(hdc, &rect, hbr);
            rect.top = 20L;
            rect.left = ps.rcPaint.left+50;
            rect.right = rect.left+512;
            rect.bottom = rect.top + 512;
            FillRect(hdc, &rect, hbrWhite);
            LPCWSTR s;
            s = TEXT("22\02\0");
//            TextOut(hdc,100,100, s, sizeof(s));
            // All painting occurs here, between BeginPaint and EndPaint.


            SetPixel(hdc,222,222,RGB(255,0,0));
            SetPixel(hdc,0,0,RGB(255,0,0));
            SetPixel(hdc,100,100,RGB(255,0,0));
            SetPixel(hdc,500,0,RGB(255,0,0));
//            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

            EndPaint(hwnd, &ps);
        }
            return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}