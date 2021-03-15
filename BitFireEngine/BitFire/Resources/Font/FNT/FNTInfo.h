#pragma once

#include "../../../Mathematic/Geometry/Padding.hpp"
#include "../../../Mathematic/Geometry/Point.hpp"
#include "../../../Utility/ASCIIString.h"

namespace BF
{
	class FNTInfo
	{
		public:

		/// <summary>
		/// Name of this font. (synonym: face)
		/// </summary>
		ASCIIString Name;

		/// <summary>
		/// Size of the Letters int Pixel as height.
		/// </summary>
		unsigned int Size;

		/// <summary>
		/// Is the text fat?
		/// </summary>
		bool Bold;

		/// <summary>
		/// Is the text cursive?
		/// </summary>
		bool Italic;

		/// <summary>
		/// The name of the OEM charset used (when not unicode). Like 'ANSI'.
		/// </summary>
		ASCIIString	CharSet;

		/// <summary>
		/// Is the charset in the unicode format?
		/// </summary>
		bool Unicode;
		unsigned int StretchH;

		/// <summary>
		/// Set to 1 if smoothing was turned on.
		/// </summary>
		unsigned int Smooth;

		/// <summary>
		/// Supersampling level used. 1 means no supersampling was used. (AA)
		/// </summary>
		unsigned int Supersampling;

		/// <summary>
		/// Padding for each character.
		/// </summary>
		Padding<unsigned int> CharacterPadding;

		Point<unsigned int> SpacerOffset;

		/// <summary>
		/// How thick is the line arount the Letter?
		/// </summary>
		unsigned int OutlineThickness;

		FNTInfo();
	};
}