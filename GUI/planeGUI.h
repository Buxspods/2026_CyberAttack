#ifndef INC_2026_CYBERATTACK_PLANEGUI_H
#define INC_2026_CYBERATTACK_PLANEGUI_H
#include"raylib.h"
#include"assets.h"

void DrawPlaneGUI(Vector2 *pozicija, GraphicAssets *assets);
void DrawPowerUp(Texture2D powerUp, Vector2 position);
void DrawProjectile(Texture2D projectile, Vector2 position);
void DrawExplosion(GraphicAssets *assets, Vector2 pozicija, bool trigger);
void DrawEnemy(Texture2D enemy, Vector2 position, float size);
void DrawTurret(Texture2D turret, Vector2 position, float rotation);
void DrawLaser(Vector2 position, Texture2D laserTexture);

#endif //INC_2026_CYBERATTACK_PLANEGUI_H
