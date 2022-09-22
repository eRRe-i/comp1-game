#include "common.h"
#include "map.h"
#include "player.h"


typedef struct phaseManager {
    
    int currentMapId;
    Map* map;
    Player* player;

} PhaseManager;

PhaseManager* loadPhaseManager();