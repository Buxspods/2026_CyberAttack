#define PROJECTILE_CAP 100
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

#include "projectile.h"
#include "raymath.h"
#include "EntityTypes.h"
#include "Player.h"
//Ova funkcija dodata da bi radila sa protivnicima
void InitProjectile(Projectile projectiles[],EntityType projectile_tag,Vector2 pos,Vector2 dir,float speed,float size) {
    for (int i = 0; i < PROJECTILE_CAP; i++) {
        if (!projectiles[i].active) {
            projectiles[i].active = true;
            projectiles[i].entityType = projectile_tag;
            projectiles[i].pos = pos;
            projectiles[i].direction = Vector2Normalize(dir);
            projectiles[i].speed = speed;
            projectiles[i].size = size;
            break;
        }
    }
}
/*void Shoot(EntityType shooter, Projectile projectiles[],Vector2 pos,float size,float speed, Vector2 target, Player *player) {
    Vector2 direction;
    EntityType projectile_tag;
    if(shooter == ENEMY_TURRET || shooter == ENEMY_RANGED_PLANE){
        projectile_tag = ENEMY_PROJECTILE;
    }
    else{
        direction = (Vector2){0,-1};
        projectile_tag = PLAYER_PROJECTILE;
    }
    for (int i = 0; i < PROJECTILE_CAP; i++) {
        if (!projectiles[i].active) {
            projectiles[i].entityType = projectile_tag;
            projectiles[i].active = true;
            projectiles[i].pos = pos;
            projectiles[i].size = size;
            projectiles[i].speed = speed;
            if(shooter == ENEMY_TURRET || shooter == ENEMY_RANGED_PLANE){
                direction = Vector2Normalize(Vector2Subtract(target,projectiles[i].pos));
            }
            projectiles[i].direction = direction;
            if (shooter == PLAYER) {
                player->ammo--;
            }
            break;
        }
    }
}*/
void UpdateProjectile(Projectile *p,float dt) {
    Vector2 normalizedDirection = Vector2Normalize(p->direction);
    p->pos.x += p->speed * dt * normalizedDirection.x;
    p->pos.y += p->speed * dt * normalizedDirection.y;
    if (p->pos.y < p->size/2 || p->pos.x < p->size/2 || p->pos.y>WINDOW_HEIGHT || p->pos.x>WINDOW_WIDTH) {//Izlazak iz ekrana
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