
#ifndef INC_2026_CYBERATTACK_WAVEMAKER_H
#define INC_2026_CYBERATTACK_WAVEMAKER_H
//#include "../AI/Enemy.h"
#include "gamestate.h"

typedef struct {
    EntityType enemies[ENEMY_CAP];
}
EnemyWave;


void SpawnWave();

#endif //INC_2026_CYBERATTACK_WAVEMAKER_H
