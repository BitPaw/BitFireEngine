#include "Window.h"


#include <GL/glew.h>
#include <GL/gl.h>

#include <stdio.h>

#if defined(OSUnix)

#define DefautPositionX 00000000000000
#define DefautPositionY 00000000000000

#elif defined(OSWindows)
#include <windowsx.h>
#include <WinUser.h>
#include <wtypes.h>
#include <hidusage.h>
#include <Dbt.h>

#define DefautPositionX CW_USEDEFAULT
#define DefautPositionY CW_USEDEFAULT

#endif

#include <Text/Text.h>
#include <Graphic/OpenGL/OpenGL.h>

#include "../Controller/ControllerData.h"
#include "../Controller/ControllerSystem.h"

#define InvokeEvent(FunctionPoniter, ...) if(FunctionPoniter) FunctionPoniter(__VA_ARGS__)

BF::Dictionary<WindowID, BF::Window*> BF::Window::_windowLookup;
BF::Window* BF::Window::_currentWindow = nullptr;

#if defined(OSUnix)
void BF::Window::OnWindowEvent(const XEvent& event)
{
    BF::Window& window = *_currentWindow;

    switch(event.type)
    {
        case KeyPress:
        {
            printf("[Event] KeyPress \n");

            break;
        }
        case KeyRelease:
        {
            printf("[Event] KeyRelease \n");

            break;
        }
        case ButtonPress:
        {
            const XButtonEvent& buttonEvent = event.xbutton;
            unsigned int buttonID = buttonEvent.button;

            printf("[Event] Button Pressed %i\n", buttonID);
            break;
        }
        case ButtonRelease:
        {
            printf("[Event] ButtonRelease \n");

            break;
        }
        case MotionNotify:
        {
            printf("[Event] MotionNotify \n");

            break;
        }
        case EnterNotify:
        {
            printf("[Event] EnterNotify \n");

            break;
        }
        case LeaveNotify:
        {
            printf("[Event] LeaveNotify \n");

            break;
        }
        case FocusIn:
        {
            printf("[Event] FocusIn \n");

            break;
        }
        case FocusOut:
        {
            printf("[Event] FocusOut \n");

            break;
        }
        case KeymapNotify:
        {
            printf("[Event] KeymapNotify \n");

            break;
        }
        case Expose:
        {
            printf("[Event] Expose \n");

            /*
              XWindowAttributes gwa;

                        XGetWindowAttributes(window.Dis, windowID, &gwa);
                        glViewport(0, 0, gwa.width, gwa.height);


                        glClearColor(1.0, 1.0, 1.0, 1.0);
                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                        glBegin(GL_POLYGON);
                        glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
                        glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
                        glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
                        glEnd();

                        // Flush drawing command buffer to make drawing happen as soon as possible.
                        //glFlush();

                        window.FrameBufferSwap();*/

            break;
        }
        case GraphicsExpose:
        {
            printf("[Event] GraphicsExpose \n");

            break;
        }
        case NoExpose:
        {
            printf("[Event] NoExpose \n");

            break;
        }
        case VisibilityNotify:
        {
            printf("[Event] VisibilityNotify \n");

            break;
        }
        case CreateNotify:
        {
            printf("[Event] CreateNotify \n");

            break;
        }
        case DestroyNotify:
        {
            printf("[Event] DestroyNotify \n");

            break;
        }
        case UnmapNotify:
        {
            printf("[Event] UnmapNotify \n");

            break;
        }
        case MapNotify:
        {
            printf("[Event] MapNotify \n");

            break;
        }
        case MapRequest:
        {
            printf("[Event] MapRequest \n");

            break;
        }
        case ReparentNotify:
        {
            printf("[Event] ReparentNotify \n");

            break;
        }
        case ConfigureNotify:
        {
            printf("[Event] ConfigureNotify \n");

            break;
        }
        case ConfigureRequest:
        {
            printf("[Event] Destroyed \n");

            break;
        }
        case GravityNotify:
        {
            printf("[Event] GravityNotify \n");

            break;
        }
        case ResizeRequest:
        {
            const XResizeRequestEvent resizeRequestEvent = event.xresizerequest;
            const int width = resizeRequestEvent.width;
            const int height = resizeRequestEvent.height;

            printf("[Event] Resize %i x %i. Type %i\n", width, height);

            //InvokeEvent(window.WindowSizeChangedCallBack, width, height);

            break;
        }
        case CirculateNotify:
        {
            printf("[Event] CirculateNotify \n");

            break;
        }
        case CirculateRequest:
        {
            printf("[Event] CirculateRequest \n");

            break;
        }
        case PropertyNotify:
        {
            printf("[Event] PropertyNotify \n");

            break;
        }
        case SelectionClear:
        {
            printf("[Event] SelectionClear \n");

            break;
        }
        case SelectionRequest:
        {
            printf("[Event] SelectionRequest \n");

            break;
        }
        case SelectionNotify:
        {
            printf("[Event] SelectionNotify \n");

            break;
        }
        case ColormapNotify:
        {
            printf("[Event] ColormapNotify \n");

            break;
        }
        case ClientMessage:
        {
            printf("[Event] ClientMessage \n");

            break;
        }
        case MappingNotify:
        {
            printf("[Event] MappingNotify \n");

            break;
        }
        case GenericEvent:
        {
            break;
        }
    }
}
#elif defined(OSWindows)

enum class WindowEventType
{
    Invalid,

    NoMessage,
    Create,
    Destroy,
    Move,
    Size,
    Activate,
    RedrawSet,
    FocusSet,
    FocusKill,
    Enable,
    TextSet,
    TextGet,
    TextGetLength,
    Paint,
    Close,
    SessionQuerryEnd,
    SessionEnd,
    QuerryOpen,
    Quit,
    BackgroundErase,
    SystemColorChange,
    ShowWindow,
    IconChange,
    SettingChange,
    DeviceModeChange,
    ActivateApp,
    FontChange,
    TimeChange,
    CancelMode,
    CursorSet,
    MouseActivate,
    ChildActivate,
    QueueSync,
    SizeChange,
    IconPaint,

