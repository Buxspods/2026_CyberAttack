#include"raylib.h"
#include"assets.h"
#include<stdio.h>
#include<string.h>
#include"glavniMeni.h"
#include"highest-score.h"
#define windowWidth 1000
#define windowHeight 1000

extern GameState gamestate;
/*
 * ZA MACOLU:
 *  U OVE FUNKCIJE ISPOD SAM STAVIO DA SE KAO SCORE NA OVIM END SCREENOVIMA ISPISUJE
 *  SCORE KOJI JE SMESTEN U GAMESTATE-OVOM IGRACU (OVAJ EXTERN GAMESTATE)
 *  JER SE PRE TOGA NIJE LEPO ISPISIVALO I TO JE POPRAVILO PROBLEM//////
*/

void DrawYouWonScreen(GraphicAssets *assets, int score) {
    DrawTexture(assets->background, 0, 0, WHITE);
    //Kada igrac umre, pre dodeljivanja funkcije, staviti assets.score = score koji je igrac imao pre nego sto je umro
    static bool scores = false;
    if (!scores) {
        DodajNoviRezultat(score);
        scores = true;
    }
    DrawRectangle(0, 0, windowWidth, windowHeight, Fade(BLACK, 0.5f));

    Vector2 dimNaslov = MeasureTextEx(assets->fontOrbitron, "YOU WON", 70, 2);
    DrawTextEx(assets->fontOrbitron, "YOU WON", (Vector2){windowWidth/2.0f - dimNaslov.x/2.0f, 0.15f*windowHeight}, 70, 2, WHITE);

    char scoreText[30];
    sprintf(scoreText, "SCORE: %.0f", gamestate.player.score);
    Vector2 dimScore = MeasureTextEx(assets->fontOrbitron, scoreText, 40, 2);
    DrawTextEx(assets->fontOrbitron, scoreText, (Vector2){windowWidth/2.0f - dimScore.x/2.0f, 0.25f*windowHeight}, 40, 2, WHITE);


    Vector2 dimPlayAgain = MeasureTextEx(assets->fontOrbitron, "PLAY AGAIN", 40, 2);
    Rectangle recPlayAgain = {windowWidth/2.0f - dimPlayAgain.x/2.0f, 0.4f*windowHeight, dimPlayAgain.x, dimPlayAgain.y};
    DrawTextEx(assets->fontOrbitron, "PLAY AGAIN", (Vector2){windowWidth/2.0f - dimPlayAgain.x/2.0f, 0.4f*windowHeight}, 40, 2, WHITE);
    bool isHovered = CheckCollisionPointRec(assets->mis, recPlayAgain);
    if (isHovered) {
        DrawTextEx(assets->fontOrbitron, "PLAY AGAIN", (Vector2){windowWidth/2.0f - dimPlayAgain.x/2.0f, 0.4f*windowHeight}, 40, 2, BLUE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySound(assets->click);
            Music muzika = {0};
            switch (assets->currLevel) {
                case LEVEL1:
                    muzika = assets->level1;
                    break;
                case LEVEL2:
                    muzika = assets->level2;
                    break;
                case LEVEL3:
                    muzika = assets->level3;
                    break;
                default:
                    break;
            }
            StopMusicStream(assets->level1);
            StopMusicStream(assets->level3);
            StopMusicStream(assets->mainMenu);
            StopMusicStream(assets->level2);
            PlayMusicStream(muzika);
            assets->level1Map.offset = 0;
            assets->level2Map.offset = 0;
            assets->level3Map.offset = 0;
            assets->level1Map.isMoving = true;
            assets->level2Map.isMoving = true;
            assets->level3Map.isMoving = true;
            gamestate = InitGameState();
            Set_Keys(assets);
            assets->currScreen = assets->currLevel;
            scores = false;
        }
    }

    Vector2 dimMainMenu = MeasureTextEx(assets->fontOrbitron, "BACK TO MAIN MENU", 40, 2);
    Rectangle recMainMenu = {windowWidth/2.0f - dimMainMenu.x/2.0f, 0.5f*windowHeight, dimMainMenu.x, dimMainMenu.y};
    DrawTextEx(assets->fontOrbitron, "BACK TO MAIN MENU", (Vector2){windowWidth/2.0f - dimMainMenu.x/2.0f, 0.5f*windowHeight}, 40, 2, WHITE);
    bool isHovered3 = CheckCollisionPointRec(assets->mis, recMainMenu);
    if (isHovered3) {
        DrawTextEx(assets->fontOrbitron, "BACK TO MAIN MENU", (Vector2){windowWidth/2.0f - dimMainMenu.x/2.0f, 0.5f*windowHeight}, 40, 2, BLUE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySound(assets->click);
            PlayMusicStream(assets->mainMenu);
            assets->prethodnaFja = assets->fja;
            assets->fja = NULL;
            scores = false;
            assets->currLevel = MAIN_MENU; //mora se restartuje gamestate kada se vratimo na main meni da bi moglo da se igra opet
            gamestate = InitGameState();
        }
    }
}

