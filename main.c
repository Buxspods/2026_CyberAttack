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
    srand(time(NULL));
    float fire_timer =0.0f;//Prebaciti ovo verovatno u logiku za igraca nekakvu
    float spawn_timer =4.0f;
    GameState gamestate = InitGameState();//Inicijalizuje Igraca protivnike i metkove
    //pravljenje pocetnog prozora i postavljanje najveceg dozvoljenog FPS-a
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "2026: Cyber Attack");
    SetTargetFPS(60);

    GraphicAssets assets = {0};
    assets.highestScores = NULL;
    Vector2 pozicijaAviona = {100, 100};

    InitGlavni(&assets);
    InitPause(&assets);

    Vector2 dimenzije = MeasureTextEx(assets.fontOrbitron, "2026: Cyber Attack", 70, 2);
    Vector2 pozicija = {windowWidth / 2.0f - dimenzije.x / 2, windowHeight * 0.125f};
    float vreme = 0.0f;
    float providnost = 1.0f;
    SetExitKey(KEY_NULL);
    //Game Loop
    SpawnEnemy(gamestate.enemies,ENEMY_TURRET,(Vector2){100,100});
    SpawnEnemy(gamestate.enemies,ENEMY_TURRET,(Vector2){900,100});
    //SpawnEnemy(gamestate.enemies,ENEMY_TURRET,(Vector2){100,900});
    //SpawnEnemy(gamestate.enemies,ENEMY_TURRET,(Vector2){450,450});
    //SpawnEnemy(gamestate.enemies,ENEMY_TURRET,(Vector2){900,900});
    //SpawnEnemy(gamestate.enemies,ENEMY_TURRET,(Vector2){550,450});


    while(!WindowShouldClose()) {
        Color BackgroundColor = {67, 67, 69, 255}; //OVU BOJU CEMO SVAKAKO SKLONITI KAD TAD

        float dt = GetFrameTime(); //delta time potreban da bi na svakom kompu igra isla istom brzinom
        fire_timer+=dt;
        spawn_timer+=dt;

        if (spawn_timer>3) {
            spawn_timer=0;
            //SpawnEnemy(gamestate.enemies,ENEMY_MELEE_PLANE,(Vector2){500,1000});
            SpawnEnemy(gamestate.enemies,ENEMY_RANGED_PLANE,(Vector2){0,WINDOW_HEIGHT/2});
            //Iz nekog razloga se ekran zacrni kada se ovde stavi window height
        }
        if (fire_timer > 600) {
            fire_timer = 0.0f; //ako je igrac bio afk duze od 10 minuta fire timer se resetuje
        }

        if (fire_timer > (1/gamestate.player.fireRate) && IsKeyDown(KEY_K) && gamestate.player.ammo > 0) {
            Shoot(PLAYER, gamestate.projectiles, gamestate.player.playerPos, 5, 750, (Vector2){0, 0}, &gamestate.player);
            fire_timer = 0;
        }

        if(IsKeyDown(KEY_H)) { //sluzi za dopunu municije samo dok se testira
            gamestate.player.ammo = 100;
        }

        UpdatePlayerPosition(&gamestate.player);
        UpdateProjectiles(gamestate.projectiles);
        UpdateEnemies(&gamestate);
        CheckCollisions(&gamestate);
       
//
        //Ova linija treba da se ukljuci kada bude potreban pause meni
        assets.mis = GetMousePosition();
        if (IsKeyPressed(KEY_ESCAPE)) assets.isPaused = assets.isPaused == 0? 1: 0;
        //CRTANJE
        BeginDrawing();
        ClearBackground(BackgroundColor);
        DrawPlayer(gamestate.player, &assets);

        //OVO JE KORISCENO SAMO DA SE VIDI HITBOX IGRACA I TO JE TOOOOOO
        //Color newCol = {255, 0, 127, 200};
        //DrawCircle(gamestate.player.playerPos.x, gamestate.player.playerPos.y, gamestate.player.playerSize / 1.5, newCol);

        DrawProjectiles(gamestate.projectiles);
        DrawEnemies(gamestate.enemies);//Wrappuj ove tri funkcije u DrawGameState
        DrawPowerUps(gamestate.powerups);
        PrikaziStats(gamestate.player.score, gamestate.player.lives,gamestate.player.ammo , &assets);

        //Test za crtanje metka i PowerUp-ova
        //DrawPowerUp(assets.powerUpAmmo, (Vector2){400, 100});
        //DrawPowerUp(assets.powerUpHealth, (Vector2){400, 200});
        //DrawPowerUp(assets.powerUpSpeed, (Vector2){400, 300});
        //DrawProjectile(assets.metak, (Vector2){400, 400});
        //Ovo ispod je za test glavnog menija, pauseMenija i GUI-a aviona, u nekom trenutku ce biti potrebno
        /*if (assets.fja == NULL) {
            CrtajMeni(&pozicija ,&vreme, &providnost, &assets);
            //DrawRectangle(0, 0, windowWidth, windowHeight, BLACK);
            DrawPlaneGUI(&pozicijaAviona, &assets);
        }
        else {
            assets.fja(&assets);
            if (assets.isPaused) {
                CrtajPause(&assets);
                int score = 16;
                int lives = 10;
                int ammo = 100;
                PrikaziStats(score, lives, ammo, &assets);
            }
        }*/
        //Linije iznad treba da se ukljuce kada budu bili potrebni glavni i pause meni
        EndDrawing();
    }
    UnloadAssets(&assets);
    CloseWindow();
    return 0;
}