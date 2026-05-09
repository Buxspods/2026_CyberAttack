//
// Created by A1 on 5/4/2026.
//

#ifndef INC_2026_CYBERATTACK_PROJECTILE_H
#define INC_2026_CYBERATTACK_PROJECTILE_H
#define PROJECTILE_CAP 100
#include "raylib.h"
#include "EntityTypes.h"
#include "Player.h"

typedef struct {
    EntityType entityType;
    Vector2 pos;
    float size;
    float speed;
    Texture2D texture;
    bool active;
    Vector2 direction;
}Projectile;
void Shoot(EntityType shooter, Projectile projectiles[],Vector2 pos,float size,float speed, Vector2 target, Player *player);
void UpdateProjectiles(Projectile projectiles[]);
void DrawProjectiles(Projectile projectiles[]);
void UpdateProjectile(Projectile *p,float dt);
//void ShootAt(Projectile projectiles[],Vector2 pos,float size,float speed,Vector2 target);
#endif //INC_2026_CYBERATTACK_PROJECTILE_H