void DrawGameOverScreen(GraphicAssets *assets, int score) {
    DrawTexture(assets->background, 0, 0, WHITE);
    //Kada igrac umre, pre dodeljivanja funkcije, staviti assets.score = score koji je igrac imao pre nego sto je umro
    static bool scores = false;
    if (!scores) {
        DodajNoviRezultat(score);
        scores = true;
    }
    DrawRectangle(0, 0, windowWidth, windowHeight, Fade(BLACK, 0.5f));

    Vector2 dimNaslov = MeasureTextEx(assets->fontOrbitron, "GAME OVER, YOU LOST", 70, 2);
    DrawTextEx(assets->fontOrbitron, "GAME OVER, YOU LOST", (Vector2){windowWidth/2.0f - dimNaslov.x/2.0f, 0.15f*windowHeight}, 70, 2, WHITE);

    char scoreText[30];
    sprintf(scoreText, "SCORE: %.0f", gamestate.player.score);
    Vector2 dimScore = MeasureTextEx(assets->fontOrbitron, scoreText, 40, 2);
    DrawTextEx(assets->fontOrbitron, scoreText, (Vector2){windowWidth/2.0f - dimScore.x/2.0f, 0.25f*windowHeight}, 40, 2, WHITE);


    Vector2 dimPlayAgain = MeasureTextEx(assets->fontOrbitron, "PLAY AGAIN", 40, 2);
    Rectangle recPlayAgain = {windowWidth/2.0f - dimPlayAgain.x/2.0f, 0.4f*windowHeight, dimPlayAgain.x, dimPlayAgain.y};
    DrawTextEx(assets->fontOrbitron, "PLAY AGAIN", (Vector2){windowWidth/2.0f - dimPlayAgain.x/2.0f, 0.4f*windowHeight}, 40, 2, WHITE);
    bool isHovered = CheckCollisionPointRec(assets->mis, recPlayAgain);
    if (isHovered) {
        DrawTextEx(assets->fontOrbitron, "PLAY AGAIN", (Vector2){windowWidth/2.0f - dimPlayAgain.x/2.0f, 0.4f*windowHeight}, 40, 2, BLUE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySound(assets->click);
            Music muzika = {0};
            switch (assets->currLevel) {
                case LEVEL1:
                    muzika = assets->level1;
                    break;
                case LEVEL2:
                    muzika = assets->level2;
                    break;
                case LEVEL3:
                    muzika = assets->level3;
                    break;
                default:
                    break;
            }
            StopMusicStream(assets->level1);
            StopMusicStream(assets->level3);
            StopMusicStream(assets->mainMenu);
            StopMusicStream(assets->level2);
            PlayMusicStream(muzika);
            assets->level1Map.offset = 0;
            assets->level2Map.offset = 0;
            assets->level3Map.offset = 0;
            assets->level1Map.isMoving = true;
            assets->level2Map.isMoving = true;
            assets->level3Map.isMoving = true;
            gamestate = InitGameState();
            Set_Keys(assets);
            assets->currScreen = assets->currLevel;
            scores = false;
        }
    }

    Vector2 dimMainMenu = MeasureTextEx(assets->fontOrbitron, "BACK TO MAIN MENU", 40, 2);
    Rectangle recMainMenu = {windowWidth/2.0f - dimMainMenu.x/2.0f, 0.5f*windowHeight, dimMainMenu.x, dimMainMenu.y};
    DrawTextEx(assets->fontOrbitron, "BACK TO MAIN MENU", (Vector2){windowWidth/2.0f - dimMainMenu.x/2.0f, 0.5f*windowHeight}, 40, 2, WHITE);
    bool isHovered3 = CheckCollisionPointRec(assets->mis, recMainMenu);
    if (isHovered3) {
        DrawTextEx(assets->fontOrbitron, "BACK TO MAIN MENU", (Vector2){windowWidth/2.0f - dimMainMenu.x/2.0f, 0.5f*windowHeight}, 40, 2, BLUE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySound(assets->click);
            assets->prethodnaFja = assets->fja;
            assets->fja = NULL;
            scores = false;
            PlayMusicStream(assets->mainMenu);
            assets->currLevel = MAIN_MENU; //mora se restartuje gamestate kada se vratimo na main meni da bi moglo da se igra opet
            gamestate = InitGameState();
        }
    }
}