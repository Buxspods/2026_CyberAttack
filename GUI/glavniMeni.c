#include"raylib.h"
#include"glavniMeni.h"
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"loadGame.h"
#include "endScreen.h"

void Set_Keys(GraphicAssets *assets) {
    for (int i = 0; i < 7; i++) {
        gamestate.keys[i] = assets->keys[i];
    }
}

void ResetLevel(Level *level) {
    for (int i = 0; i < level->level_size; i++) {
        EnemyWave wave1 = level->waves[i];
        for (int j = 0; j < wave1.waveSize; j++) {
            wave1.enemies[j].spawned = false;
        }
        level->waves[i] = wave1;
    }
}

const char* keyString(int keyID) {
    if (keyID == 341 || keyID == 345) return "CTRL";
    if (keyID == 340) return "SHIFT";
    if (keyID == 256) return "ESC";
    if (keyID == 32)  return "SPACE";
    return TextFormat("%c", (char)keyID);
}

void sacuvajSettings(GraphicAssets *assets) {
    FILE *controls = fopen("documents/controls.txt", "w");
    if (controls == NULL) {
        printf("Fajl prazan!");
        return;
    }
    char textControls[200];
    sprintf(textControls, "%d, %d, %d, %d - Movements\n%d - Shooting\n%d - Dash\n%d - Pause Menu", assets->keys[ACTION_UP], assets->keys[ACTION_DOWN], assets->keys[ACTION_LEFT], assets->keys[ACTION_RIGHT], assets->keys[ACTION_SHOOT], assets->keys[ACTION_DASH], assets->keys[ACTION_PAUSE]);
    fprintf(controls, "%s",textControls);
    fclose(controls);

    FILE *audio = fopen("documents/audio.txt", "w");
    if (audio == NULL) {
        printf("Fajl prazan!");
        return;
    }
    char textAudio[100];
    sprintf(textAudio, "MUSIC:%03d%%\nSFX:%03d%%", (int)(assets->music*100), (int)(assets->sfx*100));
    fprintf(audio, "%s",textAudio);
    fclose(audio);
}

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
            PlaySound(assets->click);
            StopMusicStream(assets->level2);
            StopMusicStream(assets->level3);
            StopMusicStream(assets->mainMenu);
            PlayMusicStream(assets->level1);
            gamestate = InitGameState();
            Set_Keys(assets);
            assets->currLevel = LEVEL1;
            assets->currScreen = LEVEL1;
        }
    }

    Vector2 dimGuide = MeasureTextEx(assets->fontOrbitron, "LEVEL 2", 40, 2);
    Rectangle recGuide = {windowWidth/2.0f - dimGuide.x/2.0f, 0.45f*windowHeight, dimGuide.x, dimGuide.y};
    DrawTextEx(assets->fontOrbitron, "LEVEL 2", (Vector2){windowWidth/2.0f - dimGuide.x/2.0f, 0.45f*windowHeight}, 40, 2, WHITE);
    bool isHovered2 = CheckCollisionPointRec(assets->mis, recGuide);
    if (isHovered2) {
        DrawTextEx(assets->fontOrbitron, "LEVEL 2", (Vector2){windowWidth/2.0f - dimGuide.x/2.0f, 0.45f*windowHeight}, 40, 2, BLUE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySound(assets->click);
            StopMusicStream(assets->level1);
            StopMusicStream(assets->level3);
            StopMusicStream(assets->mainMenu);
            PlayMusicStream(assets->level2);
            gamestate = InitGameState();
            Set_Keys(assets);
            assets->currLevel = LEVEL2;
            assets->currScreen = LEVEL2;
        }
    }

    Vector2 dimMainMenu = MeasureTextEx(assets->fontOrbitron, "LEVEL 3", 40, 2);
    Rectangle recMainMenu = {windowWidth/2.0f - dimMainMenu.x/2.0f, 0.5f*windowHeight, dimMainMenu.x, dimMainMenu.y};
    DrawTextEx(assets->fontOrbitron, "LEVEL 3", (Vector2){windowWidth/2.0f - dimMainMenu.x/2.0f, 0.5f*windowHeight}, 40, 2, WHITE);
    bool isHovered3 = CheckCollisionPointRec(assets->mis, recMainMenu);
    if (isHovered3) {
        DrawTextEx(assets->fontOrbitron, "LEVEL 3", (Vector2){windowWidth/2.0f - dimMainMenu.x/2.0f, 0.5f*windowHeight}, 40, 2, BLUE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySound(assets->click);
            StopMusicStream(assets->level1);
            StopMusicStream(assets->level2);
            StopMusicStream(assets->mainMenu);
            PlayMusicStream(assets->level3);
            gamestate = InitGameState();
            Set_Keys(assets);
            assets->currLevel = LEVEL3;
            assets->currScreen = LEVEL3;
        }
    }

    Rectangle backHitBox = { 40, 40, 180, 45 };
    DrawTextEx(assets->fontExo, "< BACK", (Vector2){ backHitBox.x + 2, backHitBox.y + 2 }, 35, 2, DARKBLUE);
    DrawTextEx(assets->fontExo, "< BACK", (Vector2){ backHitBox.x, backHitBox.y }, 35, 2, WHITE);
    if (CheckCollisionPointRec(assets->mis, (Rectangle){40, 40, 180, 45}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        PlaySound(assets->click);
        StopMusicStream(assets->level1);
        StopMusicStream(assets->level3);
        StopMusicStream(assets->level2);
        PlayMusicStream(assets->mainMenu);
        assets->prethodnaFja = assets->fja;
        assets->fja = NULL;
        //assets->currScreen = MAIN_MENU;
    }
}
void LoadGame(GraphicAssets *assets, int score) {
    DrawTexture(assets->background, 0, 0, WHITE);
    DrawRectangle(0, 0, windowWidth, windowHeight, Fade(BLACK, 0.5f));
    Rectangle backHitBox = { 40, 40, 180, 45 };
    DrawTextEx(assets->fontExo, "< BACK", (Vector2){ backHitBox.x + 2, backHitBox.y + 2 }, 35, 2, DARKBLUE);
    DrawTextEx(assets->fontExo, "< BACK", (Vector2){ backHitBox.x, backHitBox.y }, 35, 2, WHITE);
    if (CheckCollisionPointRec(assets->mis, (Rectangle){40, 40, 180, 45}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        PlaySound(assets->click);
        assets->prethodnaFja = assets->fja;
        assets->fja = NULL;
    }

    DrawTextEx(assets->fontExo, "SELECT SAVED GAME", (Vector2){ windowWidth / 2 - 180, 60 }, 40, 2, BLUE);
    FilePathList saveFiles = LoadDirectoryFiles("savedGames");
    int brFajlova = 0;

    for (int i = 0; i < saveFiles.count; i++) {
        if (DirectoryExists(saveFiles.paths[i])) continue;
        const char* cistoImeFajla = GetFileName(saveFiles.paths[i]);

        const char* slotText = TextFormat("#%d - %s", brFajlova + 1, cistoImeFajla);
        Vector2 dimSlot = MeasureTextEx(assets->fontOrbitron, slotText, 30,2);
        Rectangle recSlot = (Rectangle){windowWidth/2.0f - dimSlot.x / 2, 200.0f + (brFajlova * 80.0f), dimSlot.x, dimSlot.y};
        bool hoverSlot = CheckCollisionPointRec(assets->mis, recSlot);
        DrawTextEx(assets->fontExo, slotText, (Vector2){windowWidth/2.0f - dimSlot.x / 2, 200.0f + (brFajlova * 80.0f)}, 30, 2, (hoverSlot) ? BLUE : WHITE);


        if (hoverSlot && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySound(assets->click);
            InitGameState();
            LoadGame2(cistoImeFajla);
            Set_Keys(assets);

            /*for (int j=0;j<ENEMY_CAP;j++) {
                if (!gamestate.enemies[j].active) {
                    gamestate.enemies[j].deathScore = DEFAULT_DEATH_SCORE;
                    switch (gamestate.enemies[j].type) {
                        case ENEMY_MELEE_PLANE:InitMeelePlane(&gamestate.enemies[j]);break;
                        case ENEMY_TURRET:InitTurret(&gamestate.enemies[j]);break;
                        case ENEMY_RANGED_PLANE:InitRangedPlane(&gamestate.enemies[j]);break;
                        case BOSS:InitBoss(&gamestate.enemies[j]);break;
                    }
                    break;
                }
            }*/

            StopMusicStream(assets->mainMenu);
            if (assets->currLevel == LEVEL1) PlayMusicStream(assets->level1);
            else if (assets->currLevel == LEVEL2) PlayMusicStream(assets->level2);
            else if (assets->currLevel == LEVEL3) PlayMusicStream(assets->level3);
            assets->fja = NULL;

            remove(saveFiles.paths[i]);
            UnloadDirectoryFiles(saveFiles);
            return;
        }
        brFajlova++;
    }

    if (brFajlova == 0) {
        DrawTextEx(assets->fontExo, "NO SAVED GAMES FOUND", (Vector2){ windowWidth / 2 - 170, windowHeight / 2 }, 30, 2, GRAY);
    }
    UnloadDirectoryFiles(saveFiles);
}

void HighestScores(GraphicAssets *assets, int score) {
    if (assets->currScreen == MAIN_MENU) DrawTexture(assets->background, 0, 0, WHITE);
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
        const char* scoreTekst = TextFormat("%02d.%02d.%04d. %02d:%02d \t %d", assets->highestScores[i].dan, assets->highestScores[i].mesec, assets->highestScores[i].godina, assets->highestScores[i].sat, assets->highestScores[i].minut, assets->highestScores[i].score);

        Vector2 dimenzije = MeasureTextEx(assets->fontOrbitron, scoreTekst, 30, 2);
        Vector2 pozicija = {(float)windowWidth / 2.0f - dimenzije.x / 2, (float)i * windowHeight * 0.065f + windowHeight * 0.25f};
        DrawTextEx(assets->fontOrbitron, scoreTekst, pozicija, 30, 2, WHITE);
    }
    Rectangle backHitBox = { 40, 40, 180, 45 };
    DrawTextEx(assets->fontExo, "< BACK", (Vector2){ backHitBox.x + 2, backHitBox.y + 2 }, 35, 2, DARKBLUE);
    DrawTextEx(assets->fontExo, "< BACK", (Vector2){ backHitBox.x, backHitBox.y }, 35, 2, WHITE);
    if (CheckCollisionPointRec(assets->mis, (Rectangle){40, 40, 180, 45}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        PlaySound(assets->click);
        podaciUcitani = false;
        assets->fja = assets->prethodnaFja;
        assets->prethodnaFja = HighestScores;
    }
}
void Guide(GraphicAssets *assets, int score) {
    if (assets->currScreen == MAIN_MENU) DrawTexture(assets->background, 0, 0, WHITE);
    DrawRectangle(0, 0, windowWidth, windowHeight, Fade(BLACK, 0.5f));

    Vector2 dimNaslov = MeasureTextEx(assets->fontOrbitron, "Guide", 60, 2);
    DrawTextEx(assets->fontOrbitron, "Guide", (Vector2){windowWidth/2.0f - dimNaslov.x / 2, 150}, 60, 2, WHITE);

    char kretanje[100];
    char pucanje[100];
    char dash[100];
    char pauza[100];

    sprintf(kretanje, "%s, %s, %s, %s - Movements (Up, Down, Left, Right)", keyString(assets->keys[ACTION_UP]), keyString(assets->keys[ACTION_DOWN]),  keyString(assets->keys[ACTION_LEFT]), keyString(assets->keys[ACTION_RIGHT]));
    sprintf(pucanje, "%s - Shooting", keyString(assets->keys[ACTION_SHOOT]));
    sprintf(dash, "%s - Dash", keyString(assets->keys[ACTION_DASH]));
    sprintf(pauza, "%s - Pause Menu", keyString(assets->keys[ACTION_PAUSE]));

    char *text[] = {kretanje, pucanje, dash, pauza,"- Power Up Health", " - Power Up Ammo", " - Power Up Speed", " - Turret", " - Ranged Plane", "\t - Meele Plane", "\t - Final Boss"};
    Texture teksture[] = {assets->powerUpHealth, assets->powerUpAmmo, assets->powerUpSpeed, assets->turret, assets->ranged, assets->meele, assets->finalBoss};


    for (int i = 0; i< 11;i++) {
        Vector2 rec = (Vector2)MeasureTextEx(assets->fontExo, text[i], 30, 2);
        Vector2 pozicija = (Vector2){windowWidth / 2.0f - rec.x / 2, (float)i*windowHeight*0.055f + windowHeight*0.25f};
        if (i>3) {
            if (i == 10) {
                pozicija = (Vector2){windowWidth / 2.0f - rec.x / 2, (float)(i+1)*windowHeight*0.055f + windowHeight*0.25f};
                DrawTextEx(assets->fontExo, text[i], pozicija, 30, 2, WHITE);
                DrawTexture(teksture[i-4], pozicija.x - 130, pozicija.y - 20, WHITE);
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
        PlaySound(assets->click);
        assets->fja = assets->prethodnaFja;
        assets->prethodnaFja = Guide;
    }
}
void Settings(GraphicAssets *assets, int score) {
    static int music2 = -1;
    static int sfx2 = -1;
    static int promenjeno = 0;
    static float blokadaTajmer = 0.0f;
    static int keyChange = -1;
    static KeyboardKey keys2[7] = {-1, -1, -1, -1, -1, -1, -1};
    char akcije[7][30] = {"MOVE UP - ", "MOVE DOWN - ", "MOVE LEFT - ", "MOVE RIGHT - ", "SHOOT - ", "DASH - ", "PAUSE MENU - "};
    Vector2 akcijeDim[7];
    blokadaTajmer += GetFrameTime();

    if (music2 == -1) {
        music2 = (int)(assets->music*100);
    }
    if (sfx2 == -1) {
        sfx2 = (int)(assets->sfx*100);
    }

    if (assets->currScreen == MAIN_MENU) DrawTexture(assets->background, 0, 0, WHITE);
    DrawRectangle(0, 0, windowWidth, windowHeight, Fade(BLACK, 0.5f));
    Vector2 dimNaslov = MeasureTextEx(assets->fontOrbitron, "Settings", 60, 2);
    DrawTextEx(assets->fontOrbitron, "Settings", (Vector2){windowWidth/2.0f - dimNaslov.x / 2, 0.1f*windowHeight}, 60, 2, WHITE);

    Vector2 dimControls = MeasureTextEx(assets->fontOrbitron, "Controls", 40, 2);
    DrawTextEx(assets->fontOrbitron, "Controls", (Vector2){windowWidth/2.0f - dimControls.x / 2, 0.2f*windowHeight}, 40, 2, WHITE);

    for (int i = 0; i < 7; i++) {
        if (keys2[i] == -1) {
            keys2[i] = assets->keys[i];
        }

        char temp[30];
        sprintf(temp, "%s%s", akcije[i], keyString(keys2[i]));
        akcijeDim[i] = MeasureTextEx(assets->fontOrbitron, temp, 30, 2);
        float kolona = (i % 2 == 0) ? (windowWidth * 0.1f) : (windowWidth * 0.6f);
        float red = 0.28f * windowHeight + ((i / 2) * 0.05f * windowHeight);

        Rectangle textHitBox = {kolona, red, akcijeDim[i].x, akcijeDim[i].y};
        if (CheckCollisionPointRec(assets->mis, textHitBox)) {
            DrawTextEx(assets->fontOrbitron, temp, (Vector2){kolona, red}, 30, 2, BLUE);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                PlaySound(assets->click);
                keyChange = i;
            }
        } else {
            DrawTextEx(assets->fontOrbitron, temp, (Vector2){kolona, red}, 30, 2, WHITE);
        }
    }

    Vector2 dimAudioVideo = MeasureTextEx(assets->fontOrbitron, "Audio", 40, 2);
    DrawTextEx(assets->fontOrbitron, "Audio", (Vector2){windowWidth/2.0f - dimAudioVideo.x / 2, 0.5f*windowHeight}, 40, 2, WHITE);

    Rectangle muzikaBox = { windowWidth / 2.0f - 100, 0.6f*windowHeight, 200, 25 };
    DrawTextEx(assets->fontExo, "MUSIC VOLUME:", (Vector2){muzikaBox.x - 220, muzikaBox.y - 2}, 25, 2, WHITE);
    DrawRectangleRec(muzikaBox, DARKGRAY);
    DrawRectangle(muzikaBox.x, muzikaBox.y, (int)(muzikaBox.width * music2/100.0f), muzikaBox.height, BLUE);
    DrawTextEx(assets->fontExo, TextFormat("%d%%", music2), (Vector2){muzikaBox.x + muzikaBox.width + 20, muzikaBox.y - 2}, 25, 2, WHITE);

    Rectangle sfxBox = { windowWidth / 2.0f - 100, 0.65f*windowHeight, 200, 25 };
    DrawTextEx(assets->fontExo, "SFX VOLUME:", (Vector2){sfxBox.x - 180, sfxBox.y - 2}, 25, 2, WHITE);
    DrawRectangleRec(sfxBox, DARKGRAY);
    DrawRectangle(sfxBox.x, sfxBox.y, (int)(sfxBox.width * sfx2/100.0f), sfxBox.height, BLUE);
    DrawTextEx(assets->fontExo, TextFormat("%d%%", sfx2), (Vector2){sfxBox.x + sfxBox.width + 20, sfxBox.y - 2}, 25, 2, WHITE);

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(assets->mis, muzikaBox) && blokadaTajmer > 0.5f) {
            music2 = (int)(((assets->mis.x - muzikaBox.x) / muzikaBox.width) * 100);
            if (music2 < 0) music2 = 0;
            if (music2 > 100) music2 = 100;

            float vol = (float)music2 / 100.0f;
            SetMusicVolume(assets->mainMenu, vol);
            SetMusicVolume(assets->level1, vol);
            SetMusicVolume(assets->level2, vol);
            SetMusicVolume(assets->level3, vol);
        }
        if (CheckCollisionPointRec(assets->mis, sfxBox) && blokadaTajmer > 0.5f) {
            sfx2 = (int)(((assets->mis.x - sfxBox.x) / sfxBox.width) * 100);
            if (sfx2 < 0) sfx2 = 0;
            if (sfx2 > 100) sfx2 = 100;

            float vol = (float)sfx2 / 100.0f;
            SetSoundVolume(assets->hit1, vol);
            SetSoundVolume(assets->hit2, vol);
            SetSoundVolume(assets->laser, vol);
            SetSoundVolume(assets->bossLaser, vol);
            SetSoundVolume(assets->explosion, vol);
            SetSoundVolume(assets->powerUp, vol);
            SetSoundVolume(assets->gameOver, vol);
            SetSoundVolume(assets->click, vol);
        }
    }

    Vector2 dimSave = MeasureTextEx(assets->fontOrbitron, "Save", 40, 2);
    DrawTextEx(assets->fontOrbitron, "Save", (Vector2){windowWidth/2.0f - dimSave.x / 2, 0.9f*windowHeight}, 40, 2, WHITE);
    Rectangle saveHitBox = {windowWidth/2.0f - dimSave.x / 2, 0.9f*windowHeight, dimSave.x, dimSave.y};
    if (CheckCollisionPointRec(assets->mis, saveHitBox)) {
        DrawTextEx(assets->fontOrbitron, "Save", (Vector2){windowWidth/2.0f - dimSave.x / 2, 0.9f*windowHeight}, 40, 2, BLUE);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            PlaySound(assets->click);
            DrawTextEx(assets->fontOrbitron, "Save", (Vector2){windowWidth/2.0f - dimSave.x / 2, 0.9f*windowHeight}, 40, 2, GRAY);
            promenjeno = 1;
        }
    }

    Rectangle backHitBox = { 40, 40, 180, 45 };
    DrawTextEx(assets->fontExo, "< BACK", (Vector2){ backHitBox.x + 2, backHitBox.y + 2 }, 35, 2, DARKBLUE);
    DrawTextEx(assets->fontExo, "< BACK", (Vector2){ backHitBox.x, backHitBox.y }, 35, 2, WHITE);

    if (keyChange != -1) {
        DrawRectangle(0, 0, windowWidth, windowHeight, Fade(BLACK, 0.7f));
        Vector2 anyKey = MeasureTextEx(assets->fontOrbitron, "Press Any Key...", 40, 2);
        DrawTextEx(assets->fontOrbitron, "Press Any Key...", (Vector2){windowWidth/2.0f - anyKey.x/2, 0.5f*windowHeight}, 40, 2, WHITE);
        KeyboardKey newKey = GetKeyPressed();
        if (newKey > 0) {
            keys2[keyChange] = newKey;
            keyChange = -1;
        }
    }

    if (CheckCollisionPointRec(assets->mis, (Rectangle){40, 40, 180, 45}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        PlaySound(assets->click);
        if (!promenjeno) {
            SetMusicVolume(assets->mainMenu, assets->music);
            SetMusicVolume(assets->level1, assets->music);
            SetMusicVolume(assets->level2, assets->music);
            SetMusicVolume(assets->level3, assets->music);
            SetSoundVolume(assets->hit1, assets->sfx);
            SetSoundVolume(assets->hit2, assets->sfx);
            SetSoundVolume(assets->laser, assets->sfx);
            SetSoundVolume(assets->bossLaser, assets->sfx);
            SetSoundVolume(assets->explosion, assets->sfx);
            SetSoundVolume(assets->powerUp, assets->sfx);
            SetSoundVolume(assets->gameOver, assets->sfx);
            SetSoundVolume(assets->click, assets->sfx);
            music2 = -1;
            sfx2 = -1;
            for (int i = 0; i < 7; i++) {
                keys2[i] = -1;
            }
        }
        else {
            assets->music = (float)music2/100;
            assets->sfx = (float)sfx2/100;
            for (int i = 0; i < 7; i++) {
                assets->keys[i] = keys2[i];
            }
            for (int i = 0; i <7; i++) {
                gamestate.keys[i] = assets->keys[i];
            }
            sacuvajSettings(assets);
        }
        promenjeno = 0;
        blokadaTajmer = 0.0f;

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
                PlaySound(assets->click);
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
    assets->background2 = LoadTexture("resources/images/slika2-1000px.png");
    assets->background3 = LoadTexture("resources/images/slika3_1000px.png");
    assets->finalBoss = LoadTexture("resources/images/final-boss.png");
    assets->metakBoss = LoadTexture("resources/images/metakBoss.png");
    assets->laserBoss1 = LoadTexture("resources/images/bossLaserSprite.png");
    assets->laserBoss2 = LoadTexture("resources/images/bossLaserSprite2.png");
    assets->explosion = LoadSound("resources/audio/explosion.wav");
    assets->gameOver = LoadSound("resources/audio/game-over.wav");
    assets->hit1 = LoadSound("resources/audio/hit1.wav");
    assets->hit2 = LoadSound("resources/audio/hit2.wav");
    assets->powerUp = LoadSound("resources/audio/powerUp.wav");
    assets->laser = LoadSound("resources/audio/laser.wav");
    assets->bossLaser = LoadSound("resources/audio/boss-laser.wav");
    assets->click = LoadSound("resources/audio/click.wav");
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
            assets->music = atof(p1+1)/100.0;
            assets->sfx = atof(p2+1)/100.0;
        }
        SetMusicVolume(assets->mainMenu, assets->music);
        SetMusicVolume(assets->level1, assets->music);
        SetMusicVolume(assets->level2, assets->music);
        SetMusicVolume(assets->level3, assets->music);

        SetSoundVolume(assets->hit1, assets->sfx);
        SetSoundVolume(assets->hit2, assets->sfx);
        SetSoundVolume(assets->laser, assets->sfx);
        SetSoundVolume(assets->bossLaser, assets->sfx);
        SetSoundVolume(assets->explosion, assets->sfx);
        SetSoundVolume(assets->powerUp, assets->sfx);
        SetSoundVolume(assets->gameOver, assets->sfx);
        SetSoundVolume(assets->click, assets->sfx);
    }
    fclose(fajl);

    FILE *kontrole = fopen("documents/controls.txt", "r");

    if (kontrole != NULL) {
        fscanf(kontrole, "%d, %d, %d, %d - Movements (Up, Down, Left, Right)\n", &assets->keys[ACTION_UP], &assets->keys[ACTION_DOWN], &assets->keys[ACTION_LEFT], &assets->keys[ACTION_RIGHT]);
        fscanf(kontrole, "%d - Shooting\n", &assets->keys[ACTION_SHOOT]);
        fscanf(kontrole, "%d - Dash\n", &assets->keys[ACTION_DASH]);
        fscanf(kontrole, "%d - Pause Menu\n", &assets->keys[ACTION_PAUSE]);
        fclose(kontrole);
    } else {
        assets->keys[ACTION_UP] = 87;
        assets->keys[ACTION_DOWN] = 83;
        assets->keys[ACTION_LEFT] = 65;
        assets->keys[ACTION_RIGHT] = 68;
        assets->keys[ACTION_SHOOT] = 75;
        assets->keys[ACTION_DASH] = 340;
        assets->keys[ACTION_PAUSE] = 256;
    }

    for (int i = 0; i <7; i++) {
        gamestate.keys[i] = assets->keys[i];
    }

    assets->mainMenu.looping = true;
    assets->level1.looping = true;
    assets->level2.looping = true;
    assets->level3.looping = true;

    assets->level1Map = (Map){assets->background1, 0.0f, 0.0f, 100.0f, true, 3, 0};
    assets->level2Map = (Map){assets->background2, 0.0f, 0.0f, 100.0f, true, 4, 0};
    assets->level3Map = (Map){assets->background3, 0.0f, 0.0f, 100.0f, true, 5, 0};

    assets->currScreen = MAIN_MENU;
    assets->currLevel = MAIN_MENU;

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