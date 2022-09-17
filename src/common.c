#include "common.h"

void listenEvent(KeyboardInput* keyboardInput) {

	cleanMovementInput(keyboardInput);

    SDL_Event event;

    while(SDL_PollEvent(&event)) {

        switch(event.type){
		
            case SDL_QUIT: keyboardInput->gameStateKeyboardInput.quitGame = 1; break;
            case SDL_KEYDOWN: handleKeyBoardInput(keyboardInput, &event.key); break;
            case SDL_KEYUP: handleKeyBoardInput(keyboardInput, &event.key); break;
        }
		// printKeyboardState(keyboardInput);
    }
}

void handleKeyBoardInput(KeyboardInput* keyboardInput, SDL_KeyboardEvent* key) {

	switch(key->type) {
		
		case SDL_KEYDOWN:{	keyboardInput->keyPressed = 1;
							keyboardInput->keyReleased = 0;
							break;
		}
		case SDL_KEYUP: {	keyboardInput->keyReleased = 1;
							keyboardInput->keyPressed = 0;
							break;
		}
	}

	switch(key->keysym.sym) {
		case SDLK_ESCAPE: {	keyboardInput->gameStateKeyboardInput.quitGame = 1;
							break;
		}
		case SDLK_SPACE: {	keyboardInput->gameStateKeyboardInput.pauseGame = 1;
							SDL_Log("SpacePressed");
							break;
		}
		case SDLK_UP: 	{	keyboardInput->movePlayerKeyboardInput.up = 1;
							SDL_Log("UpPressed");
							break;
		}
		case SDLK_DOWN: {	keyboardInput->movePlayerKeyboardInput.down = 1;
							SDL_Log("DownPressed"); 
							break;
		}
		case SDLK_LEFT: {	keyboardInput->movePlayerKeyboardInput.left = 1;
							SDL_Log("LeftPressed");
							break;
		}
		case SDLK_RIGHT:{	keyboardInput->movePlayerKeyboardInput.right = 1;
							SDL_Log("RightPressed");
							break;
		} 
	}
}

KeyboardInput* loadKeyBoardInput() {

	KeyboardInput* keyboardInput = (KeyboardInput*)malloc(sizeof(KeyboardInput));

	return keyboardInput;

}

void cleanMovementInput(KeyboardInput* keyboardInput) {

	keyboardInput->movePlayerKeyboardInput.up = 0;
	keyboardInput->movePlayerKeyboardInput.down = 0;
	keyboardInput->movePlayerKeyboardInput.right = 0;
	keyboardInput->movePlayerKeyboardInput.left = 0;
	keyboardInput->keyPressed = 0;
	keyboardInput->keyReleased = 0;

	return;
}

void printKeyboardState(KeyboardInput* input) {

	printf("KEYBOARDSTATE:\n KEY PRESSED: %i\n UP: %i\n DOWN: %i\n LEFT: %i\n RIGHT: %i\n", input->keyPressed,
																			input->movePlayerKeyboardInput.up, 
																			input->movePlayerKeyboardInput.down,
																			input->movePlayerKeyboardInput.left, 
																			input->movePlayerKeyboardInput.right);

}