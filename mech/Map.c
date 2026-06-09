#include "Map.h"

void MoveMap(Map *map, GameState *state){
    float dt = GetFrameTime();
    if (map->isMoving){
        map->offset += map->speed * dt;
        if (map->offset >= map->map.height){
            map->doneLoops++;
            if (map->doneLoops >= map->numOfLoops){
                map->isMoving = false;
            }
            else{
                map->offset -= map->map.height;
            }
        }
    }

    for (int i = 0; i < ENEMY_CAP; i++){
        if (state->enemies[i].type == ENEMY_TURRET){
            state->enemies[i].movementData.restrictions.canMove =
                map->isMoving;
        }
    }

    float y = map->offset;

    DrawTexture(map->map, 0, (int)(y - map->map.height), WHITE);
    DrawTexture(map->map, 0, (int)y, WHITE);
}
