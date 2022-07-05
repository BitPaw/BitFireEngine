#include "Window.h"


#include <GL/glew.h>
#include <GL/gl.h>

#include <stdio.h>

#if defined(OSUnix)

#include <X11/cursorfont.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/XInput2.h>
#include <X11/Xmd.h>

#define DefautPositionX 00000000000000
#define DefautPositionY 00000000000000

#define MouseButtonLeft 1
#define MouseButtonMiddle 2
#define MouseButtonRight 3
#define MouseScrollUp 4
#define MouseScrollDown 5

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
#include <File/File.h>
#include <Graphic/OpenGL/OpenGL.h>
#include <Controller/ControllerData.h>
#include <Controller/ControllerSystem.h>
#include <Hardware/Memory/Memory.h>
#include <Event/Event.hpp>

BF::Dictionary<WindowID, BF::Window*> BF::Window::_windowLookup;

#if defined(OSUnix)

void BF::Window::OnWindowEvent(BF::Window& window, const XEvent& event)
{
    switch(event.type)
    {
        case KeyPress:
        case KeyRelease:
        {
            const XKeyEvent& keyEvent = event.xkey;
            const unsigned int keyCode = keyEvent.keycode;
            const bool release = event.type == KeyRelease;
            const KeySym keySym = XKeycodeToKeysym(window.DisplayCurrent, keyCode, 0);
            const char* keyName = XKeysymToString(keySym);

            KeyBoardKey keyBoardKey = BF::ConvertKeyBoardKey(keySym);

            KeyBoardKeyInfo keyBoardKeyInfo;

            keyBoardKeyInfo.Key = keyBoardKey;
            keyBoardKeyInfo.Mode = release ? ButtonState::Release : ButtonState::Down;
            keyBoardKeyInfo.Repeat = 0;
            keyBoardKeyInfo.ScanCode = keySym;
            keyBoardKeyInfo.SpecialKey = 0;
            keyBoardKeyInfo.KontextCode = 0;
            keyBoardKeyInfo.PreState = 0;
            keyBoardKeyInfo.GapState = 0;

            InvokeEvent(window.KeyBoardKeyCallBack, keyBoardKeyInfo);

            if(release)
            {
                printf("[Event] Key-Release %2i %2i %s\n",keyCode,keySym, keyName);
            }
            else
            {
                printf("[Event] Key-Press %2i %2i %s\n", keyCode, keySym, keyName);
            }

            break;
        }
        case ButtonRelease:
        case ButtonPress:
        {
            const XButtonEvent& buttonEvent = event.xbutton;
            const unsigned int buttonID = buttonEvent.button;
            const ButtonState buttonState = event.type == ButtonPress ? ButtonState::Down :  ButtonState::Release;
            MouseButton mouseButton = MouseButton::Invalid;

            switch(buttonID)
            {
                case MouseButtonLeft:
                    InvokeEvent(window.MouseClickCallBack, MouseButton::Left, buttonState);
                    break;

                case MouseButtonMiddle:
                    InvokeEvent(window.MouseClickCallBack, MouseButton::Middle, buttonState);
                    break;

                case MouseButtonRight:
                    InvokeEvent(window.MouseClickCallBack, MouseButton::Right, buttonState);
                    break;

                case MouseScrollUp:
                    InvokeEvent(window.MouseScrollCallBack, MouseScrollDirection::Up);
                    break;

                case MouseScrollDown:
                    InvokeEvent(window.MouseScrollCallBack, MouseScrollDirection::Down);
                    break;

            }
        }
        case MotionNotify:
        {
            printf("[Event] MotionNotify \n");

            break;
        }
        case EnterNotify:
        {
            InvokeEvent(window.MouseEnterCallBack);
            break;
        }
        case LeaveNotify:
        {
            InvokeEvent(window.MouseLeaveCallBack);
            break;
        }
        case FocusIn:
        {
            InvokeEvent(window.FocusEnterCallBack);
            break;
        }
        case FocusOut:
        {
            InvokeEvent(window.FocusLeaveCallBack);
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

           // glViewport(0,0, width, height);

            InvokeEvent(window.WindowSizeChangedCallBack, width, height);

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
            XGenericEventCookie cookie = event.xcookie; // Make Copy

            const int result = XGetEventData(window.DisplayCurrent, &cookie);
            const bool sucessful = result != 0 && cookie.data;

            if (sucessful)
            {
                switch(cookie.evtype)
                {
                    case XI_RawMotion:
                    {
                        XIRawEvent* re = (XIRawEvent*)cookie.data;

                        if (re->valuators.mask_len)
                        {
                            const double* values = re->raw_values;
                            const bool isX = XIMaskIsSet(re->valuators.mask, 0);
                            const bool isY = XIMaskIsSet(re->valuators.mask, 1);
                            double xpos = 0;
                            double ypos = 0;

                            if (isX)
                            {
                                xpos += *values;
                                ++values;
                            }

                            if(isY)
                            {
                                ypos += *values;
                            }


                            window.MouseDeltaX = window.MousePositionX - xpos;
                            window.MouseDeltaY = window.MousePositionY - ypos;

                            window.MousePositionX = xpos;
                            window.MousePositionY = ypos;

                            printf("[Event] RawMotion %5.4lf %5.4lf\n", xpos, ypos);

                            InvokeEvent(window.MouseMoveCallBack, window.MousePositionX, window.MousePositionY, xpos, ypos);

                            //printf("[Event] RawMotion %5.4lf %5.4lf\n", window.MouseDeltaX, window.MouseDeltaY);

                            //InvokeEvent(window.MouseMoveCallBack, window.MousePositionX, window.MousePositionY, window.MouseDeltaX, window.MouseDeltaY);
                        }
                    }
                }
            }
            else
            {
                printf("[Event] GenericEvent %i\n", cookie.evtype);
            }

            XFreeEventData(window.DisplayCurrent, &cookie);

            break;
        }
        default:
        {
            printf("[Event] default: unkown event \n");

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
        case WM_IME_ENDCOMPOSITION: return WindowEventType::IME_ENDCOMPOSITION;
        case WM_IME_COMPOSITION: return WindowEventType::IME_COMPOSITION;
            //case WM_IME_KEYLAST: return WindowEventType::IME_KEYLAST;
        case WM_INITDIALOG: return WindowEventType::INITDIALOG;
        case WM_COMMAND: return WindowEventType::COMMAND;
        case WM_SYSCOMMAND: return WindowEventType::SYSCOMMAND;
        case WM_TIMER: return WindowEventType::TIMER;
        case WM_HSCROLL: return WindowEventType::HSCROLL;
        case WM_VSCROLL: return WindowEventType::VSCROLL;
        case WM_INITMENU: return WindowEventType::INITMENU;
        case WM_INITMENUPOPUP: return WindowEventType::INITMENUPOPUP;
        case WM_GESTURE: return WindowEventType::GESTURE;
        case WM_GESTURENOTIFY: return WindowEventType::GESTURENOTIFY;
        case WM_MENUSELECT: return WindowEventType::MENUSELECT;
        case WM_MENUCHAR: return WindowEventType::MENUCHAR;
        case WM_ENTERIDLE: return WindowEventType::ENTERIDLE;
        case WM_MENURBUTTONUP: return WindowEventType::MENURBUTTONUP;
        case WM_MENUDRAG: return WindowEventType::MENUDRAG;
        case WM_MENUGETOBJECT: return WindowEventType::MENUGETOBJECT;
        case WM_UNINITMENUPOPUP: return WindowEventType::UNINITMENUPOPUP;
        case WM_MENUCOMMAND: return WindowEventType::MENUCOMMAND;
        case WM_CHANGEUISTATE: return WindowEventType::CHANGEUISTATE;
        case WM_UPDATEUISTATE: return WindowEventType::UPDATEUISTATE;
        case WM_QUERYUISTATE: return WindowEventType::QUERYUISTATE;
        case WM_CTLCOLORMSGBOX: return WindowEventType::CTLCOLORMSGBOX;
        case WM_CTLCOLOREDIT: return WindowEventType::CTLCOLOREDIT;
        case WM_CTLCOLORLISTBOX: return WindowEventType::CTLCOLORLISTBOX;
        case WM_CTLCOLORBTN: return WindowEventType::CTLCOLORBTN;
        case WM_CTLCOLORDLG: return WindowEventType::CTLCOLORDLG;
        case WM_CTLCOLORSCROLLBAR: return WindowEventType::CTLCOLORSCROLLBAR;

        case WM_CTLCOLORSTATIC: return WindowEventType::CTLCOLORSTATIC;
        case MN_GETHMENU: return WindowEventType::GETHMENU;
            //case WM_MOUSEFIRST: return WindowEventType::MOUSEFIRST;
        case WM_MOUSEMOVE: return WindowEventType::MOUSEMOVE;

        case WM_LBUTTONDOWN: return WindowEventType::LBUTTONDOWN;
        case WM_LBUTTONUP: return WindowEventType::LBUTTONUP;
        case WM_LBUTTONDBLCLK: return WindowEventType::LBUTTONDBLCLK;
        case WM_RBUTTONDOWN: return WindowEventType::RBUTTONDOWN;
        case WM_RBUTTONUP: return WindowEventType::RBUTTONUP;

        case WM_RBUTTONDBLCLK: return WindowEventType::RBUTTONDBLCLK;
        case WM_MBUTTONDOWN: return WindowEventType::MBUTTONDOWN;
        case WM_MBUTTONUP: return WindowEventType::MBUTTONUP;
        case WM_MBUTTONDBLCLK: return WindowEventType::MBUTTONDBLCLK;
        case WM_MOUSEWHEEL: return WindowEventType::MOUSEWHEEL;

        case WM_XBUTTONDOWN: return WindowEventType::XBUTTONDOWN;
        case WM_XBUTTONUP: return WindowEventType::XBUTTONUP;
        case WM_XBUTTONDBLCLK: return WindowEventType::XBUTTONDBLCLK;
        case WM_MOUSEHWHEEL: return WindowEventType::MOUSEHWHEEL;
            //case WM_MOUSELAST: return WindowEventType::MOUSELAST;
        case WM_PARENTNOTIFY: return WindowEventType::PARENTNOTIFY;
        case WM_ENTERMENULOOP: return WindowEventType::ENTERMENULOOP;
        case WM_EXITMENULOOP: return WindowEventType::EXITMENULOOP;
        case WM_NEXTMENU: return WindowEventType::NEXTMENU;
        case WM_SIZING: return WindowEventType::SIZING;
        case WM_CAPTURECHANGED: return WindowEventType::CAPTURECHANGED;
        case WM_MOVING: return WindowEventType::MOVING;
        case WM_POWERBROADCAST: return WindowEventType::POWERBROADCAST;
        case WM_DEVICECHANGE: return WindowEventType::DEVICECHANGE;
        case WM_MDICREATE: return WindowEventType::MDICREATE;
        case WM_MDIDESTROY: return WindowEventType::MDIDESTROY;
        case WM_MDIACTIVATE: return WindowEventType::MDIACTIVATE;
        case WM_MDIRESTORE: return WindowEventType::MDIRESTORE;
        case WM_MDINEXT: return WindowEventType::MDINEXT;

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
        case WM_NCPOINTERUPDATE: return WindowEventType::NCPOINTERUPDATE;
        case WM_NCPOINTERDOWN: return WindowEventType::NCPOINTERDOWN;
        case WM_NCPOINTERUP: return WindowEventType::NCPOINTERUP;
        case WM_POINTERUPDATE: return WindowEventType::POINTERUPDATE;
        case WM_POINTERDOWN: return WindowEventType::POINTERDOWN;
        case WM_POINTERUP: return WindowEventType::POINTERUP;
        case WM_POINTERENTER: return WindowEventType::POINTERENTER;
        case WM_POINTERLEAVE: return WindowEventType::POINTERLEAVE;
        case WM_POINTERACTIVATE: return WindowEventType::POINTERACTIVATE;
        case WM_POINTERCAPTURECHANGED: return WindowEventType::POINTERCAPTURECHANGED;
        case WM_TOUCHHITTESTING: return WindowEventType::TOUCHHITTESTING;
        case WM_POINTERWHEEL: return WindowEventType::POINTERWHEEL;
        case WM_POINTERHWHEEL: return WindowEventType::POINTERHWHEEL;
        case WM_POINTERROUTEDTO: return WindowEventType::POINTERROUTEDTO;
        case WM_POINTERROUTEDAWAY: return WindowEventType::POINTERROUTEDAWAY;
        case WM_POINTERROUTEDRELEASED: return WindowEventType::POINTERROUTEDRELEASED;
        case WM_IME_SETCONTEXT: return WindowEventType::IME_SETCONTEXT;
        case WM_IME_NOTIFY: return WindowEventType::IME_NOTIFY;
        case WM_IME_CONTROL: return WindowEventType::IME_CONTROL;
        case WM_IME_COMPOSITIONFULL: return WindowEventType::IME_COMPOSITIONFULL;
        case WM_IME_SELECT: return WindowEventType::IME_SELECT;
        case WM_IME_CHAR: return WindowEventType::IME_CHAR;
        case WM_IME_REQUEST: return WindowEventType::IME_REQUEST;
        case WM_IME_KEYDOWN: return WindowEventType::IME_KEYDOWN;
        case WM_IME_KEYUP: return WindowEventType::IME_KEYUP;
        case WM_MOUSEHOVER: return WindowEventType::MOUSEHOVER;
        case WM_MOUSELEAVE: return WindowEventType::MOUSELEAVE;
        case WM_NCMOUSEHOVER: return WindowEventType::NCMOUSEHOVER;
        case WM_NCMOUSELEAVE: return WindowEventType::NCMOUSELEAVE;
        case WM_WTSSESSION_CHANGE: return WindowEventType::WTSSESSION_CHANGE;
        case WM_TABLET_FIRST: return WindowEventType::TABLET_FIRST;
        case WM_TABLET_LAST: return WindowEventType::TABLET_LAST;
        case WM_DPICHANGED: return WindowEventType::DPICHANGED;
        case WM_DPICHANGED_BEFOREPARENT: return WindowEventType::DPICHANGED_BEFOREPARENT;
        case WM_DPICHANGED_AFTERPARENT: return WindowEventType::DPICHANGED_AFTERPARENT;
        case WM_GETDPISCALEDSIZE: return WindowEventType::GETDPISCALEDSIZE;
        case WM_CUT: return WindowEventType::CUT;
        case WM_COPY: return WindowEventType::COPY;
        case WM_PASTE: return WindowEventType::PASTE;
        case WM_CLEAR: return WindowEventType::CLEAR;
        case WM_UNDO: return WindowEventType::UNDO;
        case WM_RENDERFORMAT: return WindowEventType::RENDERFORMAT;
        case WM_RENDERALLFORMATS: return WindowEventType::RENDERALLFORMATS;
        case WM_DESTROYCLIPBOARD: return WindowEventType::DESTROYCLIPBOARD;
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
    BF::Window** windowAdressReference = _windowLookup.Find(windowsID);

    if(!windowAdressReference)
    {
        return DefWindowProc(windowsID, eventID, wParam, lParam);
    }

    BF::Window& window = **windowAdressReference;

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
        {
            const DWORD width = LOWORD(lParam);
            const DWORD height = HIWORD(lParam);

            window.Width = width;
            window.Height = height;

            window.HasSizeChanged = true;

            InvokeEvent(window.WindowSizeChangedCallBack, width, height);

            break;
        }
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
        {
            bool closeWindow = true;

            InvokeEvent(window.WindowClosingCallBack, closeWindow);

            if(closeWindow)
            {
                const LRESULT result = DefWindowProc(windowsID, WM_CLOSE, wParam, lParam);

                InvokeEvent(window.WindowClosedCallBack);

                return result;
            }

            break;
        }
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
        {
            const HWND windowsHandle = (HWND)wParam;
            const WORD hitTestResult = LOWORD(lParam);
            const WORD sourceMessage = HIWORD(lParam);
            const bool showCursor = !(window.CursorModeCurrent == CursorMode::Invisible || window.CursorModeCurrent == CursorMode::LockAndHide);

            if(showCursor)
            {
                while(ShowCursor(true) < 0);
            }
            else
            {
                while(ShowCursor(false) >= 0);
            }

            return true; // prevent further processing
        }
        case WindowEventType::MouseActivate:
            break;
        case WindowEventType::ChildActivate:
            break;
        case WindowEventType::QueueSync:
            break;
        case WindowEventType::SizeChange:
        {
            //wParam is unused
            const MINMAXINFO* minmaxInfo = (MINMAXINFO*)lParam;
            const auto width = minmaxInfo->ptMaxSize.x;
            const auto height = minmaxInfo->ptMaxSize.y;

            // Not useable for resize event. Its not what it seems

            break;
        }
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
                            const bool interactable = window.Interactable();

                            if(interactable)
                            {
                                InvokeEvent(window.MouseMoveCallBack, window.MousePositionX, window.MousePositionY ,mouseX, mouseY);
                            }

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

        case WindowEventType::KEYFIRST:
            break;

        case WindowEventType::KEYDOWN:
        case WindowEventType::KEYUP:
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
            InvokeEvent(window.MouseClickCallBack, MouseButton::Left, ButtonState::Down);
            break;

        case WindowEventType::LBUTTONUP:
            InvokeEvent(window.MouseClickCallBack, MouseButton::Left, ButtonState::Release);
            break;

        case WindowEventType::LBUTTONDBLCLK:
            InvokeEvent(window.MouseClickDoubleCallBack, MouseButton::Left);
            break;

        case WindowEventType::RBUTTONDOWN:
            InvokeEvent(window.MouseClickCallBack, MouseButton::Right, ButtonState::Down);
            break;

        case WindowEventType::RBUTTONUP:
            InvokeEvent(window.MouseClickCallBack, MouseButton::Right, ButtonState::Release);
            break;

        case WindowEventType::RBUTTONDBLCLK:
            InvokeEvent(window.MouseClickDoubleCallBack, MouseButton::Right);
            break;

        case WindowEventType::MBUTTONDOWN:
            InvokeEvent(window.MouseClickCallBack, MouseButton::Middle, ButtonState::Down);
            break;

        case WindowEventType::MBUTTONUP:
            InvokeEvent(window.MouseClickCallBack, MouseButton::Middle, ButtonState::Release);
            break;

        case WindowEventType::MBUTTONDBLCLK:
            InvokeEvent(window.MouseClickDoubleCallBack, MouseButton::Middle);
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
}
#endif


    /*

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
    }*/


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

    HasSizeChanged = true;

    CursorModeCurrent = CursorMode::Show;

    MouseScrollCallBack = 0;
    MouseClickCallBack = 0;
    MouseClickDoubleCallBack = 0;
    MouseMoveCallBack = 0;
    KeyBoardKeyCallBack = 0;
    MouseEnterCallBack = 0;
    MouseLeaveCallBack = 0;
    FocusEnterCallBack = 0;
    FocusLeaveCallBack = 0;
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

    BF::Window& window = *((Window*)windowAdress);

    window.IsRunning = false;

#if defined(OSUnix)
    XInitThreads();

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





    // Create colormapping
    Colormap colormap = XCreateColormap(display, windowRoot, visualInfo->visual, AllocNone);

    XSetWindowAttributes setWindowAttributes;
    //setWindowAttributes.cursor = ;
    setWindowAttributes.colormap = colormap;
    setWindowAttributes.event_mask =
        KeyPressMask |
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
        OwnerGrabButtonMask |
       // XI_RawMotion |
        0;

    int borderWidth = 0;

    XID windowID = XCreateWindow
    (
        display,
        windowRoot,
        window.X,
        window.Y,
        window.Width,
        window.Height,
        borderWidth,
        visualInfo->depth,
        InputOutput,
        visualInfo->visual,
        CWColormap | CWEventMask,
        &setWindowAttributes
    );
    window.ID = windowID;

    char windowTitle[256];

    Text::Copy(windowTitle, 256, window.Title, 256);

    XMapWindow(display, windowID);
    XStoreName(display, windowID, windowTitle);

    GLXContext glContext = glXCreateContext(display, visualInfo, NULL, GL_TRUE);

    window.OpenGLConext = glContext;

#if 0 // Grab means literally Drag%Drop grab. This is not mouse motion
    //bool   ret    = false;
    XID cursor = XCreateFontCursor(display, XC_crosshair);
    int    root   = DefaultRootWindow(display);

    const int grabResult = XGrabPointer
    (
        display,
        root,
        0,
        ButtonMotionMask,
        GrabModeAsync,
        GrabModeAsync,
        root,
        None,
        CurrentTime
    );
#endif


    // Raw mouse movement

    const int root = DefaultRootWindow(display);

    XIEventMask eventmask{0};
    const size_t maskLength = (XI_LASTEVENT + 7)/8;
    unsigned char mask[maskLength]{0};


    memset(mask, 0, maskLength);
    XISetMask(mask, XI_RawMotion);
    //XISetMask(mask, XI_RawButtonPress);
    //XISetMask(mask, XI_RawKeyPress);

    eventmask.deviceid = XIAllMasterDevices;
    eventmask.mask_len = maskLength;
    eventmask.mask = mask;


    XISelectEvents(display, root, &eventmask, 1);
    XFlush(display);


#elif defined(OSWindows)
    DWORD windowStyle = WS_EX_APPWINDOW;
    DWORD dwStyle = WS_VISIBLE | WS_OVERLAPPEDWINDOW;
    HWND hWndParent = nullptr;
    HMENU hMenu = nullptr;
    HINSTANCE hInstance = GetModuleHandle(NULL);
    void* lpParam = 0;
    const wchar_t* lpClassName = L"BFE::Window::AsyncThread";

    const HCURSOR cursorID = LoadCursor(hInstance, IDC_WAIT);
    window.CursorID = cursorID;

    WNDCLASS wndclass{ 0 };
    wndclass.style = CS_OWNDC; //  CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = OnWindowEvent;
    wndclass.cbClsExtra = 0; // The number of extra bytes to allocate following the window-class structure.
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_HAND);
    wndclass.hCursor = window.CursorID;
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
        const int letWindowsChooseThisPixelFormat = ChoosePixelFormat(windowHandleToDeviceContext, &pfd);
        const bool sucessul = SetPixelFormat(windowHandleToDeviceContext, letWindowsChooseThisPixelFormat, &pfd);

        window.HandleDeviceContext = windowHandleToDeviceContext;
    }

    // Register input device
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

    // Create context
    window.FrameBufferContextRegister();

    {
        const unsigned int result = glewInit(); // Initialise OpenGL enviroment

        switch(result)
        {
            case GLEW_OK: // No Error, do nothing
                break;

            case GLEW_ERROR_NO_GL_VERSION:
                return (ThreadFunctionReturnType)1u;

            case GLEW_ERROR_GL_VERSION_10_ONLY:
                return (ThreadFunctionReturnType)2u;

            case GLEW_ERROR_GLX_VERSION_11_ONLY:
                return (ThreadFunctionReturnType)3u;

            case GLEW_ERROR_NO_GLX_DISPLAY:
                return (ThreadFunctionReturnType)4u;

            default:
                return (ThreadFunctionReturnType)5u;
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

    glClearColor(0.2, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    _windowLookup.Add(windowID, &window);

    InvokeEvent(window.WindowCreatedCallBack, window);

    window.FrameBufferContextRelease();

    window.IsRunning = true;

#if defined(OSUnix)
#if 0
    int numberOfDevices = 0;

    const XDeviceInfo* deviceInfoList = XListInputDevices(display, &numberOfDevices);

    for (int i = 0; i < numberOfDevices; ++i)
    {
        const XDeviceInfo& xDeviceInfo = deviceInfoList[i];

        printf
        (
            "[Device] ID:%i Name:%s Use:%i\n",
            xDeviceInfo.id,
            xDeviceInfo.name,
            xDeviceInfo.use
        );

        // XOpenDevice(display, i); // Cannot open mouse or keyboard??  invalid call

        // XEventClass eventList[8]={0,0,0,0,0,0,0,0};
       //  int listSize = xDeviceInfo.num_classes;

       //  int resultE = XSelectExtensionEvent(display, windowID, eventList, listSize);

        // printf("");
    }
#endif
#endif

    while(window.IsRunning)
    {
#if defined(OSUnix)
        XEvent windowEvent;

    /*
        Window root_return, child_return;
        int root_x_return, root_y_return;
        int win_x_return, win_y_return;
        unsigned int mask_return;
        /*
         * We need:
         *     child_return - the active window under the cursor
         *     win_{x,y}_return - pointer coordinate with respect to root window
         * /
        int retval = XQueryPointer
        (
            display,
            root_window,
            &root_return,
            &child_return,
            &root_x_return,
            &root_y_return,
            &win_x_return,
            &win_y_return,
            &mask_return
        );*/




        XLockDisplay(window.DisplayCurrent);

        XNextEvent(display, &windowEvent);

        XUnlockDisplay(window.DisplayCurrent);

        OnWindowEvent(window, windowEvent);

#if 0
  glClearColor(1.0, 1.0, 1.0, 1.0);
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 glBegin(GL_QUADS);
  glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
  glColor3f(0., 1., 0.); glVertex3f( .75, -.75, 0.);
  glColor3f(0., 0., 1.); glVertex3f( .75,  .75, 0.);
  glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
 glEnd();

 window.FrameBufferSwap();
#endif


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

void BF::Window::Create(bool async)
{
    Create(DefautPositionX, DefautPositionY, "Unnamed window", async);
}

void BF::Window::Create(const unsigned int width, const unsigned int height, const char* title, bool async)
{
    Width = width;
    Height = height;

    Text::Copy(title, PathMaxSize, Title, PathMaxSize);

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
            printf("[Cursor] Show\n");

            while(ShowCursor(true) < 0);

            const bool clipResult = ClipCursor(NULL);
            const HCURSOR cursorSet = SetCursor(CursorID);

            break;
        }
        case CursorMode::Lock:
        {
            printf("[Cursor] Lock\n");

            // Capture cursor
            {
                RECT clipRect;
                GetClientRect(ID, &clipRect);
                ClientToScreen(ID, (POINT*)&clipRect.left);
                ClientToScreen(ID, (POINT*)&clipRect.right);
                ClipCursor(&clipRect);
            }

            break;
        }
        case CursorMode::LockAndHide:
        {
            printf("[Cursor] Lock and hide\n");

            while(ShowCursor(false) >= 0);

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

                bool sucessClip = ClipCursor(&clipRect);
            }


            CURSORINFO cursorInfo{ 0 };
            cursorInfo.cbSize = sizeof(CURSORINFO);

            const bool sucessfulInfoGet = GetCursorInfo(&cursorInfo);

            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

            CONSOLE_CURSOR_INFO lpCursor;
            lpCursor.bVisible = false;
            lpCursor.dwSize = sizeof(CONSOLE_CURSOR_INFO);
            bool y = SetConsoleCursorInfo(console, &lpCursor);

            break;
        }
    }

    CursorModeCurrent = cursorMode;
#endif
}

void BF::Window::ScreenShotTake(Image image)
{
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int width = 0;
    unsigned int height = 0;

    Size(x, y, width, height);

    unsigned int size = width * height * 3;

    if(image.PixelDataSize != size)
    {
        Memory::Release(image.PixelData, size);
        image.PixelData = Memory::Reallocate<unsigned char>(image.PixelData, size);
        image.PixelDataSize = size;
    }

    image.Width = width;
    image.Height = height;
    image.Format = BF::ImageDataFormat::BGR;

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, image.PixelData);
}

