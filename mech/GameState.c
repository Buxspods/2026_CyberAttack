#include "GameState.h"
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

    gamestate.globalLevelTimer = 0.0f;/////////
    gamestate.gameOver = false;
    //gamestate.player.lives = 5;
    gamestate.player = InitPlayer(0, (Vector2) {WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 1.25},20,500.0f,3,10, PROJECTILE_CAP);
    return gamestate;
}