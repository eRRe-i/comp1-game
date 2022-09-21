#include "common.h"
#include "textures.h"

void listenEvent(KeyboardInput* keyboardInput) {


    SDL_Event event;

    while(SDL_PollEvent(&event)) {

        switch(event.type){
		
            case SDL_QUIT: keyboardInput->gameStateKeyboardInput.quitGame = 1; break;
            case SDL_KEYDOWN: handleKeyBoardInput(keyboardInput, &event.key); break;
			case SDL_KEYUP:handleKeyBoardInput(keyboardInput, &event.key); break;
            
        }
    }
}

void handleKeyBoardInput(KeyboardInput* keyboardInput, SDL_KeyboardEvent* key) {

	switch(key->type) {
		
		case SDL_KEYDOWN:{	keyboardInput->keyPressed = 1;
							keyboardInput->keyReleased = 0;
							break;
		}
		case SDL_KEYUP:{ 	keyboardInput->keyPressed = 0;
							keyboardInput->keyReleased = 1;
							keyboardInput->movePlayerKeyboardInput.currentInput = NO_KEYBOARD_INPUT;
							break;

		}
	}

	switch(key->keysym.sym) {
		case SDLK_ESCAPE: {	keyboardInput->gameStateKeyboardInput.quitGame = 1;
							break;
		}
		case SDLK_SPACE: {	keyboardInput->gameStateKeyboardInput.pauseGame = 1;
							break;
		}
		case SDLK_UP: 	{	keyboardInput->movePlayerKeyboardInput.previousInput = keyboardInput->movePlayerKeyboardInput.currentInput;
							keyboardInput->movePlayerKeyboardInput.currentInput = CHARACTER_UP;
							break;
		}
		case SDLK_DOWN: {	keyboardInput->movePlayerKeyboardInput.previousInput = keyboardInput->movePlayerKeyboardInput.currentInput;
							keyboardInput->movePlayerKeyboardInput.currentInput = CHARACTER_DOWN;
							break;
		}
		case SDLK_LEFT: {	keyboardInput->movePlayerKeyboardInput.previousInput = keyboardInput->movePlayerKeyboardInput.currentInput;
							keyboardInput->movePlayerKeyboardInput.currentInput = CHARACTER_LEFT;
							break;
		}
		case SDLK_RIGHT:{	keyboardInput->movePlayerKeyboardInput.previousInput = keyboardInput->movePlayerKeyboardInput.currentInput;
							keyboardInput->movePlayerKeyboardInput.currentInput = CHARACTER_RIGHT;
							break;
		}
	}
}

KeyboardInput* loadKeyBoardInput() {

	KeyboardInput* keyboardInput = (KeyboardInput*)malloc(sizeof(KeyboardInput));

	keyboardInput->gameStateKeyboardInput.pauseGame = 0;
	keyboardInput->gameStateKeyboardInput.quitGame=0;
	keyboardInput->movePlayerKeyboardInput.currentInput=0;
	keyboardInput->movePlayerKeyboardInput.previousInput=0;


	return keyboardInput;

}

void cleanMovementInput(KeyboardInput* keyboardInput) {

	keyboardInput->movePlayerKeyboardInput.currentInput = 0;
	keyboardInput->movePlayerKeyboardInput.previousInput=0;
	keyboardInput->keyPressed = 0;
	keyboardInput->keyReleased = 0;

	return;
}
