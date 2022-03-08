#include "Window.h"

#include <GL/GL.h>
#include <stdio.h>

#if defined(OSUnix)
#elif defined(OSWindows)
#include <windowsx.h>
#include <WinUser.h>
#include <wtypes.h>
#include <hidusage.h>
#include <Dbt.h>
#endif

#include "../File/Text.h"
#include "../Controller/ControllerData.h"
#include "../Controller/ControllerSystem.h"

#define InvokeEvent(FunctionPoniter, ...) if(FunctionPoniter) FunctionPoniter(__VA_ARGS__)


BF::Dictionary<WindowID, BF::Window*> BF::Window::_windowLookup;
BF::Window* BF::Window::_currentWindow = nullptr;

#if defined(OSWindows)
LRESULT BF::Window::OnWindowEvent(HWND windowsID, UINT eventID, WPARAM wParam, LPARAM lParam)
{
    bool letWindowsHandleEvent = true;

    BF::Window* window = nullptr;
    BF::Window** windowAdress = BF::Window::_windowLookup.GetValue(windowsID);
    const bool isRegistered = windowAdress;
    
    if (isRegistered)
    {
        window = *windowAdress;
    }

    switch (eventID)
    {
#if 0 // Can be used but is an inferior version of just polling the data with 'joyGetDevData()' as this is also time based (Polling)
        case MM_JOY1MOVE: 
        {
            const WORD fwButtons = wParam;
            const WORD xPos = LOWORD(lParam);
            const WORD yPos = HIWORD(lParam);
            const bool isButton1Pressed = (fwButtons & JOY_BUTTON1) == JOY_BUTTON1;
            const bool isButton2Pressed = (fwButtons & JOY_BUTTON2) == JOY_BUTTON2;
            const bool isButton3Pressed = (fwButtons & JOY_BUTTON3) == JOY_BUTTON3;
            const bool isButton4Pressed = (fwButtons & JOY_BUTTON4) == JOY_BUTTON4;

            break;
        }
#endif 
        case WM_SETCURSOR:
        {
            const HWND windowsHandle = (HWND)wParam;
            const WORD hitTestResult = LOWORD(lParam);
            const WORD sourceMessage = HIWORD(lParam);

            SetCursor(NULL);

            return true; // prevent further processing
        }
        case WM_GETMINMAXINFO:
        {
            //wParam is unused
            MINMAXINFO* minmaxInfo = (MINMAXINFO*)lParam;

            break;
        }
        case WM_CREATE:
        {          
            const HDC windowHandleToDeviceContext = GetDC(windowsID);

            if (_currentWindow)
            {
                window = _currentWindow;    
                window->ID = windowsID;
                window->HandleDeviceContext = windowHandleToDeviceContext;

                _currentWindow = nullptr;

                _windowLookup.Add(windowsID, window);

                InvokeEvent(window->WindowCreatedCallBack, *window);

                window->IsRunning = true;
            }                

            break;
        }       
        case WM_CLOSE:
        {
            InvokeEvent(window->WindowClosingCallBack, letWindowsHandleEvent);

            if (letWindowsHandleEvent)
            {
                const LRESULT result = DefWindowProc(windowsID, WM_CLOSE, wParam, lParam);

                InvokeEvent(window->WindowClosedCallBack);

                return result;
            }

            break;
        }
        case WM_CAPTURECHANGED:
        {
            // wParam unused 
            const WindowID id = (WindowID)lParam;

            break;            
        }
        case WM_INPUT:
        {
            const size_t inputCode = GET_RAWINPUT_CODE_WPARAM(wParam);
            const HRAWINPUT handle = (HRAWINPUT)lParam;         
            const UINT uiCommand = RID_INPUT; // RID_HEADER        
                      
            switch (inputCode)
            {
                case RIM_INPUT: // Input occurred while the application was in the foreground.
                {
                    RAWINPUT rawInput{ 0 };
                    UINT rawInputSize = sizeof(RAWINPUT); // Can't be 'const' ! 

                    const UINT result = GetRawInputData(handle, uiCommand, &rawInput, &rawInputSize, sizeof(RAWINPUTHEADER));
                    const bool sucessful = result != -1;

                    if (sucessful)
                    {
#if UseRawMouseData
                        if (rawInput.header.dwType == RIM_TYPEMOUSE)
                        {
                            const LONG mouseX = rawInput.data.mouse.lLastX;
                            const LONG mouseY = rawInput.data.mouse.lLastY;

                            InvokeEvent(window->MouseMoveCallBack, mouseX, mouseY);

                            // Wheel data needs to be pointer casted to interpret an unsigned short as a short, with no conversion
                            // otherwise it'll overflow when going negative.
                            // Didn't happen before some minor changes in the code, doesn't seem to go away
                            // so it's going to have to be like this.
                           // if (raw->data.mouse.usButtonFlags & RI_MOUSE_WHEEL)
                           //     input.mouse.wheel = (*(short*)&raw->data.mouse.usButtonData) / WHEEL_DELTA;
                        }
#endif               
                    }

                    break;
                }
                case RIM_INPUTSINK: // Input occurred while the application was not in the foreground.
                {
                    break;
                }

                default:
                    break;
            }

            break;
        }
        case WM_SIZE:
        {
            const DWORD width = LOWORD(lParam);
            const DWORD height = HIWORD(lParam);

            InvokeEvent(window->WindowSizeChangedCallBack, width, height);

            break;
        }
        case WM_SETFOCUS:
        {
            // Create, position, and display the caret when the 
            // window receives the keyboard focus. 

            //CreateCaret(window->ID, (HBITMAP)1, 0, dwCharY);
            //SetCaretPos(nCaretPosX, nCaretPosY * dwCharY);
            //ShowCaret(window->ID);
            break;
        }     
        case WM_KILLFOCUS:
        {
            // Hide and destroy the caret when the window loses the 
            // keyboard focus. 

            //HideCaret(window->ID);
            //DestroyCaret();
            break;
        }
        case WM_LBUTTONDOWN:   
        {
            InvokeEvent(window->MouseClickCallBack, MouseButton::Left, ButtonState::Down);
            break;
        }
        case WM_LBUTTONUP:            
        {
            InvokeEvent(window->MouseClickCallBack, MouseButton::Left, ButtonState::Release);   
            break;
        }
        case WM_LBUTTONDBLCLK:      
        {
            InvokeEvent(window->MouseClickDoubleCallBack, MouseButton::Left);
            break;
        }
        case WM_RBUTTONDOWN:   
        { 
            InvokeEvent(window->MouseClickCallBack, MouseButton::Right, ButtonState::Down);   
            break;
        }
        case WM_RBUTTONUP:         
        {
            InvokeEvent(window->MouseClickCallBack, MouseButton::Right, ButtonState::Release);    
            break;
        }
        case WM_RBUTTONDBLCLK:        
        {
            InvokeEvent(window->MouseClickDoubleCallBack, MouseButton::Right);
            break;
        }
        case WM_MBUTTONDOWN:           
        {       
            InvokeEvent(window->MouseClickCallBack, MouseButton::Middle, ButtonState::Down);   
            break;
        }
        case WM_MBUTTONUP:           
        {  
            InvokeEvent(window->MouseClickCallBack, MouseButton::Middle, ButtonState::Release);    
            break;
        }
        case WM_MBUTTONDBLCLK:  
        {
            InvokeEvent(window->MouseClickDoubleCallBack, MouseButton::Middle);
            break;
        }
        case WM_MOUSEMOVE:
        {
            // Do not use this function if you want precise movement!
            // Windows adds 'mouse acceleration' this will create inconsistent movement.

#if !UseRawMouseData
            const short x = GET_X_LPARAM(lParam);
            const short y = GET_Y_LPARAM(lParam);

            InvokeEvent(window->MouseMoveCallBack, x, y);
#endif
            break;
        }
        case WM_KEYDOWN:
        case WM_KEYUP:
       // case WM_CHAR:    
        {            
            ButtonState mode;

            switch (eventID)
            {
                case WM_KEYUP:
                {
                    mode = ButtonState::Release;
                    break;
                }
                case WM_KEYDOWN:
                {
                    mode = ButtonState::Down;
                    break;
                }
                default:
                    break;
            }

            const size_t character = wParam;
            const size_t characterInfo = lParam;

            KeyBoardKeyInfo buttonInfo;
            buttonInfo.Key = ConvertKeyBoardKey(character);
            buttonInfo.Mode = mode;
            buttonInfo.Repeat          = (characterInfo & 0b00000000000000001111111111111111); // Die Wiederholungsanzahl für die aktuelle Meldung.Der Wert gibt an, wie oft die Tastatureingabe automatisch angezeigt wird, wenn der Benutzer den Schlüssel hält.Die Wiederholungsanzahl ist immer 1 für eine WM _ KEYUP - Nachricht.
            buttonInfo.ScanCode        = (characterInfo & 0b00000000111111110000000000000000) >> 16; // Der Scancode.Der Wert hängt vom OEM ab.
            buttonInfo.SpecialKey      = (characterInfo & 0b00000001000000000000000000000000) >> 24; // Gibt an, ob es sich bei der Taste um eine erweiterte Taste handelt, z.B.die rechte ALT - und STRG - Taste, die auf einer erweiterten Tastatur mit 101 oder 102 Tasten angezeigt werden.Der Wert ist 1, wenn es sich um einen erweiterten Schlüssel handelt.andernfalls ist es 0.
            //buttonInfo.ReservedDontUse = (characterInfo & 0b00011110000000000000000000000000) >> 25; //	Reserviert; nicht verwenden.
            buttonInfo.KontextCode     = (characterInfo & 0b00100000000000000000000000000000) >> 29; // Der Kontextcode.Der Wert ist für eine WM _ KEYUP - Nachricht immer 0.
            buttonInfo.PreState        = (characterInfo & 0b01000000000000000000000000000000) >> 30; // Der vorherige Schlüsselzustand.Der Wert ist immer 1 für eine WM _ KEYUP - Nachricht.
            buttonInfo.GapState        = (characterInfo & 0b10000000000000000000000000000000) >> 31; // Der Übergangszustand.Der Wert ist immer 1 für eine WM _ KEYUP - Nachricht.
            
            InvokeEvent(window->KeyBoardKeyCallBack, buttonInfo);

            break;
        }          
        /*
        case WM_KEYDOWN:
            switch (wParam)
            {
                case VK_LEFT:   // LEFT ARROW 

                    // The caret can move only to the beginning of 
                    // the current line. 

                    if (nCaretPosX > 0)
                    {
                        HideCaret(hwndMain);

                        // Retrieve the character to the left of 
                        // the caret, calculate the character's 
                        // width, then subtract the width from the 
                        // current horizontal position of the caret 
                        // to obtain the new position. 

                        ch = pchInputBuf[--nCurChar];
                        hdc = GetDC(hwndMain);
                        GetCharWidth32(hdc, ch, ch, &nCharWidth);
                        ReleaseDC(hwndMain, hdc);
                        nCaretPosX = max(nCaretPosX - nCharWidth,
                            0);
                        ShowCaret(hwndMain);
                    }
                    break;

                case VK_RIGHT:  // RIGHT ARROW 

                    // Caret moves to the right or, when a carriage 
                    // return is encountered, to the beginning of 
                    // the next line. 

                    if (nCurChar < cch)
                    {
                        HideCaret(hwndMain);

                        // Retrieve the character to the right of 
                        // the caret. If it's a carriage return, 
                        // position the caret at the beginning of 
                        // the next line. 

                        ch = pchInputBuf[nCurChar];
                        if (ch == 0x0D)
                        {
                            nCaretPosX = 0;
                            nCaretPosY++;
                        }

                        // If the character isn't a carriage 
                        // return, check to see whether the SHIFT 
                        // key is down. If it is, invert the text 
                        // colors and output the character. 

                        else
                        {
                            hdc = GetDC(hwndMain);
                            nVirtKey = GetKeyState(VK_SHIFT);
                            if (nVirtKey & SHIFTED)
                            {
                                crPrevText = SetTextColor(hdc,
                                    RGB(255, 255, 255));
                                crPrevBk = SetBkColor(hdc,
                                    RGB(0, 0, 0));
                                TextOut(hdc, nCaretPosX,
                                    nCaretPosY * dwCharY,
                                    &ch, 1);
                                SetTextColor(hdc, crPrevText);
                                SetBkColor(hdc, crPrevBk);
                            }

                            // Get the width of the character and 
                            // calculate the new horizontal 
                            // position of the caret. 

                            GetCharWidth32(hdc, ch, ch, &nCharWidth);
                            ReleaseDC(hwndMain, hdc);
                            nCaretPosX = nCaretPosX + nCharWidth;
                        }
                        nCurChar++;
                        ShowCaret(hwndMain);
                        break;
                    }
                    break;

                case VK_UP:     // UP ARROW 
                case VK_DOWN:   // DOWN ARROW 
                    MessageBeep((UINT)-1);
                    return 0;

                case VK_HOME:   // HOME 

                    // Set the caret's position to the upper left 
                    // corner of the client area. 

                    nCaretPosX = nCaretPosY = 0;
                    nCurChar = 0;
                    break;

                case VK_END:    // END  

                    // Move the caret to the end of the text. 

                    for (i = 0; i < cch; i++)
                    {
                        // Count the carriage returns and save the 
                        // index of the last one. 

                        if (pchInputBuf[i] == 0x0D)
                        {
                            cCR++;
                            nCRIndex = i + 1;
                        }
                    }
                    nCaretPosY = cCR;

                    // Copy all text between the last carriage 
                    // return and the end of the keyboard input 
                    // buffer to a temporary buffer. 

                    for (i = nCRIndex, j = 0; i < cch; i++, j++)
                        szBuf[j] = pchInputBuf[i];
                    szBuf[j] = TEXT('\0');

                    // Retrieve the text extent and use it 
                    // to set the horizontal position of the 
                    // caret. 

                    hdc = GetDC(hwndMain);
                    hResult = StringCchLength(szBuf, 128, pcch);
                    if (FAILED(hResult))
                    {
                        // TODO: write error handler
                    }
                    GetTextExtentPoint32(hdc, szBuf, *pcch,
                        &sz);
                    nCaretPosX = sz.cx;
                    ReleaseDC(hwndMain, hdc);
                    nCurChar = cch;
                    break;

                default:
                    break;
            }
            SetCaretPos(nCaretPosX, nCaretPosY * dwCharY);
            break;
            */
        case WM_PAINT:
           // if (cch == 0)       // nothing in input buffer 
                break;

           // hdc = BeginPaint(hwndMain, &ps);
           // HideCaret(hwndMain);

            // Set the clipping rectangle, and then draw the text 
            // into it. 

            //SetRect(&rc, 0, 0, dwLineLen, dwClientY);
           // DrawText(hdc, pchInputBuf, -1, &rc, DT_LEFT);

            //ShowCaret(hwndMain);
            //EndPaint(hwndMain, &ps);
            break;

            // Process other messages. 

        case WM_DESTROY:
            //PostQuitMessage(0);

            // Free the input buffer. 

           // GlobalFree((HGLOBAL)pchInputBuf);
            //UnregisterHotKey(hwndMain, 0xAAAA);OpenGL
            break;

        case WM_DISPLAYCHANGE:
            //_glfwPollMonitorsWin32();
            break;

        case WM_DEVICECHANGE:
        {
           // if (!_glfw.joysticksInitialized)
            //    break;

            const WORD eventID = wParam;

            switch (eventID)
            {
                case DBT_DEVNODES_CHANGED: // A device has been added to or removed from the system.
                {
                    break;
                }
                case DBT_QUERYCHANGECONFIG: // Permission is requested to change the current configuration(dock or undock).
                {
                    break;
                }
                case DBT_CONFIGCHANGED: // The current configuration has changed, due to a dock or undock.
                {
                    break;
                }
                case DBT_CONFIGCHANGECANCELED: // A request to change the current configuration(dock or undock) has been canceled.
                {
                    break;
                }
                case DBT_DEVICEARRIVAL: // A device or piece of media has been inserted and is now available.
                {
                    DEV_BROADCAST_HDR* dbh = (DEV_BROADCAST_HDR*)lParam;
                    if (dbh && dbh->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
                    {
                        // _glfwDetectJoystickConnectionWin32();
                    }

                    break;
                }
                case DBT_DEVICEQUERYREMOVE: // Permission is requested to remove a device or piece of media.Any application can deny this request and cancel the removal.
                {
                    break;
                }
                case DBT_DEVICEQUERYREMOVEFAILED: // A request to remove a device or piece of media has been canceled.
                {
                    break;
                }
                case DBT_DEVICEREMOVEPENDING: // A device or piece of media is about to be removed.Cannot be denied.
                {
                    break;
                }
                case DBT_DEVICEREMOVECOMPLETE: // A device or piece of media has been removed.
                {
                    DEV_BROADCAST_HDR* dbh = (DEV_BROADCAST_HDR*)lParam;
                    if (dbh && dbh->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
                    //     _glfwDetectJoystickDisconnectionWin32();

                    break;
                }
                case DBT_DEVICETYPESPECIFIC: // A device - specific event has occurred.
                {
                    break;
                }
                case DBT_CUSTOMEVENT: // A custom event has occurred.
                {
                    break;
                }
                case DBT_USERDEFINED: // The meaning of this message is user - defined.
                {
                    break;
                }
                default:
                {
                    break;
                }
            }

            break;
        }
    }

    if (letWindowsHandleEvent)
    {
        return DefWindowProc(windowsID, eventID, wParam, lParam);
    }

    return NULL;
}
#endif

BF::Window::Window()
{
    ID = 0;
    HandleDeviceContext = 0;
    OpenGLRenderingContext = 0;

    MessageThreadID = 0;
    IsRunning = 0;
    CursorID = 0;

    _cursorMode = CursorMode::Show;

    MouseClickCallBack = 0;
    MouseClickDoubleCallBack = 0;
    MouseMoveCallBack = 0;
    KeyBoardKeyCallBack = 0;
    WindowCreatedCallBack = 0;
    WindowSizeChangedCallBack = 0;
    WindowClosingCallBack = 0;
    WindowClosedCallBack = 0;
}

BF::Window::~Window()
{
    Destroy();
}

ThreadFunctionReturnType BF::Window::WindowThead(void* windowCreationInfoAdress)
{
    if (!windowCreationInfoAdress)
    {
        return -1;
    }

    WindowCreationInfo& creationInfo = *(WindowCreationInfo*)windowCreationInfoAdress;

    DWORD windowStyle = WS_EX_APPWINDOW;
    DWORD dwStyle = WS_VISIBLE | WS_OVERLAPPEDWINDOW;
    HWND hWndParent = nullptr;
    HMENU hMenu = nullptr;
    HINSTANCE hInstance = GetModuleHandle(NULL);
    void* lpParam = 0;
    const wchar_t* lpClassName = L"BFE::Window::AsyncThread";


    const HCURSOR cursorID = LoadCursor(NULL, IDC_PERSON);
    creationInfo.CreatedWindow->CursorID = cursorID;

    WNDCLASS wndclass{ 0 }; 
    wndclass.style = CS_OWNDC; //  CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = OnWindowEvent;
    wndclass.cbClsExtra = 0; // The number of extra bytes to allocate following the window-class structure.
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_HAND);
    wndclass.hCursor = cursorID;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(COLOR_BACKGROUND);
    wndclass.lpszMenuName = 0;
    wndclass.lpszClassName = lpClassName;


    const WORD classID = RegisterClassW(&wndclass);

    lpClassName = (wchar_t*)classID;

    _currentWindow = creationInfo.CreatedWindow;

    WindowID windowID = CreateWindowExW
    (
        windowStyle,
        lpClassName,
        creationInfo.Title,
        dwStyle,
        creationInfo.X,
        creationInfo.Y,
        creationInfo.Width,
        creationInfo.Height,
        hWndParent,
        hMenu,
        hInstance,
        lpParam
    );

    if (windowID == NULL)
    {
        DWORD error = GetLastError();
        wchar_t errorBuffer[1024];
        wsprintf(errorBuffer, L"Error creating window. Error code, decimal %d, hexadecimal %X.", error, error);
        MessageBox(NULL, errorBuffer, L"Error", MB_ICONHAND);
    }

    {
        // We're configuring just one RAWINPUTDEVICE, the mouse, so it's a single-element array (a pointer).
        const RAWINPUTDEVICE rid
        {
            HID_USAGE_PAGE_GENERIC,
            HID_USAGE_GENERIC_MOUSE,
            RIDEV_INPUTSINK,
            windowID
        };

        RegisterRawInputDevices(&rid, 1, sizeof(RAWINPUTDEVICE));

        // RegisterRawInputDevices should not be used from a library, as it may interfere with any raw input processing logic already present in applications that load it.
    }

    {
        Window& window = *creationInfo.CreatedWindow;
        
        while (creationInfo.Async)
        {
            MSG message{ 0 };
            const bool peekResult = PeekMessageW(&message, nullptr, 0, 0, PM_NOREMOVE);
                      
            if (peekResult)
            {
                const bool messageResult = GetMessageW(&message, nullptr, 0, 0);

                if (messageResult)
                {
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }
                else
                {
                    // An error occurred! Handle it and bail out.
                    MessageBox(nullptr, L"Unexpected Error", nullptr, MB_OK | MB_ICONERROR);
                }
            }           
        }   
    }    
}

void BF::Window::Create()
{
    Create(CW_USEDEFAULT, CW_USEDEFAULT, "BitFire Engine Window");
}

void BF::Window::Create(const unsigned int width, const unsigned int height, const char* title)
{
    WindowCreationInfo* creationInfo = new WindowCreationInfo();
    creationInfo->Async = true;
    creationInfo->CreatedWindow = this;
    creationInfo->X = CW_USEDEFAULT;
    creationInfo->Y = CW_USEDEFAULT;
    creationInfo->Width = width;
    creationInfo->Height = height;

    Text::Copy(creationInfo->Title, title, 256);

    if (creationInfo->Async)
    {
        const ThreadID id = Thread::Run(WindowThead, creationInfo);
        
        MessageThreadID = id;

        while (ID == 0)
        {

        }
    }
    else
    {
        WindowThead(creationInfo);
    }  

    //Thread::WaitForFinish(id);    
}

void BF::Window::Destroy()
{
    CloseWindow(ID);
}

void BF::Window::IconCorner()
{

}

void BF::Window::IconTaskBar()
{

}

void BF::Window::Size
(
    unsigned int& x,
    unsigned int& y,
    unsigned int& width,
    unsigned int& height
)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    RECT rect{ 0 };

    const bool result = GetWindowRect(ID, &rect);
    const bool success = result != 0;

    // Get Last Error

    x = rect.left;
    y = rect.top;
    width = rect.right - x;
    height = rect.bottom - y; 
#endif
}

