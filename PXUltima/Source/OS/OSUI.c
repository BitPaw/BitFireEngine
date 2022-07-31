#include "OSUI.h"

#define WindowsEnableModernColorSceme 1

#if defined(OSUnix)
#elif defined(OSWindows)

#if WindowsEnableModernColorSceme

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


#include <CommCtrl.h>
#include <commdlg.h>
//#include <ShObjIdl.h>
#endif

#include <Memory/Memory.h>
#include <Text/Text.h>
#include <Math/Math.h>

#include <stdio.h>


#if defined(OSWindows)
void OSUIElementTextGet(const UIElementID uiElementID, const wchar_t* buffer, const size_t bufferSize, size_t* bufferRead)
{
    const int textLength = GetWindowTextLengthW(uiElementID) + 1;
    const int maximum = MathMinimum(textLength, bufferSize);
    const int lengthRead = GetWindowTextW(uiElementID, buffer, maximum);

    *bufferRead = lengthRead;
}

void OSUIElementTextSet(const UIElementID uiElementID, const wchar_t* buffer, const size_t bufferSize, size_t* bufferWritten)
{
    const int lengthWrittem = SetWindowTextW(uiElementID, buffer, bufferSize);

    *bufferWritten = lengthWrittem;
}
#endif

void OSUIElementEnable()
{
#if defined(OSWindows)
    INITCOMMONCONTROLSEX icex;

    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC =
        ICC_LISTVIEW_CLASSES | // listview, header
        ICC_TREEVIEW_CLASSES | // treeview, tooltips
        ICC_BAR_CLASSES | // toolbar, statusbar, trackbar, tooltips
        ICC_TAB_CLASSES | // tab, tooltips
        ICC_UPDOWN_CLASS | // updown
        ICC_PROGRESS_CLASS | // progress
        ICC_HOTKEY_CLASS | // hotkey
        ICC_ANIMATE_CLASS | // animate
        ICC_WIN95_CLASSES |
        ICC_DATE_CLASSES | // month picker, date picker, time picker, updown
        ICC_USEREX_CLASSES | // comboex
        ICC_COOL_CLASSES | // rebar (coolbar) control
        ICC_INTERNET_CLASSES |
        ICC_PAGESCROLLER_CLASS |   // page scroller

#if (NTDDI_VERSION >= NTDDI_WINXP)
        ICC_STANDARD_CLASSES |
        ICC_LINK_CLASS |
#endif
        ICC_NATIVEFNTCTL_CLASS;   // native font control



    InitCommonControlsEx(&icex);
#endif
}


void UIElementConstruct(const CWindowID window, UIElementID* ID, UILayout* Layout, const wchar_t* className, const wchar_t* name)
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

    if(*ID)
    {
        printf("\n[i][UI] %ls create : %p\n", className,*ID);
    }
    else
    {
        printf("\n[x][UI] %ls create <FAILED> : %p\n", className, *ID);
    }


}

void ButtonConstruct(const CWindowID window, OSButton* button, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
    MemorySet(button, sizeof(OSButton), 0);

#if defined(OSUnix)
#elif defined(OSWindows)
    button->Layout.Style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_USERBUTTON | WS_BORDER;
    button->Layout.X = x;
    button->Layout.Y = y;
    button->Layout.Width = width;
    button->Layout.Height = height;

    UIElementConstruct(window, &button->ID, &button->Layout, WC_BUTTONW, buttonText);
#endif
}

void ComboBoxConstruct(const CWindowID window, OSComboBox* comboBox, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
    MemorySet(comboBox, sizeof(OSComboBox), 0);

#if defined(OSUnix)
#elif defined(OSWindows)

    comboBox->Layout.Style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER;
    comboBox->Layout.X = x;
    comboBox->Layout.Y = y;
    comboBox->Layout.Width = width;
    comboBox->Layout.Height = height;

    // WC_COMBOBOXEXW or WC_COMBOBOXW ??

    UIElementConstruct(window, &comboBox->ID, &comboBox->Layout, WC_COMBOBOXEXW, buttonText);
#endif
}

void ListBoxConstruct(const CWindowID window, OSListBox* listBox, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
    MemorySet(listBox, sizeof(OSListBox), 0);

#if defined(OSUnix)
#elif defined(OSWindows)

    listBox->Layout.Style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER;
    listBox->Layout.X = x;
    listBox->Layout.Y = y;
    listBox->Layout.Width = width;
    listBox->Layout.Height = height;

    UIElementConstruct(window, &listBox->ID, &listBox->Layout, WC_LISTBOXW, buttonText);
#endif
}

