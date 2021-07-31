#pragma once

namespace BF
{
	enum class RenderMode
	{
		Unkown,

		Point,

		Line,
		LineLoop,
		LineStrip,
		LineStripAdjacency,
		LineAdjacency,

		Triangle,
		TriangleAdjacency,
		TriangleFAN,
		TriangleStrip,
		TriangleStripAdjacency,

		Square,

		Patches
	};
}