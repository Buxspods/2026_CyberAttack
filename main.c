#include "raylib.h"
#include <math.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define PROJECTILE_CAP 100

typedef struct {
    Vector2 playerPos;
    float playerSize;
    float playerSpeed;
    int lives;
    float fireRate;
    Texture2D texture;
} Player;

typedef struct {
    Vector2 pos;
    float size;
    float speed;
    Texture2D texture;
    bool active;
    Vector2 direction;
}Projectile;

void shoot(Projectile projectiles[],Vector2 pos,float size,float speed) {
    for (int i = 0; i < PROJECTILE_CAP; i++) {
        if (!projectiles[i].active) {
            projectiles[i].active = true;
            projectiles[i].pos = pos;
            projectiles[i].size = size;
            projectiles[i].speed = speed;
            Vector2 direction = {0,-1};
            projectiles[i].direction = direction;
            break;
        }
    }
}
int main() {
    //inicijalizacija igraca (sve se ovo moze proizvoljno menjati)
    Player player = {0};
    player.playerPos = (Vector2) {WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 1.25};
    player.playerSpeed = 500.0f;
    player.playerSize = 20;
    player.lives = 3;
    player.fireRate=10;//Znaci da puca x puta po sekundi
    //Napraviti neku funkciju za inicijalizaciju
    float fire_timer =0.0;
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
        Vector2 movement = {0, 0}; //vektor koji nam govori u kom smeru i pravcu se krece igrac

        //offset pozicije igraca sa vodjenjem racuna o granicama prozora
        if (IsKeyDown(KEY_D)) movement.x += player.playerPos.x < WINDOW_WIDTH - player.playerSize? 1 : 0;
        if (IsKeyDown(KEY_A)) movement.x -= player.playerPos.x > player.playerSize? 1 : 0;
        if (IsKeyDown(KEY_W)) movement.y -= player.playerPos.y > player.playerSize? 1 : 0;
        if (IsKeyDown(KEY_S)) movement.y += player.playerPos.y < WINDOW_HEIGHT - player.playerSize? 1 : 0;

        fire_timer+=dt;
        if ((fire_timer > 1/player.fireRate) && IsKeyDown(KEY_K)) {
            shoot(projectiles, player.playerPos, 5, 750);
            fire_timer = 0;
        }
        //kretanje po dijagonali je bilo brze od horizontalnog ili vertikalnog kretanja pa je moralo ovo da se doda
        if (movement.x != 0 || movement.y != 0) {
            float le = sqrtf(movement.x * movement.x + movement.y * movement.y);
            movement.x /= le;
            movement.y /= le; //le znaci length kao duzina
        }

        player.playerPos.x += movement.x * dt * player.playerSpeed;
        player.playerPos.y += movement.y * dt * player.playerSpeed;

        for (int i = 0; i < PROJECTILE_CAP; i++) {
            if (projectiles[i].active) {
                projectiles[i].pos.x += projectiles[i].speed * dt * projectiles[i].direction.x;
                projectiles[i].pos.y += projectiles[i].speed * dt * projectiles[i].direction.y;//Treba odraditi normalizaciju

                if (projectiles[i].pos.y < projectiles[i].size/2 && projectiles[i].pos.x < projectiles[i].size/2) {//Izlazak iz ekrana
                    projectiles[i].active = false;
                }
            }
        }

        //CRTANJE
        BeginDrawing();
        ClearBackground(background);
        DrawCircleV(player.playerPos, player.playerSize, WHITE);
        for (int i = 0; i < PROJECTILE_CAP; i++) {
            if (projectiles[i].active) {
                DrawCircleV(projectiles[i].pos, projectiles[i].size, RED);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}