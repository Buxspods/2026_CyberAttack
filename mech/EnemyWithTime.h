#ifndef INC_2026_CYBERATTACK_ENEMYWITHTIME_H
#define INC_2026_CYBERATTACK_ENEMYWITHTIME_H

#include "EntityTypes.h"

enum movementType {
    LEFT_SINE,
    RIGHT_SINE,
    LEFT_CIRCULAR,
    RIGHT_CIRCULAR,
    LEFT_LINEAR,
    RIGHT_LINEAR
};

typedef struct {
    EntityType type;
    Vector2 position;
    float spawnTime;
    bool spawned;
    Vector2 direction; //ovo se za sad koristi samo za melee planes
    enum movementType movementMode;
    Vector2 center;
} EnemyWithTime;

#endif //INC_2026_CYBERATTACK_ENEMYWITHTIME_H
