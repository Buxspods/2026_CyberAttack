//
// Created by A1 on 5/6/2026.
//
#include "Enemy.h"
#include "../mech/projectile.h"
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
void SpawnEnemy(Enemy enemies[],EnemyType type,Vector2 position) {
    for (int i=0;i<ENEMY_CAP;i++) {
        if (!enemies[i].active) {
            enemies[i].active = true;
            enemies[i].position = position;
            enemies[i].type = type;
            switch (enemies[i].type) {
                case MELEE_PLANE:
                    InitMeelePlane(&enemies[i]);
            }
            break;
        }
    }
}
void InitMeelePlane(Enemy *e) {
    e->HP = 10;//Za sad
    e->maxHP = 10;
    e->speed = 200.0f;
    e->movementDirection = (Vector2){0,-1};
    e->size = 40;
}
void UpdateEnemies(Enemy enemies[]) {
    for (int i=0;i<ENEMY_CAP;i++) {
        if (enemies[i].active) {
            Decision(&enemies[i]);
        }
    }
}
void Decision(Enemy *e) {
    float dt = GetFrameTime();
    switch (e->type) {
        case (MELEE_PLANE): MeelePlaneDecision(e,dt); break;
        case(TURRET):TurretDecision(e,dt); break;
    }
}
void MeelePlaneDecision(Enemy *e,float dt) {
    e->position.x += e->speed * dt * e->movementDirection.x;
    e->position.y += e->speed * dt * e->movementDirection.y;//Normalizacija
    if (e->position.x <e->size || e->position.x>WINDOW_WIDTH || e->position.y <e->size || e->position.y>WINDOW_HEIGHT) {
        e->active = false;
    }
}
void TurretDecision(Enemy *e,float dt) {
    //Treba da puca nije zavrseno jer ne moze ovde da se iskoristi shoot funkcija jer nemam pristup nizu sa metkovima.
    //Resenje je da se taj niz pozicije igraca i slicno ubace u strukturu koja se zove GameState i onda da se prosledjuje u ove odluke
    //Odradicu to za sledeci put.
    e->actionTimer+=dt;
    if (e->actionTimer>1) {
        e->actionTimer = 0;
    }
}
void DrawEnemies(Enemy enemies[]) {
    for (int i=0;i<ENEMY_CAP;i++) {
        if (enemies[i].active) {
            DrawCircle(enemies[i].position.x,enemies[i].position.y,enemies[i].size, YELLOW);
        }
    }
}