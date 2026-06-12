#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int StartsWith(const char *str, const char *prefix)
{
    while (*prefix && *str == *prefix)
        ++str, ++prefix;
    return *prefix == 0;
}

void SaveGameState(int playerTurnIndex, int cellCountX, int cellCountY, int **board)
{
    FILE *saveFile = fopen("files/save.txt", "w");
    if (saveFile == NULL)
    {
        printf("save file not found");
        return;
    }
    fprintf(saveFile, "%d\n", playerTurnIndex);
    for (int row = 0; row < cellCountY; row++)
    {
        for (int col = 0; col < cellCountX; col++)
        {
            fprintf(saveFile, "%d", board[row][col]);
        }
        fprintf(saveFile, "\n");
    }
    
    fclose(saveFile);
}

void LoadGameState(int *playerTurnIndex, int cellCountX, int cellCountY, int **board)
{
    FILE *saveFile = fopen("files/save.txt", "r");
    if (saveFile == NULL)
    {
        printf("save file not found");
        return;
    }
    char fileLine[100];
    int y = -1;
    int value;
    while (fgets(fileLine, 100, saveFile))
    {
        if (y == -1)
        {
            sscanf(fileLine, "%d", &value);

            *playerTurnIndex = (value == 1 || value == 2) ? value : 1;
            y++;
            continue;
        }
        for (int x = 0; x < cellCountX; x++)
        {
            value = (int)fileLine[x] - 48;
            board[y][x] = (value >= 0 && value <= 9) ? value : 0;
        }
        printf("\n");
        y++;
    }

    fclose(saveFile);
}

void ClearGameState(int cellCountX, int cellCountY)
{
    FILE *saveFile = fopen("files/save.txt", "w");
    if (saveFile == NULL)
    {
        printf("save file not found");
        return;
    }
    fprintf(saveFile, "%d\n", 1);
    for (int row = 0; row < cellCountY; row++)
    {
        for (int col = 0; col < cellCountX; col++)
        {
            fprintf(saveFile, "%d", 0);
        }
        fprintf(saveFile, "\n");
    }
    
    fclose(saveFile);
}

#include "../include/game_logic.h"
#include "../include/gui.h"

void SetSettings(char *lable, char *setting)
{
    int value;

    if (StartsWith(lable, "width:"))
    {
        sscanf(setting, "%d", &value);
        printf("set width %d\n", value);

        SetBoardWidth(value);
    }
    if (StartsWith(lable, "height:"))
    {
        sscanf(setting, "%d", &value);
        printf("set height %d\n", value);

        SetBoardHeight(value);
    }
    if (StartsWith(lable, "window width px:"))
    {
        sscanf(setting, "%d", &value);
        printf("window width px %d\n", value);

        SetWindowWidth(value);
    }
    if (StartsWith(lable, "window height px:"))
    {
        sscanf(setting, "%d", &value);
        printf("window height px %d\n", value);

        SetWindowHeight(value);
    }
}

void FileManager_ReadConfigFile()
{
    FILE *file = fopen("files/config.txt", "r");
    if (file == NULL)
    {
        printf("config file not found");
        return;
    }
    char fileLine[100];
    char currentLable[100] = "";
    while (fgets(fileLine, 100, file))
    {
        if (currentLable[0] == '\0')
        {
            strcpy(currentLable, fileLine);
            printf("%s", currentLable);
        }
        else
        {
            SetSettings(currentLable, fileLine);
            strcpy(currentLable, "");
        }
    }
    fclose(file);
}
