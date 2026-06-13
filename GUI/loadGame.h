#ifndef INC_2026_CYBERATTACK_LOADGAME_H
#define INC_2026_CYBERATTACK_LOADGAME_H
#include"assets.h"
#include"../mech/GameState.h"


extern GameState gamestate;
extern GraphicAssets assets;

typedef enum {
    UPDATE_NONE = 0,
    FUNC_LINEAR_MOVEMENT,
    FUNC_CIRCULAR_MOVEMENT,
    FUNC_SINE_MOVEMENT,
    FUNC_LINEAR_SHOT,
    FUNC_SHOTGUN_SHOT,
    FUNC_PLAYER_SHOT_LINEAR,
    FUNC_BOSS_PHASE1
} UpdateFuncID;

bool SaveGame(const char* filename);
bool LoadGame2(const char* filename);

#endif //INC_2026_CYBERATTACK_LOADGAME_H
