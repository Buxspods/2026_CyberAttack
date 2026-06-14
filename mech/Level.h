#ifndef INC_2026_CYBERATTACK_LEVEL_H
#define INC_2026_CYBERATTACK_LEVEL_H

#include "Wave.h"
#include "../GUI/assets.h"
#include "../GUI/endScreen.h"

#define WAVE_AMOUNT 5
typedef struct {
    EnemyWave waves[WAVE_AMOUNT];
    int level_size;
    //bool isFinished; MORAM DA DODAM OVO SUTRA JER MOZE DA SE DESI DA SE IZMEDJU TALASA ZAUSTAVI LEVEL AKO OVOGA NEMA
} Level;

void StartLevel(Level *level, GameState *gamestate, float *globalTimer);
void isLevelComplete(GameState *state);
void UpdateLevelEnd(GraphicAssets *assets, GameState *state, Level *level);/////////////
#endif //INC_2026_CYBERATTACK_LEVEL_H
