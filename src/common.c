#include "common.h"
#include "textures.h"

void listenEvent(KeyboardInput* keyboardInput) {


    SDL_Event event;

    while(SDL_PollEvent(&event)) {

        switch(event.type){
		
            case SDL_QUIT: keyboardInput->gameStateKeyboardInput.quitGame = 1; break;
            case SDL_KEYDOWN: handleKeyBoardInput(keyboardInput, &event.key); break;
			case SDL_KEYUP:handleKeyBoardInput(keyboardInput, &event.key); break;
			default: {
			keyboardInput->movePlayerKeyboardInput.moveInput = NO_KEYBOARD_INPUT;
			break;
			}
            
        }
    }
}

void handleKeyBoardInput(KeyboardInput* keyboardInput, SDL_KeyboardEvent* key) {

	switch(key->type) {
		
		case SDL_KEYDOWN:{	keyboardInput->keyPressed = 1;
							keyboardInput->keyReleased = 0;
							SDL_Log("KeyPressed");

							break;
		}
		case SDL_KEYUP:{ 	keyboardInput->keyPressed = 0;
							keyboardInput->keyReleased = 1;
							SDL_Log("KeyReleased");
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
		case SDLK_UP: 	{	keyboardInput->movePlayerKeyboardInput.moveInput = CHARACTER_UP;
							SDL_Log("UpPressed");
							break;
		}
		case SDLK_DOWN: {	keyboardInput->movePlayerKeyboardInput.moveInput = CHARACTER_DOWN;
							SDL_Log("DownPressed"); 
							break;
		}
		case SDLK_LEFT: {	keyboardInput->movePlayerKeyboardInput.moveInput = CHARACTER_LEFT;
							SDL_Log("LeftPressed");
							break;
		}
		case SDLK_RIGHT:{	keyboardInput->movePlayerKeyboardInput.moveInput = CHARACTER_RIGHT;
							SDL_Log("RightPressed");
							break;
		}
	}
}

KeyboardInput* loadKeyBoardInput() {

	KeyboardInput* keyboardInput = (KeyboardInput*)malloc(sizeof(KeyboardInput));

	keyboardInput->gameStateKeyboardInput.pauseGame = 0;
	keyboardInput->gameStateKeyboardInput.quitGame=0;
	keyboardInput->movePlayerKeyboardInput.moveInput=0;

	return keyboardInput;

}

void cleanMovementInput(KeyboardInput* keyboardInput) {

	keyboardInput->movePlayerKeyboardInput.moveInput = 0;
	keyboardInput->keyPressed = 0;
	keyboardInput->keyReleased = 0;

	return;
}
