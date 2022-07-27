#include "OSUI.h"

#if defined(OSUnix)
#elif defined(OSWindows)
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include <Memory/Memory.h>

void UIElementConstruct(const WindowID window, UIElementID* ID, UILayout* Layout, const wchar_t* className, const wchar_t* name)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    DWORD dwExStyle = 0;
    wchar_t* lpClassName = className;// Predefined class; Unicode assumed ;
    wchar_t* lpWindowName = name;
    HWND hWndParent = window;
    HMENU hMenu = 0; // No menu.
    HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(window, GWLP_HINSTANCE);
    LPVOID lpParam = NULL; // Pointer not needed.

    *ID = CreateWindowExW
    (
        dwExStyle,
        lpClassName,
        lpWindowName,
        Layout->Style,
        Layout->X,
        Layout->Y,
        Layout->Width,
        Layout->Height,
        hWndParent,
        hMenu,
        hInstance,
        lpParam
    );
#endif

    //printf("\n[UI] %ls create : %p\n", className, ID);
}

void ButtonConstruct(const WindowID window, OSButton* button, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
    MemorySet(button, sizeof(OSButton), 0);

#if defined(OSUnix)
#elif defined(OSWindows)
    button->Layout.Style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_USERBUTTON;
    button->Layout.X = x;
    button->Layout.Y = y;
    button->Layout.Width = width;
    button->Layout.Height = height;

    UIElementConstruct(window, &button->ID, &button->Layout, L"BUTTON", buttonText);
#endif
}

void ComboBoxConstruct(const WindowID window, OSComboBox* comboBox, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
    MemorySet(comboBox, sizeof(OSComboBox), 0);

#if defined(OSUnix)
#elif defined(OSWindows)

    comboBox->Layout.Style = WS_TABSTOP | WS_VISIBLE | WS_CHILD ;
    comboBox->Layout.X = x;
    comboBox->Layout.Y = y;
    comboBox->Layout.Width = width;
    comboBox->Layout.Height = height;

    UIElementConstruct(window, &comboBox->ID, &comboBox->Layout, L"COMBOBOX", buttonText);
#endif
}

void ListBoxConstruct(const WindowID window, OSListBox* listBox, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
    MemorySet(listBox, sizeof(OSListBox), 0);

#if defined(OSUnix)
#elif defined(OSWindows)

    listBox->Layout.Style = WS_TABSTOP | WS_VISIBLE | WS_CHILD ;
    listBox->Layout.X = x;
    listBox->Layout.Y = y;
    listBox->Layout.Width = width;
    listBox->Layout.Height = height;

    UIElementConstruct(window, &listBox->ID, &listBox->Layout, L"LISTBOX", buttonText);
#endif
}

void TextEditConstruct(const WindowID window, OSTextEdit* textEdit, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
    MemorySet(textEdit, sizeof(OSTextEdit), 0);

#if defined(OSUnix)
#elif defined(OSWindows)

    textEdit->Layout.Style = WS_TABSTOP | WS_VISIBLE | WS_CHILD;
    textEdit->Layout.X = x;
    textEdit->Layout.Y = y;
    textEdit->Layout.Width = width;
    textEdit->Layout.Height = height;

    UIElementConstruct(window, &textEdit->ID, &textEdit->Layout, L"EDIT", buttonText);
#endif
}

void RichEditConstruct(const WindowID window, OSRichEdit* richEdit, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
    MemorySet(richEdit, sizeof(OSRichEdit), 0);

#if defined(OSUnix)
#elif defined(OSWindows)

    richEdit->Layout.Style = WS_TABSTOP | WS_VISIBLE | WS_CHILD;
    richEdit->Layout.X = x;
    richEdit->Layout.Y = y;
    richEdit->Layout.Width = width;
    richEdit->Layout.Height = height;

    UIElementConstruct(window, &richEdit->ID, &richEdit->Layout, L"RICHEDIT_CLASS", buttonText);
#endif
}

void ScrollBarConstruct(const WindowID window, OSScrollBar* scrollBar, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
    MemorySet(scrollBar, sizeof(OSScrollBar), 0);

#if defined(OSUnix)
#elif defined(OSWindows)

    scrollBar->Layout.Style = WS_TABSTOP | WS_VISIBLE | WS_CHILD;
    scrollBar->Layout.X = x;
    scrollBar->Layout.Y = y;
    scrollBar->Layout.Width = width;
    scrollBar->Layout.Height = height;

    UIElementConstruct(window, &scrollBar->ID, &scrollBar->Layout, L"SCROLLBAR", buttonText);
#endif
}