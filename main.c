//#include "raylib.h" Ne treba include jer je raylib vec ukljucen u drugim header fajlovima
#include <math.h>
#include "mechanics.h"
#include "AI.h"
#include"GUI.h"
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define PROJECTILE_CAP 100
#define ENEMY_CAP 100

Font font_exo;
Font font_orbitron;
Font press_start_2p;
Texture2D background;
MeniOpcija opcije[6], opcijePause[5];
int isPaused = 0;

int main() {
    float fire_timer =0.0f;//Prebaciti ovo verovatno u logiku za igraca nekakvu
    float spawn_timer =4.0f;
    GameState gamestate = InitGameState();//Inicijalizuje Igraca protivnike i metkove
    //pravljenje pocetnog prozora i postavljanje najveceg dozvoljenog FPS-a
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "2026: Cyber Attack");
    SetTargetFPS(60);

    InitGlavni();
    InitPause();
    Vector2 dimenzije = MeasureTextEx(font_orbitron, "2026: Cyber Attack", 70, 2);
    Vector2 pozicija = {WINDOW_WIDTH / 2.0f - dimenzije.x / 2, WINDOW_WIDTH * 0.125f};
    float vreme = 0.0f;
    float providnost = 1.0f;
    SetExitKey(KEY_NULL);
    //Game Loop
    SpawnEnemy(gamestate.enemies,TURRET,(Vector2){100,100});
    while(!WindowShouldClose()) {
        Color BackgroundColor = {67, 67, 69, 255}; //OVU BOJU CEMO SVAKAKO SKLONITI KAD TAD

        float dt = GetFrameTime(); //delta time potreban da bi na svakom kompu igra isla istom brzinom
        fire_timer+=dt;
        spawn_timer+=dt;

        if (spawn_timer>3) {
            spawn_timer=0;
            SpawnEnemy(gamestate.enemies,MELEE_PLANE,(Vector2){500,1000});
            //Iz nekog razloga se ekran zacrni kada se ovde stavi window height
        }
        if (fire_timer > 600) {
            fire_timer = 0.0f; //ako je igrac bio afk duze od 10 minuta fire timer se resetuje
        }

        if (fire_timer > (1/gamestate.player.fireRate) && IsKeyDown(KEY_K)) {
            Shoot(gamestate.projectiles, gamestate.player.playerPos, 5, 750);
            fire_timer = 0;
        }

        UpdatePlayerPosition(&gamestate.player);
        UpdateProjectiles(gamestate.projectiles);
        UpdateEnemies(&gamestate);

        //Ova linija treba da se ukljuci kada bude potreban pause meni
        //if (IsKeyPressed(KEY_ESCAPE)) isPaused = isPaused == 0? 1: 0;
        //CRTANJE
        BeginDrawing();
        ClearBackground(BackgroundColor);
        DrawPlayer(gamestate.player);
        DrawProjectiles(gamestate.projectiles);
        DrawEnemies(gamestate.enemies);//Wrappuj ove tri funkcije u DrawGameState
        //Linije ispod treba da se ukljuce kada budu bili potrebni glavni i pause meni
        /*CrtajMeni(&pozicija, &vreme, &providnost);
        if (isPaused) {
            CrtajPause();
        }*/
        EndDrawing();
    }
    UnloadFont(font_exo);
    UnloadFont(font_orbitron);
    UnloadFont(press_start_2p);
    UnloadTexture(background);
    CloseWindow();
    return 0;
}