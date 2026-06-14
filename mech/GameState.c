#include "GameState.h"

#include <stddef.h>
#include <stdio.h>

#include "raymath.h"
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
GameState InitGameState() {
    GameState gamestate;
    for (int i=0;i<PROJECTILE_CAP;i++) {
        gamestate.projectiles[i].active=false;
    }
    for (int i=0;i<ENEMY_CAP;i++) {
        gamestate.enemies[i].active=false;
    }
    for (int i=0;i<POWERUP_CAP;i++) {
        gamestate.powerups[i].active=false;
    }

    gamestate.globalLevelTimer = 0.0f;/////////
    gamestate.gameOver = false;
    gamestate.gameLoaded = false;

    //gamestate.player.lives = 5;
    gamestate.player = InitPlayer(0, (Vector2) {WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 1.25},20,500.0f,3,10, PROJECTILE_CAP);
    return gamestate;
}
Vector2 AutoMove(GameState *state) {
    Vector2 movementDirection = {0, 0};
    bool evading = false;

    for (int i = 0; i < PROJECTILE_CAP; i++) {
        if (!state->projectiles[i].active) continue;

        Vector2 playerPosition = state->player.playerPos;
        Vector2 projectilePosition = state->projectiles[i].pos;
        float dist = Vector2Distance(playerPosition, projectilePosition);

        if (dist < 100.0f && state->projectiles[i].entityType != PLAYER_PROJECTILE) {
            Vector2 toPlayer = Vector2Subtract(playerPosition, projectilePosition);

            if (fabsf(Vector2Angle(toPlayer, state->projectiles[i].direction)) < (PI / 18.0f)) {
                evading = true;
                Vector2 normal1 = {-state->projectiles[i].direction.y, state->projectiles[i].direction.x};
                Vector2 normal2 = {state->projectiles[i].direction.y, -state->projectiles[i].direction.x};

                if (Vector2DotProduct(toPlayer, normal1) > 0) {
                    movementDirection = Vector2Add(movementDirection, Vector2Normalize(normal1));
                } else {
                    movementDirection = Vector2Add(movementDirection, Vector2Normalize(normal2));
                }
                break;
            }
        }
    }

    if (evading) return Vector2Normalize(movementDirection);

    Enemy *closest_enemy = NULL;
    float closest_distance = 100000.0f;

    for (int i = 0; i < ENEMY_CAP; i++) {
        if (state->enemies[i].active) {
            float d = Vector2Distance(state->player.playerPos, state->enemies[i].position);
            if (!closest_enemy || d < closest_distance) {
                closest_distance = d;
                closest_enemy = &state->enemies[i];
            }
        }
    }

    if (!closest_enemy) return (Vector2){0, 0};

    // Keep position 150 pixels below the target enemy
    Vector2 desiredPos = { closest_enemy->position.x, closest_enemy->position.y + 200.0f };
    Vector2 toDesired = Vector2Subtract(desiredPos, state->player.playerPos);

    if (Vector2Length(toDesired) > 5.0f) {
        movementDirection = Vector2Normalize(toDesired);
    }
    return movementDirection;
}

bool ShootDecision(GameState *state) {
    for (int i = 0; i < ENEMY_CAP; i++) {
        // Added fabsf to prevent negative coordinate false-positives
        if (state->enemies[i].active && fabsf(state->enemies[i].position.x - state->player.playerPos.x) < 50.0f) {
            return true;
        }
    }
    return false;
}

void AutoRegimePlayerUpdate(GameState *state, bool *shouldShoot) {
    state->player.mvmntVect = AutoMove(state);
    *shouldShoot = ShootDecision(state);
}