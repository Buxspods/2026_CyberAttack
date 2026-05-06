//
// Created by A1 on 5/6/2026.
//

#ifndef INC_2026_CYBERATTACK_ENEMY_H
#define INC_2026_CYBERATTACK_ENEMY_H
#include "EnemyTypes.h"
#include "raylib.h"
#define ENEMY_CAP 100
typedef struct {
    Vector2 position;
    int HP;
    int maxHP;
    float size;
    float speed;
    EnemyType type;
    Vector2 movementDirection;
    Vector2 shootingDirection;
    float actionTimer;//Napraviti bolji sistem za ovo (za sada AI moze da radi samo po jednu akciju ovo treba da bude niz
    //Sa vise akcija gde ce svaka akcija da pozove odredjenu funkciju
    bool active;//Ista logika kao i za metkove
}Enemy;
//Funkcije za inicijalizaciju razlicitih tipova protivnika
void SpawnEnemy(Enemy enemies[],EnemyType type,Vector2 position);
void InitMeelePlane(Enemy *e);
void InitTurret(Enemy *e);
//Logika
void Decision(Enemy *e);
void MeelePlaneDecision(Enemy *e,float dt);
void TurretDecision(Enemy *e,float dt);
void UpdateEnemies(Enemy enemies[]);

void DrawEnemies(Enemy enemies[]);
#endif //INC_2026_CYBERATTACK_ENEMY_H
