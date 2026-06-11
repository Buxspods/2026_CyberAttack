#include "Powerup.h"
#include "GameState.h"
#define POWERUP_CAP 5
#include <stdlib.h>
#include"../GUI/assets.h"
#include"../GUI/planeGUI.h"

extern GraphicAssets assets;

EntityType ChooseRandomType() {
    EntityType types[3] = {SPEED_POWERUP, HEALTH_POWERUP, AMMO_POWERUP};
    int idx = 0;//rand() % 3;
    return types[idx];
}

void InitPowerUp(PowerUp *powerup) {
    //powerup->active = false;
    powerup->type = ChooseRandomType();
    powerup->size = 20;
}
//
void SpawnPowerUp(PowerUp *powerup, Vector2 spawnPos) {
    int doSpawn = 0;//rand() % 5; //DA BI BILO 20% SANSE DA SE STVORI NEKI POWERUP
    if (doSpawn == 0) {
        if (!powerup->active) {
            powerup->active = true;
            powerup->position = spawnPos;
            InitPowerUp(powerup);
        }
    }
}

void DrawPowerUps(PowerUp powerups[]) {
    for (int i = 0; i < POWERUP_CAP; i++) {
        PowerUp powerup = powerups[i];
        if (!powerup.active) continue;

        switch (powerup.type) {
            case SPEED_POWERUP:
                DrawCircleV(powerup.position, powerup.size, (Color){1,1,1,0});
                DrawPowerUp(assets.powerUpSpeed, powerup.position);
                break;
            case HEALTH_POWERUP:
                DrawCircleV(powerup.position, powerup.size, RED);
                DrawPowerUp(assets.powerUpHealth, powerup.position);
                break;
            case AMMO_POWERUP:
                DrawCircleV(powerup.position, powerup.size, DARKGREEN);
                DrawPowerUp(assets.powerUpAmmo, powerup.position);
                break;
            default: break;
        }
    }
}

void PickUpPowerUp(PowerUp *powerup, Player *player) {
    PlaySound(assets.powerUp);
    switch (powerup->type) {
        case SPEED_POWERUP:
            player->speedPowerUpTimer += 5; break;
        case HEALTH_POWERUP:
            player->lives = 10; break;
        case AMMO_POWERUP:
            player->ammo += 100; break;
            default: break;
    }
    powerup->active = false;
}

