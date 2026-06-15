#include"raylib.h"
#include"stats.h"
#include"glavniMeni.h"

void DrawTextGlow(Font font, const char* text, Vector2 pos, float size, Color color) {
    DrawTextEx(font, text, (Vector2){pos.x - 2, pos.y}, size, 2, Fade(WHITE, 0.1f));
    DrawTextEx(font, text, (Vector2){pos.x + 2, pos.y}, size, 2, Fade(WHITE, 0.1f));
    DrawTextEx(font, text, (Vector2){pos.x, pos.y - 2}, size, 2, Fade(WHITE, 0.1f));
    DrawTextEx(font, text, (Vector2){pos.x, pos.y + 2}, size, 2, Fade(WHITE, 0.1f));

    DrawTextEx(font, text, (Vector2){pos.x - 1, pos.y}, size, 2, Fade(WHITE, 0.4f));
    DrawTextEx(font, text, (Vector2){pos.x + 1, pos.y}, size, 2, Fade(WHITE, 0.4f));
    DrawTextEx(font, text, (Vector2){pos.x, pos.y - 1}, size, 2, Fade(WHITE, 0.4f));
    DrawTextEx(font, text, (Vector2){pos.x, pos.y + 1}, size, 2, Fade(WHITE, 0.4f));

    DrawTextEx(font, text, pos, size, 2, color);
}

void PrikaziStats(int score, int lives, int ammo, GraphicAssets *assets) {
    Color color1;
    if (assets->currLevel == LEVEL2) color1 = ORANGE;
    else color1 = SKYBLUE;

    DrawTextGlow(assets->fontCommando, "SCORE", (Vector2){50, 50}, 40, color1);
    DrawTextGlow(assets->fontCommando, TextFormat("%07i", score), (Vector2){50, 90}, 40, color1);
    DrawTextGlow(assets->fontCommando, "AMMO", (Vector2){800, 850}, 40, color1);
    DrawTextGlow(assets->fontCommando, TextFormat("%07i", ammo), (Vector2){800, 900}, 40, color1);
    DrawTextGlow(assets->fontCommando, "LIVES", (Vector2){50, 850}, 40, color1);

    Texture2D srce;
    if (assets->currLevel == LEVEL2) srce = assets->orangeSrce;
    else srce = assets->srce;
    for (int i = 0; i < lives; i++) {
        DrawTexture(srce, (float)i*45 + 35, 900, WHITE);
    }
}