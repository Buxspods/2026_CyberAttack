
#ifndef INC_2026_CYBERATTACK_WAVEMAKER_H
#define INC_2026_CYBERATTACK_WAVEMAKER_H
//#include "../AI/Enemy.h"
#include "gamestate.h"
#include "EnemyWithTime.h"
#define WAVE_SIZE 25

typedef struct {
    EnemyWithTime enemies[WAVE_SIZE];
    float startingMoment;
    int waveSize;
}
EnemyWave;

void SpawnWave(GameState *gamestate, EnemyWave *wave, float *timer);

#endif //INC_2026_CYBERATTACK_WAVEMAKER_H
