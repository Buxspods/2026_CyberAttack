#include "Level.h"


void StartLevel(Level *level, GameState *gamestate, float *globalTimer) {
    for(int i = 0; i < level->level_size; i++) {
        EnemyWave *wave = &level->waves[i];
        if (*globalTimer >= wave->startingMoment) {
            SpawnWave(gamestate, wave, globalTimer);
        }
    }
}
