// debug.c
#include <stdio.h>
#include "raylib.h"

#include "types.h"

void debug(Ui* ui, App* app)
{
  Vector2 start_hor = {0,GetScreenHeight()/2};
  Vector2 end_hor = {GetScreenWidth(),GetScreenHeight()/2};

  Vector2 start_vert = {GetScreenWidth()/2, 0};
  Vector2 end_vert = {GetScreenWidth()/2, GetScreenHeight()};

  DrawLineEx(start_hor, end_hor, 3, BLACK);
  DrawLineEx(start_vert, end_vert, 3, BLACK);
}
