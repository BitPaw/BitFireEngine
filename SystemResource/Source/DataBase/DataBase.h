#pragma once

namespace BF
{
	class DataBase
	{
		public:
		void ConnectToFile(const wchar_t* filaPath);
		void ConnectToServer(const wchar_t* filaPath);
	};
}