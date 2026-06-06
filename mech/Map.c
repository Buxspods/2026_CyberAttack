#include "Map.h"

void MoveMap(Map *map) {
    float dt = GetFrameTime();
    float yPos = -GetScreenHeight() + (int)map->offset;

    if (yPos < 0) map->offset += map->speed * dt;

    DrawTexture(map->map, 0, yPos, WHITE);
}