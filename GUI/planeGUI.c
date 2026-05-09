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