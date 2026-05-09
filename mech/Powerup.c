#include "Powerup.h"
#include "GameState.h"
#define POWERUP_CAP 5
#include <stdlib.h>

EntityType ChooseRandomType() {
    EntityType types[3] = {SPEED_POWERUP, HEALTH_POWERUP, AMMO_POWERUP};
    int idx = rand() % 3;
    return types[idx];
}

void InitPowerUp(PowerUp *powerup) {
    //powerup->active = false;
    powerup->type = ChooseRandomType();
    powerup->size = 7;
}
//
void SpawnPowerUp(PowerUp *powerup, Vector2 spawnPos) {
    int doSpawn = rand() % 5; //DA BI BILO 20% SANSE DA SE STVORI NEKI POWERUP
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
                DrawCircleV(powerup.position, powerup.size, SKYBLUE); break;
            case HEALTH_POWERUP:
                DrawCircleV(powerup.position, powerup.size, RED); break;
            case AMMO_POWERUP:
                DrawCircleV(powerup.position, powerup.size, DARKGREEN); break;
            default: break;
        }
    }
}

void PickUpPowerUp(PowerUp *powerup, Player *player) {
    switch (powerup->type) {
        case SPEED_POWERUP:
            //JEDINO MOZDA DA SE DODA DA OVAJ SPEED POWERUP
            //TRAJE NEKO ODREDJENO VREME ALI TO CEMO SE DOGOVORITI
            player->playerSpeed = 750; break;
        case HEALTH_POWERUP:
            player->lives = 10; break;
        case AMMO_POWERUP:
            player->ammo = 100; break;
            default: break;
    }
    powerup->active = false;
}

