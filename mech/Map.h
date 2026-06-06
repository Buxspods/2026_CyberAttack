#ifndef INC_2026_CYBERATTACK_MAP_H
#define INC_2026_CYBERATTACK_MAP_H

#include "raylib.h"


typedef struct{
    Texture2D map;
    float offset;
    float speed;} Map;

void MoveMap(Map *map);

#endif //INC_2026_CYBERATTACK_MAP_H
