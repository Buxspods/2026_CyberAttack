#include"raylib.h"
#include"glavniMeni.h"
#include"pauseMeni.h"
#include<string.h>

void ResumeGame(GraphicAssets *assets, int score) {
    assets->isPaused = (assets->isPaused == 1)? 0: 1;
}
void ExitAndSave(GraphicAssets *assets, int score) {
    //Za sad
    assets->isPaused = (assets->isPaused == 1)? 0: 1;
}

void CrtajPause(GraphicAssets *assets) {
    DrawRectangle(0, 0, windowWidth, windowHeight, Fade(BLACK, 0.5f));
    for (int i = 0; i < 5; i++) {
        Color color1 = WHITE;
        Color color2 = BLUE;
        Rectangle textHitBox = {assets->opcijePause[i].pozicija.x, assets->opcijePause[i].pozicija.y, assets->opcijePause[i].dimenzija.x, assets->opcijePause[i].dimenzija.y};
        if (CheckCollisionPointRec(assets->mis, textHitBox)) {
            color1 = BLUE;
            color2 = WHITE;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                assets->opcijePause[i].akcija(assets, 0);
            }
        }
        DrawTextEx(assets->fontExo, assets->opcijePause[i].naziv, (Vector2){assets->opcijePause[i].pozicija.x - 1.5f, assets->opcijePause[i].pozicija.y + 1.5f}, 50, 2, color2);
        DrawTextEx(assets->fontExo, assets->opcijePause[i].naziv, assets->opcijePause[i].pozicija, 50, 2, color1);
    }
}

void InitPause(GraphicAssets *assets) {
    memcpy(assets->opcijePause, (MeniOpcija[]){
    {"RESUME GAME", {0,0}, {0, 0}, ResumeGame},
    {"HIGHEST SCORES", {0,0}, {0, 0}, HighestScores},
    {"GUIDE", {0,0}, {0, 0}, Guide},
    {"SETTINGS",{0, 0}, {0, 0}, Settings},
    {"EXIT AND SAVE", {0,0}, {0, 0}, ExitAndSave}
}, sizeof(assets->opcijePause));

    for (int i = 0; i < 5; i++) {
        assets->opcijePause[i].dimenzija = (Vector2)MeasureTextEx(assets->fontExo, assets->opcijePause[i].naziv, 40, 2);
        assets->opcijePause[i].pozicija.x = windowWidth / 2.0f - assets->opcijePause[i].dimenzija.x / 2;
        assets->opcijePause[i].pozicija.y = i*65 + windowHeight * 0.1f + 250;
    }
}