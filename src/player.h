#include "common.h"
#include "textures.h"

typedef struct Player {

	int life;
	int isMoving;
    
    int facingSide;
    int frame;

    CharacterTexture* characterTexture;


} Player;

Player* loadPlayerInitialState(CharacterTexture* texture);
void updatePlayerState(Player* player, KeyboardInput* keyboardInput);
void updateCharacterFrame(Player* player);