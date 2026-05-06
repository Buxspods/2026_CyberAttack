#include"raylib.h"
#include"glavniMeni.h"
#include"pauseMeni.h"
#include<string.h>

void ResumeGame() {
    isPaused = (isPaused == 1)? 0: 1;
}
void HighestScores2() {
    return;
}
void Controls2() {
    return;
}
void Settings2() {
    return;
}
void ExitAndSave() {
    //Za sad
    isPaused = (isPaused == 1)? 0: 1;
}

void CrtajPause() {
    Vector2 misPozicija = GetMousePosition();
    DrawRectangle(0, 0, windowWidth, windowHeight, Fade(BLACK, 0.5f));
    for (int i = 0; i < 5; i++) {
        Color color1 = WHITE;
        Color color2 = BLUE;
        Rectangle textHitBox = {opcijePause[i].pozicija.x, opcijePause[i].pozicija.y, opcijePause[i].dimenzija.x, opcijePause[i].dimenzija.y};
        if (CheckCollisionPointRec(misPozicija, textHitBox)) {
            color1 = BLUE;
            color2 = WHITE;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                opcijePause[i].akcija();
            }
        }
        DrawTextEx(font_exo, opcijePause[i].naziv, (Vector2){opcijePause[i].pozicija.x - 1.5f, opcijePause[i].pozicija.y + 1.5f}, 50, 2, color2);
        DrawTextEx(font_exo, opcijePause[i].naziv, opcijePause[i].pozicija, 50, 2, color1);
    }
}

void InitPause() {
    memcpy(opcijePause, (MeniOpcija[]){
    {"RESUME GAME", {0,0}, {0, 0}, ResumeGame},
    {"HIGHEST SCORES", {0,0}, {0, 0}, HighestScores2},
    {"CONTROLS", {0,0}, {0, 0}, Controls2},
    {"SETTINGS",{0, 0}, {0, 0}, Settings2},
    {"EXIT AND SAVE", {0,0}, {0, 0}, ExitAndSave}
}, sizeof(opcijePause));

    for (int i = 0; i < 5; i++) {
        opcijePause[i].dimenzija = (Vector2)MeasureTextEx(font_exo, opcijePause[i].naziv, 40, 2);
        opcijePause[i].pozicija.x = windowWidth / 2.0f - opcijePause[i].dimenzija.x / 2;
        opcijePause[i].pozicija.y = (float)i*windowHeight*0.065f + windowHeight * 0.35f;
    }
}