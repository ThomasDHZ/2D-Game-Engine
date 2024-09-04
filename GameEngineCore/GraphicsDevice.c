#include "GraphicsDevice.h"

LRESULT CALLBACK WindowProc2(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        // Handle painting logic if needed
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

HWND __stdcall CreateVulkanWindow(HINSTANCE hInstance, int width, int height, const wchar_t* title)
{
    // Register the window class
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc2;
    wc.hInstance = hInstance;
    wc.lpszClassName = WINDOW_CLASS_NAME;

    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        WINDOW_CLASS_NAME,             // Window class
        title,                         // Window title
        WS_OVERLAPPEDWINDOW,           // Window style
        CW_USEDEFAULT,                 // X position
        CW_USEDEFAULT,                 // Y position
        width,                         // Width
        height,                        // Height
        NULL,                       // Parent window    
        NULL,                       // Menu
        hInstance,                     // Instance handle
        NULL                        // Additional application data
    );

    if (hwnd == NULL) {
        // Handle error
        return NULL;
    }

    ShowWindow(hwnd, SW_SHOW);

    return hwnd;
}