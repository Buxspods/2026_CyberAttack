#include"raylib.h"
#include"assets.h"
#include<stdio.h>
#include<string.h>
#include"glavniMeni.h"
#include"highest-score.h"
#define windowWidth 1000
#define windowHeight 1000


void DrawGameOverScreen(GraphicAssets *assets, int score) {
    DrawTexture(assets->background, 0, 0, WHITE);
    //Kada igrac umre, pre dodeljivanja funkcije, staviti assets.score = score koji je igrac imao pre nego sto je umro
    static bool scores = false;
    if (!scores) {
        scores = true;
    }
    DrawRectangle(0, 0, windowWidth, windowHeight, Fade(BLACK, 0.5f));

    Vector2 dimNaslov = MeasureTextEx(assets->fontOrbitron, "GAME OVER", 70, 2);
    DrawTextEx(assets->fontOrbitron, "GAME OVER", (Vector2){windowWidth/2.0f - dimNaslov.x/2.0f, 0.15f*windowHeight}, 70, 2, WHITE);

    char scoreText[30];
    sprintf(scoreText, "SCORE: %d", score);
    Vector2 dimScore = MeasureTextEx(assets->fontOrbitron, scoreText, 40, 2);
    DrawTextEx(assets->fontOrbitron, scoreText, (Vector2){windowWidth/2.0f - dimScore.x/2.0f, 0.25f*windowHeight}, 40, 2, WHITE);


    Vector2 dimPlayAgain = MeasureTextEx(assets->fontOrbitron, "PLAY AGAIN", 40, 2);
    Rectangle recPlayAgain = {windowWidth/2.0f - dimPlayAgain.x/2.0f, 0.4f*windowHeight, dimPlayAgain.x, dimPlayAgain.y};
    DrawTextEx(assets->fontOrbitron, "PLAY AGAIN", (Vector2){windowWidth/2.0f - dimPlayAgain.x/2.0f, 0.4f*windowHeight}, 40, 2, WHITE);
    bool isHovered = CheckCollisionPointRec(assets->mis, recPlayAgain);
    if (isHovered) {
        DrawTextEx(assets->fontOrbitron, "PLAY AGAIN", (Vector2){windowWidth/2.0f - dimPlayAgain.x/2.0f, 0.4f*windowHeight}, 40, 2, BLUE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            //funkcija koja pokrece igru
            scores = false;
        }
    }

    Vector2 dimGuide = MeasureTextEx(assets->fontOrbitron, "GUIDE", 40, 2);
    Rectangle recGuide = {windowWidth/2.0f - dimGuide.x/2.0f, 0.45f*windowHeight, dimGuide.x, dimGuide.y};
    DrawTextEx(assets->fontOrbitron, "GUIDE", (Vector2){windowWidth/2.0f - dimGuide.x/2.0f, 0.45f*windowHeight}, 40, 2, WHITE);
    bool isHovered2 = CheckCollisionPointRec(assets->mis, recGuide);
    if (isHovered2) {
        DrawTextEx(assets->fontOrbitron, "GUIDE", (Vector2){windowWidth/2.0f - dimGuide.x/2.0f, 0.45f*windowHeight}, 40, 2, BLUE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            //funkcija koja pokrece igru
            assets->prethodnaFja = assets->fja;
            assets->fja = Guide;
        }
    }

    Vector2 dimMainMenu = MeasureTextEx(assets->fontOrbitron, "BACK TO MAIN MENU", 40, 2);
    Rectangle recMainMenu = {windowWidth/2.0f - dimMainMenu.x/2.0f, 0.5f*windowHeight, dimMainMenu.x, dimMainMenu.y};
    DrawTextEx(assets->fontOrbitron, "BACK TO MAIN MENU", (Vector2){windowWidth/2.0f - dimMainMenu.x/2.0f, 0.5f*windowHeight}, 40, 2, WHITE);
    bool isHovered3 = CheckCollisionPointRec(assets->mis, recMainMenu);
    if (isHovered3) {
        DrawTextEx(assets->fontOrbitron, "BACK TO MAIN MENU", (Vector2){windowWidth/2.0f - dimMainMenu.x/2.0f, 0.5f*windowHeight}, 40, 2, BLUE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            assets->prethodnaFja = assets->fja;
            assets->fja = NULL;
            scores = false;
        }
    }
}