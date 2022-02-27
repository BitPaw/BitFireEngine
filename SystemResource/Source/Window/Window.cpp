#include "Window.h"

#include <WinUser.h>
#include <wtypes.h>

#include <windowsx.h>
#include <GL/GL.h>
#include <stdio.h>

#include "../File/Text.h"

using namespace BF;


BF::Dictionary<WindowID, Window*> BF::Window::_windowLookup;
BF::Window* BF::Window::_currentWindow = nullptr;

LRESULT BF::Window::OnWindowEvent(const HWND windowsID, const unsigned int eventID, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;                   // handle to device context 
    TEXTMETRIC tm;             // structure for text metrics 
    static DWORD dwCharX;      // average width of characters 
    static DWORD dwCharY;      // height of characters 
    static DWORD dwClientX;    // width of client area 
    static DWORD dwClientY;    // height of client area 
    static DWORD dwLineLen;    // line length 
    static DWORD dwLines;      // text lines in client area 
    static int nCaretPosX = 0; // horizontal position of caret 
    static int nCaretPosY = 0; // vertical position of caret 
    static int nCharWidth = 0; // width of a character 
    static int cch = 0;        // characters in buffer 
    static int nCurChar = 0;   // index of current character 
    static PTCHAR pchInputBuf; // input buffer 
    int i, j;                  // loop counters 
    int cCR = 0;               // count of carriage returns 
    int nCRIndex = 0;          // index of last carriage return 
    int nVirtKey;              // virtual-key code 
    TCHAR szBuf[128];          // temporary buffer 
    TCHAR ch;                  // current character 
    PAINTSTRUCT ps;            // required by BeginPaint 
    RECT rc;                   // output rectangle for DrawText 
    SIZE sz;                   // string dimensions 
    COLORREF crPrevText;       // previous text color 
    COLORREF crPrevBk;         // previous background color
    size_t* pcch;
    HRESULT hResult;

 

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
                _currentWindow = nullptr;

                window->ID = windowsID;
                window->HandleDeviceContext = windowHandleToDeviceContext;

                _windowLookup.Add(windowsID, window);

                if (window->WindowCreatedCallBack)
                {
                    window->WindowCreatedCallBack(*window);
                }

                window->IsRunning = true;
            }                

            break;
        }       
        case WM_CLOSE:
        {
            if (window->WindowClosingCallBack)
            {              
                window->WindowClosingCallBack(letWindowsHandleEvent);
            }          

            if (letWindowsHandleEvent)
            {
                const LRESULT result = DefWindowProc(windowsID, WM_CLOSE, wParam, lParam);

                if (window->WindowClosedCallBack)
                {
                    window->WindowClosedCallBack();
                }

                return result;
            }

            break;
        }
        case WM_CAPTURECHANGED:
        {
            // wParam unused 
            const WindowID id = (WindowID)lParam;

            
        }
        case WM_SIZE:
        {
            const DWORD width = LOWORD(lParam);
            const DWORD height = HIWORD(lParam);

            if (window->WindowSizeChangedCallBack)
            {
                window->WindowSizeChangedCallBack(width, height);
            }        

            break;
        }
        case WM_SETFOCUS:
        {
            // Create, position, and display the caret when the 
            // window receives the keyboard focus. 

            //CreateCaret(hwndMain, (HBITMAP)1, 0, dwCharY);
            //SetCaretPos(nCaretPosX, nCaretPosY * dwCharY);
            //ShowCaret(hwndMain);
            break;
        }     
        case WM_KILLFOCUS:
        {
            // Hide and destroy the caret when the window loses the 
            // keyboard focus. 

            //HideCaret(hwndMain);
            //DestroyCaret();
            break;
        }

        case WM_LBUTTONDOWN:   
        {
            if (window->MouseButtonCallBack)
            {
                window->MouseButtonCallBack(MouseButton::Left, ButtonState::Down);
            }

            break;
        }
        case WM_LBUTTONUP:            
        {
            if (window->MouseButtonCallBack)
            {
                window->MouseButtonCallBack(MouseButton::Left, ButtonState::Release);
            }

            break;
        }
        case WM_LBUTTONDBLCLK:      
        {
            break;
        }
        case WM_RBUTTONDOWN:   
        {
            if (window->MouseButtonCallBack)
            {
                window->MouseButtonCallBack(MouseButton::Right, ButtonState::Down);
            }

            break;
        }
        case WM_RBUTTONUP:         
        {
            if (window->MouseButtonCallBack)
            {
                window->MouseButtonCallBack(MouseButton::Right, ButtonState::Release);
            }

            break;
        }
        case WM_RBUTTONDBLCLK:        
        {
            break;
        }
        case WM_MBUTTONDOWN:           
        {
            if (window->MouseButtonCallBack)
            {
                window->MouseButtonCallBack(MouseButton::Middle, ButtonState::Down);
            }

            break;
        }
        case WM_MBUTTONUP:           
        {
            if (window->MouseButtonCallBack)
            {
                window->MouseButtonCallBack(MouseButton::Middle, ButtonState::Release);
            }

            break;
        }
        case WM_MBUTTONDBLCLK:  
        {
            break;
        }
        case WM_MOUSEMOVE:
        {
            const short x = GET_X_LPARAM(lParam);
            const short y = GET_Y_LPARAM(lParam);

            //OnMouseMoveEvent(x, y);

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
            
            if (window->KeyBoardKeyCallBack)
            {
                window->KeyBoardKeyCallBack(buttonInfo);
            }

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
            if (cch == 0)       // nothing in input buffer 
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
    }

    if (letWindowsHandleEvent)
    {
        return DefWindowProc(windowsID, eventID, wParam, lParam);
    }

    return NULL;
}

BF::Window::Window()
{
    ID = 0;
    HandleDeviceContext = 0;
    OpenGLRenderingContext = 0;

    MessageThreadID = 0;
    IsRunning = 0;

    _cursorMode = CursorMode::Show;

    MouseButtonCallBack = 0;
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

    WNDCLASS wndclass{ 0 };

    wndclass.style = CS_OWNDC;
    wndclass.lpfnWndProc = OnWindowEvent;
    wndclass.hInstance = hInstance;
    wndclass.lpszClassName = lpClassName;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(COLOR_BACKGROUND);
    /*
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszMenuName = NULL;*/

    WORD classID = RegisterClassW(&wndclass);

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
        Window& window = *creationInfo.CreatedWindow;
        
        while (creationInfo.Async)
        {
            MSG message{ 0 };
            const bool peekResult = PeekMessageW(&message, nullptr, 0, 0, PM_NOREMOVE);
                      
           // printf("Tick");

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

}

void BF::Window::IconCorner()
{

}

void BF::Window::IconTaskBar()
{

}

void BF::Window::Size(unsigned int& width, unsigned int& height)
{

}

void BF::Window::SizeChange(const unsigned int width, const unsigned int height)
{

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
            ClipCursor(&desktop);
            ShowCursor(true);

            break;
        }
        case CursorMode::Locked:
        {
            RECT newPOS{0};
            GetWindowRect(ID, &newPOS);            

            unsigned int midX = (newPOS.right - newPOS.left) / 2;
            unsigned int midY = (newPOS.bottom - newPOS.top) / 2;

            desktop.left = midX;
            desktop.right = midX;
            desktop.bottom = midY;
            desktop.top = midY;         

            ClipCursor(&desktop);
            SetCursorPos(midX, midY);

            while (ShowCursor(false) >= 0);
            
            break;
        }
    }

    _cursorMode = cursorMode;
}