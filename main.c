#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "include/file_manager.h"
#include "include/game_logic.h"
#include "include/gui.h"

int main()
{
    FileManager_ReadConfigFile();
    GameLogic_Setup();
    GUI_DrawGame();

    return 0;
}
