//
// Created by A1 on 5/4/2026.
//
#include "Player.h"
#include <math.h>
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

Player InitPlayer(Vector2 playerPos, float playerSize, float playerSpeed, int lives, float fireRate) {
    Player player = {0};
    player.entityType = PLAYER;
    player.playerPos = playerPos;
    player.playerSpeed = 500.0f;
    player.playerSize = 20;
    player.lives = 3;
    player.fireRate=10;
    return player;
}
void DrawPlayer(Player player) {
    DrawCircleV(player.playerPos, player.playerSize, WHITE);
}
void UpdatePlayerPosition(Player *player) {
    float dt = GetFrameTime(); //delta time potreban da bi na svakom kompu igra isla istom brzinom
    Vector2 movement = {0, 0}; //vektor koji nam govori u kom smeru i pravcu se krece igrac

    //offset pozicije igraca sa vodjenjem racuna o granicama prozora
    if (IsKeyDown(KEY_D)) movement.x += player->playerPos.x < WINDOW_WIDTH - player->playerSize? 1 : 0;
    if (IsKeyDown(KEY_A)) movement.x -= player->playerPos.x > player->playerSize? 1 : 0;
    if (IsKeyDown(KEY_W)) movement.y -= player->playerPos.y > player->playerSize? 1 : 0;
    if (IsKeyDown(KEY_S)) movement.y += player->playerPos.y < WINDOW_HEIGHT - player->playerSize? 1 : 0;


    if (movement.x != 0 || movement.y != 0) {
        float le = sqrtf(movement.x * movement.x + movement.y * movement.y);
        movement.x /= le;
        movement.y /= le; //le znaci length kao duzina
    }

    player->playerPos.x += movement.x * dt * player->playerSpeed;
    player->playerPos.y += movement.y * dt * player->playerSpeed;
}