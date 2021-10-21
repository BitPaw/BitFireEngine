#pragma once

namespace BF
{
	struct MeshRenderInfo
	{
		bool ShouldBeRendered;
		unsigned int ShaderProgramID;
		unsigned int MaterialID;

		MeshRenderInfo();
	};
}