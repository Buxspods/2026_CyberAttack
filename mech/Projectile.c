#define PROJECTILE_CAP 100
#include "projectile.h"
void Shoot(Projectile projectiles[],Vector2 pos,float size,float speed) {
    for (int i = 0; i < PROJECTILE_CAP; i++) {
        if (!projectiles[i].active) {
            projectiles[i].active = true;
            projectiles[i].pos = pos;
            projectiles[i].size = size;
            projectiles[i].speed = speed;
            Vector2 direction = {0,-1};
            projectiles[i].direction = direction;
            break;
        }
    }
}

void UpdateProjectile(Projectile *p,float dt) {
    p->pos.x += p->speed * dt * p->direction.x;
    p->pos.y += p->speed * dt * p->direction.y;//Treba odraditi normalizaciju

    if (p->pos.y < p->size/2 || p->pos.x < p->size/2) {//Izlazak iz ekrana
        p->active = false;
    }
}

void UpdateProjectiles(Projectile projectiles[]) {
    float dt=GetFrameTime();
    //Prethodna funkcija rastavljena ovako jer je bio bug da posle 100 ispucanih metaka nece vise da puca
    for (int i = 0; i < PROJECTILE_CAP; i++) {
        if (projectiles[i].active) {
            UpdateProjectile(&projectiles[i],dt);
        }
    }
}
void DrawProjectiles(Projectile projectiles[]) {
    for (int i = 0; i < PROJECTILE_CAP; i++) {
        if (projectiles[i].active) {
            DrawCircleV(projectiles[i].pos, projectiles[i].size, RED);
        }
    }
}