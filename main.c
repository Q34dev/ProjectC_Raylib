#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "include/game_logic.h"
#include "include/gui.h"

int main()
{
    GameLogic_Setup(GetCellCount());
    GUI_DrawGame();

    return 0;
}
