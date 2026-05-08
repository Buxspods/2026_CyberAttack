//
// Created by Asus on 6.5.2026..
//

#ifndef INC_2026_CYBERATTACK_GLAVNIMENI_H
#define INC_2026_CYBERATTACK_GLAVNIMENI_H
#define windowWidth 1000
#define windowHeight 1000
#include"assets.h"
#include"highest-score.h"

void StartNewGame(GraphicAssets *assets);
void LoadGame(GraphicAssets *assets);
void HighestScores(GraphicAssets *assets);
void Settings(GraphicAssets *assets);
void Controls(GraphicAssets *assets);
void ExitGame(GraphicAssets *assets);

void CrtajMeni(Vector2 *pozicija,float *vreme, float *providnost, GraphicAssets *assets);
void InitGlavni(GraphicAssets *assets);
void UnloadAssets(GraphicAssets *assets);

#endif //INC_2026_CYBERATTACK_GLAVNIMENI_H
