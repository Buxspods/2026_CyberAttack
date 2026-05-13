//
// Created by A1 on 5/12/2026.
//

#ifndef INC_2026_CYBERATTACK_ENEMYACTIONS_H
#define INC_2026_CYBERATTACK_ENEMYACTIONS_H
#include "Enemy.h"
//Enemy update Functions
void LinearMovement(Enemy *e,GameState *state, float dt);
void CircularMovement(Enemy *e, GameState *state, float dt);
void SineMovement(Enemy *e,GameState *state, float dt);
void LinearShot(Enemy *e,GameState *state, float dt);
void ShotgunShot(Enemy *e,GameState *state, float dt);
#endif //INC_2026_CYBERATTACK_ENEMYACTIONS_H
