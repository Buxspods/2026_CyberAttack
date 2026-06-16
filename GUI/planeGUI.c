#include "planeGUI.h"

#include "glavniMeni.h"

void DrawPlaneGUI(Vector2 *pozicija, GraphicAssets *assets) {
    float dt = GetFrameTime();

    static float frameLevo = 0.0f;
    static float frameDesno = 0.0f;
    static float framePravo = 0.0f;
    float animSpeed = 10.0f;

    Texture2D trenutnaTextura;
    int maxFrames;
    float *aktivniFrame;

    if (IsKeyDown(KEY_A)) {
        trenutnaTextura = assets->avionLevo;
        maxFrames = 5;
        aktivniFrame = &frameLevo;
        frameDesno = 0; framePravo = 0;
    }
    else if (IsKeyDown(KEY_D)) {
        trenutnaTextura = assets->avionDesno;
        maxFrames = 5;
        aktivniFrame = &frameDesno;
        frameLevo = 0; framePravo = 0;
    }
    else {
        trenutnaTextura = assets->avionPravo;
        maxFrames = 13;
        aktivniFrame = &framePravo;
        frameLevo = 0; frameDesno = 0;
    }

    *aktivniFrame += animSpeed * dt;
    if (*aktivniFrame >= (float)maxFrames) {
        if (trenutnaTextura.id == assets->avionLevo.id || trenutnaTextura.id == assets->avionDesno.id) {
            *aktivniFrame = (float)maxFrames - 1;
        } else {
            *aktivniFrame = 0;
        }
    }
    float sirinaFrejma = (float)trenutnaTextura.width / (float)maxFrames;
    Rectangle sourceRec = { (int)(*aktivniFrame) * sirinaFrejma, 0, sirinaFrejma, (float)trenutnaTextura.height };
    DrawTextureRec(trenutnaTextura, sourceRec, (Vector2){ pozicija->x - sirinaFrejma/2, pozicija->y - 1.5*20.0f }, WHITE);
    //DrawCircleV((Vector2){pozicija->x, pozicija->y}, 20.0f, WHITE);
}

void DrawPowerUp(Texture2D powerUp, Vector2 position) {
    position.x -=25;
    position.y -= 25;
    DrawTexture(powerUp, position.x, position.y, WHITE);
}

void DrawProjectile(Texture2D projectile, Vector2 position) {
    position.x -= 3;
    position.y -= 3;
    DrawTexture(projectile, position.x, position.y, WHITE);
}

void SpawnExplosion(GraphicAssets *assets, Vector2 pozicija){
    for (int i = 0; i < EXPLOSION_CAP; i++) {

        if (!assets->eksplozije[i].active) {
            assets->eksplozije[i].active = true;
            assets->eksplozije[i].pozicija = pozicija;
            assets->eksplozije[i].currentFrame = 0;
            assets->eksplozije[i].timer = 0.0f;
            break;
        }
    }
}

void DrawExplosion(GraphicAssets *assets){
    int maxFrames = 9;
    float frameSpeed = 15.0f;
    float dt = GetFrameTime();

    for (int i = 0; i < EXPLOSION_CAP; i++) {
        if (!assets->eksplozije[i].active) continue;
        assets->eksplozije[i].timer += dt;

        if (assets->eksplozije[i].timer >= (1.0f / frameSpeed)) {
            assets->eksplozije[i].timer = 0.0f;
            assets->eksplozije[i].currentFrame++;

            if (assets->eksplozije[i].currentFrame >= maxFrames) {
                assets->eksplozije[i].active = false;
                continue;
            }
        }

        float frameWidth = (float)assets->eksplozija.width / maxFrames;
        Rectangle sourceRec = {assets->eksplozije[i].currentFrame * frameWidth,0,frameWidth, (float)assets->eksplozija.height};
        Vector2 pozicijaEksplozije = {assets->eksplozije[i].pozicija.x - frameWidth / 2,assets->eksplozije[i].pozicija.y - assets->eksplozija.height / 2};

        BeginBlendMode(BLEND_ADDITIVE);
        DrawTextureRec(assets->eksplozija, sourceRec,pozicijaEksplozije,WHITE);
        EndBlendMode();
    }
}

void DrawEnemy(Texture2D enemy, Vector2 position, float size) {
    position.x -= (size + 5.0f);
    position.y -= (size + 5.0f);
    DrawTexture(enemy, position.x, position.y, WHITE);
}

void DrawTurret(Texture2D turret, Vector2 position, float rotation) {
    DrawTexturePro(turret, (Rectangle){0, 0, turret.width, turret.height}, (Rectangle){position.x, position.y, turret.width, turret.height}, (Vector2){turret.width/2.0f, turret.height/2.0f}, rotation, WHITE);
}

void DrawLaser(Vector2 position, Texture2D laserTexture){
    static float frame = 0.0f;
    float dt = GetFrameTime();
    float animSpeed = 12.0f;

    position.x -= 25;
    //position.y += 64;
    frame += animSpeed * dt;

    if (frame >= 4.0f)
        frame = 0.0f;

    Rectangle sourceRec = {(int)frame * 53.0f, 0, 53.0f, 1000.0f};
    DrawTextureRec(laserTexture, sourceRec, position, WHITE);
}

void DrawHealthBar(Enemy *e,Vector2 position) {
    Rectangle rec = (Rectangle) {0, 0, 0, 0};
    if (e->type == BOSS) {
        position.x -= 40;
        position.y -= 90;
        rec.width = 80;
    }
    else {
        position.x -= 30;
        position.y -= 40;
        rec.width = 60;
    }
    rec.height = 5;
    rec = (Rectangle){position.x, position.y, rec.width, rec.height};
    Rectangle rec2 = (Rectangle){rec.x, rec.y, ((float)(e->HP)/(float)e->maxHP)*rec.width, rec.height};
    DrawRectangle((int)rec.x - 2, (int)rec.y - 2, (int)rec.width + 4, (int)rec.height + 4, BLACK);
    DrawRectangle((int)rec.x, (int)rec.y, (int)rec.width, (int)rec.height, GRAY);
    DrawRectangle((int)rec2.x, (int)rec2.y, (int)rec2.width, (int)rec2.height, RED);
}