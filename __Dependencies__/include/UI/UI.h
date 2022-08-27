#ifndef UIDEFINED
#define UIDEFINED

#ifdef __cplusplus
extern "C"
{
#endif

	typedef enum UIState
	{
		UIStateInvalid,
		UIStateActive,
		UIStateHot,
		UIStateIDLE
	}UIState;

	typedef enum UIScalingType_
	{
		UIScalingInvalid,
		UIScalingRelativeToParent
	}
	UIScalingType;
	

	// Offset the whole child-Container
	// (Make empty space)
	typedef struct UIMargin_
	{
		float LeftTop;
		float Top;
		float Right;
		float Bottom;
	}
	UIMargin;

	// Offset the space as the child container 
	// (Make object take more space)
	typedef struct UIPadding_
	{
		float LeftTop;
		float Top;
		float Right;
		float Bottom;
	}
	UIPadding;

	typedef struct UILayout_
	{
		UIMargin Margin;
		UIPadding Padding;

		void* Parent;
		void* Child;
	}UILayout;

	typedef struct UIText_
	{
		unsigned char _SUMMY__;
	}
	UIText;


	typedef struct UIContainerRoot_
	{
		unsigned char _SUMMY__;
	}
	UIContainerRoot;

	typedef struct UIElement_
	{
		UILayout Layout; 

	}
	UIElement;


	extern void UIContainerElementAdd(UIContainerRoot* uiContainerRoot);

#ifdef __cplusplus
}
#endif

#endif