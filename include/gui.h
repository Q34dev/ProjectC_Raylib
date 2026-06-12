#ifndef GUI_H
#define GUI_H

#include "../src/gui.c"
#include "raylib.h"

void CellGridSetup();
void DrawCell(Vector2 cellPos, int boardVal);
int GetFirstEmptyRowIndex(int columnIndex);

void UpdateDrawFrame();
void GUI_DrawGame();

Vector2 GetCellCount();

void SetWindowWidth(int width);
void SetWindowHeight(int height);

#endif
