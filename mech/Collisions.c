#include "raylib.h"
#include <math.h>
#include <stdlib.h>

#include <stdio.h>
#include "Player.h"
#include "Projectile.h"
#include "EntityTypes.h"
#include "GameState.h"


void CheckCollisions(GameState *gameState) {
    for (int i = 0; i < PROJECTILE_CAP; i++) {
        Projectile *project = &gameState->projectiles[i];
        if (!project->active) {
            continue;
        }

        if (project->entityType == PLAYER_PROJECTILE) {

            for (int j = 0; j < ENEMY_CAP; j++) {
                Enemy *enemy = &gameState->enemies[j];

                if (!enemy->active) {continue;}

                if (CheckCollisionCircles(enemy->position, enemy->size,project->pos, project->size)) {
                    project->active = false;
                }
            }
        }

        if (project->entityType == ENEMY_PROJECTILE) {
            Player *player = &gameState->player;
            if (CheckCollisionCircles(player->playerPos, player->playerSize,project->pos, project->size)) {
                project->active = false;
            }
        }
    }

    for (int i = 0; i < ENEMY_CAP; i++) {
        Player *player = &gameState->player;
        Enemy *enemy = &gameState->enemies[i];
        if (!enemy->active) {continue;}
        if (CheckCollisionCircles(player->playerPos, player->playerSize,enemy->position, enemy->size))
        {
            //MENJACE SE STA SE RADI KADA MARE MACOLA DODA GUI ZA STATS
            enemy->active = false;
        }
    }
}


