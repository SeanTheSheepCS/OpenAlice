#ifndef SAVE_GAME_HELPER_H
#define SAVE_GAME_HELPER_H

#include "save_file.h"

#define PATH_TO_FIRST_SAVE "../saves/savegame_one.oas"
#define PATH_TO_SECOND_SAVE "../saves/savegame_two.oas"
#define PATH_TO_THIRD_SAVE "../saves/savegame_three.oas"

class SaveGameHelper
{
	public:
		static SaveFile loadSaveFile(int saveFileNumberToLoad);
		static void deleteSaveFile(int saveFileNumberToDelete);
	protected:
		//
	private:
		//
};

#endif
