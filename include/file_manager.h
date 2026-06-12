#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "../src/file_manager.c"

int StartsWith(const char *str, const char *prefix);
void SetSettings(char *lable, char *setting);
void FileManager_ReadConfigFile();
void LoadGame(int *playerTurnIndex, int cellCountX, int cellCountY, int **board);
void SaveGame(int playerTurnIndex, int cellCountX, int cellCountY, int **board);
void IsBoardEmpty(int cellCountX, int cellCountY, int **board);
#endif
