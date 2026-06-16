//
// Created by A1 on 5/6/2026.
//

#ifndef INC_2026_CYBERATTACK_ENEMY_H
#define INC_2026_CYBERATTACK_ENEMY_H
//#include "EnemyTypes.h"
#include "raylib.h"
#include "../mech/EntityTypes.h"
#include "../Mech/EnemyWithTime.h"

#define ENEMY_CAP 100
#define DEFAULT_DEATH_SCORE 50
// #define MOVEMENT_ACTION 0
// #define SHOOTING_ACTION 1
#define MAX_ACTIONS 2
typedef struct Enemy Enemy;
typedef struct GameState GameState;
typedef void (*EnemyUpdateFunc)(Enemy *e, GameState *state, float dt);
typedef struct{
    EnemyUpdateFunc update;
    float actionTimer;
    float currentTime;
    //ActionType type; mozda ako nekada neko hoce da napravi da protivnik moze da stackuje movement actions
    //Ili bilo koji drugi tip akcije ova linija koda moze da stoji tu. Medjutim za ovaj projekat ona je potpuno nepotrebna i cini mi se kao cool ideja koju vredi istraziti
}Action;
struct Enemy{
    Vector2 position;
    bool laserActive;
    int HP;
    int maxHP;
    float size;
    float speed;
    float fireRate;
    EntityType type;
    float deathScore;
    int ammoRefill;
    Action actions[MAX_ACTIONS];
    bool active;//Ista logika kao i za metkove
    int movementType; //za ranged plane
    int leftOrRight;
    union{
        struct {bool canMove;} restrictions;
        struct {Vector2 direction;float acceleration;}linear;
        struct {Vector2 center;Vector2 position;int direction;} circular;//direction je +/- jedan da bi odlucio da li hoces na desnu ili levu stranu
        struct {Vector2 position;float amplitude;float frequency; float baseline;int direction;} sine;
    } movementData;
    union {
        struct {Vector2 direction;float speed;float size;} single;
        struct {Vector2 direction;int amount;float rotationAngleRadians;float speed; float size;} shotgun;
    }shootingData;
};
typedef struct GameState GameState;
//Funkcije za inicijalizaciju razlicitih tipova protivnika
Enemy* SpawnEnemy(Enemy enemies[],EntityType type,Vector2 position, enum movementType mvType, Vector2 center);
void InitMeelePlane(Enemy *e);
void InitTurret(Enemy *e);
void InitRangedPlane(Enemy *e, enum movementType mvType, Vector2 center);
void InitBoss(Enemy *e);
void DrawEnemies(Enemy enemies[]);
void DestroyEnemy(Enemy *enemy);
void UpdateEnemies(GameState * gamestate);
#endif //INC_2026_CYBERATTACK_ENEMY_H
