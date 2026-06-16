//#include "raylib.h" Ne treba include jer je raylib vec ukljucen u drugim header fajlovima
#include <math.h>
#include <stdio.h>
#include<stdlib.h>
#include "mechanics.h"
#include "AI.h"
#include"GUI.h"
#include <time.h>
#include "mech/PowerUp.h"

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

    EnemyWave wave11 = {
        .enemies ={
                        {.type = ENEMY_MELEE_PLANE, .position = {100, -50},.spawnTime = 1.0f, .direction = {0, 1}},
                        {.type = ENEMY_MELEE_PLANE, .position = {300, -50},.spawnTime = 1.5f, .direction = {0, 1}},
                        {.type = ENEMY_MELEE_PLANE, .position = {500, -50},.spawnTime = 2.0f, .direction = {0, 1}},
                        {.type = ENEMY_MELEE_PLANE, .position = {700, -50},.spawnTime = 2.5f, .direction = {0, 1}},
                        {.type = ENEMY_MELEE_PLANE, .position = {900, -50},.spawnTime = 3.0f, .direction = {0, 1}}},
                    2.0f, 5};
    EnemyWave wave12 = {
        .enemies ={
                        {.type = ENEMY_MELEE_PLANE, .position = {-50, -50},.spawnTime = 3.5f, .direction = {1, 1}},
                        {.type = ENEMY_MELEE_PLANE, .position = {1050, -50},.spawnTime = 3.5f, .direction = {-1, 1}}},
                        2.5f, 2};

    EnemyWave wave13 = {
        .enemies ={
                        {.type = ENEMY_MELEE_PLANE, .position = {100, -50},.spawnTime = 4.75f, .direction = {0, 1}},
                        {.type = ENEMY_MELEE_PLANE, .position = {300, -50},.spawnTime = 4.5f, .direction = {0, 1}},
                        {.type = ENEMY_MELEE_PLANE, .position = {500, -50},.spawnTime = 4.5f, .direction = {0, 1}},
                        {.type = ENEMY_MELEE_PLANE, .position = {700, -50},.spawnTime = 4.5f, .direction = {0, 1}},
                        {.type = ENEMY_MELEE_PLANE, .position = {900, -50},.spawnTime = 4.75f, .direction = {0, 1}},
                        {.type = ENEMY_TURRET, .position = {300, -15},.spawnTime = 5.0f, .direction = {0, 1}},
                        {.type = ENEMY_TURRET, .position = {700, -15},.spawnTime = 5.0f, .direction = {0, 1}},
                        {.type = ENEMY_TURRET, .position = {500, -15},.spawnTime = 5.5f, .direction = {0, 1}},
                        {.type = ENEMY_TURRET, .position = {100, -15},.spawnTime = 6.75f, .direction = {0, 1}},
                        {.type = ENEMY_TURRET, .position = {900, -15},.spawnTime = 5.75f, .direction = {0, 1}}},
                            3.5f, 10};

    EnemyWave wave14 = {
        .enemies ={
                        {.type = ENEMY_RANGED_PLANE, .position = {450, 0},.spawnTime = 5.5f, .movementMode = RIGHT_CIRCULAR, .center = {-150, -150}},
                        {.type = ENEMY_RANGED_PLANE, .position = {550, 0},.spawnTime = 5.5f, .movementMode = LEFT_CIRCULAR, .center = {1150, -150}}},
                            5.5f, 2};


    Level level1 = {.waves = {wave11, wave12, wave13, wave14}, 4};

    //pravljenje pocetnog prozora i postavljanje najveceg dozvoljenog FPS-a
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "2026: Cyber Attack");
    InitAudioDevice();
    SetTargetFPS(60);

    for (int i = 0; i < 30; i++) {
        BeginDrawing();
        ClearBackground((Color){15, 15, 20, 255}); // Cyberpunk tamna pozadina

        // Koristimo običan tekst dok se fontovi ne učitaju
        DrawText("2026: CYBER ATTACK", WINDOW_WIDTH / 2 - 220, WINDOW_HEIGHT / 2 - 40, 40, BLUE);
        DrawText("Loading Assets...", WINDOW_WIDTH / 2 - 120, WINDOW_HEIGHT / 2 + 20, 20, GRAY);
        EndDrawing();
    }

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
        bool AutoRegime = false;//ZA AUTOMATSKI REZIM
        bool aiShoot = false;
        assets.mis = GetMousePosition();
        if (IsKeyPressed(gamestate.keys[ACTION_PAUSE]) && assets.currScreen != MAIN_MENU) {
            if (assets.isPaused) {
                assets.level1Map.isMoving = true;
                assets.level2Map.isMoving = true;
                assets.level3Map.isMoving = true;
            }
            else {
                if (assets.fja != CrtajPause)
                    assets.fja = CrtajPause;
            }
            assets.isPaused = assets.isPaused == 0? 1: 0;
            assets.currScreen = (assets.currScreen == PAUSE_MENU)? assets.currLevel:PAUSE_MENU;
        }

        /*if (!assets.isPaused) {
            if (assets.odbrojavanje) {
                assets.timer -= GetFrameTime();
                if (assets.timer <= 0.0f) {
                    assets.odbrojavanje = false;
                }
            }
            else {
                UpdatePlayerPosition(&gamestate.player);
                if (AutoRegime) {
                    AutoRegimePlayerUpdate(&gamestate,&aiShoot);
                    gamestate.player.playerPos.x += gamestate.player.mvmntVect.x * gamestate.player.playerSpeed *dt;
                    gamestate.player.playerPos.y += gamestate.player.mvmntVect.y * gamestate.player.playerSpeed *dt;
                    if (gamestate.player.playerPos.x < 0) {
                        gamestate.player.playerPos.x = 0;
                    }
                    if (gamestate.player.playerPos.y < 0) {
                        gamestate.player.playerPos.y = 0;
                    }
                    if (gamestate.player.playerPos.x > WINDOW_WIDTH) {
                        gamestate.player.playerPos.x = WINDOW_WIDTH;
                    }
                    if (gamestate.player.playerPos.y > WINDOW_HEIGHT) {
                        gamestate.player.playerPos.y = WINDOW_HEIGHT;
                    }
                }
                UpdateShootingMode(&gamestate.player, dt);
                UpdateInvincibility(&gamestate.player, dt, INVINCIBILITY_TIME);
                UpdateDash(&gamestate.player, dt, DASH_TIME, gamestate.player.mvmntVect);
                UpdateSpeed(&gamestate.player, dt);
                UpdateProjectiles(gamestate.projectiles);
                UpdateEnemies(&gamestate);
                CheckCollisions(&gamestate);
            }
        }
        else {
            assets.level1Map.isMoving = false;
            assets.level2Map.isMoving = false;
            assets.level3Map.isMoving = false;
        }*/

        if (!assets.isPaused && assets.currScreen != MAIN_MENU && !assets.odbrojavanje) {
            gamestate.globalLevelTimer+=dt;
            printf("%f\n", gamestate.globalLevelTimer);
        }

        switch (assets.currScreen) {
            case LEVEL1:
                StartLevel(&level1, &gamestate, &gamestate.globalLevelTimer);
                break;
            case LEVEL2:
                StartLevel(&level1, &gamestate, &gamestate.globalLevelTimer);
                break;
            case LEVEL3:
                StartLevel(&level1, &gamestate, &gamestate.globalLevelTimer);
                break;
            case INFINITE_LEVEL:
                break;
            case DEMO_MODE:
                StartLevel(&level1, &gamestate, &gamestate.globalLevelTimer);
                break;
            default:
                break;
        }

        if (fire_timer > (1/gamestate.player.fireRate) && (IsKeyDown(gamestate.keys[ACTION_SHOOT]) || aiShoot) && gamestate.player.ammo > 0) {//Ovo x je samo zbog testiranja
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
                DrawPowerUps(gamestate.powerups, assets.level1Map.speed, dt,assets.level1Map.isMoving);
                DrawProjectiles(gamestate.projectiles);
                DrawEnemies(gamestate.enemies);//Wrappuj ove tri funkcije u DrawGameState
                PrikaziStats(gamestate.player.score, gamestate.player.lives,gamestate.player.ammo , &assets);
                break;
            case 2:
                MoveMap(&assets.level2Map, &gamestate);
                DrawPlaneGUI(&gamestate.player.playerPos, &assets);
                DrawPowerUps(gamestate.powerups, assets.level1Map.speed, dt, assets.level1Map.isMoving);
                DrawProjectiles(gamestate.projectiles);
                DrawEnemies(gamestate.enemies);//Wrappuj ove tri funkcije u DrawGameState
                PrikaziStats(gamestate.player.score, gamestate.player.lives,gamestate.player.ammo , &assets);
                break;
            case 3:
                MoveMap(&assets.level3Map, &gamestate);
                DrawPlaneGUI(&gamestate.player.playerPos, &assets);
                DrawPowerUps(gamestate.powerups, assets.level1Map.speed, dt, assets.level1Map.isMoving);
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
                DrawPowerUps(gamestate.powerups, assets.level1Map.speed, dt, assets.level1Map.isMoving);
                DrawProjectiles(gamestate.projectiles);
                DrawEnemies(gamestate.enemies);//Wrappuj ove tri funkcije u DrawGameState
                PrikaziStats(gamestate.player.score, gamestate.player.lives,gamestate.player.ammo , &assets);
                if (assets.fja!= NULL)
                    assets.fja(&assets, 0);
                break;
            case 5:
                //INFINITE LEVEL
                break;
            case 6:
                AutoRegime = true;
                MoveMap(&assets.level1Map, &gamestate);
                DrawPlaneGUI(&gamestate.player.playerPos, &assets);
                DrawPowerUps(gamestate.powerups, assets.level1Map.speed, dt,assets.level1Map.isMoving);
                DrawProjectiles(gamestate.projectiles);
                DrawEnemies(gamestate.enemies);//Wrappuj ove tri funkcije u DrawGameState
                PrikaziStats(gamestate.player.score, gamestate.player.lives,gamestate.player.ammo , &assets);
                break;
            default:
                ResetLevel(&level1);
                if (assets.fja == NULL) {
                    CrtajMeni(&pozicija ,&vreme, &providnost, &assets);
                }
                else {
                    if (assets.fja == DrawGameOverScreen || assets.fja == DrawYouWonScreen) {
                        assets.fja(&assets, assets.currScore);
                    }
                    else {
                        assets.fja(&assets, 0);
                    }
                }
                break;
        }
        if (assets.odbrojavanje) {
            DrawRectangle(0, 0, windowWidth, windowHeight, Fade(BLACK, 0.5f));
            DrawTextEx(assets.fontOrbitron, TextFormat("%d", (int)ceil(assets.timer)), (Vector2){windowWidth/2.0f - 60,windowHeight/2.0f - 60},120,2,WHITE);
        }

        if (!assets.isPaused) {
            if (assets.odbrojavanje) {
                assets.timer -= GetFrameTime();
                if (assets.timer <= 0.0f) {
                    assets.odbrojavanje = false;
                }
            }
            else {
                UpdatePlayerPosition(&gamestate.player);
                if (AutoRegime) {
                    AutoRegimePlayerUpdate(&gamestate,&aiShoot);
                    gamestate.player.playerPos.x += gamestate.player.mvmntVect.x * gamestate.player.playerSpeed *dt;
                    gamestate.player.playerPos.y += gamestate.player.mvmntVect.y * gamestate.player.playerSpeed *dt;
                    if (gamestate.player.playerPos.x < 0) {
                        gamestate.player.playerPos.x = 0;
                    }
                    if (gamestate.player.playerPos.y < 0) {
                        gamestate.player.playerPos.y = 0;
                    }
                    if (gamestate.player.playerPos.x > WINDOW_WIDTH) {
                        gamestate.player.playerPos.x = WINDOW_WIDTH;
                    }
                    if (gamestate.player.playerPos.y > WINDOW_HEIGHT) {
                        gamestate.player.playerPos.y = WINDOW_HEIGHT;
                    }
                }
                UpdateShootingMode(&gamestate.player, dt);
                UpdateInvincibility(&gamestate.player, dt, INVINCIBILITY_TIME);
                UpdateDash(&gamestate.player, dt, DASH_TIME, gamestate.player.mvmntVect);
                UpdateSpeed(&gamestate.player, dt);
                UpdateProjectiles(gamestate.projectiles);
                UpdateEnemies(&gamestate);
                DrawExplosion(&assets);
                CheckCollisions(&gamestate);
            }
        }
        else {
            assets.level1Map.isMoving = false;
            assets.level2Map.isMoving = false;
            assets.level3Map.isMoving = false;
        }

        UpdateLevelEnd(&assets, &gamestate, &level1);
        EndDrawing();
    }
    UnloadAssets(&assets);
    CloseWindow();
    return 0;
}