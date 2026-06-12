#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "../src/file_manager.c"

void ReadConfigFile();
int StartsWith(const char *str, const char *prefix);

void SetSettings(char *lable, char *setting);

#endif
