#ifndef INC_2026_CYBERATTACK_LEVEL_H
#define INC_2026_CYBERATTACK_LEVEL_H

#include "Wave.h"
#define WAVE_AMOUNT 5
typedef struct {
    EnemyWave waves[WAVE_AMOUNT];
    int level_size;
} Level;

void StartLevel(Level *level, GameState *gamestate, float *globalTimer);

bool isLevelComplete(GameState *state);

#endif //INC_2026_CYBERATTACK_LEVEL_H