void TextEditConstruct(const CWindowID window, OSTextEdit* textEdit, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
    MemorySet(textEdit, sizeof(OSTextEdit), 0);

#if defined(OSUnix)
#elif defined(OSWindows)

    textEdit->Layout.Style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER;
    textEdit->Layout.X = x;
    textEdit->Layout.Y = y;
    textEdit->Layout.Width = width;
    textEdit->Layout.Height = height;

    UIElementConstruct(window, &textEdit->ID, &textEdit->Layout, WC_EDITW, buttonText);
#endif
}

void TextEditContentGet(OSTextEdit* textEdit, const wchar_t* buffer, const size_t bufferSize, size_t* bufferWritten)
{
    OSUIElementTextGet(textEdit->ID, buffer, bufferSize, bufferWritten);
}

void RichEditConstruct(const CWindowID window, OSRichEdit* richEdit, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
    MemorySet(richEdit, sizeof(OSRichEdit), 0);

#if defined(OSUnix)
#elif defined(OSWindows)

    richEdit->Layout.Style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER;
    richEdit->Layout.X = x;
    richEdit->Layout.Y = y;
    richEdit->Layout.Width = width;
    richEdit->Layout.Height = height;

    UIElementConstruct(window, &richEdit->ID, &richEdit->Layout, L"RICHEDIT_CLASS", buttonText);
#endif
}

void ScrollBarConstruct(const CWindowID window, OSScrollBar* scrollBar, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
    MemorySet(scrollBar, sizeof(OSScrollBar), 0);

#if defined(OSUnix)
#elif defined(OSWindows)

    scrollBar->Layout.Style = WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER;
    scrollBar->Layout.X = x;
    scrollBar->Layout.Y = y;
    scrollBar->Layout.Width = width;
    scrollBar->Layout.Height = height;

    UIElementConstruct(window, &scrollBar->ID, &scrollBar->Layout, WC_SCROLLBARW, buttonText);
#endif
}

void OSUITextConstruct(const CWindowID window, OSUIText* uiText, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
    MemorySet(uiText, sizeof(OSUIText), 0);

#if defined(OSUnix)
#elif defined(OSWindows)

    uiText->Layout.Style = WS_VISIBLE | WS_CHILD | SS_LEFT | WS_BORDER;
    uiText->Layout.X = x;
    uiText->Layout.Y = y;
    uiText->Layout.Width = width;
    uiText->Layout.Height = height;

    UIElementConstruct(window, &uiText->ID, &uiText->Layout, WC_STATICW, buttonText);
#endif

}

void OSCheckBoxConstruct(const CWindowID window, OSUICheckBox* uiCheckBox, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
    MemorySet(uiCheckBox, sizeof(OSUICheckBox), 0);

#if defined(OSUnix)
#elif defined(OSWindows)

    uiCheckBox->Layout.Style = WS_VISIBLE | WS_CHILD | BS_CHECKBOX | WS_BORDER;
    uiCheckBox->Layout.X = x;
    uiCheckBox->Layout.Y = y;
    uiCheckBox->Layout.Width = width;
    uiCheckBox->Layout.Height = height;

    UIElementConstruct(window, &uiCheckBox->ID, &uiCheckBox->Layout, WC_BUTTONW, buttonText);

    CheckDlgButton(uiCheckBox->ID, 1, BST_CHECKED); // BST_UNCHECKED
#endif
}

void OSUITrackbarCreate(const CWindowID window, OSUITrackbar* osUITrackbar, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    osUITrackbar->Layout.Style = WS_VISIBLE | WS_CHILD | TBS_AUTOTICKS | WS_BORDER;
    osUITrackbar->Layout.X = x;
    osUITrackbar->Layout.Y = y;
    osUITrackbar->Layout.Width = width;
    osUITrackbar->Layout.Height = height;

    UIElementConstruct(window, &osUITrackbar->ID, &osUITrackbar->Layout, TRACKBAR_CLASSW, buttonText);
#endif
}

void OSUIStatusbarCreate(const CWindowID window, OSUIStatusbar* osUIStatusbar, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    osUIStatusbar->Layout.Style = WS_VISIBLE | WS_CHILD | WS_BORDER;
    osUIStatusbar->Layout.X = x;
    osUIStatusbar->Layout.Y = y;
    osUIStatusbar->Layout.Width = width;
    osUIStatusbar->Layout.Height = height;

    UIElementConstruct(window, &osUIStatusbar->ID, &osUIStatusbar->Layout, STATUSCLASSNAMEW, buttonText);
#endif
}

void OSUIUpDownCreate(const CWindowID window, OSUIUpDown* osUIUpDown, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    osUIUpDown->Layout.Style = WS_VISIBLE | WS_CHILD | WS_BORDER;
    osUIUpDown->Layout.X = x;
    osUIUpDown->Layout.Y = y;
    osUIUpDown->Layout.Width = width;
    osUIUpDown->Layout.Height = height;

    UIElementConstruct(window, &osUIUpDown->ID, &osUIUpDown->Layout, UPDOWN_CLASSW, buttonText);
#endif
}

