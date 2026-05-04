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

void UpdateProjectiles(Projectile projectiles[]) {
    for (int i = 0; i < PROJECTILE_CAP; i++) {
        if (projectiles[i].active) {

            float dt = GetFrameTime();
            projectiles[i].pos.x += projectiles[i].speed * dt * projectiles[i].direction.x;
            projectiles[i].pos.y += projectiles[i].speed * dt * projectiles[i].direction.y;//Treba odraditi normalizaciju

            if (projectiles[i].pos.y < projectiles[i].size/2 && projectiles[i].pos.x < projectiles[i].size/2) {//Izlazak iz ekrana
                projectiles[i].active = false;
            }
        }
    }
}
void drawProjectiles(Projectile projectiles[]) {
    for (int i = 0; i < PROJECTILE_CAP; i++) {
        if (projectiles[i].active) {
            DrawCircleV(projectiles[i].pos, projectiles[i].size, RED);
        }
    }
}