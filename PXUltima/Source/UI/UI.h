#ifndef UIDEFINED
#define UIDEFINED

#ifdef __cplusplus
extern "C"
{
#endif

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

	typedef struct UILayout
	{
		UIMargin Margin;
		UIPadding Padding;
	};

	typedef struct UIText
	{
		unsigned char _SUMMY__;
	};

#ifdef __cplusplus
}
#endif

#endif