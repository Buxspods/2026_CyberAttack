//#include "raylib.h" Ne treba include jer je raylib vec ukljucen u drugim header fajlovima
#include <math.h>
#include<stdlib.h>
#include "mechanics.h"
#include "AI.h"
#include"GUI.h"
#include <time.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define PROJECTILE_CAP 100
#define ENEMY_CAP 100

GameState gamestate;
GraphicAssets assets;
int main() {

    srand(time(NULL));
    float fire_timer =0.0f;//Prebaciti ovo verovatno u logiku za igraca nekakvu
    float spawn_timer =4.0f;

    gamestate = InitGameState();//Inicijalizuje Igraca protivnike i metkove

    EnemyWave wave4 = {
        .enemies ={
                    {ENEMY_RANGED_PLANE, {100, 750},0.0f},
                    {ENEMY_RANGED_PLANE, {100, 750},0.5f},
                    {ENEMY_RANGED_PLANE, {100, 750},1.0f},
                    {ENEMY_RANGED_PLANE, {100, 750},1.5f}},
                    2.0f, 4};
    EnemyWave wave2 = {
        .enemies = {
                    {ENEMY_TURRET, {100, 550},1.0f},
                    {ENEMY_TURRET, {300, 550},2.0f},
                    {ENEMY_TURRET, {500, 550},3.0f},
                    {ENEMY_TURRET, {700, 550},4.0f}},
                        12.0f, 4};
    EnemyWave wave3 = {
        .enemies = {
                    {ENEMY_MELEE_PLANE, {100, 650},1.0f},
                    {ENEMY_MELEE_PLANE, {200, 650},2.5f},
                    {ENEMY_MELEE_PLANE, {300, 650},3.0f},
                    {ENEMY_MELEE_PLANE, {400, 650},4.5f},
                    {ENEMY_MELEE_PLANE, {100, 650},5.0f}},
                        5.0f, 5};

    const EnemyWave wave1 = {.enemies = { {ENEMY_TURRET, {100, 100}, 1}}, 22.0f, 1};

    Level level = {.waves = {wave1, wave2, wave3, wave4}, 4};
    Vector2 vect = {100, 100};


    //pravljenje pocetnog prozora i postavljanje najveceg dozvoljenog FPS-a
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "2026: Cyber Attack");
    InitAudioDevice();
    SetTargetFPS(60);

    assets.highestScores = NULL;
    Vector2 pozicijaAviona = {100, 100};
    InitGlavni(&assets);
    InitPause(&assets);
    PlayMusicStream(assets.mainMenu);

    Vector2 dimenzije = MeasureTextEx(assets.fontOrbitron, "2026: Cyber Attack", 70, 2);
    Vector2 pozicija = {windowWidth / 2.0f - dimenzije.x / 2, windowHeight * 0.125f};
    float vreme = 0.0f;
    float providnost = 1.0f;
    float rotation = 0.0f;
    assets.currScore = 0;
    bool guideMenu = false;
    SetExitKey(KEY_NULL);

    //Game Loop
    while(!WindowShouldClose()) {
        UpdateMusicStream(assets.mainMenu);
        UpdateMusicStream(assets.level1);
        UpdateMusicStream(assets.level2);
        UpdateMusicStream(assets.level3);
        Color BackgroundColor = {67, 67, 69, 255}; //OVU BOJU CEMO SVAKAKO SKLONITI KAD TAD
        float dt = GetFrameTime(); //delta time potreban da bi na svakom kompu igra isla istom brzinom
        fire_timer+=dt;
        spawn_timer+=dt;

        assets.mis = GetMousePosition();
        if (IsKeyPressed(gamestate.keys[ACTION_PAUSE]) && assets.currScreen != MAIN_MENU) {
            if (assets.isPaused) {
                assets.level1Map.isMoving = true;
                assets.level2Map.isMoving = true;
                assets.level3Map.isMoving = true;
            }
            assets.isPaused = assets.isPaused == 0? 1: 0;
            assets.currScreen = (assets.currScreen == PAUSE_MENU)? assets.currLevel:PAUSE_MENU;
        }

        if (!assets.isPaused) {
            UpdatePlayerPosition(&gamestate.player);
            UpdateInvincibility(&gamestate.player, dt, INVINCIBILITY_TIME);
            UpdateDash(&gamestate.player, dt, DASH_TIME, gamestate.player.mvmntVect);
            UpdateSpeed(&gamestate.player, dt);
            UpdateProjectiles(gamestate.projectiles);
            UpdateEnemies(&gamestate);
            CheckCollisions(&gamestate);
        }
        else {
            assets.level1Map.isMoving = false;
            assets.level2Map.isMoving = false;
            assets.level3Map.isMoving = false;
        }

        if (!assets.isPaused && assets.currScreen != MAIN_MENU) {
            gamestate.globalLevelTimer+=dt;
        }

        switch (assets.currScreen) {
            case LEVEL1:
                StartLevel(&level, &gamestate, &gamestate.globalLevelTimer);
                break;
            case LEVEL2:
                StartLevel(&level, &gamestate, &gamestate.globalLevelTimer);
                break;
            case LEVEL3:
                StartLevel(&level, &gamestate, &gamestate.globalLevelTimer);
                break;
            default:
                break;
        }

        if (fire_timer > (1/gamestate.player.fireRate) && IsKeyDown(gamestate.keys[ACTION_SHOOT]) && gamestate.player.ammo > 0) {
            PlaySound(assets.laser);
            PlayerShootBullet(&gamestate,&gamestate.player);
            //Shoot(PLAYER, gamestate.projectiles, gamestate.player.playerPos, 5, 750, (Vector2){0, 0}, &gamestate.player);
            fire_timer = 0;
        }

        if(IsKeyDown(KEY_H)) { //sluzi za dopunu municije i hp samo dok se testira
            gamestate.player.ammo = 100;
            gamestate.player.lives = 20;
        }

        //CRTANJE
        BeginDrawing();
        ClearBackground(BackgroundColor);
        switch (assets.currScreen) {
            case 1:
                MoveMap(&assets.level1Map, &gamestate);
                DrawPlaneGUI(&gamestate.player.playerPos, &assets);
                DrawPowerUps(gamestate.powerups);
                DrawProjectiles(gamestate.projectiles);
                DrawEnemies(gamestate.enemies);//Wrappuj ove tri funkcije u DrawGameState
                PrikaziStats(gamestate.player.score, gamestate.player.lives,gamestate.player.ammo , &assets);
                break;
            case 2:
                MoveMap(&assets.level2Map, &gamestate);
                DrawPlaneGUI(&gamestate.player.playerPos, &assets);
                DrawPowerUps(gamestate.powerups);
                DrawProjectiles(gamestate.projectiles);
                DrawEnemies(gamestate.enemies);//Wrappuj ove tri funkcije u DrawGameState
                PrikaziStats(gamestate.player.score, gamestate.player.lives,gamestate.player.ammo , &assets);
                break;
            case 3:
                MoveMap(&assets.level3Map, &gamestate);
                DrawPlaneGUI(&gamestate.player.playerPos, &assets);
                DrawPowerUps(gamestate.powerups);
                DrawProjectiles(gamestate.projectiles);
                DrawEnemies(gamestate.enemies);//Wrappuj ove tri funkcije u DrawGameState
                PrikaziStats(gamestate.player.score, gamestate.player.lives,gamestate.player.ammo , &assets);
                break;
            case 4:
                switch (assets.currLevel) {
                    case 1:
                        MoveMap(&assets.level1Map, &gamestate);
                        break;
                    case 2:
                        MoveMap(&assets.level2Map, &gamestate);
                        break;
                    case 3:
                        MoveMap(&assets.level3Map, &gamestate);
                        break;
                    default:
                        break;
                }
                DrawPlaneGUI(&gamestate.player.playerPos, &assets);
                DrawPowerUps(gamestate.powerups);
                DrawProjectiles(gamestate.projectiles);
                DrawEnemies(gamestate.enemies);//Wrappuj ove tri funkcije u DrawGameState
                PrikaziStats(gamestate.player.score, gamestate.player.lives,gamestate.player.ammo , &assets);
                CrtajPause(&assets);
                if (assets.fja == Guide || assets.fja == HighestScores || assets.fja == Settings) {
                    assets.fja(&assets, 0);
                }
                break;
            default:
                ResetLevel(&level);
                if (assets.fja == NULL) {
                    CrtajMeni(&pozicija ,&vreme, &providnost, &assets);
                    guideMenu = true;
                }
                else {
                    if (assets.fja == DrawGameOverScreen && guideMenu) {
                        assets.fja(&assets, assets.currScore);
                    }
                    else {
                        assets.fja(&assets, 0);
                    }
                }
                break;
        }

        UpdateLevelEnd(&assets, &gamestate);
        EndDrawing();
    }
    UnloadAssets(&assets);
    CloseWindow();
    return 0;
}
