#include "Level.h"
#include <stdlib.h>
#include<stdio.h>

void StartLevel(Level *level, GameState *gamestate, float *globalTimer) {
    if (gamestate->gameLoaded) {
        for (int i = 0; i < level->level_size; i++)
        {
            EnemyWave *wave = &level->waves[i];
            float waveTimer = *globalTimer - wave->startingMoment;

            if (waveTimer < 0) continue;

            for (int j = 0; j < wave->waveSize; j++){
                if (wave->enemies[j].spawnTime <= waveTimer){
                    wave->enemies[j].spawned = true;
                }
            }
        }
        gamestate->gameLoaded = false;
    }

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

bool AreAllWavesFinished(Level *level){
    for (int i = 0; i < level->level_size; i++){
        EnemyWave *wave = &level->waves[i];

        for (int j = 0; j < wave->waveSize; j++){
            if (!wave->enemies[j].spawned){
                return false;
            }
        }
    }
    return true;
}


void UpdateLevelEnd(GraphicAssets *assets, GameState *gamestate, Level *level){
    if (gamestate->exitingToMenu) return;

    isLevelComplete(gamestate);
    bool allWavesFinished = AreAllWavesFinished(level);

    if ((allWavesFinished && gamestate->gameOver) || gamestate->player.lives <= 0)
    {
        assets->currScore = (int)gamestate->player.score;

        StopMusicStream(assets->level1);
        StopMusicStream(assets->level2);
        StopMusicStream(assets->level3);
        StopMusicStream(assets->mainMenu);

        StopSound(assets->explosion);
        StopSound(assets->powerUp);
        StopSound(assets->laser);
        StopSound(assets->bossLaser);
        StopSound(assets->hit1);
        StopSound(assets->hit2);

        for (int i = 0; i < ENEMY_CAP; i++)
            gamestate->enemies[i].active = false;

        for (int i = 0; i < PROJECTILE_CAP; i++)
            gamestate->projectiles[i].active = false;

        for (int i = 0; i < POWERUP_CAP; i++)
            gamestate->powerups[i].active = false;

        if (gamestate->player.lives > 0) {
            PlaySound(assets->youWon);
            if (assets->currScreen == LEVEL1 && assets->najvisiLevel == LEVEL1) {
                assets->najvisiLevel = LEVEL2;
            }
            else if (assets->currScreen == LEVEL2 && assets->najvisiLevel == LEVEL2) assets->najvisiLevel = LEVEL3;
            assets->fja = DrawYouWonScreen;
        }
        else {
            assets->fja = DrawGameOverScreen;
        }
        assets->currScreen = MAIN_MENU;
    }
}

