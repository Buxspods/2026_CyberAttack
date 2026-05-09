#ifndef INC_2026_CYBERATTACK_POWERUP_H
#define INC_2026_CYBERATTACK_POWERUP_H

#include "EntityTypes.h"
#include "raylib.h"
#include "Player.h"
#define POWERUP_CAP 5

typedef struct {
    EntityType type;
    int size;
    bool active;
    Vector2 position;
}PowerUp;

void InitPowerUp(PowerUp *powerup);
void SpawnPowerUp(PowerUp *powerup, Vector2 position);
void DrawPowerUps(PowerUp powerups[]);
void PickUpPowerUp(PowerUp *powerup, Player *player);
#endif //INC_2026_CYBERATTACK_POWERUP_H
