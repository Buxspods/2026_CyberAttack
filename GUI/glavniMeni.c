#include"raylib.h"
#include"glavniMeni.h"
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include "stats.h"
//#include"highest-score.h"

void StartNewGame(GraphicAssets *assets) {
    return;
}
void LoadGame(GraphicAssets *assets) {
    DrawRectangle(20, 20, 20, 20, WHITE);
    if (CheckCollisionPointRec(assets->mis, (Rectangle){20, 20, 20, 20}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        assets->fja = NULL;
    }
}
void HighestScores(GraphicAssets *assets) {
    DrawTexture(assets->background, 0, 0, WHITE);
    DrawRectangle(0, 0, windowWidth, windowHeight, Fade(BLACK, 0.5f));
    int numberOfLines = ReturnNumberOfLines(assets);
    if (numberOfLines > 10) numberOfLines = 10;
    Vector2 dimNaslov = MeasureTextEx(assets->fontOrbitron, "Highest scores", 60, 2);
    DrawTextEx(assets->fontOrbitron, "Highest Scores", (Vector2){windowWidth/2.0f - dimNaslov.x / 2, 150}, 60, 2, WHITE);
    if (numberOfLines == 0) {

    }
    for (int i = 0; i < numberOfLines; i++) {
        const char* scoreTekst = TextFormat("%02d.%02d.%04d. \t %d",
                                        assets->highestScores[i].dan,
                                        assets->highestScores[i].mesec,
                                        assets->highestScores[i].godina,
                                        assets->highestScores[i].score);

        Vector2 dimenzije = MeasureTextEx(assets->fontOrbitron, scoreTekst, 30, 2);
        Vector2 pozicija = {(float)windowWidth / 2.0f - dimenzije.x / 2, (float)i * windowHeight * 0.065f + windowHeight * 0.25f};
        DrawTextEx(assets->fontOrbitron, scoreTekst, pozicija, 30, 2, WHITE);
    }
    DrawRectangle(20, 20, 20, 20, WHITE);
    if (CheckCollisionPointRec(assets->mis, (Rectangle){20, 20, 20, 20}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        assets->fja = NULL;
    }
}
void Controls(GraphicAssets *assets) {
    DrawRectangle(20, 20, 20, 20, WHITE);
    if (CheckCollisionPointRec(assets->mis, (Rectangle){20, 20, 20, 20}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        assets->fja = NULL;
    }
}
void Settings(GraphicAssets *assets) {
    DrawRectangle(20, 20, 20, 20, WHITE);
    if (CheckCollisionPointRec(assets->mis, (Rectangle){20, 20, 20, 20}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        assets->fja = NULL;
    }
}
void ExitGame(GraphicAssets *assets) {
    CloseWindow();
    exit(0);
}

void CrtajMeni(Vector2 *pozicija,float *vreme, float *providnost, GraphicAssets *assets) {
    DrawTexture(assets->background, 0, 0, WHITE);
    //Vector2 misPozicija = GetMousePosition();
    *vreme+= GetFrameTime();
    float lebdenje = sinf((*vreme)*2.0f)*0.5f;

    pozicija->y += lebdenje;
    DrawTextEx(assets->fontOrbitron, "2026: Cyber Attack", (Vector2){pozicija->x - 4, pozicija->y + 4}, 70, 2, BLUE);
    DrawTextEx(assets->fontOrbitron, "2026: Cyber Attack", *pozicija, 70, 2, WHITE);

    for (int i = 0; i < 6; i++) {
        Color color1 = WHITE;
        Color color2 = BLUE;
        Rectangle textHitBox = {assets->opcije[i].pozicija.x, assets->opcije[i].pozicija.y, assets->opcije[i].dimenzija.x, assets->opcije[i].dimenzija.y};
        if (CheckCollisionPointRec(assets->mis, textHitBox)) {
            color1 = BLUE;
            color2 = WHITE;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                assets->fja = assets->opcije[i].akcija;
                assets->opcije[i].akcija(assets);
            }
        }
        DrawTextEx(assets->fontExo, assets->opcije[i].naziv, (Vector2){assets->opcije[i].pozicija.x - 1.5f, assets->opcije[i].pozicija.y + 1.5f}, 50, 2, color2);
        DrawTextEx(assets->fontExo, assets->opcije[i].naziv, assets->opcije[i].pozicija, 50, 2, color1);
    }
    if (*providnost > 0.0f) {
        DrawRectangle(0, 0, windowWidth, windowHeight, Fade(BLACK, *providnost));
        *providnost -= 0.5f * GetFrameTime();
    }
}

void InitGlavni(GraphicAssets *assets) {
    assets->fontExo = LoadFontEx("resources/fonts/exo_2/ExoBold-qxl5.otf", 64, 0, 0);
    assets->fontOrbitron = LoadFontEx("resources/fonts/orbitron/OrbitronBlack-n6dV.ttf", 64, 0, 0);
    assets->fontCommando = LoadFontEx("resources/fonts/commando/commando.ttf", 64, 0 , 0);
    assets->background = LoadTexture("resources/images/background.png");
    assets->srce = LoadTexture("resources/images/srce2.png");
    assets->avionLevo = LoadTexture("resources/images/spritesheetAvionLevo.png");
    assets->avionDesno = LoadTexture("resources/images/spritesheetAvionDesno.png");
    assets->avionPravo = LoadTexture("resources/images/spritesheetAvionPravo.png");
    assets->metak = LoadTexture("resources/images/metak.png");
    assets->powerUpAmmo = LoadTexture("resources/images/powerUpAmmo.png");
    assets->powerUpSpeed = LoadTexture("resources/images/powerUpBrzina.png");
    assets->powerUpHealth = LoadTexture("resources/images/powerUpHealth.png");
    assets->fja = NULL;

    memcpy(assets->opcije, (MeniOpcija[]){
    {"START NEW GAME", {0,0}, {0, 0}, StartNewGame},
    {"LOAD GAME", {0,0}, {0, 0}, LoadGame},
    {"HIGHEST SCORES", {0,0}, {0, 0}, HighestScores},
    {"CONTROLS", {0,0}, {0, 0}, Controls},
    {"SETTINGS",{0, 0}, {0, 0}, Settings},
    {"EXIT GAME", {0,0}, {0, 0}, ExitGame}
}, sizeof(assets->opcije));

    for (int i = 0; i < 6; i++) {
        assets->opcije[i].dimenzija = (Vector2)MeasureTextEx(assets->fontExo, assets->opcije[i].naziv, 40, 2);
        assets->opcije[i].pozicija.x = windowWidth / 2.0f - assets->opcije[i].dimenzija.x / 2;
        assets->opcije[i].pozicija.y = (float)i*windowHeight*0.065f + windowHeight*0.35f;
    }
}

void UnloadAssets(GraphicAssets *assets) {
    UnloadFont(assets->fontExo);
    UnloadFont(assets->fontOrbitron);
    UnloadFont(assets->fontCommando);
    UnloadTexture(assets->background);
    UnloadTexture(assets->srce);
    UnloadTexture(assets->avionDesno);
    UnloadTexture(assets->avionPravo);
    UnloadTexture(assets->avionLevo);
    UnloadTexture(assets->metak);
    UnloadTexture(assets->powerUpAmmo);
    UnloadTexture(assets->powerUpSpeed);
    UnloadTexture(assets->powerUpHealth);
    free(assets->highestScores);
}