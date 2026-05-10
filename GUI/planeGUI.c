#include "planeGUI.h"
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
    DrawTextureRec(trenutnaTextura, sourceRec, (Vector2){ pozicija->x - sirinaFrejma/2, pozicija->y }, WHITE);
}

void DrawPowerUp(Texture2D powerUp, Vector2 position) {
    DrawTexture(powerUp, position.x, position.y, WHITE);
}

void DrawProjectile(Texture2D projectile, Vector2 position) {
    DrawTexture(projectile, position.x, position.y, WHITE);
}

void DrawExplosion(GraphicAssets *assets, Vector2 pozicija, bool trigger) {
    static int currentFrame = 0;
    static float frameTimer = 0.0f;
    static bool isPlaying = false;

    int maxFrames = 9;
    float frameSpeed = 15.0f;

    if (trigger) {
        isPlaying = true;
        currentFrame = 0;
        frameTimer = 0.0f;
    }

    if (isPlaying) {
        frameTimer += GetFrameTime();

        if (frameTimer >= (1.0f / frameSpeed)) {
            frameTimer = 0.0f;
            currentFrame++;

            if (currentFrame >= maxFrames) {
                isPlaying = false;
                currentFrame = 0;
            }
        }

        if (isPlaying) {
            float frameWidth = (float)assets->eksplozija.width / maxFrames;
            Rectangle sourceRec = { (float)currentFrame * frameWidth, 0, frameWidth, (float)assets->eksplozija.height };

            BeginBlendMode(BLEND_ADDITIVE);
            DrawTextureRec(assets->eksplozija, sourceRec, pozicija, WHITE);
            EndBlendMode();
        }
    }
}