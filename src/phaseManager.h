#include "common.h"
#include "map.h"
#include "player.h"
#include "attack.h"


typedef struct phaseManager {
    
    int currentMapId;
    Map* map;
    Player* player;
    AttackManager* attackManager; 
    

} PhaseManager;

PhaseManager* loadPhaseManager();