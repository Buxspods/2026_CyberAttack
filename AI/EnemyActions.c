#include <stdio.h>

#include "Enemy.h"
#include "raymath.h"
#include "../mech/GameState.h"

//
// Created by A1 on 5/12/2026.
//
#define WINDOW_HEIGHT 1000
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
void LinearShoot(Enemy *e,GameState *state) {
    Shoot(e->type,state->projectiles,e->position,5,700,state->player.playerPos,&state->player);
}
void LinearShot(Enemy *e,GameState *state, float dt) {
    e->actions[SHOOTING_ACTION].currentTime+=dt;
    if (e->actions[SHOOTING_ACTION].currentTime>=e->actions[SHOOTING_ACTION].actionTimer) {
        e->actions[SHOOTING_ACTION].currentTime=0;
        LinearShoot(e,state);
    }
}
void ShotgunShot(Enemy *e,GameState *state, float dt) {

}