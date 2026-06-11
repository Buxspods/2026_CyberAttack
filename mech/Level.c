#include "Level.h"
#include <stdlib.h>

void StartLevel(Level *level, GameState *gamestate, float *globalTimer) {
    for(int i = 0; i < level->level_size; i++) {
        EnemyWave *wave = &level->waves[i];
        if (*globalTimer >= wave->startingMoment) {
            SpawnWave(gamestate, wave, globalTimer);
        }
    }
}

void isLevelComplete(GameState *state) {
    for (int i = 0; i < ENEMY_CAP; i++) {
        if (state->enemies[i].active) {
            state->gameOver = false;
            return;
        }
    }
    state->gameOver = true;
}

void UpdateLevelEnd(GraphicAssets *assets, GameState *gamestate) {
    isLevelComplete(gamestate);
    if ((gamestate->globalLevelTimer > 5.0f && gamestate->gameOver) || gamestate->player.lives <= 0) {
        assets->currScore = (int)gamestate->player.score;
        //DrawGameOverScreen(assets, (int)gamestate->player.score);
        StopMusicStream(assets->level1); //gasenje svih zvukova
        StopMusicStream(assets->level2);
        StopMusicStream(assets->level3);
        StopMusicStream(assets->mainMenu);
        StopSound(assets->explosion);
        StopSound(assets->powerUp);
        StopSound(assets->laser);
        StopSound(assets->bossLaser);
        StopSound(assets->hit1);
        StopSound(assets->hit2);
        for (int i = 0; i < ENEMY_CAP; i++) { //gasenje svega sto se nalazilo na mapi
            gamestate->enemies[i].active = false;
        }
        for (int i = 0; i < PROJECTILE_CAP; i++) {
            gamestate->projectiles[i].active = false;
        }
        for (int i = 0; i < POWERUP_CAP; i++) {
            gamestate->powerups[i].active = false;
        }

        assets->fja = DrawGameOverScreen;
        assets->currScreen = MAIN_MENU;
        PlayMusicStream(assets->mainMenu);
    }
}


