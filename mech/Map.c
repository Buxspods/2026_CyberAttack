#include "Map.h"

void MoveMap(Map *map, GameState *state) {
    float dt = GetFrameTime();
    float yPos = -GetScreenHeight() + (int)map->offset;

    if (yPos < 0) {
        map->offset += map->speed * dt;
        map->isMoving = true;
    }
    else {
        map->isMoving = false;
    }

    for (int i = 0; i < ENEMY_CAP; i++)
    {
        if (state->enemies[i].type == ENEMY_TURRET)
        {
            state->enemies[i].movementData.restrictions.canMove =
                map->isMoving;
        }
    }

    DrawTexture(map->map, 0, yPos, WHITE);
}