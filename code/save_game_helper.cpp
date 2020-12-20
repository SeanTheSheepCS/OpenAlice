#include "save_game_helper.h"
#include <stdio.h>

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

/* static */ void SaveGameHelper::deleteSaveFile(int saveFileNumberToDelete)
{
	switch(saveFileNumberToDelete)
	{
		case 1:
			{
				remove(PATH_TO_FIRST_SAVE);
			}
			break;
		case 2:
			{
				remove(PATH_TO_SECOND_SAVE);
			}
			break;
		case 3:
			{
				remove(PATH_TO_THIRD_SAVE);
			}
			break;
	}
}