void BF::Window::SizeChange
(
    const unsigned int x,
    const unsigned int y,
    const unsigned int width,
    const unsigned int height
)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    RECT rect
    {
        x,
        y,
        width + x, 
        height + y
    };

    DWORD style = 0;
    DWORD exStyle = 0;

    //AdjustWindowRectEx();

    const bool result = AdjustWindowRectEx(&rect, style, FALSE, exStyle);
    const bool success = result != 0;

    // Get Last Error
#endif
}

void BF::Window::Position(unsigned int& x, unsigned int& y)
{
    
}

void BF::Window::PositionChange(const unsigned int x, const unsigned int y)
{

}

void BF::Window::PositonCenterScreen()
{

}

void BF::Window::Cursor()
{

}

void BF::Window::Cursor(const CursorIcon cursorIcon)
{
    const unsigned int cursorID = ToCursorIcon(cursorIcon);
    const bool validCursorIcon = cursorID != -1;

    if (!validCursorIcon)
    {
        return;
    }

    HANDLE handle = LoadImageW(NULL, MAKEINTRESOURCEW(cursorID), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
 
}

void BF::Window::CursorTexture()
{

}

BF::CursorMode BF::Window::CursorCaptureMode()
{
    return _cursorMode;
}

void BF::Window::CursorCaptureMode(const CursorMode cursorMode)
{
    RECT desktop;
    // Get a handle to the desktop window
    const HWND hDesktop = GetDesktopWindow();
    // Get the size of screen to the variable desktop
    GetWindowRect(hDesktop, &desktop);
    // The top left corner will have coordinates (0,0)
    // and the bottom right corner will have coordinates
    // (horizontal, vertical)
    unsigned int horizontal = desktop.right;
    unsigned int vertical = desktop.bottom;


    switch (cursorMode)
    {
        case CursorMode::Show:
        {  
            //ClipCursor(&desktop);
            //ShowCursor(true);

            SetCursor(LoadCursorW(NULL, IDC_ARROW));

            ClipCursor(NULL);

            break;
        }
        case CursorMode::Lock:
        {
            RECT clipRect;
            GetClientRect(ID, &clipRect);
            ClientToScreen(ID, (POINT*)&clipRect.left);
            ClientToScreen(ID, (POINT*)&clipRect.right);
            ClipCursor(&clipRect);

            SetCursor(NULL);

            break;
        }
        case CursorMode::LockAndHide:
        {
            RECT clipRect;
            GetClientRect(ID, &clipRect);
            ClientToScreen(ID, (POINT*)&clipRect.left);
            ClientToScreen(ID, (POINT*)&clipRect.right);

            int xOff = (clipRect.right - clipRect.left) / 2;
            int yoFf = (clipRect.bottom - clipRect.top) / 2;

            clipRect.left += xOff;
            clipRect.top += yoFf;
            clipRect.right -= xOff;
            clipRect.bottom -= yoFf;

            ClipCursor(&clipRect);

            SetCursor(NULL);

            break;
        }
    }

    _cursorMode = cursorMode;
}