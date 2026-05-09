//
// Created by A1 on 5/6/2026.
//
#include "../mech/projectile.h"
#include "Enemy.h"

#include <stdio.h>

#include "../mech/GameState.h"
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
void SpawnEnemy(Enemy enemies[],EntityType type,Vector2 position) {
    for (int i=0;i<ENEMY_CAP;i++) {
        if (!enemies[i].active) {
            enemies[i].active = true;
            enemies[i].position = position;
            enemies[i].type = type;
            enemies[i].deathScore = DEFAULT_DEATH_SCORE;
            switch (enemies[i].type) {
                case ENEMY_MELEE_PLANE:InitMeelePlane(&enemies[i]);break;
                case ENEMY_TURRET:InitTurret(&enemies[i]);break;
            }
            break;
        }
    }
}
void InitMeelePlane(Enemy *e) {
    e->HP = 5;//Za sad
    e->maxHP = 5;
    e->speed = 200.0f;
    e->movementDirection = (Vector2){0,-1};
    e->size = 40;
}
void InitTurret(Enemy *e) {
    e->HP = 5;
    e->maxHP = 5;
    e->speed = 0;
    e->size = 20;
    e->actionTimer = 0;
}
void UpdateEnemies(GameState * state) {
    for (int i=0;i<ENEMY_CAP;i++) {
        if (state->enemies[i].active) {
            Decision(&(state->enemies[i]),state);
        }
    }
}
void Decision(Enemy *e,GameState *state) {
    float dt = GetFrameTime();
    switch (e->type) {
        case (ENEMY_MELEE_PLANE): MeelePlaneDecision(e,dt); break;
        case(ENEMY_TURRET):TurretDecision(e,dt,state); break;
    }
}
void MeelePlaneDecision(Enemy *e,float dt) {
    e->position.x += e->speed * dt * e->movementDirection.x;
    e->position.y += e->speed * dt * e->movementDirection.y;//Normalizacija
    if (e->position.x <e->size || e->position.x>WINDOW_WIDTH || e->position.y <e->size || e->position.y>WINDOW_HEIGHT) {
        e->active = false;
    }
}
void TurretDecision(Enemy *e,float dt,GameState * state) {
    e->actionTimer+=dt;
    if (e->actionTimer>1) {
        e->actionTimer =0;
        Shoot(ENEMY_TURRET,state->projectiles,e->position,5,700,state->player.playerPos, &state->player);
    }
}
void DrawEnemies(Enemy enemies[]) {
    for (int i=0;i<ENEMY_CAP;i++) {
        if (enemies[i].active) {
            DrawCircle(enemies[i].position.x,enemies[i].position.y,enemies[i].size, YELLOW);
        }
    }
}

void DestroyEnemy(Enemy *enemy) {
    enemy->active = false;
}