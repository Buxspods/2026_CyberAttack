#ifndef INC_2026_CYBERATTACK_ASSETS_H
#define INC_2026_CYBERATTACK_ASSETS_H
#include "raylib.h"
#include "highest-score.h"
#include"assets.h"
struct GraphicAssets;

typedef void (*MojaFja)(struct GraphicAssets *assets, int score);
typedef void (*MojaFja2)(struct GraphicAssets *assets);

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
    Texture2D metak;
    Texture2D powerUpHealth;
    Texture2D powerUpAmmo;
    Texture2D powerUpSpeed;
    Texture2D eksplozija;
    Texture2D background;
    Texture2D srce;
    Texture2D avionLevo, avionDesno, avionPravo;
    Texture2D meele, ranged, turret, finalBoss;
    Texture2D background1, background2, background3;
    Sound gameOver, explosion, powerUp, laser, bossLaser, hit1, hit2;
    Music mainMenu, level1, level2, level3;
    MeniOpcija opcije[6], opcijePause[5];
    Vector2 mis;
    Score *highestScores;
    void (*fja)(struct GraphicAssets *assets, int score);
    void (*prethodnaFja)(struct GraphicAssets *assets, int score);
    void (*fjaPause)(struct GraphicAssets *assets);
    int isPaused;
    int currScore;
} GraphicAssets;




#endif //INC_2026_CYBERATTACK_ASSETS_H
