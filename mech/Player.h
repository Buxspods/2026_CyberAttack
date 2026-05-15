//
// Created by A1 on 5/4/2026.
//

#ifndef INC_2026_CYBERATTACK_PLAYER_H
#define INC_2026_CYBERATTACK_PLAYER_H
#include "raylib.h"
#include "EntityTypes.h"
#include"../GUI/assets.h"
typedef struct GameState GameState;
typedef struct {
    EntityType entityType;
    Vector2 playerPos;
    float playerSize;
    float playerSpeed;
    float score;
    int lives;
    float fireRate;
    int ammo;
    Texture2D texture;
} Player;
Player InitPlayer(float score, Vector2 playerPos, float playerSize, float playerSpeed, int lives, float fireRate, int ammo);
void DrawPlayer(Player player, GraphicAssets *assets);
void UpdatePlayerPosition(Player *player);
void PlayerShootBullet(GameState *state,Player *player);
#endif //INC_2026_CYBERATTACK_PLAYER_H
