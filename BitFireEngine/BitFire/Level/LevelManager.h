#pragma once

#include "Level.h"

namespace BF
{
	class LevelManager
	{
	private:
		List<Level> _levelList;

		Level* _currentLevel;

	public:
		LevelManager();

		void LoadLevel();
		void LoadAllLevels();
		void SaveCurrentLevel();
		void ReloadCurrentLevel();
	};
}