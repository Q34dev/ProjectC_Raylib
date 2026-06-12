#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/game_logic.h"

int StartsWith(const char *str, const char *prefix)
{
    while (*prefix && *str == *prefix)
        ++str, ++prefix;
    return *prefix == 0;
}

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
