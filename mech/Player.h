//
// Created by A1 on 5/4/2026.
//

#ifndef INC_2026_CYBERATTACK_PLAYER_H
#define INC_2026_CYBERATTACK_PLAYER_H
#include "raylib.h"

typedef struct {
    Vector2 playerPos;
    float playerSize;
    float playerSpeed;
    int lives;
    float fireRate;
    Texture2D texture;
} Player;
Player InitPlayer(Vector2 playerPos, float playerSize, float playerSpeed, int lives, float fireRate);
void DrawPlayer(Player player);
void UpdatePlayerPosition(Player *player);
#endif //INC_2026_CYBERATTACK_PLAYER_H
