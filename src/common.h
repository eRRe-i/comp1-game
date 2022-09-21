#ifndef COMMON
#define COMMON

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct gameStateKeyboardInput {

    int quitGame;
    int pauseGame;

} GameStateKeyboardInput;

typedef struct movePlayerKeyboardInput {

    int previousInput;
    int currentInput;

} MovePlayerKeyboardInput;

typedef struct keyboardInput {

    int keyPressed;
    int keyReleased;

    GameStateKeyboardInput gameStateKeyboardInput;
    MovePlayerKeyboardInput movePlayerKeyboardInput;

} KeyboardInput;

typedef struct timer {

    Uint32 currentTime;
    Uint32 elapsedTime;
    Uint32 pausedTime;

} Timer;

KeyboardInput* loadKeyBoardInput();
void handleKeyBoardInput(KeyboardInput* keyboardInput, SDL_KeyboardEvent* key);
void listenEvent(KeyboardInput* keyboardInput);
void cleanMovementInput(KeyboardInput* keyboardInput);
void printKeyboardState(KeyboardInput* input);



#endif //COMMON