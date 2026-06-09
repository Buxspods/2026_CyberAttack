//
// Created by Asus on 6.5.2026..
//

#ifndef INC_2026_CYBERATTACK_GLAVNIMENI_H
#define INC_2026_CYBERATTACK_GLAVNIMENI_H
#define windowWidth 1000
#define windowHeight 1000
#include"assets.h"
#include"../mech/GameState.h"
#include"../mech/Level.h"


extern GameState gamestate;
void ResetLevel(Level *level);
const char* keyString(int keyID);
void StartNewGame(GraphicAssets *assets, int score);
void LoadGame(GraphicAssets *assets, int score);
void HighestScores(GraphicAssets *assets, int score);
void Settings(GraphicAssets *assets, int score);
void Guide(GraphicAssets *assets, int score);
void ExitGame(GraphicAssets *assets, int score);

void CrtajMeni(Vector2 *pozicija,float *vreme, float *providnost, GraphicAssets *assets);
void InitGlavni(GraphicAssets *assets);
void UnloadAssets(GraphicAssets *assets);


#endif //INC_2026_CYBERATTACK_GLAVNIMENI_H
