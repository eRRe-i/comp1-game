#ifndef COMMON
#define COMMON

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct gameStateKeyboardInput {

    int quitGame;
    int pauseGame;

} GameStateKeyboardInput;

typedef struct movePlayerKeyboardInput {

    int up;
    int down;
    int left;
    int right;

} MovePlayerKeyboardInput;

typedef struct keyboardInput {

    int keyPressed;
    int keyReleased;

    GameStateKeyboardInput gameStateKeyboardInput;
    MovePlayerKeyboardInput movePlayerKeyboardInput;

} KeyboardInput;

KeyboardInput* loadKeyBoardInput();
void handleKeyBoardInput(KeyboardInput* keyboardInput, SDL_KeyboardEvent* key);
void listenEvent(KeyboardInput* keyboardInput);
void cleanMovementInput(KeyboardInput* keyboardInput);
void printKeyboardState(KeyboardInput* input);

#endif //COMMON