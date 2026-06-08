//
// Created by A1 on 5/6/2026.
//

#ifndef INC_2026_CYBERATTACK_GAMESTATE_H
#define INC_2026_CYBERATTACK_GAMESTATE_H
#include "Player.h"
#include "Projectile.h"
#include "PowerUp.h"
#include "../AI/Enemy.h"
typedef struct GameState{
    Projectile projectiles[PROJECTILE_CAP];
    Player player;
    Enemy enemies[ENEMY_CAP];
    PowerUp powerups[POWERUP_CAP];
}GameState;

GameState InitGameState();

#endif //INC_2026_CYBERATTACK_GAMESTATE_H
