#ifndef PXUIInclude
#define PXUIInclude

#include <OS/Error/PXActionResult.h>
#include <OS/Window/PXWindow.h>

#if OSUnix
typedef unsigned int UIElementID;
#elif OSWindows
#include <Windows.h>
typedef HWND UIElementID;
#endif


#ifdef __cplusplus
extern "C"
{
#endif

#if OSWindows
	PXPublic void PXUIElementTextGet(const UIElementID uiElementID, const wchar_t* buffer, const PXSize bufferSize, PXSize* bufferRead);
	PXPublic void PXUIElementTextSet(const UIElementID uiElementID, const wchar_t* buffer, const PXSize bufferSize, PXSize* bufferWritten);
#endif

	PXPublic void PXUIElementEnable();

	typedef struct UILayout_
	{
		unsigned int Style;
		unsigned int X;
		unsigned int Y;
		unsigned int Width;
		unsigned int Height;
		
	}UILayout;


	PXPublic void UIElementConstruct(const PXWindowID window, UIElementID* ID, UILayout* Layout, const wchar_t* className, const wchar_t* name);

	typedef struct OSButton_
	{
		UIElementID ID;
		UILayout Layout;

	}OSButton;

	PXPublic void ButtonConstruct
	(
		const PXWindowID window,
		OSButton* button,
		const unsigned int x,
		const unsigned int y,
		const unsigned int width,
		const unsigned int height,
		const wchar_t* buttonText
	);

	//-------------------------------------------------------------------------

	typedef struct OSComboBox_
	{
		UIElementID ID;
		UILayout Layout;

	}OSComboBox;

	PXPublic void ComboBoxConstruct
	(
		const PXWindowID window,
		OSComboBox* comboBox,
		const unsigned int x,
		const unsigned int y,
		const unsigned int width,
		const unsigned int height,
		const wchar_t* buttonText
	);

	//-------------------------------------------------------------------------

	typedef struct OSListBox_
	{
		UIElementID ID;
		UILayout Layout;

	}OSListBox;

	PXPublic void ListBoxConstruct
	(
		const PXWindowID window,
		OSListBox* listBox,
		const unsigned int x,
		const unsigned int y,
		const unsigned int width,
		const unsigned int height,
		const wchar_t* buttonText
	);
	//-------------------------------------------------------------------------

	typedef struct OSTextEdit_
	{
		UIElementID ID;
		UILayout Layout;

	}OSTextEdit;

	PXPublic void TextEditConstruct
	(
		const PXWindowID window,
		OSTextEdit* textEdit,
		const unsigned int x,
		const unsigned int y,
		const unsigned int width,
		const unsigned int height,
		const wchar_t* buttonText
	);
	PXPublic void TextEditContentGet(OSTextEdit* textEdit, const wchar_t* buffer, const PXSize bufferSize, PXSize* bufferWritten);

	//-------------------------------------------------------------------------


	// MDICLIENT
	//-------------------------------------------------------------------------


	typedef struct OSRichEdit_
	{
		UIElementID ID;
		UILayout Layout;

	}OSRichEdit;

	PXPublic void RichEditConstruct
	(
		const PXWindowID window,
		OSRichEdit* richEdit,
		const unsigned int x,
		const unsigned int y,
		const unsigned int width,
		const unsigned int height,
		const wchar_t* buttonText
	);

	//-------------------------------------------------------------------------


	typedef struct OSScrollBar_
	{
		UIElementID ID;
		UILayout Layout;

	}OSScrollBar;

	PXPublic void ScrollBarConstruct
	(
		const PXWindowID window,
		OSScrollBar* scrollBar,
		const unsigned int x,
		const unsigned int y,
		const unsigned int width,
		const unsigned int height,
		const wchar_t* buttonText
	);

	//-------------------------------------------------------------------------



	//-------------------------------------------------------------------------


 // Static objects?


	typedef struct PXOSUIText_
	{
		UIElementID ID;
		UILayout Layout;
	}
	PXOSUIText;

	PXPublic void PXUITextConstruct
	(
		const PXWindowID window,
		PXOSUIText* uiText,
		const unsigned int x,
		const unsigned int y,
		const unsigned int width,
		const unsigned int height,
		const wchar_t* buttonText
	);


	typedef struct PXUICheckBox_
	{
		UIElementID ID;
		UILayout Layout;
		unsigned char IsChecked;

	}PXUICheckBox;

	PXPublic void OSCheckBoxConstruct
	(
		const PXWindowID window,
		PXUICheckBox* uiCheckBox,
		const unsigned int x,
		const unsigned int y,
		const unsigned int width,
		const unsigned int height,
		const wchar_t* buttonText
	);

	//-------------------------------------------------------------------------

	typedef struct PXUITrackbar_
	{
		UIElementID ID;
		UILayout Layout;

	}PXUITrackbar;

	PXPublic void PXUITrackbarCreate(const PXWindowID window, PXUITrackbar* PXUITrackbar, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText);

	//-------------------------------------------------------------------------



	//-------------------------------------------------------------------------

	typedef struct PXUIStatusbar_
	{
		UIElementID ID;
		UILayout Layout;
	}
	PXUIStatusbar;

	PXPublic void PXUIStatusbarCreate(const PXWindowID window, PXUIStatusbar* PXUIStatusbar, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText);

	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------

	typedef struct PXUIUpDown_
	{
		UIElementID ID;
		UILayout Layout;

	}PXUIUpDown;

	PXPublic void PXUIUpDownCreate(const PXWindowID window, PXUIUpDown* PXUIUpDown, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText);

	//-------------------------------------------------------------------------

		//-------------------------------------------------------------------------

	typedef struct PXUIProgressbar_
	{
		UIElementID ID;
		UILayout Layout;

	}PXUIProgressbar;

	PXPublic void PXUIProgressbarCreate(const PXWindowID window, PXUIProgressbar* PXUIProgressbar, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText);

	//-------------------------------------------------------------------------

		//-------------------------------------------------------------------------

	typedef struct PXUIHotKey_
	{
		UIElementID ID;
		UILayout Layout;

	}PXUIHotKey;

	PXPublic void PXUIHotKeyCreate(const PXWindowID window, PXUIHotKey* PXUIHotKey, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText);

	//-------------------------------------------------------------------------


	typedef struct PXUICalender_
	{
		UIElementID ID;
		UILayout Layout;

	}PXUICalender;

	PXPublic void PXUICalenderCreate(const PXWindowID window, PXUICalender* PXUICalender, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText);


	typedef struct PXUIToolTip_
	{
		UIElementID ID;
		UILayout Layout;

	}PXUIToolTip;

	PXPublic void PXUIToolTipCreate(const PXWindowID window, PXUIToolTip* PXUIToolTip, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText);


	typedef struct PXUIAnimate_
	{
		UIElementID ID;
		UILayout Layout;

	}PXUIAnimate;

	PXPublic void PXUIAnimateCreate(const PXWindowID window, PXUIAnimate* PXUIAnimate, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText);


	typedef struct PXUIDateTimePicker_
	{
		UIElementID ID;
		UILayout Layout;

	}PXUIDateTimePicker;

	PXPublic void PXUIDateTimePickerCreate(const PXWindowID window, PXUIDateTimePicker* PXUIDateTimePicker, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText);


	typedef struct PXUIGroupBox_
	{
		UIElementID ID;
		UILayout Layout;

	}PXUIGroupBox;

	PXPublic void PXUIGroupBoxCreate(const PXWindowID window, PXUIGroupBox* PXUIGroupBox, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText);


	typedef struct PXUIRadioButton_
	{
		UIElementID ID;
		UILayout Layout;

	}PXUIRadioButton;

	PXPublic void PXUIRadioButtonCreate(const PXWindowID window, PXUIRadioButton* PXUIRadioButton, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText);




	typedef struct PXUIGroupRadioButton_
	{
		UIElementID ID;
		UILayout Layout;

	}PXUIGroupRadioButton;

	PXPublic void PXUIGroupRadioButtonCreate(const PXWindowID window, PXUIGroupRadioButton* PXUIGroupRadioButton, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText);


	typedef struct PXUIListBox_
	{
		UIElementID ID;
		UILayout Layout;

	}PXUIListBox;


	PXPublic void PXUIListBoxCreate(const PXWindowID window, PXUIListBox* PXUIListBox, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText);


	typedef struct PXUITreeView_
	{
		UIElementID ID;
		UILayout Layout;
	}
	PXUITreeView;

	PXPublic void PXUITreeViewCreate(const PXWindowID window, PXUITreeView* PXUITreeView, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText);



	typedef struct PXUIIPInput_
	{
		UIElementID ID;
		UILayout Layout;

	}PXUIIPInput;

	PXPublic void PXUIIPInputCreate(const PXWindowID window, PXUIIPInput* PXUIIPInput, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText);



	typedef struct PXUITabControl_
	{
		UIElementID ID;
		UILayout Layout;

	}PXUITabControl;

	PXPublic void PXUITabControlCreate(const PXWindowID window, PXUITabControl* PXUITabControl, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText);








	typedef struct PXUIPageScroller_
	{
		UIElementID ID;
		UILayout Layout;

	}PXUIPageScroller;

	PXPublic void PXUIPageScrollerCreate(const PXWindowID window, PXUIPageScroller* PXUIPageScroller, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText);


	typedef struct PXUIFontSelector_
	{
		UIElementID ID;
		UILayout Layout;

	}PXUIFontSelector;

	PXPublic void PXUIFontSelectorCreate(const PXWindowID window, PXUIFontSelector* PXUIFontSelector, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText);


	typedef struct PXUIHeader_
	{
		UIElementID ID;
		UILayout Layout;

	}PXUIHeader;

	PXPublic void PXUIHeaderCreate(const PXWindowID window, PXUIHeader* PXUIHeader, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText);


	typedef struct PXUILink_
	{
		UIElementID ID;
		UILayout Layout;

	}PXUILink;

	PXPublic void PXUILinkCreate(const PXWindowID window, PXUILink* PXUILink, const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height, const wchar_t* buttonText);






	


#ifdef __cplusplus
}
#endif

#endif


