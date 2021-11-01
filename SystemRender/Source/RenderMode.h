#pragma once

namespace BF
{
	enum class RenderMode
	{
		Invalid,

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

		WireFrame,

		Square,

		Patches
	};
}