    IconBackgroundErase,
    DialogControlNext,
    SPOOLERSTATUS,
    ItemDraw,
    ItemMeasure,
    ItemDelete,
    VKEYTOITEM,
    CHARTOITEM,
    FontSet,
    FontGet,
    SETHOTKEY,
    GETHOTKEY,
    QUERYDRAGICON,
    COMPAREITEM,
    GETOBJECT,
    COMPACTING,
    COMMNOTIFY,
    WINDOWPOSCHANGING,
    WINDOWPOSCHANGED,
    POWER,
    COPYDATA,
    CANCELJOURNAL,
    NOTIFY,
    INPUTLANGCHANGEREQUEST,
    INPUTLANGCHANGE,
    TCARD,
    HELP,
    USERCHANGED,
    NOTIFYFORMAT,
    CONTEXTMENU,
    STYLECHANGING,
    STYLECHANGED,
    DISPLAYCHANGE,
    GETICON,
    SETICON,
    NCCREATE,
    NCDESTROY,
    NCCALCSIZE,
    NCHITTEST,
    NCPAINT,
    NCACTIVATE,
    GETDLGCODE,
    SYNCPAINT,
    NCMOUSEMOVE,
    NCLBUTTONDOWN,
    NCLBUTTONUP,
    NCLBUTTONDBLCLK,
    NCRBUTTONDOWN,
    NCRBUTTONUP,
    NCRBUTTONDBLCLK,
    NCMBUTTONDOWN,
    NCMBUTTONUP,
    NCMBUTTONDBLCLK,
    NCXBUTTONDOWN,
    NCXBUTTONUP,
    NCXBUTTONDBLCLK,
    INPUT_DEVICE_CHANGE,
    INPUT,
    KEYFIRST,
    KEYDOWN,
    KEYUP,
    CHAR,
    DEADCHAR,
    SYSKEYDOWN,
    SYSKEYUP,
    SYSCHAR,
    SYSDEADCHAR,
    UNICHAR,
    KEYLAST,
    //UNICODE_NOCHAR,
    IME_STARTCOMPOSITION,
    IME_ENDCOMPOSITION,
    IME_COMPOSITION,
    IME_KEYLAST,
    INITDIALOG,
    COMMAND,
    SYSCOMMAND,
    TIMER,
    HSCROLL,
    VSCROLL,
    INITMENU,
    INITMENUPOPUP,
    GESTURE,
    GESTURENOTIFY,
    MENUSELECT,
    MENUCHAR,
    ENTERIDLE,
    MENURBUTTONUP,
    MENUDRAG,
    MENUGETOBJECT,
    UNINITMENUPOPUP,
    MENUCOMMAND,
    CHANGEUISTATE,
    UPDATEUISTATE,
    QUERYUISTATE,
    CTLCOLORMSGBOX,
    CTLCOLOREDIT,
    CTLCOLORLISTBOX,
    CTLCOLORBTN,
    CTLCOLORDLG,
    CTLCOLORSCROLLBAR,
    CTLCOLORSTATIC,
    GETHMENU,
    MOUSEFIRST,
    MOUSEMOVE,
    LBUTTONDOWN,
    LBUTTONUP,
    LBUTTONDBLCLK,
    RBUTTONDOWN,
    RBUTTONUP,
    RBUTTONDBLCLK,
    MBUTTONDOWN,
    MBUTTONUP,
    MBUTTONDBLCLK,
    MOUSEWHEEL,
    XBUTTONDOWN,
    XBUTTONUP,
    XBUTTONDBLCLK,
    MOUSEHWHEEL,
    MOUSELAST,
    PARENTNOTIFY,
    ENTERMENULOOP,
    EXITMENULOOP,
    NEXTMENU,
    SIZING,
    CAPTURECHANGED,
    MOVING,
    POWERBROADCAST,
    DEVICECHANGE,
    MDICREATE,
    MDIDESTROY,
    MDIACTIVATE,
    MDIRESTORE,
    MDINEXT,
    MDIMAXIMIZE,
    MDITILE,
    MDICASCADE,
    MDIICONARRANGE,
    MDIGETACTIVE,
    MDISETMENU,
    ENTERSIZEMOVE,
    EXITSIZEMOVE,
    DROPFILES,
    MDIREFRESHMENU,
    POINTERDEVICECHANGE,
    POINTERDEVICEINRANGE,
    POINTERDEVICEOUTOFRANGE,
    TOUCH,
    NCPOINTERUPDATE,
    NCPOINTERDOWN,
    NCPOINTERUP,
    POINTERUPDATE,
    POINTERDOWN,
    POINTERUP,
    POINTERENTER,
    POINTERLEAVE,
    POINTERACTIVATE,
    POINTERCAPTURECHANGED,
    TOUCHHITTESTING,
    POINTERWHEEL,
    POINTERHWHEEL,
    POINTERROUTEDTO,
    POINTERROUTEDAWAY,
    POINTERROUTEDRELEASED,
    IME_SETCONTEXT,
    IME_NOTIFY,
    IME_CONTROL,
    IME_COMPOSITIONFULL,
    IME_SELECT,
    IME_CHAR,
    IME_REQUEST,
    IME_KEYDOWN,
    IME_KEYUP,
    MOUSEHOVER,
    MOUSELEAVE,
    NCMOUSEHOVER,
    NCMOUSELEAVE,
    WTSSESSION_CHANGE,
    TABLET_FIRST,
    TABLET_LAST,
    DPICHANGED,
    DPICHANGED_BEFOREPARENT,
    DPICHANGED_AFTERPARENT,
    GETDPISCALEDSIZE,
    CUT,
    COPY,
    PASTE,
    CLEAR,
    UNDO,
    RENDERFORMAT,
    RENDERALLFORMATS,
    DESTROYCLIPBOARD,
    DRAWCLIPBOARD,
    PAINTCLIPBOARD,
    VSCROLLCLIPBOARD,
    SIZECLIPBOARD,
    ASKCBFORMATNAME,
    CHANGECBCHAIN,
    HSCROLLCLIPBOARD,
    QUERYNEWPALETTE,
    PALETTEISCHANGING,
    PALETTECHANGED,
    HOTKEY,
    PRINT,
    PRINTCLIENT,
    APPCOMMAND,
    THEMECHANGED,
    CLIPBOARDUPDATE,
    DWMCOMPOSITIONCHANGED,
    DWMNCRENDERINGCHANGED,
    DWMCOLORIZATIONCOLORCHANGED,
    DWMWINDOWMAXIMIZEDCHANGE,
    DWMSENDICONICTHUMBNAIL,
    DWMSENDICONICLIVEPREVIEWBITMAP,
    GETTITLEBARINFOEX,
    HANDHELDFIRST,
    HANDHELDLAST,
    AFXFIRST,
    AFXLAST,
    PENWINFIRST,
    PENWINLAST,
    APP
};

