#ifndef INC_2026_CYBERATTACK_PAUSEMENI_H
#define INC_2026_CYBERATTACK_PAUSEMENI_H

#include"assets.h"
#include"../mech/Screens.h"
#include"../mech/GameState.h"

extern GameState gamestate;
void ResumeGame(GraphicAssets *assets, int score);
void ExitAndSave(GraphicAssets *assets, int score);

void CrtajPause(GraphicAssets *assets);
void InitPause(GraphicAssets *assets);

#endif //INC_2026_CYBERATTACK_PAUSEMENI_H
