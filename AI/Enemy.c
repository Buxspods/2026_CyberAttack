//
// Created by A1 on 5/6/2026.
//
#include "../mech/projectile.h"
#include "Enemy.h"
#include"EnemyActions.h"
#include <stdio.h>
#include <stdlib.h>

#include "raymath.h"

#include "../mech/GameState.h"
#include "EnemyActions.h"
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
                case ENEMY_RANGED_PLANE:InitRangedPlane(&enemies[i]);break;
                case BOSS:InitBoss(&enemies[i]);break;
            }
            break;
        }
    }
}
Action InitAction(EnemyUpdateFunc f,float timer) {
    Action res;
    res.update = f;
    res.actionTimer = timer;
    res.currentTime=0;
    return res;
}
void InitMeelePlane(Enemy *e) {
    e->HP = 5;//Za sad
    e->maxHP = 5;
    e->speed = 200.0f;
    e->size = 40;
    e->actions[MOVEMENT_ACTION] = InitAction(&LinearMovement,GetFrameTime());
    e->actions[SHOOTING_ACTION].update = NULL;
    e->movementData.linear.direction = (Vector2){0,-1};
}
void InitTurret(Enemy *e) {
    e->HP = 5;
    e->maxHP = 5;
    e->speed = 100;
    e->size = 20;
    e->fireRate = 2.73f;//The binding of Isaac reference
    e->actions[MOVEMENT_ACTION].update = &LinearMovement;
    e->movementData.linear.direction = (Vector2){0,1};
    e->actions[SHOOTING_ACTION] = InitAction(&PlayerShotLinear,1/e->fireRate);
    e->shootingData.single.direction = (Vector2){0,1};
    e->shootingData.single.size = 5;
    e->shootingData.single.speed = 700.0f;
}
//Dodati funkciju za inicijalizaciju uniona mozda
void InitRangedPlane(Enemy *e) {
    e->HP = 5;
    e->maxHP = 5;
    e->size = 15;
    e->fireRate = 2.73f;
    e->speed = 350.0f;
    int random = GetRandomValue(0,2);
    e->actions[SHOOTING_ACTION] = InitAction(&ShotgunShot,1/e->fireRate);
    if (random ==0) {
        e->actions[MOVEMENT_ACTION] = InitAction(&SineMovement,GetFrameTime());
        e->movementData.sine.direction=1;
        e->movementData.sine.amplitude = 30.f;
        e->movementData.sine.frequency= 0.02f;
        e->movementData.sine.baseline = WINDOW_HEIGHT/2;
        e->movementData.sine.position = e->position;
    }
    if (random ==1) {
        e->actions[MOVEMENT_ACTION] = InitAction(&CircularMovement,GetFrameTime());
        e->movementData.circular.position = e->position;
        int randomDir = GetRandomValue(0,1);
        if (randomDir ==0) {
            e->movementData.circular.direction = -1;
        }
        else
            e->movementData.circular.direction = 1;
        e->movementData.circular.center = (Vector2){WINDOW_WIDTH/2,WINDOW_HEIGHT/2};
    }
    if (random ==2) {
        e->actions[MOVEMENT_ACTION] = InitAction(&LinearMovement,GetFrameTime());
        e->movementData.linear.direction = (Vector2){1,0};
    }
    e->shootingData.shotgun.size = 5;
    e->shootingData.shotgun.speed = 700.0f;
    e->shootingData.shotgun.direction = (Vector2){0,1};
    e->shootingData.shotgun.rotationAngleRadians = PI/4;
    e->shootingData.shotgun.amount=3;
}
void InitBoss(Enemy *e) {
    e-> HP = 40;
    e->maxHP = 40;
    e->speed = 200.0f;
    e->size = 80;
    e->actions[MOVEMENT_ACTION] = InitAction(&BossPhase1,300);//Timer ovde oznacava predjeni put nakon kog boss automatski puca oko sebe
    e->actions[SHOOTING_ACTION].update = NULL;
    e->movementData.linear.direction = (Vector2) {3,2};
    e->movementData.linear.acceleration = 200;
    e->shootingData.shotgun.size = 15;
    e->shootingData.shotgun.speed = 800.0f;
    e->shootingData.shotgun.direction = (Vector2){0,1};
    e->shootingData.shotgun.rotationAngleRadians = PI/4;
    e->shootingData.shotgun.amount =8;
    e->laserActive = false;
}
void UpdateEnemies(GameState * state) {
    float dt = GetFrameTime();
    for (int i=0;i<ENEMY_CAP;i++) {
        if (state->enemies[i].active) {
            for (int j=0;j<MAX_ACTIONS;j++) {
                if (state->enemies[i].actions[j].update != NULL)
                    state->enemies[i].actions[j].update(&state->enemies[i],state,dt);
            }
            if (state->enemies[i].position.y > WINDOW_HEIGHT + state->enemies[i].size+15 || state->enemies[i].position.y < -state->enemies[i].size-15 ||state->enemies[i].position.x > WINDOW_WIDTH + state->enemies[i].size+15 ||
                state->enemies[i].position.x < -state->enemies[i].size-15) {
                    DestroyEnemy(&state->enemies[i]);
            }
        }
    }
}
void DrawEnemies(Enemy enemies[]) {
    for (int i=0;i<ENEMY_CAP;i++) {
        if (enemies[i].active) {
            if (enemies[i].laserActive) {
                DrawRectangle(enemies[i].position.x - enemies[i].size/2, enemies[i].position.y, enemies[i].size, WINDOW_HEIGHT, ORANGE);
            }
            DrawCircle(enemies[i].position.x,enemies[i].position.y,enemies[i].size, YELLOW);
        }
    }
}

void DestroyEnemy(Enemy *enemy) {
    enemy->active = false;
}