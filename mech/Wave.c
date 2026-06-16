#include "gamestate.h"
#include "../AI/Enemy.h"
#include "Wave.h"

void SpawnWave(GameState *gamestate, EnemyWave *wave, float *timer) {
    if (*timer < wave->startingMoment)
        return;

    float waveTimer = *timer - wave->startingMoment;

    for (int i = 0; i < wave->waveSize; i++) {
        EnemyWithTime *enemy = &wave->enemies[i];

        if (waveTimer >= enemy->spawnTime && !enemy->spawned) {
            Enemy *spawnedEnemy = SpawnEnemy(gamestate->enemies, enemy->type, enemy->position, enemy->movementMode, enemy->center);
            if (enemy->type == ENEMY_MELEE_PLANE) {
                spawnedEnemy->movementData.linear.direction = enemy->direction;
            }
            if (enemy->type == ENEMY_RANGED_PLANE) {
                switch (enemy->movementMode) {
                    case LEFT_SINE:
                        spawnedEnemy->movementType = 0;
                        spawnedEnemy->leftOrRight = -1;
                        break;
                    case RIGHT_SINE:
                        spawnedEnemy->movementType = 0;
                        spawnedEnemy->leftOrRight = 1;
                        break;
                    case LEFT_CIRCULAR:
                        spawnedEnemy->movementType = 1;
                        spawnedEnemy->leftOrRight = -1;
                        spawnedEnemy->movementData.circular.center = enemy->center;

                        break;
                    case RIGHT_CIRCULAR:
                        spawnedEnemy->movementType = 1;
                        spawnedEnemy->leftOrRight = 1;
                        spawnedEnemy->movementData.circular.center = enemy->center;
                        break;
                    case LEFT_LINEAR:
                        spawnedEnemy->movementType = 2;
                        spawnedEnemy->leftOrRight = -1;
                        break;
                    case RIGHT_LINEAR:
                        spawnedEnemy->movementType = 2;
                        spawnedEnemy->leftOrRight = 1;
                        break;

                }
            }
            enemy->spawned = true;
        }
    }
}
