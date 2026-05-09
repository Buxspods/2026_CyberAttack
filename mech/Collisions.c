#include "raylib.h"
#include "Player.h"
#include "Projectile.h"
#include "PowerUp.h"
#include "EntityTypes.h"
#include "GameState.h"

void CheckCollisions(GameState *gameState) {
    Player *player = &gameState->player;

    for (int i = 0; i < PROJECTILE_CAP; i++) {
        Projectile *project = &gameState->projectiles[i];
        if (!project->active) {
            continue;
        }
        if (project->entityType == PLAYER_PROJECTILE) { //ENEMY/PLAYER BULLET COLLISION

            for (int j = 0; j < ENEMY_CAP; j++) {
                Enemy *enemy = &gameState->enemies[j];

                if (!enemy->active) {continue;}

                if (CheckCollisionCircles(enemy->position, enemy->size,project->pos, project->size)) {
                    project->active = false;
                    enemy->HP--;
                    if (enemy->HP <= 0) { //ako negativac umre
                        gameState->player.score += enemy->deathScore;
                        for (int k = 0; k < POWERUP_CAP; k++) {
                            PowerUp *powerup = &gameState->powerups[k];

                            if (!powerup->active) {
                                SpawnPowerUp(powerup, enemy->position);
                                break;
                            }
                        }
                        DestroyEnemy(enemy);
                    }
                }
            }
        }

        if (project->entityType == ENEMY_PROJECTILE) {//PLAYER/ENEMY BULLET COLIISION
            //Player *player = &gameState->player;
            if (CheckCollisionCircles(player->playerPos, player->playerSize,project->pos, project->size)) {
                project->active = false;
                player->lives--;
                if (player->lives <= 0) {
                    //MARE MACOLA MORA DA MI DODA SCREEN ZA SMRT
                }
            }
        }
    }

    for (int i = 0; i < ENEMY_CAP; i++) { //ENEMY/PLAYER COLLISION
        //Player *player = &gameState->player;
        Enemy *enemy = &gameState->enemies[i];
        if (!enemy->active) {continue;}
        if (CheckCollisionCircles(player->playerPos, player->playerSize,enemy->position, enemy->size))
        {
            for (int k = 0; k < POWERUP_CAP; k++) {
                PowerUp *powerup = &gameState->powerups[k];

                if (!powerup->active) {
                    SpawnPowerUp(powerup, enemy->position);
                    break;
                }
            }
            gameState->player.score += enemy->deathScore;
            DestroyEnemy(enemy);
            player->lives -= enemy->HP;
        }
    }

    for (int i = 0; i < POWERUP_CAP; i++) {
        PowerUp *powerup = &gameState->powerups[i];
        if (CheckCollisionCircles(player->playerPos, player->playerSize,powerup->position, powerup->size)) {
            PickUpPowerUp(powerup, player);
        }
    }
}