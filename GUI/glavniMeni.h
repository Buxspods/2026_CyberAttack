//
// Created by Asus on 6.5.2026..
//

#ifndef INC_2026_CYBERATTACK_GLAVNIMENI_H
#define INC_2026_CYBERATTACK_GLAVNIMENI_H
#define windowWidth 1000
#define windowHeight 1000
#include"raylib.h"

extern Font font_exo;
extern Font font_orbitron;
extern Font press_start_2p;
extern Texture2D background;
typedef void (*MojaFja)();
typedef struct {
    char naziv[20];
    Vector2 pozicija;
    Vector2 dimenzija;
    MojaFja akcija;
}MeniOpcija;
extern MeniOpcija opcije[6];

void StartNewGame();
void LoadGame();
void HighestScores();
void Settings();
void Controls();
void ExitGame();

void CrtajMeni(Vector2 *pozicija, float *vreme, float *providnost);
void InitGlavni();


#endif //INC_2026_CYBERATTACK_GLAVNIMENI_H
