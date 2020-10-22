#pragma once

namespace BF
{
	enum class MTLCommand
	{
		Invalid,

		Command,

		MaterialDeclaration,

		AmbientColor,
		DiffuseColor,
		SpecularColor,

		Dissolvence,
		Transparency,

		Illumation
	};
}