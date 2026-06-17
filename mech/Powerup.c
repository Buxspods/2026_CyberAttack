#include "Powerup.h"
#include "GameState.h"
#define POWERUP_CAP 5
#include <stdlib.h>
#include"../GUI/assets.h"
#include"../GUI/planeGUI.h"

extern GraphicAssets assets;

EntityType ChooseRandomType() {
    EntityType types[4] = {SPEED_POWERUP, HEALTH_POWERUP, AMMO_POWERUP, SPECIAL_AMMO_POWERUP };
    int idx = rand() % 4;
    return types[idx];
}

void InitPowerUp(PowerUp *powerup) {
    //powerup->active = false;
    powerup->type = ChooseRandomType();
    powerup->size = 20;
    powerup->offset = 0;
}
//
void SpawnPowerUp(PowerUp *powerup, Vector2 spawnPos) {
    int doSpawn = rand() % 4;
    if (doSpawn == 0) {
        if (!powerup->active) {
            powerup->active = true;
            powerup->position = spawnPos;
            InitPowerUp(powerup);
        }
    }
}

void DrawPowerUps(PowerUp powerups[], float mapSpeed, float dt, bool move) {
    for (int i = 0; i < POWERUP_CAP; i++) {
        PowerUp *powerup = &powerups[i];
        if (!powerup->active) continue;

        if (move) powerup->position.y += mapSpeed * dt;///////////

        switch (powerup->type) {
            case SPEED_POWERUP:
                DrawCircleV(powerup->position, powerup->size, (Color){1,1,1,0});
                DrawPowerUp(assets.powerUpSpeed, powerup->position);
                break;
            case HEALTH_POWERUP:
                DrawCircleV(powerup->position, powerup->size, (Color){1,1,1,0});
                DrawPowerUp(assets.powerUpHealth, powerup->position);
                break;
            case AMMO_POWERUP:
                DrawCircleV(powerup->position, powerup->size, (Color){1,1,1,0});
                DrawPowerUp(assets.powerUpAmmo, powerup->position);
                break;
            case SPECIAL_AMMO_POWERUP:
                DrawCircleV(powerup->position, powerup->size, (Color){1,1,1,0});
                DrawPowerUp(assets.powerUpSuperAmmo, powerup->position);
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
        case SPECIAL_AMMO_POWERUP:
            player->shotgunTimer += 5; break;
            default: break;
    }
    powerup->active = false;
}

void MovePowerUps() {

}


