#include "GameState.h"
#include"../GUI/assets.h"
#include <math.h>
#include <stddef.h>

#include "raymath.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

extern GameState gamestate;

Player InitPlayer(float score, Vector2 playerPos, float playerSize, float playerSpeed, int lives, float fireRate, int ammo) {
    Player player = {0};
    player.entityType = PLAYER;
    player.playerPos = playerPos;
    player.playerSpeed = 500.0f;
    player.isDashing = false;
    player.canDash = true;
    player.dashSpeed = 2500.0f;
    player.dashTimer = 0;
    player.dashCooldown = 3.0f;
    player.playerSize = 20;
    player.lives = 5;
    player.fireRate = 10;
    player.ammo = ammo;
    player.score = 0;
    player.isInvincible = false;
    player.invincibilityTimer = 0;
    player.speedPowerUpTimer = 0;
    player.shotgunTimer = 0;
    return player;
}
/*void DrawPlayer(Player player, GraphicAssets *assets) {
    //DrawCircleV(player.playerPos, player.playerSize, WHITE);
    Vector2 pos = (Vector2){player.playerPos.x, player.playerPos.y - 1.5 * player.playerSize};
    DrawPlaneGUI(&pos, assets);
}*/
void UpdatePlayerPosition(Player *player) {
    float dt = GetFrameTime(); //delta time potreban da bi na svakom kompu igra isla istom brzinom
    Vector2 movement = {0, 0}; //vektor koji nam govori u kom smeru i pravcu se krece igrac

    //offset pozicije igraca sa vodjenjem racuna o granicama prozora
    if (IsKeyDown(gamestate.keys[ACTION_RIGHT])) movement.x += player->playerPos.x < WINDOW_WIDTH - player->playerSize? 1 : 0;
    if (IsKeyDown(gamestate.keys[ACTION_LEFT])) movement.x -= player->playerPos.x > player->playerSize? 1 : 0;
    if (IsKeyDown(gamestate.keys[ACTION_UP])) movement.y -= player->playerPos.y > player->playerSize? 1 : 0;
    if (IsKeyDown(gamestate.keys[ACTION_DOWN])) movement.y += player->playerPos.y < WINDOW_HEIGHT - player->playerSize? 1 : 0;

    if (movement.x != 0 || movement.y != 0) {
        float le = sqrtf(movement.x * movement.x + movement.y * movement.y);
        movement.x /= le;
        movement.y /= le; //le znaci length kao duzina
    }
    if (IsKeyDown(gamestate.keys[ACTION_DASH]) && player->canDash) {
        SetDash(player,true);
        player-> canDash = false;
    }
    else if (!player->canDash) {
        player->dashTimer += dt;
        if (player->dashTimer >= player->dashCooldown) {
            player-> canDash = true;
            player->dashTimer = 0;
        }
    }

    player->mvmntVect = movement;
    player->playerPos.x += movement.x * dt * player->playerSpeed;
    player->playerPos.y += movement.y * dt * player->playerSpeed;
}

void PlayerShootBullet(GameState *state, Player *player) {
    if (player->shotgunTimer <= 0.0f) {
        player->shotgunTimer = 0.0f;
        InitProjectile(state->projectiles,PLAYER_PROJECTILE,state->player.playerPos,(Vector2){0,-1},700,5);
    }
    else {
        InitProjectile(state->projectiles,PLAYER_PROJECTILE,state->player.playerPos,(Vector2){-0.25f,-1},700,5);
        InitProjectile(state->projectiles,PLAYER_PROJECTILE,state->player.playerPos,(Vector2){0,-1},700,5);
        InitProjectile(state->projectiles,PLAYER_PROJECTILE,state->player.playerPos,(Vector2){0.25f,-1},700,5);
        InitProjectile(state->projectiles,PLAYER_PROJECTILE,state->player.playerPos,(Vector2){-0.125f,-1},700,5);
        InitProjectile(state->projectiles,PLAYER_PROJECTILE,state->player.playerPos,(Vector2){0.125f,-1},700,5);
    }
    player->ammo--;
}

void UpdateShootingMode(Player *player, float tick) {
    if (player->shotgunTimer > 0.0f) {
        player->shotgunTimer -= tick;
    }
    else {
        player->shotgunTimer = 0;
    }
}


void SetInvincibility(Player *player, bool mode) {
    player->isInvincible = mode;
    player->invincibilityTimer = 0;
}

void UpdateInvincibility(Player *player, float tick, float time) {
    if (player->isInvincible) {
        player-> invincibilityTimer += tick;
        if (player->invincibilityTimer >= time) {
            player->invincibilityTimer = 0;
            SetInvincibility(player,false);
        }
    }
}

void SetDash(Player *player, bool mode) {
    player->isDashing = mode;
    player->dashTimer = 0;
}

void UpdateDash(Player *player, float tick, float time, Vector2 dash) {
    if (player->isDashing) {
        player-> canDash = false;
        player-> dashTimer += tick;
        player->playerPos.x += dash.x * player-> dashSpeed * tick;
        player->playerPos.y += dash.y * player-> dashSpeed * tick;
        if (player->dashTimer >= time) {
            player->dashTimer = 0;
            SetDash(player,false);
        }
    }
}

/// Funkcija koja izvrsava efekat speed powerup-a
/// @param player igrac
/// @param tick Uglavnom dt
void UpdateSpeed(Player *player, float tick) {
    if (player->speedPowerUpTimer > 0.0f) {
        player->playerSpeed = 1000;
        player->speedPowerUpTimer -= tick;
    }
    else {
        player->speedPowerUpTimer = 0;
        player->playerSpeed = 500;
        }
}