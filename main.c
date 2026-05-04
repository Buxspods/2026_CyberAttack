#include "raylib.h"
#include <math.h>
#include "mechanics.h"
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define PROJECTILE_CAP 100
int main() {
    //inicijalizacija igraca (sve se ovo moze proizvoljno menjati)
    Player player = InitPlayer((Vector2) {WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 1.25},20,500.0f,3,10);
    float fire_timer =0.0f;
    Projectile projectiles[PROJECTILE_CAP];
    for (int i=0; i<PROJECTILE_CAP; i++) {
        projectiles[i].active = false;
    }
    //pravljenje pocetnog prozora i postavljanje najveceg dozvoljenog FPS-a
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "2026: Cyber Attack");
    SetTargetFPS(60);
    //Game Loop
    while(!WindowShouldClose()) {
        Color background = {67, 67, 69, 255}; //OVU BOJU CEMO SVAKAKO SKLONITI KAD TAD

        float dt = GetFrameTime(); //delta time potreban da bi na svakom kompu igra isla istom brzinom
        fire_timer+=dt;

        if (fire_timer > 600) {
            fire_timer = 0.0f; //ako je igrac bio afk duze od 10 minuta fire timer se resetuje
        }

        if (fire_timer > 1/player.fireRate && IsKeyDown(KEY_K)) {
            Shoot(projectiles, player.playerPos, 5, 750);
            fire_timer = 0;
        }
        UpdatePlayerPosition(&player);
        UpdateProjectiles(projectiles);

        //CRTANJE
        BeginDrawing();
        ClearBackground(background);
        DrawPlayer(player);
        drawProjectiles(projectiles);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}