//#include "raylib.h" Ne treba include jer je raylib vec ukljucen u drugim header fajlovima
#include <math.h>
#include "mechanics.h"
#include "AI.h"
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define PROJECTILE_CAP 100
#define ENEMY_CAP 100
int main() {
    //inicijalizacija igraca (sve se ovo moze proizvoljno menjati)
    Player player = InitPlayer((Vector2) {WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 1.25},20,500.0f,3,10);
    float fire_timer =0.0f;//Prebaciti ovo verovatno u logiku za igraca nekakvu
    float spawn_timer =4.0f;

    Projectile projectiles[PROJECTILE_CAP];
    Enemy enemies[ENEMY_CAP];

    for (int i=0; i<PROJECTILE_CAP; i++) {
        projectiles[i].active = false;
    }
    for (int i=0; i<ENEMY_CAP; i++) {
        enemies[i].active = false;
    }
    //pravljenje pocetnog prozora i postavljanje najveceg dozvoljenog FPS-a
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "2026: Cyber Attack");
    SetTargetFPS(60);
    //Game Loop
    while(!WindowShouldClose()) {
        Color background = {67, 67, 69, 255}; //OVU BOJU CEMO SVAKAKO SKLONITI KAD TAD

        float dt = GetFrameTime(); //delta time potreban da bi na svakom kompu igra isla istom brzinom
        fire_timer+=dt;
        spawn_timer+=dt;

        if (spawn_timer>3) {
            spawn_timer=0;
            SpawnEnemy(enemies,MELEE_PLANE,(Vector2){500,1000});
            //Iz nekog razloga se ekran zacrni kada se ovde stavi window height
        }
        if (fire_timer > 600) {
            fire_timer = 0.0f; //ako je igrac bio afk duze od 10 minuta fire timer se resetuje
        }

        if (fire_timer > (1/player.fireRate) && IsKeyDown(KEY_K)) {
            Shoot(projectiles, player.playerPos, 5, 750);
            fire_timer = 0;
        }

        UpdatePlayerPosition(&player);
        UpdateProjectiles(projectiles);
        UpdateEnemies(enemies);

        //CRTANJE
        BeginDrawing();
        ClearBackground(background);
        DrawPlayer(player);
        DrawProjectiles(projectiles);
        DrawEnemies(enemies);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}