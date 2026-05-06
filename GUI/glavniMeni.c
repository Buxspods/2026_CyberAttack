#include"raylib.h"
#include"glavniMeni.h"
#include<math.h>
#include<stdlib.h>
#include<string.h>

void StartNewGame() {
    return;
}
void LoadGame() {
    return;
}
void HighestScores() {
    return;
}
void Controls() {
    return;
}
void Settings() {
    return;
}
void ExitGame() {
    CloseWindow();
    exit(0);
}

void CrtajMeni(Vector2 *pozicija, float *vreme, float *providnost) {
    DrawTexture(background, 0, 0, WHITE);
    Vector2 misPozicija = GetMousePosition();
    *vreme+= GetFrameTime();
    float lebdenje = sinf((*vreme)*2.0f)*0.5f;

    pozicija->y += lebdenje;
    DrawTextEx(font_orbitron, "2026: Cyber Attack", (Vector2){pozicija->x - 4, pozicija->y + 4}, 70, 2, BLUE);
    DrawTextEx(font_orbitron, "2026: Cyber Attack", *pozicija, 70, 2, WHITE);

    for (int i = 0; i < 6; i++) {
        Color color1 = WHITE;
        Color color2 = BLUE;
        Rectangle textHitBox = {opcije[i].pozicija.x, opcije[i].pozicija.y, opcije[i].dimenzija.x, opcije[i].dimenzija.y};
        if (CheckCollisionPointRec(misPozicija, textHitBox)) {
            color1 = BLUE;
            color2 = WHITE;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                opcije[i].akcija();
            }
        }
        DrawTextEx(font_exo, opcije[i].naziv, (Vector2){opcije[i].pozicija.x - 1.5f, opcije[i].pozicija.y + 1.5f}, 50, 2, color2);
        DrawTextEx(font_exo, opcije[i].naziv, opcije[i].pozicija, 50, 2, color1);
    }
    if (*providnost > 0.0f) {
        DrawRectangle(0, 0, windowWidth, windowHeight, Fade(BLACK, *providnost));
        *providnost -= 0.5f * GetFrameTime();
    }
}

void InitGlavni() {
    font_exo = LoadFontEx("resources/fonts/exo_2/ExoBold-qxl5.otf", 64, 0, 0);
    font_orbitron = LoadFontEx("resources/fonts/orbitron/OrbitronBlack-n6dV.ttf", 64, 0, 0);
    press_start_2p = LoadFontEx("resources/fonts/press_start_2p/PressStart2P-Regular.ttf", 64, 0 , 0);
    background = LoadTexture("resources/images/background.png");

    memcpy(opcije, (MeniOpcija[]){
    {"START NEW GAME", {0,0}, {0, 0}, StartNewGame},
    {"LOAD GAME", {0,0}, {0, 0}, LoadGame},
    {"HIGHEST SCORES", {0,0}, {0, 0}, HighestScores},
    {"CONTROLS", {0,0}, {0, 0}, Controls},
    {"SETTINGS",{0, 0}, {0, 0}, Settings},
    {"EXIT GAME", {0,0}, {0, 0}, ExitGame}
}, sizeof(opcije));

    for (int i = 0; i < 6; i++) {
        opcije[i].dimenzija = (Vector2)MeasureTextEx(font_exo, opcije[i].naziv, 40, 2);
        opcije[i].pozicija.x = windowWidth / 2.0f - opcije[i].dimenzija.x / 2;
        opcije[i].pozicija.y = (float)i*windowHeight*0.065f + windowHeight*0.35f;
    }
}