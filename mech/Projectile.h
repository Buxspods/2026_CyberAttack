//
// Created by A1 on 5/4/2026.
//

#ifndef INC_2026_CYBERATTACK_PROJECTILE_H
#define INC_2026_CYBERATTACK_PROJECTILE_H
#include "raylib.h"

typedef struct {
    Vector2 pos;
    float size;
    float speed;
    Texture2D texture;
    bool active;
    Vector2 direction;
}Projectile;
void Shoot(Projectile projectiles[],Vector2 pos,float size,float speed);
void UpdateProjectiles(Projectile projectiles[]);
void drawProjectiles(Projectile projectiles[]);
#endif //INC_2026_CYBERATTACK_PROJECTILE_H
