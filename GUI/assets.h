#ifndef INC_2026_CYBERATTACK_ASSETS_H
#define INC_2026_CYBERATTACK_ASSETS_H
#include "raylib.h"
#include "highest-score.h"
#include"assets.h"
#include"../mech/Map.h"
#include"../mech/Screens.h"
#define EXPLOSION_CAP 100

struct GraphicAssets;

typedef void (*MojaFja)(struct GraphicAssets *assets, int score);
typedef void (*MojaFja2)(struct GraphicAssets *assets);

typedef struct {
    bool active;
    Vector2 pozicija;
    int currentFrame;
    float timer;
}Explosion;

typedef struct {
    char naziv[20];
    Vector2 pozicija;
    Vector2 dimenzija;
    MojaFja akcija;
} MeniOpcija;

typedef enum {
    ACTION_UP,
    ACTION_DOWN,
    ACTION_LEFT,
    ACTION_RIGHT,
    ACTION_SHOOT,
    ACTION_DASH,
    ACTION_PAUSE
} ActionID;

typedef struct GraphicAssets {
    Font fontExo;
    Font fontOrbitron;
    Font fontCommando;
    Texture2D metak;
    Texture2D powerUpHealth;
    Texture2D powerUpAmmo;
    Texture2D powerUpSpeed;
    Texture2D powerUpSuperAmmo;
    Texture2D eksplozija;
    Texture2D background;
    Texture2D srce, orangeSrce;
    Texture2D avionLevo, avionDesno, avionPravo;
    Texture2D meele, ranged, turret, finalBoss;
    Texture2D background1, background2, background3;
    Texture2D metakBoss, laserBoss1, laserBoss2;
    Texture2D planeGameOver, planeYouWon;
    Sound gameOver, explosion, powerUp, laser, bossLaser, hit1, hit2, click, hover, youWon;
    Music mainMenu, level1, level2, level3;
    SCREEN najvisiLevel;
    float music, sfx;
    MeniOpcija opcije[6], opcijePause[5];
    KeyboardKey keys[7];
    Vector2 mis;
    Score *highestScores;
    Map level1Map;// = {assets.background1, map1Offset, map1Offset,  map1Speed, true, 3, 0};
    Map level2Map;// = {assets.background2, map2Offset, map1Offset, map2Speed, true, 3, 0};
    Map level3Map;// = {assets.background3, map3Offset, map1Offset,map3Speed, true, 5, 0};
    SCREEN currScreen;
    SCREEN currLevel;
    bool odbrojavanje;
    float timer;
    Explosion eksplozije[EXPLOSION_CAP];

    void (*fja)(struct GraphicAssets *assets, int score);
    void (*prethodnaFja)(struct GraphicAssets *assets, int score);
    void (*fjaPause)(struct GraphicAssets *assets);
    int isPaused;
    int currScore;
} GraphicAssets;

#endif //INC_2026_CYBERATTACK_ASSETS_H
