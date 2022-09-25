#include "common.h"
#include "map.h"
#include "player.h"
#include "attack.h"
#include "board.h"
#include "enemy.h"
#include "score.h"
#include "life.h"

typedef struct phaseManager {
    
    Map* map;
    Board* board;
    Player* player;
    AttackManager* attackManager;
    EnemyManager* enemyManager;
    Life* life;
    Score* score;

} PhaseManager;

PhaseManager* loadPhaseManager();