WindowEventType ToWindowEventType(const unsigned int windowEventID)
{
    switch(windowEventID)
    {
        case WM_NULL: return WindowEventType::NoMessage;
        case WM_CREATE: return WindowEventType::Create;
        case WM_DESTROY: return WindowEventType::Destroy;
        case WM_MOVE: return WindowEventType::Move;
        case WM_SIZE: return WindowEventType::Size;
        case WM_ACTIVATE: return WindowEventType::Activate;
        case WM_SETFOCUS: return WindowEventType::FocusSet;
        case WM_KILLFOCUS: return WindowEventType::FocusKill;
        case WM_ENABLE: return WindowEventType::Enable;
        case WM_SETREDRAW: return WindowEventType::RedrawSet;
        case WM_SETTEXT: return WindowEventType::TextSet;
        case WM_GETTEXT: return WindowEventType::TextGet;
        case WM_GETTEXTLENGTH: return WindowEventType::TextGetLength;
        case WM_PAINT: return WindowEventType::Paint;
        case WM_CLOSE: return WindowEventType::Close;
        case WM_QUERYENDSESSION: return WindowEventType::SessionQuerryEnd;
        case WM_QUERYOPEN: return WindowEventType::QuerryOpen;
        case WM_ENDSESSION: return WindowEventType::SessionEnd;
        case WM_QUIT: return WindowEventType::Quit;
        case WM_ERASEBKGND: return WindowEventType::BackgroundErase;
        case WM_SYSCOLORCHANGE: return WindowEventType::SystemColorChange;
        case WM_SHOWWINDOW: return WindowEventType::ShowWindow;
        case WM_WININICHANGE: return WindowEventType::IconChange;
        //case WM_SETTINGCHANGE                WM_WININICHANGE 
        case WM_DEVMODECHANGE: return WindowEventType::DeviceModeChange;
        case WM_ACTIVATEAPP: return WindowEventType::ActivateApp; 
        case WM_FONTCHANGE: return WindowEventType::FontChange;
        case WM_TIMECHANGE: return WindowEventType::TimeChange;
        case WM_CANCELMODE: return WindowEventType::CancelMode; 
        case WM_SETCURSOR: return WindowEventType::CursorSet;
        case WM_MOUSEACTIVATE: return WindowEventType::MouseActivate; 
        case WM_CHILDACTIVATE: return WindowEventType::ChildActivate;
        case WM_QUEUESYNC: return WindowEventType::QueueSync; 
        case WM_GETMINMAXINFO: return WindowEventType::SizeChange; 
        case WM_PAINTICON: return WindowEventType::IconPaint;

            

        case WM_ICONERASEBKGND: return WindowEventType::IconBackgroundErase;
        case WM_NEXTDLGCTL: return WindowEventType::DialogControlNext; 
        case WM_SPOOLERSTATUS: return WindowEventType::SPOOLERSTATUS; 
        case WM_DRAWITEM: return WindowEventType::ItemDraw; 
        case WM_MEASUREITEM: return WindowEventType::ItemMeasure; 
        case WM_DELETEITEM: return WindowEventType::ItemDelete; 
        case WM_VKEYTOITEM: return WindowEventType::VKEYTOITEM;
        case WM_CHARTOITEM: return WindowEventType::CHARTOITEM;
        case WM_SETFONT: return WindowEventType::FontSet; 
        case WM_GETFONT: return WindowEventType::FontGet; 
        case WM_SETHOTKEY: return WindowEventType::SETHOTKEY;
        case WM_GETHOTKEY: return WindowEventType::GETHOTKEY;
        case WM_QUERYDRAGICON: return WindowEventType::QUERYDRAGICON;
        case WM_COMPAREITEM: return WindowEventType::COMPAREITEM;
        case WM_GETOBJECT: return WindowEventType::GETOBJECT;
        case WM_COMPACTING: return WindowEventType::COMPACTING;
        case WM_COMMNOTIFY: return WindowEventType::COMMNOTIFY;   /* no longer suported */
        case WM_WINDOWPOSCHANGING: return WindowEventType::WINDOWPOSCHANGING;
        case WM_WINDOWPOSCHANGED: return WindowEventType::WINDOWPOSCHANGED;
        case WM_POWER: return WindowEventType::POWER;
        case WM_COPYDATA: return WindowEventType::COPYDATA;
        case WM_CANCELJOURNAL: return WindowEventType::CANCELJOURNAL;
        case WM_NOTIFY: return WindowEventType::NOTIFY;
        case WM_INPUTLANGCHANGEREQUEST: return WindowEventType::INPUTLANGCHANGEREQUEST;
        case WM_INPUTLANGCHANGE: return WindowEventType::INPUTLANGCHANGE;
        case WM_TCARD: return WindowEventType::TCARD;
        case WM_HELP: return WindowEventType::HELP;
        case WM_USERCHANGED: return WindowEventType::USERCHANGED;
        case WM_NOTIFYFORMAT: return WindowEventType::NOTIFYFORMAT;
        case WM_CONTEXTMENU: return WindowEventType::CONTEXTMENU;
        case WM_STYLECHANGING: return WindowEventType::STYLECHANGING;
        case WM_STYLECHANGED: return WindowEventType::STYLECHANGED;
        case WM_DISPLAYCHANGE: return WindowEventType::DISPLAYCHANGE;
        case WM_GETICON: return WindowEventType::GETICON;
        case WM_SETICON: return WindowEventType::SETICON;
        case WM_NCCREATE: return WindowEventType::NCCREATE;
        case WM_NCDESTROY: return WindowEventType::NCDESTROY;
        case WM_NCCALCSIZE: return WindowEventType::NCCALCSIZE;
        case WM_NCHITTEST: return WindowEventType::NCHITTEST;
        case WM_NCPAINT: return WindowEventType::NCPAINT;
        case WM_NCACTIVATE: return WindowEventType::NCACTIVATE;
        case WM_GETDLGCODE: return WindowEventType::GETDLGCODE;
        case WM_SYNCPAINT: return WindowEventType::SYNCPAINT;
        case WM_NCMOUSEMOVE: return WindowEventType::NCMOUSEMOVE;
        case WM_NCLBUTTONDOWN: return WindowEventType::NCLBUTTONDOWN;
        case WM_NCLBUTTONUP: return WindowEventType::NCLBUTTONUP;
        case WM_NCLBUTTONDBLCLK: return WindowEventType::NCLBUTTONDBLCLK;
        case WM_NCRBUTTONDOWN: return WindowEventType::NCRBUTTONDOWN;
        case WM_NCRBUTTONUP: return WindowEventType::NCRBUTTONUP;
        case WM_NCRBUTTONDBLCLK: return WindowEventType::NCRBUTTONDBLCLK;
        case WM_NCMBUTTONDOWN: return WindowEventType::NCMBUTTONDOWN;
        case WM_NCMBUTTONUP: return WindowEventType::NCMBUTTONUP;
        case WM_NCMBUTTONDBLCLK: return WindowEventType::NCMBUTTONDBLCLK;
        case WM_NCXBUTTONDOWN: return WindowEventType::NCXBUTTONDOWN;
        case WM_NCXBUTTONUP: return WindowEventType::NCXBUTTONUP;
        case WM_NCXBUTTONDBLCLK: return WindowEventType::NCXBUTTONDBLCLK;
        case WM_INPUT_DEVICE_CHANGE: return WindowEventType::INPUT_DEVICE_CHANGE;
        case WM_INPUT: return WindowEventType::INPUT;
        //case WM_KEYFIRST: return WindowEventType::KEYFIRST;
        case WM_KEYDOWN: return WindowEventType::KEYDOWN;
        case WM_KEYUP: return WindowEventType::KEYUP;
        case WM_CHAR: return WindowEventType::CHAR;
        case WM_DEADCHAR: return WindowEventType::DEADCHAR;
        case WM_SYSKEYDOWN: return WindowEventType::SYSKEYDOWN;
        case WM_SYSKEYUP: return WindowEventType::SYSKEYUP;
        case WM_SYSCHAR: return WindowEventType::SYSCHAR;
        case WM_SYSDEADCHAR: return WindowEventType::SYSDEADCHAR;
        case WM_UNICHAR: return WindowEventType::UNICHAR;
        //case WM_KEYLAST: return WindowEventType::KEYLAST;
           // case UNICODE_NOCHAR: return WindowEventType::XXXXXXXXXXXXXXX;
            case WM_IME_STARTCOMPOSITION: return WindowEventType::IME_STARTCOMPOSITION;

                /*
            case WM_IME_ENDCOMPOSITION: return WindowEventType::XXXXXXXXXXXXXXX;
            case WM_IME_COMPOSITION: return WindowEventType::XXXXXXXXXXXXXXX;
            case WM_IME_KEYLAST: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_INITDIALOG: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_COMMAND: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_SYSCOMMAND: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_TIMER: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_HSCROLL: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_VSCROLL: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_INITMENU: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_INITMENUPOPUP: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_GESTURE: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_GESTURENOTIFY: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_MENUSELECT: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_MENUCHAR: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_ENTERIDLE: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_MENURBUTTONUP: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_MENUDRAG: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_MENUGETOBJECT: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_UNINITMENUPOPUP: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_MENUCOMMAND: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_CHANGEUISTATE: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_UPDATEUISTATE: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_QUERYUISTATE: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_CTLCOLORMSGBOX: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_CTLCOLOREDIT: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_CTLCOLORLISTBOX: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_CTLCOLORBTN: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_CTLCOLORDLG: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_CTLCOLORSCROLLBAR: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_CTLCOLORSTATIC: return WindowEventType::CTLCOLORSTATIC;
            case MN_GETHMENU: return WindowEventType::GETHMENU;
            //case WM_MOUSEFIRST: return WindowEventType::MOUSEFIRST;
            case WM_MOUSEMOVE: return WindowEventType::MOUSEMOVE;
            case WM_LBUTTONDOWN: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_LBUTTONUP: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_LBUTTONDBLCLK: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_RBUTTONDOWN: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_RBUTTONUP: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_RBUTTONDBLCLK: return WindowEventType::RBUTTONDBLCLK;
            case WM_MBUTTONDOWN: return WindowEventType::MBUTTONDOWN;
            case WM_MBUTTONUP: return WindowEventType::MBUTTONUP;
            case WM_MBUTTONDBLCLK: return WindowEventType::MBUTTONDBLCLK;
            case WM_MOUSEWHEEL: return WindowEventType::MOUSEWHEEL;
            case WM_XBUTTONDOWN: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_XBUTTONUP: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_XBUTTONDBLCLK: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_MOUSEHWHEEL: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_MOUSELAST: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_PARENTNOTIFY: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_ENTERMENULOOP: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_EXITMENULOOP: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_NEXTMENU: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_SIZING: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_CAPTURECHANGED: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_MOVING: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_POWERBROADCAST: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_DEVICECHANGE: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_MDICREATE: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_MDIDESTROY: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_MDIACTIVATE: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_MDIRESTORE: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_MDINEXT: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_MDIMAXIMIZE: return WindowEventType::MDIMAXIMIZE;
            case WM_MDITILE: return WindowEventType::MDITILE;
            case WM_MDICASCADE: return WindowEventType::MDICASCADE;
            case WM_MDIICONARRANGE: return WindowEventType::MDIICONARRANGE;
            case WM_MDIGETACTIVE: return WindowEventType::MDIGETACTIVE;
            case WM_MDISETMENU: return WindowEventType::MDISETMENU;
            case WM_ENTERSIZEMOVE: return WindowEventType::ENTERSIZEMOVE;
            case WM_EXITSIZEMOVE: return WindowEventType::EXITSIZEMOVE;
            case WM_DROPFILES: return WindowEventType::DROPFILES;
            case WM_MDIREFRESHMENU: return WindowEventType::MDIREFRESHMENU;
            case WM_POINTERDEVICECHANGE: return WindowEventType::POINTERDEVICECHANGE;
            case WM_POINTERDEVICEINRANGE: return WindowEventType::POINTERDEVICEINRANGE;
            case WM_POINTERDEVICEOUTOFRANGE: return WindowEventType::POINTERDEVICEOUTOFRANGE;
            case WM_TOUCH: return WindowEventType::TOUCH;
            case WM_NCPOINTERUPDATE: return WindowEventType::XXXXXXXXXXXXXXX; 241
            case WM_NCPOINTERDOWN: return WindowEventType::XXXXXXXXXXXXXXX; 242
            case WM_NCPOINTERUP: return WindowEventType::XXXXXXXXXXXXXXX; 243
            case WM_POINTERUPDATE: return WindowEventType::XXXXXXXXXXXXXXX; 245
            case WM_POINTERDOWN: return WindowEventType::XXXXXXXXXXXXXXX; 246
            case WM_POINTERUP: return WindowEventType::XXXXXXXXXXXXXXX; 247
            case WM_POINTERENTER: return WindowEventType::XXXXXXXXXXXXXXX; 249
            case WM_POINTERLEAVE: return WindowEventType::XXXXXXXXXXXXXXX; 24A
            case WM_POINTERACTIVATE: return WindowEventType::XXXXXXXXXXXXXXX; 24B
            case WM_POINTERCAPTURECHANGED: return WindowEventType::XXXXXXXXXXXXXXX; 24C
            case WM_TOUCHHITTESTING: return WindowEventType::XXXXXXXXXXXXXXX; 24D
            case WM_POINTERWHEEL: return WindowEventType::XXXXXXXXXXXXXXX; 24E
            case WM_POINTERHWHEEL: return WindowEventType::XXXXXXXXXXXXXXX; 24F
            case DM_POINTERHITTEST: return WindowEventType::XXXXXXXXXXXXXXX; 250
            case WM_POINTERROUTEDTO: return WindowEventType::XXXXXXXXXXXXXXX; 251
            case WM_POINTERROUTEDAWAY: return WindowEventType::XXXXXXXXXXXXXXX; 252
            case WM_POINTERROUTEDRELEASED: return WindowEventType::XXXXXXXXXXXXXXX; 253
            case WM_IME_SETCONTEXT: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_IME_NOTIFY: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_IME_CONTROL: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_IME_COMPOSITIONFULL: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_IME_SELECT: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_IME_CHAR: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_IME_REQUEST: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_IME_KEYDOWN: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_IME_KEYUP: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_MOUSEHOVER: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_MOUSELEAVE: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_NCMOUSEHOVER: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_NCMOUSELEAVE: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_WTSSESSION_CHANGE: return WindowEventType::XXXXXXXXXXXXXXX;
            case WM_TABLET_FIRST: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_TABLET_LAST: return WindowEventType::XXXXXXXXXXXXXXX;
            case WM_DPICHANGED: return WindowEventType::XXXXXXXXXXXXXXX;
            case WM_DPICHANGED_BEFOREPARENT: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_DPICHANGED_AFTERPARENT: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_GETDPISCALEDSIZE: return WindowEventType::XXXXXXXXXXXXXXX;
            case WM_CUT: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_COPY: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_PASTE: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_CLEAR: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_UNDO: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_RENDERFORMAT: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_RENDERALLFORMATS: return WindowEventType::XXXXXXXXXXXXXXX; 
            case WM_DESTROYCLIPBOARD: return WindowEventType::XXXXXXXXXXXXXXX; */


            case WM_DRAWCLIPBOARD: return WindowEventType::DRAWCLIPBOARD;
            case WM_PAINTCLIPBOARD: return WindowEventType::PAINTCLIPBOARD;
            case WM_VSCROLLCLIPBOARD: return WindowEventType::VSCROLLCLIPBOARD;
            case WM_SIZECLIPBOARD: return WindowEventType::SIZECLIPBOARD;
            case WM_ASKCBFORMATNAME: return WindowEventType::ASKCBFORMATNAME;
            case WM_CHANGECBCHAIN: return WindowEventType::CHANGECBCHAIN;
            case WM_HSCROLLCLIPBOARD: return WindowEventType::HSCROLLCLIPBOARD;
            case WM_QUERYNEWPALETTE: return WindowEventType::QUERYNEWPALETTE;
            case WM_PALETTEISCHANGING: return WindowEventType::PALETTEISCHANGING;
            case WM_PALETTECHANGED: return WindowEventType::PALETTECHANGED;
            case WM_HOTKEY: return WindowEventType::HOTKEY;
            case WM_PRINT: return WindowEventType::PRINT;
            case WM_PRINTCLIENT: return WindowEventType::PRINTCLIENT;
            case WM_APPCOMMAND: return WindowEventType::APPCOMMAND;
            case WM_THEMECHANGED: return WindowEventType::THEMECHANGED;
            case WM_CLIPBOARDUPDATE: return WindowEventType::CLIPBOARDUPDATE;
            case WM_DWMCOMPOSITIONCHANGED: return WindowEventType::DWMCOMPOSITIONCHANGED;
            case WM_DWMNCRENDERINGCHANGED: return WindowEventType::DWMNCRENDERINGCHANGED;
            case WM_DWMCOLORIZATIONCOLORCHANGED: return WindowEventType::DWMCOLORIZATIONCOLORCHANGED;
            case WM_DWMWINDOWMAXIMIZEDCHANGE: return WindowEventType::DWMWINDOWMAXIMIZEDCHANGE;
            case WM_DWMSENDICONICTHUMBNAIL: return WindowEventType::DWMSENDICONICTHUMBNAIL;
            case WM_DWMSENDICONICLIVEPREVIEWBITMAP: return WindowEventType::DWMSENDICONICLIVEPREVIEWBITMAP;
            case WM_GETTITLEBARINFOEX: return WindowEventType::GETTITLEBARINFOEX;
            case WM_HANDHELDFIRST: return WindowEventType::HANDHELDFIRST;
            case WM_HANDHELDLAST: return WindowEventType::HANDHELDLAST;
            case WM_AFXFIRST: return WindowEventType::AFXFIRST;
            case WM_AFXLAST: return WindowEventType::AFXLAST;
            case WM_PENWINFIRST: return WindowEventType::PENWINFIRST; 
            case WM_PENWINLAST: return WindowEventType::PENWINLAST;
            case WM_APP: return WindowEventType::APP;


            default: return WindowEventType::Invalid;
    }
}



