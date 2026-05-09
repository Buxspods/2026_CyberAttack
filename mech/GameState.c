#include "GameState.h"
//
// Created by A1 on 5/6/2026.
//
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
GameState InitGameState() {
    GameState gamestate;
    for (int i=0;i<PROJECTILE_CAP;i++) {
        gamestate.projectiles[i].active=false;
    }
    for (int i=0;i<ENEMY_CAP;i++) {
        gamestate.enemies[i].active=false;
    }
    for (int i=0;i<POWERUP_CAP;i++) {
        gamestate.powerups[i].active=false;
    }

    gamestate.player = InitPlayer(0, (Vector2) {WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 1.25},20,500.0f,3,10, PROJECTILE_CAP);
    return gamestate;
}