void OSUIProgressbarCreate(const CWindowID window, OSUIProgressbar* osUIProgressbar, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    osUIProgressbar->Layout.Style = WS_VISIBLE | WS_CHILD | WS_BORDER;
    osUIProgressbar->Layout.X = x;
    osUIProgressbar->Layout.Y = y;
    osUIProgressbar->Layout.Width = width;
    osUIProgressbar->Layout.Height = height;

    UIElementConstruct(window, &osUIProgressbar->ID, &osUIProgressbar->Layout, PROGRESS_CLASSW, buttonText); // "Progress bar"
#endif
}

void OSUIHotKeyCreate(const CWindowID window, OSUIHotKey* osUIHotKey, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    osUIHotKey->Layout.Style = WS_VISIBLE | WS_CHILD | WS_BORDER;
    osUIHotKey->Layout.X = x;
    osUIHotKey->Layout.Y = y;
    osUIHotKey->Layout.Width = width;
    osUIHotKey->Layout.Height = height;

    UIElementConstruct(window, &osUIHotKey->ID, &osUIHotKey->Layout, HOTKEY_CLASSW, buttonText);
#endif
}

void OSUICalenderCreate(const CWindowID window, OSUICalender* osUICalender, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    osUICalender->Layout.Style = WS_VISIBLE | WS_CHILD | WS_BORDER;
    osUICalender->Layout.X = x;
    osUICalender->Layout.Y = y;
    osUICalender->Layout.Width = width;
    osUICalender->Layout.Height = height;

    UIElementConstruct(window, &osUICalender->ID, &osUICalender->Layout, MONTHCAL_CLASSW, buttonText);
#endif
}

void OSUIToolTipCreate(const CWindowID window, OSUIToolTip* osUIToolTip, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    osUIToolTip->Layout.Style = WS_VISIBLE | WS_CHILD | WS_BORDER;
    osUIToolTip->Layout.X = x;
    osUIToolTip->Layout.Y = y;
    osUIToolTip->Layout.Width = width;
    osUIToolTip->Layout.Height = height;

    UIElementConstruct(window, &osUIToolTip->ID, &osUIToolTip->Layout, TOOLTIPS_CLASSW, buttonText);
#endif
}

void OSUIAnimateCreate(const CWindowID window, OSUIAnimate* osUIAnimate, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    osUIAnimate->Layout.Style = WS_VISIBLE | WS_CHILD | WS_BORDER;
    osUIAnimate->Layout.X = x;
    osUIAnimate->Layout.Y = y;
    osUIAnimate->Layout.Width = width;
    osUIAnimate->Layout.Height = height;

    UIElementConstruct(window, &osUIAnimate->ID, &osUIAnimate->Layout, ANIMATE_CLASSW, buttonText);
#endif
}

void OSUIDateTimePickerCreate(const CWindowID window, OSUIDateTimePicker* osUIDateTimePicker, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    osUIDateTimePicker->Layout.Style = WS_VISIBLE | WS_CHILD | WS_BORDER;
    osUIDateTimePicker->Layout.X = x;
    osUIDateTimePicker->Layout.Y = y;
    osUIDateTimePicker->Layout.Width = width;
    osUIDateTimePicker->Layout.Height = height;

    UIElementConstruct(window, &osUIDateTimePicker->ID, &osUIDateTimePicker->Layout, DATETIMEPICK_CLASSW, buttonText);
#endif
}

void OSUIGroupBoxCreate(const CWindowID window, OSUIGroupBox* osUIGroupBox, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    osUIGroupBox->Layout.Style = WS_VISIBLE | WS_CHILD | BS_GROUPBOX | WS_BORDER;
    osUIGroupBox->Layout.X = x;
    osUIGroupBox->Layout.Y = y;
    osUIGroupBox->Layout.Width = width;
    osUIGroupBox->Layout.Height = height;

    UIElementConstruct(window, &osUIGroupBox->ID, &osUIGroupBox->Layout, WC_BUTTONW, buttonText);
#endif
}

void OSUIRadioButtonCreate(const CWindowID window, OSUIRadioButton* osUIRadioButton, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    osUIRadioButton->Layout.Style = WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON | WS_BORDER;
    osUIRadioButton->Layout.X = x;
    osUIRadioButton->Layout.Y = y;
    osUIRadioButton->Layout.Width = width;
    osUIRadioButton->Layout.Height = height;

    UIElementConstruct(window, &osUIRadioButton->ID, &osUIRadioButton->Layout, WC_BUTTONW, buttonText);
#endif
}

