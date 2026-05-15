#include "EnemyActions.h"

#include <stdio.h>

#include "Enemy.h"
#include "raymath.h"
#include "../mech/GameState.h"

//
// Created by A1 on 5/12/2026.
//
#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 1000
void MoveLinear(Vector2 *pos,float speed,Vector2 direction,float dt) {
    Vector2 normalizedDirection = Vector2Normalize(direction);
    pos->x += speed * dt * normalizedDirection.x;
    pos->y += speed * dt * normalizedDirection.y;
}

void MoveSine(Vector2 *pos, float amplitude, float frequency,float y0,float speed,int direction,float dt){
    //Amplitude i frequency odredjuju sinus. y0 je na kojoj visini se krece, direction +/-1 za desno/levo
    pos->x += speed * dt*direction;
    pos->y = y0 / 2 + sinf(pos->x * frequency) * amplitude;
}

void MoveCircular(Vector2 *pos, Vector2 centerPos,float speed,int direction,float dt) {
    float dx = pos->x - centerPos.x;
    float dy = pos->y - centerPos.y;
    float radius = sqrtf(dx * dx + dy * dy);
    float angle = atan2f(dy, dx);
    angle += dt * speed/radius;

    pos->x = centerPos.x + cosf(angle) * radius;
    pos->y = centerPos.y + sinf(angle) * radius;
}

void LinearMovement(Enemy *e,GameState *state, float dt) {
    MoveLinear(&e->position,e->speed,e->movementData.linear.direction,dt);
}
void CircularMovement(Enemy *e,GameState *state, float dt) {
    MoveCircular(&e->position,e->movementData.circular.center,e->speed,e->movementData.circular.direction,dt);
}
void SineMovement(Enemy *e,GameState *state, float dt) {
    MoveSine(&e->position,e->movementData.sine.amplitude,e->movementData.sine.frequency,
        e->movementData.sine.baseline,e->speed,e->movementData.sine.direction,dt);
}
void LinearShoot(GameState *state, Vector2 shooterPos, Vector2 direction, float size, float speed) {
    InitProjectile(state->projectiles, ENEMY_PROJECTILE, shooterPos, direction, speed, size);
}
void ShotgunShoot(GameState *state,Vector2 centralDirection,int amount,float SpreadAngleRadians,Vector2 shooterPos,float size,float speed) {
    if (amount<1)
        return;
    if (amount%2 !=0) {
        LinearShoot(state,shooterPos,centralDirection,size,speed);
    }
    for (int i=2;i<=amount;i+=2) {
        int delta = i/2;
        Vector2 leftDirection = Vector2Rotate(centralDirection,SpreadAngleRadians*delta*(-1));
        Vector2 rightDirection = Vector2Rotate(centralDirection,SpreadAngleRadians*delta);
        LinearShoot(state,shooterPos,leftDirection,size,speed);
        LinearShoot(state,shooterPos,rightDirection,size,speed);
    }
}
void LinearShot(Enemy *e,GameState *state, float dt) {
    e->actions[SHOOTING_ACTION].currentTime+=dt;
    if (e->actions[SHOOTING_ACTION].currentTime>=e->actions[SHOOTING_ACTION].actionTimer) {
        e->actions[SHOOTING_ACTION].currentTime=0;
        LinearShoot(state,e->position,e->shootingData.single.direction,e->shootingData.single.size,e->shootingData.single.speed);
    }
}
void PlayerShotLinear(Enemy *e,GameState *state, float dt) {
    e->actions[SHOOTING_ACTION].currentTime+=dt;
    if (e->actions[SHOOTING_ACTION].currentTime>=e->actions[SHOOTING_ACTION].actionTimer) {
        e->actions[SHOOTING_ACTION].currentTime=0;
        Vector2 direction = Vector2Subtract(state->player.playerPos,e->position);
        LinearShoot(state,e->position,direction,e->shootingData.single.size,e->shootingData.single.speed);
    }
}
void ShotgunShot(Enemy *e,GameState *state, float dt) {
    e->actions[SHOOTING_ACTION].currentTime+=dt;
    if (e->actions[SHOOTING_ACTION].currentTime>=e->actions[SHOOTING_ACTION].actionTimer) {
        e->actions[SHOOTING_ACTION].currentTime=0;
        ShotgunShoot(state,e->shootingData.shotgun.direction,e->shootingData.shotgun.amount,
            e->shootingData.shotgun.rotationAngleRadians,e->position,e->shootingData.shotgun.size,e->shootingData.shotgun.speed);
    }
}
void BossPhase1(Enemy*e,GameState *state, float dt) {
    MoveLinear(&e->position,e->speed,e->movementData.linear.direction,GetFrameTime());
    e->actions[MOVEMENT_ACTION].currentTime+=dt;
    bool colided = false;
    if (e->position.x < e->size){
        colided = true;
        e->position.x = e->size;
        e->movementData.linear.direction.x*=-1;
    }
    if (e->position.x>WINDOW_WIDTH-e->size){
        colided = true;
        e->position.x = WINDOW_WIDTH-e->size;
        e->movementData.linear.direction.x*=-1;
    }

    if (e->position.y < e->size){
        colided = true;
        e->position.y = e->size;
        e->movementData.linear.direction.y*=-1;
    }
    if (e->position.y>WINDOW_HEIGHT-e->size) {
        colided = true;
        e->position.y = WINDOW_HEIGHT-e->size;
        e->movementData.linear.direction.y*=-1;
    }
    if (colided){
        e->speed += e->movementData.linear.acceleration;
        e->shootingData.shotgun.speed-=e->movementData.linear.acceleration;
        if (e->shootingData.shotgun.speed>50)
            ShotgunShot(e,state,dt);
        else {
            e->shootingData.shotgun.speed=100;
            ShotgunShot(e,state,dt);
        }
    }
    if (e->speed <400) {
        e->speed = 400;
        e->movementData.linear.acceleration*=-1;
    }
    if (e->speed>1000) {
        e->speed = 1000;
        e->movementData.linear.acceleration*=-1;
    }
}