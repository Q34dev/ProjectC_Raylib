#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "../src/file_manager.c"

int StartsWith(const char *str, const char *prefix);
void SaveGameState(int playerTurnIndex, int cellCountX, int cellCountY, int **board);
void LoadGameState(int *playerTurnIndex, int cellCountX, int cellCountY, int **board);
void ClearGameState(int cellCountX, int cellCountY);

void SetSettings(char *lable, char *setting);
void FileManager_ReadConfigFile();

#endif
