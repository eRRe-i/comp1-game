#include "common.h"
#include "map.h"
#include "player.h"


typedef struct phaseManager {

    Map* map;
    Player* player;

} PhaseManager;

PhaseManager* loadPhaseManager();