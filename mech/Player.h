//
// Created by A1 on 5/4/2026.
//

#ifndef INC_2026_CYBERATTACK_PLAYER_H
#define INC_2026_CYBERATTACK_PLAYER_H
#include "raylib.h"
#include "EntityTypes.h"
typedef struct GameState GameState;
typedef struct {
    EntityType entityType;
    Vector2 playerPos;
    Vector2 mvmntVect;
    float playerSize;
    float playerSpeed;
    bool isDashing;
    bool canDash;
    float dashSpeed;
    float dashTimer;
    float dashCooldown;
    float speedPowerUpTimer;
    float score;
    int lives;
    float fireRate;
    int ammo;
    Texture2D texture;
    bool isInvincible;
    float invincibilityTimer;
    float shotgunTimer;
} Player;
Player InitPlayer(float score, Vector2 playerPos, float playerSize, float playerSpeed, int lives, float fireRate, int ammo);
//void DrawPlayer(Player player, GraphicAssets *assets);
void UpdatePlayerPosition(Player *player);
void PlayerShootBullet(GameState *state,Player *player);
void UpdateShootingMode(Player *player, float tick);
void SetInvincibility(Player *player, bool mode);
void UpdateInvincibility(Player *player, float tick, float time);
void SetDash(Player *player, bool mode);
void UpdateDash(Player *player, float tick, float time, Vector2 dash);
void UpdateSpeed(Player *player, float tick);
#endif //INC_2026_CYBERATTACK_PLAYER_H
