#ifndef INC_2026_CYBERATTACK_PLANEGUI_H
#define INC_2026_CYBERATTACK_PLANEGUI_H
#include"raylib.h"
#include"assets.h"

void DrawPlaneGUI(Vector2 *pozicija, GraphicAssets *assets);
void DrawPowerUp(Texture2D powerUp, Vector2 position);
void DrawProjectile(Texture2D projectile, Vector2 position);
void SpawnExplosion(GraphicAssets *assets, Vector2 pozicija);
void DrawExplosion(GraphicAssets *assets);
void DrawEnemy(Texture2D enemy, Vector2 position, float size);
void DrawTurret(Texture2D turret, Vector2 position, float rotation);
void DrawLaser(Vector2 position, Texture2D laserTexture);
void DrawHealthBar(Enemy *e,Vector2 position);

#endif //INC_2026_CYBERATTACK_PLANEGUI_H
