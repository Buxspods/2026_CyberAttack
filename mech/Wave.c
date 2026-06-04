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
            SpawnEnemy(gamestate->enemies, enemy->type, enemy->position);
            enemy->spawned = true;
        }
    }
}