bool BF::Window::FrameBufferSwap()
{
    glFlush();  // Flush drawing command buffer to make drawing happen as soon as possible.

#if defined(OSUnix)
    bool successful = true; // No feedback?
    glXSwapBuffers(DisplayCurrent, ID);
#elif defined(OSWindows)
    bool successful = SwapBuffers(HandleDeviceContext);
#endif

    return successful;
}

bool BF::Window::FrameBufferContextRegister()
{
    const size_t threadID = Thread::ThreadCurrentID();

#if defined(OSUnix)
    const bool successful = glXMakeCurrent(DisplayCurrent, ID, OpenGLConext);

    //printf("[%x][OpenGL] Make context %p %i %p\n", threadID, DisplayCurrent, ID, OpenGLConext);
#elif defined(OSWindows)
    const bool successful = wglMakeCurrent(HandleDeviceContext, OpenGLConext);

    //printf("[%x][OpenGL] Make context %p %p\n", threadID, HandleDeviceContext, OpenGLConext);
#endif

    return successful;
}

bool BF::Window::FrameBufferContextRelease()
{
    const size_t threadID = Thread::ThreadCurrentID();

    //printf("[%x][OpenGL] Remove context \n", threadID);

#if defined(OSUnix)
    const bool successful = glXMakeCurrent(0, ID, OpenGLConext);
#elif defined(OSWindows)
    const bool successful = wglMakeCurrent(0, 0);
#endif

    return successful;
}

bool BF::Window::Interactable()
{
    bool react = false;

    switch(CursorModeCurrent)
    {
        case CursorMode::Ignore:
        case CursorMode::Show:
            react = false;
            break;

        case CursorMode::Invisible:
        case CursorMode::Lock:
        case CursorMode::LockAndHide:
            react = true;
            break;
    }

    return react;
}
