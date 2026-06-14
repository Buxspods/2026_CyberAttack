#include "loadGame.h"
#include"assets.h"
#include"../mech/GameState.h"
#include<stdio.h>
#include<stdlib.h>
#include"../AI/Enemy.h"
#include"../AI/EnemyActions.h"

int FunctionID(EnemyUpdateFunc func) {
    if (func == NULL) return UPDATE_NONE;
    if (func == LinearMovement) return FUNC_LINEAR_MOVEMENT;
    if (func == CircularMovement) return FUNC_CIRCULAR_MOVEMENT;
    if (func == SineMovement) return FUNC_SINE_MOVEMENT;
    if (func == LinearShot) return FUNC_LINEAR_SHOT;
    if (func == ShotgunShot) return FUNC_SHOTGUN_SHOT;
    if (func == PlayerShotLinear) return FUNC_PLAYER_SHOT_LINEAR;
    if (func == BossPhase1) return FUNC_BOSS_PHASE1;

    return UPDATE_NONE;
}

EnemyUpdateFunc FunctionFromID(int id) {
    switch (id) {
        case FUNC_LINEAR_MOVEMENT: return LinearMovement;
        case FUNC_CIRCULAR_MOVEMENT: return CircularMovement;
        case FUNC_SINE_MOVEMENT: return SineMovement;
        case FUNC_LINEAR_SHOT: return LinearShot;
        case FUNC_SHOTGUN_SHOT: return ShotgunShot;
        case FUNC_PLAYER_SHOT_LINEAR: return PlayerShotLinear;
        case FUNC_BOSS_PHASE1: return BossPhase1;
        default: return NULL;
    }
}

bool SaveGame(const char* filename) {
    FILE *f = fopen(TextFormat("savedGames/%s", filename), "wb");
    if (f == NULL) {
        printf("Greska pri otvaranju fajla za upis!\n");
        return false;
    }

    int screenInt = (int)assets.currLevel;
    fwrite(&screenInt, sizeof(int), 1, f);
    fwrite(&gamestate.globalLevelTimer, sizeof(float), 1, f);

    fwrite(&gamestate.player.playerPos, sizeof(Vector2), 1, f);
    fwrite(&gamestate.player.score, sizeof(float), 1, f);
    fwrite(&gamestate.player.lives, sizeof(int), 1, f);
    fwrite(&gamestate.player.ammo, sizeof(int), 1, f);

    int playerType = (int)gamestate.player.entityType;
    fwrite(&playerType, sizeof(int), 1, f);

    for (int i = 0; i < ENEMY_CAP; i++) {
        fwrite(&gamestate.enemies[i], sizeof(Enemy), 1, f);

        for (int j = 0; j < MAX_ACTIONS; j++) {
            int functionID = FunctionID(gamestate.enemies[i].actions[j].update);
            fwrite(&functionID, sizeof(int), 1, f);
        }
    }

    fclose(f);
    return true;
}

bool LoadGame2(const char* filename) {
    FILE* file = fopen(TextFormat("savedGames/%s", filename), "rb");
    if (file == NULL) {
        printf("Fajl za ucitavanje ne postoji!\n");
        return false;
    }

    int screenInt;
    fread(&screenInt, sizeof(int), 1, file);
    assets.currLevel = (SCREEN)screenInt;
    assets.currScreen = (SCREEN)screenInt;
    fread(&gamestate.globalLevelTimer, sizeof(float), 1, file);

    fread(&gamestate.player.playerPos, sizeof(Vector2), 1, file);
    fread(&gamestate.player.score, sizeof(float), 1, file);
    fread(&gamestate.player.lives, sizeof(int), 1, file);
    fread(&gamestate.player.ammo, sizeof(int), 1, file);

    int playerType;
    fread(&playerType, sizeof(int), 1, file);
    gamestate.player.entityType = (EntityType)playerType;

    gamestate.gameOver = false;

    for (int i = 0; i < ENEMY_CAP; i++) {
        fread(&gamestate.enemies[i], sizeof(Enemy), 1, file);

        for (int j = 0; j < MAX_ACTIONS; j++) {
            int funcID;
            fread(&funcID, sizeof(int), 1, file);
            gamestate.enemies[i].actions[j].update = FunctionFromID(funcID);
        }
    }
    gamestate.gameLoaded = true;

    fclose(file);
    return true;
}