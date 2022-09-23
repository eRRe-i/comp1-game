#ifndef COMMON
#define COMMON

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>
#include <SDL2/SDL_ttf.h>
 

#define TRUE 1
#define FALSE 0
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MIN_Enemies 5
#define MAX_ENEMY_ARRAY 100
#define MAX_SIZE 100
#define MAP_DIM_X 32
#define MAP_DIM_Y 32
#define ENEMY_MAP_ID 3

#define MAP_LIST_SIZE 10
#define MATRIX_SIZE 70

typedef struct gameStateKeyboardInput {

    int quitGame;
    int pauseGame;
    int currentMapID;

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