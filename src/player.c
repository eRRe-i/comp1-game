#include "common.h"
#include "player.h"
#include "textures.h"

Player* loadPlayerInitialState(CharacterTexture* texture) {

	Player* player = (Player*)malloc(sizeof(Player));

	player->isMoving = FALSE;
	player->facingSide = 0;
    player->frame = 0;

	player->characterTexture = texture;

	return player;

}


void updatePlayerState(Player* player, KeyboardInput* keyboardInput) {

	if(player->isMoving) {

		updateCharacterFrame(player);

	} else {

		if(player->facingSide == keyboardInput->movePlayerKeyboardInput.moveInput) {

			player->isMoving = FALSE;
			updateCharacterFrame(player);
		} else {

			player->isMoving = FALSE;
            fprintf(stderr, "%i", keyboardInput->movePlayerKeyboardInput.moveInput);
			player->facingSide = keyboardInput->movePlayerKeyboardInput.moveInput;
			updateCharacterFrame(player);
		}
	}

}

void updateCharacterFrame(Player* player) {

   player->frame = (int)(SDL_GetTicks() / CHARACTER_FRAME_RATE)%4;

}