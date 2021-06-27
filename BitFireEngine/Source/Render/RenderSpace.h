#pragma once

namespace BF
{
	enum class RenderSpace
	{
		/// <summary>
		/// Render in the worldspace. Used for general objects. 
		/// </summary>
		WorldSpace,

		/// <summary>
		/// Render as 2D object. Used for static elements as UI. 
		/// </summary>
		HUD
	};
}