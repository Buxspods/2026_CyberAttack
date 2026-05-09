#ifndef INC_2026_CYBERATTACK_PLANEGUI_H
#define INC_2026_CYBERATTACK_PLANEGUI_H
#include"raylib.h"
#include"assets.h"

void DrawPlaneGUI(Vector2 *pozicija, GraphicAssets *assets);
void DrawPowerUp(Texture2D powerUp, Vector2 position);
void DrawProjectile(Texture2D projectile, Vector2 position);

#endif //INC_2026_CYBERATTACK_PLANEGUI_H
