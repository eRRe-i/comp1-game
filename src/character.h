#ifndef CHARACTER
#define CHARACTER

#include "common.h"
 
#define CHARA_PATH "assets/chara.png"
#define MAP "assets/map.png"
#define CHARACTER_FRONT 0
#define CHARACTER_BACK 1
#define CHARACTER_LEFT 2
#define CHARACTER_RIGHT 3
#define CHARACTER_FRAME_RATE 200
 
typedef struct player {
    
    int life;
    int score;

    int currentCharacterSide;


} Player;

void movePlayer(Player* player);

#endif //CHARACTER