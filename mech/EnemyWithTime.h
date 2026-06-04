#ifndef INC_2026_CYBERATTACK_ENEMYWITHTIME_H
#define INC_2026_CYBERATTACK_ENEMYWITHTIME_H

#include "EntityTypes.h"

typedef struct {
    EntityType type;
    Vector2 position;
    float spawnTime;
    bool spawned;
} EnemyWithTime;

#endif //INC_2026_CYBERATTACK_ENEMYWITHTIME_H