LRESULT BF::Window::OnWindowEvent(HWND windowsID, UINT eventID, WPARAM wParam, LPARAM lParam)
{
    const WindowEventType windowEventType = ToWindowEventType(eventID);

    switch(windowEventType)
    {
        case WindowEventType::NoMessage:
            break;
        case WindowEventType::Create: // Gets called inside the "CreateWindow" function.
        {
            // Do nothíng here, as it's too soon to regard the window as 'created'

            return DefWindowProc(windowsID, eventID, wParam, lParam);
        }
        case WindowEventType::Destroy:
            break;
        case WindowEventType::Move:
            break;
        case WindowEventType::Size:
            break;
        case WindowEventType::Activate:
            break;
        case WindowEventType::RedrawSet:
            break;
        case WindowEventType::FocusSet:
            break;
        case WindowEventType::FocusKill:
            break;
        case WindowEventType::Enable:
            break;
        case WindowEventType::TextSet:
            break;
        case WindowEventType::TextGet:
            break;
        case WindowEventType::TextGetLength:
            break;
        case WindowEventType::Paint:
            break;
        case WindowEventType::Close:
            break;
        case WindowEventType::SessionQuerryEnd:
            break;
        case WindowEventType::SessionEnd:
            break;
        case WindowEventType::QuerryOpen:
            break;
        case WindowEventType::Quit:
            break;
        case WindowEventType::BackgroundErase:
            break;
        case WindowEventType::SystemColorChange:
            break;
        case WindowEventType::ShowWindow:
            break;
        case WindowEventType::IconChange:
            break;
        case WindowEventType::SettingChange:
            break;
        case WindowEventType::DeviceModeChange:
            break;
        case WindowEventType::ActivateApp:
            break;
        case WindowEventType::FontChange:
            break;
        case WindowEventType::TimeChange:
            break;
        case WindowEventType::CancelMode:
            break;
        case WindowEventType::CursorSet:
            break;
        case WindowEventType::MouseActivate:
            break;
        case WindowEventType::ChildActivate:
            break;
        case WindowEventType::QueueSync:
            break;
        case WindowEventType::SizeChange:
            break;
        case WindowEventType::IconPaint:
            break;
        case WindowEventType::IconBackgroundErase:
            break;
        case WindowEventType::DialogControlNext:
            break;
        case WindowEventType::SPOOLERSTATUS:
            break;
        case WindowEventType::ItemDraw:
            break;
        case WindowEventType::ItemMeasure:
            break;
        case WindowEventType::ItemDelete:
            break;
        case WindowEventType::VKEYTOITEM:
            break;
        case WindowEventType::CHARTOITEM:
            break;
        case WindowEventType::FontSet:
            break;
        case WindowEventType::FontGet:
            break;
        case WindowEventType::SETHOTKEY:
            break;
        case WindowEventType::GETHOTKEY:
            break;
        case WindowEventType::QUERYDRAGICON:
            break;
        case WindowEventType::COMPAREITEM:
            break;
        case WindowEventType::GETOBJECT:
            break;
        case WindowEventType::COMPACTING:
            break;
        case WindowEventType::COMMNOTIFY:
            break;
        case WindowEventType::WINDOWPOSCHANGING:
            break;
        case WindowEventType::WINDOWPOSCHANGED:
            break;
        case WindowEventType::POWER:
            break;
        case WindowEventType::COPYDATA:
            break;
        case WindowEventType::CANCELJOURNAL:
            break;
        case WindowEventType::NOTIFY:
            break;
        case WindowEventType::INPUTLANGCHANGEREQUEST:
            break;
        case WindowEventType::INPUTLANGCHANGE:
            break;
        case WindowEventType::TCARD:
            break;
        case WindowEventType::HELP:
            break;
        case WindowEventType::USERCHANGED:
            break;
        case WindowEventType::NOTIFYFORMAT:
            break;
        case WindowEventType::CONTEXTMENU:
            break;
        case WindowEventType::STYLECHANGING:
            break;
        case WindowEventType::STYLECHANGED:
            break;
        case WindowEventType::DISPLAYCHANGE:
            break;
        case WindowEventType::GETICON:
            break;
        case WindowEventType::SETICON:
            break;
        case WindowEventType::NCCREATE:
            break;
        case WindowEventType::NCDESTROY:
            break;
        case WindowEventType::NCCALCSIZE:
            break;
        case WindowEventType::NCHITTEST:
            break;
        case WindowEventType::NCPAINT:
            break;
        case WindowEventType::NCACTIVATE:
            break;
        case WindowEventType::GETDLGCODE:
            break;
        case WindowEventType::SYNCPAINT:
            break;
        case WindowEventType::NCMOUSEMOVE:
            break;
        case WindowEventType::NCLBUTTONDOWN:
            break;
        case WindowEventType::NCLBUTTONUP:
            break;
        case WindowEventType::NCLBUTTONDBLCLK:
            break;
        case WindowEventType::NCRBUTTONDOWN:
            break;
        case WindowEventType::NCRBUTTONUP:
            break;
        case WindowEventType::NCRBUTTONDBLCLK:
            break;
        case WindowEventType::NCMBUTTONDOWN:
            break;
        case WindowEventType::NCMBUTTONUP:
            break;
        case WindowEventType::NCMBUTTONDBLCLK:
            break;
        case WindowEventType::NCXBUTTONDOWN:
            break;
        case WindowEventType::NCXBUTTONUP:
            break;
        case WindowEventType::NCXBUTTONDBLCLK:
            break;
        case WindowEventType::INPUT_DEVICE_CHANGE:
            break;
        case WindowEventType::INPUT:
            break;
        case WindowEventType::KEYFIRST:
            break;
        case WindowEventType::KEYDOWN:
            break;
        case WindowEventType::KEYUP:
            break;
        case WindowEventType::CHAR:
            break;
        case WindowEventType::DEADCHAR:
            break;
        case WindowEventType::SYSKEYDOWN:
            break;
        case WindowEventType::SYSKEYUP:
            break;
        case WindowEventType::SYSCHAR:
            break;
        case WindowEventType::SYSDEADCHAR:
            break;
        case WindowEventType::UNICHAR:
            break;
        case WindowEventType::KEYLAST:
            break;
        case WindowEventType::IME_STARTCOMPOSITION:
            break;
        case WindowEventType::IME_ENDCOMPOSITION:
            break;
        case WindowEventType::IME_COMPOSITION:
            break;
        case WindowEventType::IME_KEYLAST:
            break;
        case WindowEventType::INITDIALOG:
            break;
        case WindowEventType::COMMAND:
            break;
        case WindowEventType::SYSCOMMAND:
            break;
        case WindowEventType::TIMER:
            break;
        case WindowEventType::HSCROLL:
            break;
        case WindowEventType::VSCROLL:
            break;
        case WindowEventType::INITMENU:
            break;
        case WindowEventType::INITMENUPOPUP:
            break;
        case WindowEventType::GESTURE:
            break;
        case WindowEventType::GESTURENOTIFY:
            break;
        case WindowEventType::MENUSELECT:
            break;
        case WindowEventType::MENUCHAR:
            break;
        case WindowEventType::ENTERIDLE:
            break;
        case WindowEventType::MENURBUTTONUP:
            break;
        case WindowEventType::MENUDRAG:
            break;
        case WindowEventType::MENUGETOBJECT:
            break;
        case WindowEventType::UNINITMENUPOPUP:
            break;
        case WindowEventType::MENUCOMMAND:
            break;
        case WindowEventType::CHANGEUISTATE:
            break;
        case WindowEventType::UPDATEUISTATE:
            break;
        case WindowEventType::QUERYUISTATE:
            break;
        case WindowEventType::CTLCOLORMSGBOX:
            break;
        case WindowEventType::CTLCOLOREDIT:
            break;
        case WindowEventType::CTLCOLORLISTBOX:
            break;
        case WindowEventType::CTLCOLORBTN:
            break;
        case WindowEventType::CTLCOLORDLG:
            break;
        case WindowEventType::CTLCOLORSCROLLBAR:
            break;
        case WindowEventType::CTLCOLORSTATIC:
            break;
        case WindowEventType::GETHMENU:
            break;
        case WindowEventType::MOUSEFIRST:
            break;
        case WindowEventType::MOUSEMOVE:
            break;
        case WindowEventType::LBUTTONDOWN:
            break;
        case WindowEventType::LBUTTONUP:
            break;
        case WindowEventType::LBUTTONDBLCLK:
            break;
        case WindowEventType::RBUTTONDOWN:
            break;
        case WindowEventType::RBUTTONUP:
            break;
        case WindowEventType::RBUTTONDBLCLK:
            break;
        case WindowEventType::MBUTTONDOWN:
            break;
        case WindowEventType::MBUTTONUP:
            break;
        case WindowEventType::MBUTTONDBLCLK:
            break;
        case WindowEventType::MOUSEWHEEL:
            break;
        case WindowEventType::XBUTTONDOWN:
            break;
        case WindowEventType::XBUTTONUP:
            break;
        case WindowEventType::XBUTTONDBLCLK:
            break;
        case WindowEventType::MOUSEHWHEEL:
            break;
        case WindowEventType::MOUSELAST:
            break;
        case WindowEventType::PARENTNOTIFY:
            break;
        case WindowEventType::ENTERMENULOOP:
            break;
        case WindowEventType::EXITMENULOOP:
            break;
        case WindowEventType::NEXTMENU:
            break;
        case WindowEventType::SIZING:
            break;
        case WindowEventType::CAPTURECHANGED:
            break;
        case WindowEventType::MOVING:
            break;
        case WindowEventType::POWERBROADCAST:
            break;
        case WindowEventType::DEVICECHANGE:
            break;
        case WindowEventType::MDICREATE:
            break;
        case WindowEventType::MDIDESTROY:
            break;
        case WindowEventType::MDIACTIVATE:
            break;
        case WindowEventType::MDIRESTORE:
            break;
        case WindowEventType::MDINEXT:
            break;
        case WindowEventType::MDIMAXIMIZE:
            break;
        case WindowEventType::MDITILE:
            break;
        case WindowEventType::MDICASCADE:
            break;
        case WindowEventType::MDIICONARRANGE:
            break;
        case WindowEventType::MDIGETACTIVE:
            break;
        case WindowEventType::MDISETMENU:
            break;
        case WindowEventType::ENTERSIZEMOVE:
            break;
        case WindowEventType::EXITSIZEMOVE:
            break;
        case WindowEventType::DROPFILES:
            break;
        case WindowEventType::MDIREFRESHMENU:
            break;
        case WindowEventType::POINTERDEVICECHANGE:
            break;
        case WindowEventType::POINTERDEVICEINRANGE:
            break;
        case WindowEventType::POINTERDEVICEOUTOFRANGE:
            break;
        case WindowEventType::TOUCH:
            break;
        case WindowEventType::NCPOINTERUPDATE:
            break;
        case WindowEventType::NCPOINTERDOWN:
            break;
        case WindowEventType::NCPOINTERUP:
            break;
        case WindowEventType::POINTERUPDATE:
            break;
        case WindowEventType::POINTERDOWN:
            break;
        case WindowEventType::POINTERUP:
            break;
        case WindowEventType::POINTERENTER:
            break;
        case WindowEventType::POINTERLEAVE:
            break;
        case WindowEventType::POINTERACTIVATE:
            break;
        case WindowEventType::POINTERCAPTURECHANGED:
            break;
        case WindowEventType::TOUCHHITTESTING:
            break;
        case WindowEventType::POINTERWHEEL:
            break;
        case WindowEventType::POINTERHWHEEL:
            break;
        case WindowEventType::POINTERROUTEDTO:
            break;
        case WindowEventType::POINTERROUTEDAWAY:
            break;
        case WindowEventType::POINTERROUTEDRELEASED:
            break;
        case WindowEventType::IME_SETCONTEXT:
            break;
        case WindowEventType::IME_NOTIFY:
            break;
        case WindowEventType::IME_CONTROL:
            break;
        case WindowEventType::IME_COMPOSITIONFULL:
            break;
        case WindowEventType::IME_SELECT:
            break;
        case WindowEventType::IME_CHAR:
            break;
        case WindowEventType::IME_REQUEST:
            break;
        case WindowEventType::IME_KEYDOWN:
            break;
        case WindowEventType::IME_KEYUP:
            break;
        case WindowEventType::MOUSEHOVER:
            break;
        case WindowEventType::MOUSELEAVE:
            break;
        case WindowEventType::NCMOUSEHOVER:
            break;
        case WindowEventType::NCMOUSELEAVE:
            break;
        case WindowEventType::WTSSESSION_CHANGE:
            break;
        case WindowEventType::TABLET_FIRST:
            break;
        case WindowEventType::TABLET_LAST:
            break;
        case WindowEventType::DPICHANGED:
            break;
        case WindowEventType::DPICHANGED_BEFOREPARENT:
            break;
        case WindowEventType::DPICHANGED_AFTERPARENT:
            break;
        case WindowEventType::GETDPISCALEDSIZE:
            break;
        case WindowEventType::CUT:
            break;
        case WindowEventType::COPY:
            break;
        case WindowEventType::PASTE:
            break;
        case WindowEventType::CLEAR:
            break;
        case WindowEventType::UNDO:
            break;
        case WindowEventType::RENDERFORMAT:
            break;
        case WindowEventType::RENDERALLFORMATS:
            break;
        case WindowEventType::DESTROYCLIPBOARD:
            break;
        case WindowEventType::DRAWCLIPBOARD:
            break;
        case WindowEventType::PAINTCLIPBOARD:
            break;
        case WindowEventType::VSCROLLCLIPBOARD:
            break;
        case WindowEventType::SIZECLIPBOARD:
            break;
        case WindowEventType::ASKCBFORMATNAME:
            break;
        case WindowEventType::CHANGECBCHAIN:
            break;
        case WindowEventType::HSCROLLCLIPBOARD:
            break;
        case WindowEventType::QUERYNEWPALETTE:
            break;
        case WindowEventType::PALETTEISCHANGING:
            break;
        case WindowEventType::PALETTECHANGED:
            break;
        case WindowEventType::HOTKEY:
            break;
        case WindowEventType::PRINT:
            break;
        case WindowEventType::PRINTCLIENT:
            break;
        case WindowEventType::APPCOMMAND:
            break;
        case WindowEventType::THEMECHANGED:
            break;
        case WindowEventType::CLIPBOARDUPDATE:
            break;
        case WindowEventType::DWMCOMPOSITIONCHANGED:
            break;
        case WindowEventType::DWMNCRENDERINGCHANGED:
            break;
        case WindowEventType::DWMCOLORIZATIONCOLORCHANGED:
            break;
        case WindowEventType::DWMWINDOWMAXIMIZEDCHANGE:
            break;
        case WindowEventType::DWMSENDICONICTHUMBNAIL:
            break;
        case WindowEventType::DWMSENDICONICLIVEPREVIEWBITMAP:
            break;
        case WindowEventType::GETTITLEBARINFOEX:
            break;
        case WindowEventType::HANDHELDFIRST:
            break;
        case WindowEventType::HANDHELDLAST:
            break;
        case WindowEventType::AFXFIRST:
            break;
        case WindowEventType::AFXLAST:
            break;
        case WindowEventType::PENWINFIRST:
            break;
        case WindowEventType::PENWINLAST:
            break;
        case WindowEventType::APP:
            break;

        case WindowEventType::Invalid:
        default:
            break;
    }

    // If nothing had grabbed the event by now, let the default funcion handle it.
    return DefWindowProc(windowsID, eventID, wParam, lParam);



    // Safe functions
    switch(eventID)
    {
      
        case WM_GETMINMAXINFO: // Gets called right after 'WM_CREATE'
        {
            //wParam is unused
            MINMAXINFO* minmaxInfo = (MINMAXINFO*)lParam;

            break;
        }
        case WM_SETCURSOR:
        {
            const HWND windowsHandle = (HWND)wParam;
            const WORD hitTestResult = LOWORD(lParam);
            const WORD sourceMessage = HIWORD(lParam);

            SetCursor(NULL);

            return true; // prevent further processing
        }
        default:
            break;
    }


    bool letWindowsHandleEvent = true;

  

    BF::Window** windowAdressReference = BF::Window::_windowLookup.GetValue(windowsID);
    const bool isRegistered = windowAdressReference;
    Window* windowADD = new Window();
    BF::Window& window = *windowADD;// **windowAdressReference;

    switch(eventID)
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

 
        case WM_CLOSE:
        {
            InvokeEvent(window.WindowClosingCallBack, letWindowsHandleEvent);

            if(letWindowsHandleEvent)
            {
                const LRESULT result = DefWindowProc(windowsID, WM_CLOSE, wParam, lParam);

                InvokeEvent(window.WindowClosedCallBack);

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

            switch(inputCode)
            {
                case RIM_INPUT: // Input occurred while the application was in the foreground.
                {
                    RAWINPUT rawInput{ 0 };
                    UINT rawInputSize = sizeof(RAWINPUT); // Can't be 'const' !

                    const UINT result = GetRawInputData(handle, uiCommand, &rawInput, &rawInputSize, sizeof(RAWINPUTHEADER));
                    const bool sucessful = result != -1;

                    if(sucessful)
                    {
#if UseRawMouseData
                        if(rawInput.header.dwType == RIM_TYPEMOUSE)
                        {
                            const LONG mouseX = rawInput.data.mouse.lLastX;
                            const LONG mouseY = rawInput.data.mouse.lLastY;

                            InvokeEvent(window.MouseMoveCallBack, mouseX, mouseY);

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

            InvokeEvent(window.WindowSizeChangedCallBack, width, height);

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
            InvokeEvent(window.MouseClickCallBack, MouseButton::Left, ButtonState::Down);
            break;
        }
        case WM_LBUTTONUP:
        {
            InvokeEvent(window.MouseClickCallBack, MouseButton::Left, ButtonState::Release);
            break;
        }
        case WM_LBUTTONDBLCLK:
        {
            InvokeEvent(window.MouseClickDoubleCallBack, MouseButton::Left);
            break;
        }
        case WM_RBUTTONDOWN:
        {
            InvokeEvent(window.MouseClickCallBack, MouseButton::Right, ButtonState::Down);
            break;
        }
        case WM_RBUTTONUP:
        {
            InvokeEvent(window.MouseClickCallBack, MouseButton::Right, ButtonState::Release);
            break;
        }
        case WM_RBUTTONDBLCLK:
        {
            InvokeEvent(window.MouseClickDoubleCallBack, MouseButton::Right);
            break;
        }
        case WM_MBUTTONDOWN:
        {
            InvokeEvent(window.MouseClickCallBack, MouseButton::Middle, ButtonState::Down);
            break;
        }
        case WM_MBUTTONUP:
        {
            InvokeEvent(window.MouseClickCallBack, MouseButton::Middle, ButtonState::Release);
            break;
        }
        case WM_MBUTTONDBLCLK:
        {
            InvokeEvent(window.MouseClickDoubleCallBack, MouseButton::Middle);
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

            switch(eventID)
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
            buttonInfo.Repeat = (characterInfo & 0b00000000000000001111111111111111); // Die Wiederholungsanzahl für die aktuelle Meldung.Der Wert gibt an, wie oft die Tastatureingabe automatisch angezeigt wird, wenn der Benutzer den Schlüssel hält.Die Wiederholungsanzahl ist immer 1 für eine WM _ KEYUP - Nachricht.
            buttonInfo.ScanCode = (characterInfo & 0b00000000111111110000000000000000) >> 16; // Der Scancode.Der Wert hängt vom OEM ab.
            buttonInfo.SpecialKey = (characterInfo & 0b00000001000000000000000000000000) >> 24; // Gibt an, ob es sich bei der Taste um eine erweiterte Taste handelt, z.B.die rechte ALT - und STRG - Taste, die auf einer erweiterten Tastatur mit 101 oder 102 Tasten angezeigt werden.Der Wert ist 1, wenn es sich um einen erweiterten Schlüssel handelt.andernfalls ist es 0.
            //buttonInfo.ReservedDontUse = (characterInfo & 0b00011110000000000000000000000000) >> 25; //	Reserviert; nicht verwenden.
            buttonInfo.KontextCode = (characterInfo & 0b00100000000000000000000000000000) >> 29; // Der Kontextcode.Der Wert ist für eine WM _ KEYUP - Nachricht immer 0.
            buttonInfo.PreState = (characterInfo & 0b01000000000000000000000000000000) >> 30; // Der vorherige Schlüsselzustand.Der Wert ist immer 1 für eine WM _ KEYUP - Nachricht.
            buttonInfo.GapState = (characterInfo & 0b10000000000000000000000000000000) >> 31; // Der Übergangszustand.Der Wert ist immer 1 für eine WM _ KEYUP - Nachricht.

            InvokeEvent(window.KeyBoardKeyCallBack, buttonInfo);

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

            switch(eventID)
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
                    if(dbh && dbh->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
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
                    if(dbh && dbh->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
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

    if(letWindowsHandleEvent)
    {
     
    }

    return NULL;
}
#endif

BF::Window::Window()
{
    ID = 0;
    MessageThreadID = 0;
    IsRunning = 0;
    OpenGLConext = 0;

    X = DefautPositionX;
    Y = DefautPositionY;
    Width = 0;
    Height = 0;

    Title[0] = '\0';

#if defined(OSUnix)
    DisplayCurrent = nullptr;
    WindowRoot = 0;
#elif defined(OSWindows)
    HandleDeviceContext = 0;
    CursorID = 0;
#endif

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

ThreadFunctionReturnType BF::Window::WindowCreateThread(void* windowAdress)
{
    if(!windowAdress)
    {
        return ThreadFunctionReturnValue;
    }

    _currentWindow = (Window*)windowAdress;

    BF::Window& window = *_currentWindow;

#if defined(OSUnix)
    Display* display = XOpenDisplay(nullptr);   // Create Window

    {
        const bool successful = display != nullptr;

        if(!successful)
        {
            return ThreadFunctionReturnValue; // printf("\n\tcannot connect to X server\n\n");
        }

        window.DisplayCurrent = display;
    }

    // Make windows root
    XID windowRoot = DefaultRootWindow(display);

    int attributeList[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

    XVisualInfo* visualInfo = glXChooseVisual(display, 0, attributeList);

    {
        const bool successful = visualInfo != nullptr;

        if(!successful)
        {
            return ThreadFunctionReturnValue; // no appropriate visual found
        }
    }

    printf("\n\tvisual %p selected\n", (void*)visualInfo->visualid); /* %p creates hexadecimal output like in glxinfo */


    // Create colormapping
    Colormap colormap = XCreateColormap(display, windowRoot, visualInfo->visual, AllocNone);

    XSetWindowAttributes setWindowAttributes;
    //setWindowAttributes.cursor = ;
    setWindowAttributes.colormap = colormap;
    setWindowAttributes.event_mask =
        KeyReleaseMask |
        ButtonPressMask |
        ButtonReleaseMask |
        EnterWindowMask |
        LeaveWindowMask |
        PointerMotionMask |
        PointerMotionHintMask |
        Button1MotionMask |
        Button2MotionMask |
        Button3MotionMask |
        Button4MotionMask |
        Button5MotionMask |
        ButtonMotionMask |
        KeymapStateMask |
        ExposureMask |
        VisibilityChangeMask |
        StructureNotifyMask |
        ResizeRedirectMask |
        SubstructureNotifyMask |
        SubstructureRedirectMask |
        FocusChangeMask |
        PropertyChangeMask |
        ColormapChangeMask |
        OwnerGrabButtonMask;


    int x = window.X;
    int y = window.Y;
    int width = window.Width;
    int height = window.Height;
    int borderWidth = 0;

    XID windowID = XCreateWindow
    (
        display,
        windowRoot,
        x,
        y,
        width,
        height,
        borderWidth,
        visualInfo->depth,
        InputOutput,
        visualInfo->visual,
        CWColormap | CWEventMask,
        &setWindowAttributes
    );
    window.ID = windowID;

    char windowTitle[256];

    Text::Copy(windowTitle, window.Title, 256);

    XMapWindow(display, windowID);
    XStoreName(display, windowID, windowTitle);

    GLXContext glContext = glXCreateContext(display, visualInfo, NULL, GL_TRUE);
    glXMakeCurrent(display, windowID, glContext);

    window.OpenGLConext = glContext;

#elif defined(OSWindows)
    DWORD windowStyle = WS_EX_APPWINDOW;
    DWORD dwStyle = WS_VISIBLE | WS_OVERLAPPEDWINDOW;
    HWND hWndParent = nullptr;
    HMENU hMenu = nullptr;
    HINSTANCE hInstance = GetModuleHandle(NULL);
    void* lpParam = 0;
    const wchar_t* lpClassName = L"BFE::Window::AsyncThread";


    const HCURSOR cursorID = LoadCursor(NULL, IDC_PERSON);
    window.CursorID = cursorID;

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

    WindowID windowID = CreateWindowExW
    (
        windowStyle,
        lpClassName,
        window.Title,
        dwStyle,
        window.X,
        window.Y,
        window.Width,
        window.Height,
        hWndParent,
        hMenu,
        hInstance,
        lpParam
    );

    {
        const bool windowCreationSucessfl = windowID != nullptr;

        if(!windowCreationSucessfl)
        {
            DWORD error = GetLastError();
            wchar_t errorBuffer[1024];
            wsprintf(errorBuffer, L"Error creating window. Error code, decimal %d, hexadecimal %X.", error, error);
            MessageBox(NULL, errorBuffer, L"Error", MB_ICONHAND);
        }

        window.ID = windowID;
    }
  
    // Create OpenGL Context
    {
        const HDC windowHandleToDeviceContext = GetDC(windowID);  

        window.HandleDeviceContext = windowHandleToDeviceContext;

        const PIXELFORMATDESCRIPTOR pfd =
        {
            sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
            PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
            32,                   // Colordepth of the framebuffer.
            0, 0, 0, 0, 0, 0,
            0,
            0,
            0,
            0, 0, 0, 0,
            24,                   // Number of bits for the depthbuffer
            8,                    // Number of bits for the stencilbuffer
            0,                    // Number of Aux buffers in the framebuffer.
            PFD_MAIN_PLANE,
            0,
            0, 0, 0
        };

        int letWindowsChooseThisPixelFormat = ChoosePixelFormat(windowHandleToDeviceContext, &pfd);
        bool sucessul = SetPixelFormat(windowHandleToDeviceContext, letWindowsChooseThisPixelFormat, &pfd);
          
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

        const bool result = RegisterRawInputDevices(&rid, 1, sizeof(RAWINPUTDEVICE));

        // RegisterRawInputDevices should not be used from a library, as it may interfere with any raw input processing logic already present in applications that load it.
    }

    window.OpenGLConext = wglCreateContext(window.HandleDeviceContext);

#endif

    window.FrameBufferContextRegister();

    {
        const unsigned int result = glewInit(); // Initialise OpenGL enviroment

        switch(result)
        {
            case GLEW_OK: // No Error, do nothing
                break;

            case GLEW_ERROR_NO_GL_VERSION:
                return 1;

            case GLEW_ERROR_GL_VERSION_10_ONLY:
                return 2;

            case GLEW_ERROR_GLX_VERSION_11_ONLY:
                return 3;

            case GLEW_ERROR_NO_GLX_DISPLAY:
                return 4;

            default:
                return 5;
        }
    }

    if(true)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

    if(true) // X-RAY
    {
        glEnable(GL_DEPTH_TEST);
    }

    if(true)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_COLOR, GL_DST_COLOR);

         //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
         //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
    }

    _windowLookup.Add(windowID, &window); 

    InvokeEvent(window.WindowCreatedCallBack, window);

    window.FrameBufferContextRelease();

    window.IsRunning = true;

    while(window.IsRunning)
    {
#if defined(OSUnix)  
        XEvent windowEvent;

        XNextEvent(display, &windowEvent);

        OnWindowEvent(windowEvent);
#elif defined(OSWindows)
        MSG message{ 0 };
        const bool peekResult = PeekMessageW(&message, nullptr, 0, 0, PM_NOREMOVE);

        if(peekResult)
        {
            const bool messageResult = GetMessageW(&message, nullptr, 0, 0);

            if(messageResult)
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
#endif
    }

    return ThreadFunctionReturnValue;
}

ThreadFunctionReturnType BF::Window::WindowEventListenThread(void* windowAdress)
{
    BF::Window& window = *((Window*)windowAdress);



    return ThreadFunctionReturnValue;
}

void BF::Window::Create(bool async)
{
    Create(DefautPositionX, DefautPositionY, "Unnamed window", async);
}

void BF::Window::Create(const unsigned int width, const unsigned int height, const char* title, bool async)
{
    Width = width;
    Height = height;

    Text::Copy(Title, title, 256);

    if(async)
    {
        const ThreadID id = Thread::Run(WindowCreateThread, this);

        MessageThreadID = id;

        while(ID == 0)
        {

        }
    }
    else
    {
        WindowCreateThread(this);
    }
}

void BF::Window::Destroy()
{
#if defined(OSUnix)
    glXMakeCurrent(DisplayCurrent, None, NULL);
    //    glXDestroyContext(DisplayCurrent, OpenGLConextID);
    XDestroyWindow(DisplayCurrent, ID);
    XCloseDisplay(DisplayCurrent);
#elif defined(OSWindows)
    CloseWindow(ID);
#endif
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
#if defined(OSUnix)
#elif defined(OSWindows)
    const unsigned int cursorID = ToCursorIcon(cursorIcon);
    const bool validCursorIcon = cursorID != -1;

    if(!validCursorIcon)
    {
        return;
    }

    HANDLE handle = LoadImageW(NULL, MAKEINTRESOURCEW(cursorID), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
#endif
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
#if defined(OSUnix)
#elif defined(OSWindows)
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


    switch(cursorMode)
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
#endif
}

// 0 = OK
// 1 = missing GL version
// 2 = Need at least OpenGL 1.1
// 3 = Need at least GLX 1.2 
// 4 = Need GLX display for GLX support
// 5 = unkown cause?
int BF::Window::FrameBufferInitialize()
{
#if defined(OSUnix)

#elif defined(OSWindows)
    HGLRC glConext = wglCreateContext(HandleDeviceContext);
#endif   

    OpenGLConext = glConext;

    FrameBufferContextRegister(); 

    {
        const unsigned int result = glewInit(); // Initialise OpenGL enviroment

        switch(result)
        {
            case GLEW_OK: // No Error, do nothing
                break;
     
            case GLEW_ERROR_NO_GL_VERSION:
                return 1;

            case GLEW_ERROR_GL_VERSION_10_ONLY:
                return 2;

            case GLEW_ERROR_GLX_VERSION_11_ONLY:
                return 3;

            case GLEW_ERROR_NO_GLX_DISPLAY:
                return 4;

            default:
                return 5;
        }
    }

    //glDebugMessageCallback(BF::BitFireEngine::ErrorMessageCallback, 0);
    //glEnable(GL_DEBUG_OUTPUT);    

    printf
    (
        "+------------------------------------------------------+\n"
        "| Graphics Card - Information                          |\n"
        "+------------------------------------------------------+\n"
        "| Vendor           : %-33s |\n"
        "| Model            : %-33s |\n"
        "| OpenGL Version   : %-33s |\n"
        "| Texture Slots    : %-33u |\n"
        "| Maximal Textures : %-33u |\n"
        "+------------------------------------------------------+\n",
        OpenGL::GPUVendorName(),
        OpenGL::GPUModel(),
        OpenGL::GLSLVersionPrimary(),
        OpenGL::TextureMaxSlots(),
        OpenGL::TextureMaxLoaded()
    );

    if(true)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

    if(true) // X-RAY
    {
        glEnable(GL_DEPTH_TEST);
    }

    if(true)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_COLOR, GL_DST_COLOR);

         //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
         //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
    }
}

void BF::Window::FrameBufferSwap()
{
    glFlush();  // Flush drawing command buffer to make drawing happen as soon as possible.

#if defined(OSUnix)
    glXSwapBuffers(DisplayCurrent, ID);
#elif defined(OSWindows)
    SwapBuffers(HandleDeviceContext);
    //wglMakeCurrent(0, 0);
#endif
}

bool BF::Window::FrameBufferContextRegister()
{
#if defined(OSUnix)
    const bool sucessfl = glXMakeCurrent(DisplayCurrent, ID, OpenGLConext);
#elif defined(OSWindows)
    const bool sucessfl = wglMakeCurrent(HandleDeviceContext, OpenGLConext);
#endif

    return sucessfl;
}

void BF::Window::FrameBufferContextRelease()
{
#if defined(OSUnix)
    glXMakeCurrent(0, 0, OpenGLConext);
#elif defined(OSWindows)
    wglMakeCurrent(0, 0);
#endif
}
