#include "save_game_helper.h"

#include <iostream>

/*static*/ SaveFile SaveGameHelper::loadSaveFile(int saveFileNumberToLoad)
{
	switch(saveFileNumberToLoad)
	{
		case 1:
			{
				SaveFile returnValue = SaveFile(PATH_TO_FIRST_SAVE);
				return returnValue;
			}
			break;
		case 2:
			{
				SaveFile returnValue = SaveFile(PATH_TO_SECOND_SAVE);
				return returnValue;
			}
			break;
		case 3:			
			{
				SaveFile returnValue = SaveFile(PATH_TO_THIRD_SAVE);
				return returnValue;
			}
			break;
	}
}

/* static */ void SaveGameHelper::deleteSaveFile(int saveFileToDelete)
{
	std::cout << "TODO: DELETE SAVE FILE PROCEDURE" << std::endl;
}
