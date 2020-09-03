#pragma once

enum class IlluminationMode
{
	// [0] Color on and Ambient off
	ColorAndAmbientDisable = 0,

	// [1] Color on and Ambient on
	ColorAndAmbientEnable = 1,

	// [2] Highlight on
	HighlightEnable = 2,

	// [3] Reflection on and Ray trace on
	ReflectionOnRayTraceEnable = 3,

	// [4] Transparency: Glass on, Reflection : Ray trace on
	ReflectionOnRayTraceTransparency = 4,

	// [5] Reflection : Fresnel on and Ray trace on
	ReflectionOnRayTraceFresnel = 5,

	// [6] Transparency : Refraction on, Reflection : Fresnel offand Ray trace on
	ReflectionOnRayTraceTransparencyFresnel = 6,

	// [7] Transparency : Refraction on, Reflection : Fresnel onand Ray trace on
	ReflectionOnRayTraceFullEnable = 7,

	// [8] Reflection on and Ray trace off
	ReflectionEnable = 8,

	// [9] Transparency : Glass on, Reflection : Ray trace off
	TransparencyEnable = 9,

	// [10] Casts shadows onto invisible surfaces
	ShadowsEnable = 10
};