void OSUIGroupRadioButtonCreate(const CWindowID window, OSUIGroupRadioButton* osUIGroupRadioButton, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    osUIGroupRadioButton->Layout.Style = WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_BORDER;
    osUIGroupRadioButton->Layout.X = x;
    osUIGroupRadioButton->Layout.Y = y;
    osUIGroupRadioButton->Layout.Width = width;
    osUIGroupRadioButton->Layout.Height = height;

    UIElementConstruct(window, &osUIGroupRadioButton->ID, &osUIGroupRadioButton->Layout, WC_BUTTONW, buttonText);
#endif
}

void OSUIListBoxCreate(const CWindowID window, OSUIListBox* osUIListBox, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    osUIListBox->Layout.Style = WS_VISIBLE | WS_CHILD | WS_BORDER;
    osUIListBox->Layout.X = x;
    osUIListBox->Layout.Y = y;
    osUIListBox->Layout.Width = width;
    osUIListBox->Layout.Height = height;

    UIElementConstruct(window, &osUIListBox->ID, &osUIListBox->Layout, WC_LISTBOXW, buttonText);
#endif
}

void OSUITreeViewCreate(const CWindowID window, OSUITreeView* OSUITreeView, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    OSUITreeView->Layout.Style = WS_VISIBLE | WS_CHILD | WS_BORDER;
    OSUITreeView->Layout.X = x;
    OSUITreeView->Layout.Y = y;
    OSUITreeView->Layout.Width = width;
    OSUITreeView->Layout.Height = height;

    UIElementConstruct(window, &OSUITreeView->ID, &OSUITreeView->Layout, WC_TREEVIEWW, buttonText);
#endif
}

void OSUIIPInputCreate(const CWindowID window, OSUIIPInput* osUIIPInput, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    osUIIPInput->Layout.Style = WS_VISIBLE | WS_CHILD | WS_BORDER;
    osUIIPInput->Layout.X = x;
    osUIIPInput->Layout.Y = y;
    osUIIPInput->Layout.Width = width;
    osUIIPInput->Layout.Height = height;

    UIElementConstruct(window, &osUIIPInput->ID, &osUIIPInput->Layout, WC_IPADDRESSW, buttonText);
#endif    
}

void OSUITabControlCreate(const CWindowID window, OSUITabControl* osUITabControl, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    osUITabControl->Layout.Style = WS_VISIBLE | WS_CHILD | WS_BORDER;
    osUITabControl->Layout.X = x;
    osUITabControl->Layout.Y = y;
    osUITabControl->Layout.Width = width;
    osUITabControl->Layout.Height = height;

    UIElementConstruct(window, &osUITabControl->ID, &osUITabControl->Layout, WC_TABCONTROLW, buttonText);
#endif
}

void OSUIPageScrollerCreate(const CWindowID window, OSUIPageScroller* osUIPageScroller, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    osUIPageScroller->Layout.Style = WS_VISIBLE | WS_CHILD | WS_BORDER;
    osUIPageScroller->Layout.X = x;
    osUIPageScroller->Layout.Y = y;
    osUIPageScroller->Layout.Width = width;
    osUIPageScroller->Layout.Height = height;

    UIElementConstruct(window, &osUIPageScroller->ID, &osUIPageScroller->Layout, WC_PAGESCROLLERW, buttonText);
#endif
}

void OSUIFontSelectorCreate(const CWindowID window, OSUIFontSelector* osUIFontSelector, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    osUIFontSelector->Layout.Style = WS_VISIBLE | WS_CHILD | NFS_USEFONTASSOC | WS_BORDER;
    osUIFontSelector->Layout.X = x;
    osUIFontSelector->Layout.Y = y;
    osUIFontSelector->Layout.Width = width;
    osUIFontSelector->Layout.Height = height;

    UIElementConstruct(window, &osUIFontSelector->ID, &osUIFontSelector->Layout, WC_NATIVEFONTCTLW, buttonText);
#endif
}

void OSUIHeaderCreate(const CWindowID window, OSUIHeader* osUIHeader, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    osUIHeader->Layout.Style = WS_VISIBLE | WS_CHILD | WS_BORDER;
    osUIHeader->Layout.X = x;
    osUIHeader->Layout.Y = y;
    osUIHeader->Layout.Width = width;
    osUIHeader->Layout.Height = height;

    UIElementConstruct(window, &osUIHeader->ID, &osUIHeader->Layout, WC_HEADERW, buttonText);
#endif
}

void OSUILinkCreate(const CWindowID window, OSUILink* osUILink, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText)
{
#if defined(OSUnix)
#elif defined(OSWindows)
    osUILink->Layout.Style = WS_VISIBLE | WS_CHILD;
    osUILink->Layout.X = x;
    osUILink->Layout.Y = y;
    osUILink->Layout.Width = width;
    osUILink->Layout.Height = height;

    UIElementConstruct(window, &osUILink->ID, &osUILink->Layout, WC_LINK, buttonText);
#endif
}