#ifndef INC_2026_CYBERATTACK_MAP_H
#define INC_2026_CYBERATTACK_MAP_H

#include "raylib.h"
#include "GameState.h"

typedef struct{
    Texture2D map;
    float offset;
    float speed;
    bool isMoving;} Map;

void MoveMap(Map *map, GameState *state);

#endif //INC_2026_CYBERATTACK_MAP_H
