#ifndef INC_2026_CYBERATTACK_ASSETS_H
#define INC_2026_CYBERATTACK_ASSETS_H
#include "raylib.h"
#include "highest-score.h"
//#include"assets.h"
struct GraphicAssets;

typedef void (*MojaFja)(struct GraphicAssets *assets);

typedef struct {
    char naziv[20];
    Vector2 pozicija;
    Vector2 dimenzija;
    MojaFja akcija;
} MeniOpcija;

typedef struct GraphicAssets {
    Font fontExo;
    Font fontOrbitron;
    Font fontCommando;
    Texture2D eksplozija;
    Texture2D metak;
    Texture2D powerUpHealth;
    Texture2D powerUpAmmo;
    Texture2D powerUpSpeed;
    Texture2D background;
    Texture2D srce;
    Texture2D avionLevo, avionDesno, avionPravo;
    MeniOpcija opcije[6], opcijePause[5];
    Vector2 mis;
    Score *highestScores;
    void (*fja)(struct GraphicAssets *assets);
    int isPaused;
} GraphicAssets;


#endif //INC_2026_CYBERATTACK_ASSETS_H
