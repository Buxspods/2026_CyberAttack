#include"raylib.h"
#include"glavniMeni.h"
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "endScreen.h"

void StartNewGame(GraphicAssets *assets, int score) {
    DrawTexture(assets->background, 0, 0, WHITE);
    DrawRectangle(0, 0, windowWidth, windowHeight, Fade(BLACK, 0.5f));

    Vector2 dimPlayAgain = MeasureTextEx(assets->fontOrbitron, "LEVEL 1", 40, 2);
    Rectangle recPlayAgain = {windowWidth/2.0f - dimPlayAgain.x/2.0f, 0.4f*windowHeight, dimPlayAgain.x, dimPlayAgain.y};
    DrawTextEx(assets->fontOrbitron, "LEVEL 1", (Vector2){windowWidth/2.0f - dimPlayAgain.x/2.0f, 0.4f*windowHeight}, 40, 2, WHITE);
    bool isHovered = CheckCollisionPointRec(assets->mis, recPlayAgain);
    if (isHovered) {
        DrawTextEx(assets->fontOrbitron, "LEVEL 1", (Vector2){windowWidth/2.0f - dimPlayAgain.x/2.0f, 0.4f*windowHeight}, 40, 2, BLUE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            StopMusicStream(assets->level2);
            StopMusicStream(assets->level3);
            StopMusicStream(assets->mainMenu);
            PlayMusicStream(assets->level1);
        }
    }

    Vector2 dimGuide = MeasureTextEx(assets->fontOrbitron, "LEVEL 2", 40, 2);
    Rectangle recGuide = {windowWidth/2.0f - dimGuide.x/2.0f, 0.45f*windowHeight, dimGuide.x, dimGuide.y};
    DrawTextEx(assets->fontOrbitron, "LEVEL 2", (Vector2){windowWidth/2.0f - dimGuide.x/2.0f, 0.45f*windowHeight}, 40, 2, WHITE);
    bool isHovered2 = CheckCollisionPointRec(assets->mis, recGuide);
    if (isHovered2) {
        DrawTextEx(assets->fontOrbitron, "LEVEL 2", (Vector2){windowWidth/2.0f - dimGuide.x/2.0f, 0.45f*windowHeight}, 40, 2, BLUE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            StopMusicStream(assets->level1);
            StopMusicStream(assets->level3);
            StopMusicStream(assets->mainMenu);
            PlayMusicStream(assets->level2);
        }
    }

    Vector2 dimMainMenu = MeasureTextEx(assets->fontOrbitron, "LEVEL 3", 40, 2);
    Rectangle recMainMenu = {windowWidth/2.0f - dimMainMenu.x/2.0f, 0.5f*windowHeight, dimMainMenu.x, dimMainMenu.y};
    DrawTextEx(assets->fontOrbitron, "LEVEL 3", (Vector2){windowWidth/2.0f - dimMainMenu.x/2.0f, 0.5f*windowHeight}, 40, 2, WHITE);
    bool isHovered3 = CheckCollisionPointRec(assets->mis, recMainMenu);
    if (isHovered3) {
        DrawTextEx(assets->fontOrbitron, "LEVEL 3", (Vector2){windowWidth/2.0f - dimMainMenu.x/2.0f, 0.5f*windowHeight}, 40, 2, BLUE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            StopMusicStream(assets->level1);
            StopMusicStream(assets->level2);
            StopMusicStream(assets->mainMenu);
            PlayMusicStream(assets->level3);
        }
    }

    Rectangle backHitBox = { 40, 40, 180, 45 };
    DrawTextEx(assets->fontExo, "< BACK", (Vector2){ backHitBox.x + 2, backHitBox.y + 2 }, 35, 2, DARKBLUE);
    DrawTextEx(assets->fontExo, "< BACK", (Vector2){ backHitBox.x, backHitBox.y }, 35, 2, WHITE);
    if (CheckCollisionPointRec(assets->mis, (Rectangle){40, 40, 180, 45}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        StopMusicStream(assets->level1);
        StopMusicStream(assets->level3);
        StopMusicStream(assets->level2);
        PlayMusicStream(assets->mainMenu);
        assets->prethodnaFja = assets->fja;
        assets->fja = NULL;
    }
}
void LoadGame(GraphicAssets *assets, int score) {
    Rectangle backHitBox = { 40, 40, 180, 45 };
    DrawTextEx(assets->fontExo, "< BACK", (Vector2){ backHitBox.x + 2, backHitBox.y + 2 }, 35, 2, DARKBLUE);
    DrawTextEx(assets->fontExo, "< BACK", (Vector2){ backHitBox.x, backHitBox.y }, 35, 2, WHITE);
    if (CheckCollisionPointRec(assets->mis, (Rectangle){40, 40, 180, 45}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        assets->prethodnaFja = assets->fja;
        assets->fja = NULL;
    }
}
void HighestScores(GraphicAssets *assets, int score) {
    DrawTexture(assets->background, 0, 0, WHITE);
    DrawRectangle(0, 0, windowWidth, windowHeight, Fade(BLACK, 0.5f));

    static bool podaciUcitani = false;
    static int numberOfLines = 0;

    if (!podaciUcitani) {
        ReadScores(assets);
        numberOfLines = ReturnNumberOfLines(assets);
        if (numberOfLines > 10) numberOfLines = 10;

        podaciUcitani = true;
    }

    Vector2 dimNaslov = MeasureTextEx(assets->fontOrbitron, "Highest scores", 60, 2);
    DrawTextEx(assets->fontOrbitron, "Highest Scores", (Vector2){windowWidth/2.0f - dimNaslov.x / 2, 150}, 60, 2, WHITE);

    if (numberOfLines == 0 || assets->highestScores == NULL) {
        Vector2 dimPrazno = MeasureTextEx(assets->fontExo, "NO RECORDS YET", 40, 2);
        DrawTextEx(assets->fontExo, "NO RECORDS YET", (Vector2){windowWidth / 2.0f - dimPrazno.x / 2, windowHeight * 0.45f}, 40, 2, GRAY);
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
    Rectangle backHitBox = { 40, 40, 180, 45 };
    DrawTextEx(assets->fontExo, "< BACK", (Vector2){ backHitBox.x + 2, backHitBox.y + 2 }, 35, 2, DARKBLUE);
    DrawTextEx(assets->fontExo, "< BACK", (Vector2){ backHitBox.x, backHitBox.y }, 35, 2, WHITE);
    if (CheckCollisionPointRec(assets->mis, (Rectangle){40, 40, 180, 45}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        podaciUcitani = false;
        assets->fja = assets->prethodnaFja;
        assets->prethodnaFja = HighestScores;
    }
}
void Guide(GraphicAssets *assets, int score) {
    DrawTexture(assets->background, 0, 0, WHITE);
    DrawRectangle(0, 0, windowWidth, windowHeight, Fade(BLACK, 0.5f));

    Vector2 dimNaslov = MeasureTextEx(assets->fontOrbitron, "Guide", 60, 2);
    DrawTextEx(assets->fontOrbitron, "Guide", (Vector2){windowWidth/2.0f - dimNaslov.x / 2, 150}, 60, 2, WHITE);

    char *text[] = {"W, S, A, D - Movements (Up, Down, Left, Right)", "K - Shooting", "SHIFT - Dash","ESC - Pause Menu","- Power Up Health", " - Power Up Ammo", " - Power Up Speed", " - Turret", " - Ranged Plane", "\t - Meele Plane", "\t - Final Boss"};
    Texture teksture[] = {assets->powerUpHealth, assets->powerUpAmmo, assets->powerUpSpeed, assets->turret, assets->ranged, assets->meele, assets->finalBoss};

    FILE *fajl = fopen("documents/controls.txt", "r");
    if (fajl != NULL) {
        char temp[100];
        int brojac = 0;

        while (fgets(temp, sizeof(temp), fajl) != NULL && brojac < 4) {
            temp[strcspn(temp, "\n")] = '\0';
            text[brojac] = (char *)malloc((strlen(temp) + 1) * sizeof(char));
            strcpy(text[brojac], temp);
            brojac++;
        }
    }
    fclose(fajl);


    for (int i = 0; i< 11;i++) {
        Vector2 rec = (Vector2)MeasureTextEx(assets->fontExo, text[i], 30, 2);
        Vector2 pozicija = (Vector2){windowWidth / 2.0f - rec.x / 2, (float)i*windowHeight*0.055f + windowHeight*0.25f};
        if (i>3) {
            if (i == 10) {
                pozicija = (Vector2){windowWidth / 2.0f - rec.x / 2, (float)(i+1)*windowHeight*0.055f + windowHeight*0.25f};
                DrawTextEx(assets->fontExo, text[i], pozicija, 30, 2, WHITE);
                DrawTexture(teksture[i-4], pozicija.x - 75, pozicija.y - 10, WHITE);
            }
            else {
                DrawTexture(teksture[i-4], pozicija.x - 50, pozicija.y - 10, WHITE);
            }
        }
        DrawTextEx(assets->fontExo, text[i], pozicija, 30, 2, WHITE);
    }

    Rectangle backHitBox = { 40, 40, 180, 45 };
    DrawTextEx(assets->fontExo, "< BACK", (Vector2){ backHitBox.x + 2, backHitBox.y + 2 }, 35, 2, DARKBLUE);
    DrawTextEx(assets->fontExo, "< BACK", (Vector2){ backHitBox.x, backHitBox.y }, 35, 2, WHITE);
    if (CheckCollisionPointRec(assets->mis, (Rectangle){40, 40, 180, 45}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        assets->fja = assets->prethodnaFja;
        assets->prethodnaFja = Guide;
    }
}
void Settings(GraphicAssets *assets, int score) {
    Rectangle backHitBox = { 40, 40, 180, 45 };
    DrawTextEx(assets->fontExo, "< BACK", (Vector2){ backHitBox.x + 2, backHitBox.y + 2 }, 35, 2, DARKBLUE);
    DrawTextEx(assets->fontExo, "< BACK", (Vector2){ backHitBox.x, backHitBox.y }, 35, 2, WHITE);
    if (CheckCollisionPointRec(assets->mis, (Rectangle){40, 40, 180, 45}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        assets->fja = assets->prethodnaFja;
        assets->prethodnaFja = Settings;
    }
}
void ExitGame(GraphicAssets *assets, int score) {
    CloseWindow();
    exit(0);
}

void CrtajMeni(Vector2 *pozicija,float *vreme, float *providnost, GraphicAssets *assets) {
    DrawTexture(assets->background, 0, 0, WHITE);
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
                assets->prethodnaFja = assets->fja;
                assets->fja = assets->opcije[i].akcija;
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
    assets->eksplozija = LoadTexture("resources/images/eksplozija.png");
    assets->turret = LoadTexture("resources/images/turret.png");
    assets->meele = LoadTexture("resources/images/meele-plane.png");
    assets->ranged = LoadTexture("resources/images/ranged.png");
    assets->background1 = LoadTexture("resources/images/slika_1000px.png");
    assets->background2 = LoadTexture("resources/images/slika2_1000px.png");
    assets->background3 = LoadTexture("resources/images/slika3_1000px.png");
    assets->finalBoss = LoadTexture("resources/images/final-boss.png");
    assets->explosion = LoadSound("resources/audio/explosion.wav");
    assets->gameOver = LoadSound("resources/audio/game-over.wav");
    assets->hit1 = LoadSound("resources/audio/hit1.wav");
    assets->hit2 = LoadSound("resources/audio/hit2.wav");
    assets->powerUp = LoadSound("resources/audio/powerUp.wav");
    assets->laser = LoadSound("resources/audio/laser.wav");
    assets->bossLaser = LoadSound("resources/audio/boss-laser.wav");
    assets->mainMenu = LoadMusicStream("resources/audio/mainMenu.mp3");
    assets->level1 = LoadMusicStream("resources/audio/level1.mp3");
    assets->level2 = LoadMusicStream("resources/audio/level2.mp3");
    assets->level3 = LoadMusicStream("resources/audio/level3.mp3");

    FILE *fajl = fopen("documents/audio.txt", "r");
    if (fajl != NULL) {
        char temp1[100], temp2[100];
        char music1[4], sfx1[4];
        float music = 0.0f, sfx = 0.0f;

        fgets(temp1, sizeof(temp1), fajl);
        fgets(temp2, sizeof(temp2), fajl);
        char *p1 = strchr(temp1, ':');
        char *p2 = strchr(temp2, ':');

        if (p1 && p2) {
            music = atof(p1+1)/100.0;
            sfx = atof(p2+1)/100.0;
        }
        SetMusicVolume(assets->mainMenu, music);
        SetMusicVolume(assets->level1, music);
        SetMusicVolume(assets->level2, music);
        SetMusicVolume(assets->level3, music);

        SetSoundVolume(assets->hit1, sfx);
        SetSoundVolume(assets->hit2, sfx);
        SetSoundVolume(assets->laser, sfx);
        SetSoundVolume(assets->bossLaser, sfx);
        SetSoundVolume(assets->explosion, sfx);
        SetSoundVolume(assets->powerUp, sfx);
        SetSoundVolume(assets->gameOver, sfx);
    }
    fclose(fajl);

    assets->mainMenu.looping = true;
    assets->level1.looping = true;
    assets->level2.looping = true;
    assets->level3.looping = true;

    assets->prethodnaFja = NULL;
    assets->fja = NULL;

    memcpy(assets->opcije, (MeniOpcija[]){
    {"START NEW GAME", {0,0}, {0, 0}, StartNewGame},
    {"LOAD GAME", {0,0}, {0, 0}, LoadGame},
    {"HIGHEST SCORES", {0,0}, {0, 0}, HighestScores},
    {"GUIDE", {0,0}, {0, 0}, Guide},
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
    UnloadTexture(assets->eksplozija);
    UnloadTexture(assets->turret);
    UnloadTexture(assets->meele);
    UnloadTexture(assets->ranged);
    UnloadTexture(assets->background1);
    UnloadTexture(assets->background2);
    UnloadTexture(assets->background3);
    UnloadTexture(assets->finalBoss);

    UnloadSound(assets->bossLaser);
    UnloadSound(assets->laser);
    UnloadSound(assets->hit1);
    UnloadSound(assets->hit2);
    UnloadSound(assets->explosion);
    UnloadSound(assets->powerUp);
    UnloadSound(assets->gameOver);

    free(assets->highestScores);
}