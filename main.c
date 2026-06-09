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


int main() {

    SCREEN currScreen = LEVEL1;

    float globalLeveltimer = 0.0f; //sluzi za tajmiranje talasa

    srand(time(NULL));
    float fire_timer =0.0f;//Prebaciti ovo verovatno u logiku za igraca nekakvu
    float spawn_timer =4.0f;

    GameState gamestate = InitGameState();//Inicijalizuje Igraca protivnike i metkove

    EnemyWave wave4 = {
        .enemies ={
                    {ENEMY_RANGED_PLANE, {100, 750},0.0f},
                    {ENEMY_RANGED_PLANE, {100, 750},0.5f},
                    {ENEMY_RANGED_PLANE, {100, 750},1.0f},
                    {ENEMY_RANGED_PLANE, {100, 750},1.5f}},
                    3.0f, 4};
    EnemyWave wave2 = {
        .enemies = {
                    {ENEMY_TURRET, {100, 550},1.0f},
                    {ENEMY_TURRET, {300, 550},2.0f},
                    {ENEMY_TURRET, {500, 550},3.0f},
                    {ENEMY_TURRET, {700, 550},4.0f}},
                        7.0f, 4};
    EnemyWave wave3 = {
        .enemies = {
                    {ENEMY_MELEE_PLANE, {100, 650},1.0f},
                    {ENEMY_RANGED_PLANE, {100, 650},1.5f},
                    {ENEMY_TURRET, {100, 650},2.0f},
                    {ENEMY_MELEE_PLANE, {100, 650},2.5f},
                    {ENEMY_MELEE_PLANE, {100, 650},3.0f}},
                        11.0f, 5};

    EnemyWave wave1 = {.enemies = { {ENEMY_TURRET, {100, 100}, 1}}, 14, 1};

    Level level = {.waves = {wave1, wave2, wave3, wave4}, 4};
    Vector2 vect = {100, 100};


    //pravljenje pocetnog prozora i postavljanje najveceg dozvoljenog FPS-a
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "2026: Cyber Attack");
    InitAudioDevice();
    SetTargetFPS(60);

    GraphicAssets assets = {0};
    assets.highestScores = NULL;
    Vector2 pozicijaAviona = {100, 100};
    InitGlavni(&assets);
    InitPause(&assets);
    //PlayMusicStream(assets.mainMenu);

    //mape za svaki nivo
    float map1Offset = 0.0f, map1Speed = 100.0f;
    float map2Offset = 0.0f, map2Speed = 100.0f;
    float map3Offset = 0.0f, map3Speed = 100.0f;

    Map level1Map = {assets.background1, map1Offset, map1Offset,  map1Speed, true, 3, 0};
    Map level2Map = {assets.background2, map2Offset, map1Offset, map2Speed, true, 3, 0};
    Map level3Map = {assets.background3, map3Offset, map1Offset,map3Speed, true, 5, 0};

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
        if (!assets.isPaused) globalLeveltimer+=dt;

        switch (currScreen) {
            case LEVEL1:
                StartLevel(&level, &gamestate, &globalLeveltimer);
                break;
            case LEVEL2:
                StartLevel(&level, &gamestate, &globalLeveltimer);
                break;
            default:
                break;
        }

        if (fire_timer > 600) {
            fire_timer = 0.0f; //ako je igrac bio afk duze od 10 minuta fire timer se resetuje
        }

        if (fire_timer > (1/gamestate.player.fireRate) && IsKeyDown(KEY_K) && gamestate.player.ammo > 0) {
            PlayerShootBullet(&gamestate,&gamestate.player);
            //Shoot(PLAYER, gamestate.projectiles, gamestate.player.playerPos, 5, 750, (Vector2){0, 0}, &gamestate.player);
            fire_timer = 0;
        }

        if(IsKeyDown(KEY_H)) { //sluzi za dopunu municije i hp samo dok se testira
            gamestate.player.ammo = 100;
            gamestate.player.lives = 10;
        }

        UpdatePlayerPosition(&gamestate.player);
        UpdateInvincibility(&gamestate.player, dt, INVINCIBILITY_TIME);
        UpdateDash(&gamestate.player, dt, DASH_TIME, gamestate.player.mvmntVect);

        UpdateProjectiles(gamestate.projectiles);
        UpdateEnemies(&gamestate);
        CheckCollisions(&gamestate);

        //Ova linija treba da se ukljuci kada bude potreban pause meni
        assets.mis = GetMousePosition();
        if (IsKeyPressed(KEY_ESCAPE)) assets.isPaused = assets.isPaused == 0? 1: 0;

        ///////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////
        //CRTANJE
        BeginDrawing();
        ClearBackground(BackgroundColor);
        switch (currScreen) {
            case 1:
                MoveMap(&level1Map, &gamestate);
                break;
            case 2:
                MoveMap(&level2Map, &gamestate);
                break;
            case 3:
                MoveMap(&level3Map, &gamestate);
                break;
            default:
                break;
        }

        //DrawPlayer(gamestate.player, &assets);
        DrawPlaneGUI(&gamestate.player.playerPos, &assets);
        DrawPowerUps(gamestate.powerups);
        DrawProjectiles(gamestate.projectiles);
        DrawEnemies(gamestate.enemies);//Wrappuj ove tri funkcije u DrawGameState
        PrikaziStats(gamestate.player.score, gamestate.player.lives,gamestate.player.ammo , &assets);

        //Ovo ispod je za test glavnog menija, pauseMenija i GUI-a aviona, u nekom trenutku ce biti potrebno
        /*if (assets.isPaused) {
            CrtajPause(&assets);
        }
        else if (assets.fja == NULL) {
            CrtajMeni(&pozicija ,&vreme, &providnost, &assets);
            //DrawTurret(assets.turret, (Vector2){100, 400}, rotation);
            //DrawRectangle(0, 0, windowWidth, windowHeight, BLACK);
            //DrawPlaneGUI(&pozicijaAviona, &assets);
            //DrawExplosion(&assets, pozicijaAviona, IsKeyPressed(KEY_K));
            guideMenu = true;
        }
        else {
            if (assets.fja == DrawGameOverScreen && guideMenu) {
                assets.fja(&assets, assets.currScore);
            }
            else {
                assets.fja(&assets, 0);
            }
        }*/
        //Linije iznad treba da se ukljuce kada budu bili potrebni glavni i pause meni
        EndDrawing();
        ///////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////
    }
    UnloadAssets(&assets);
    CloseWindow();
    return 0;
}
