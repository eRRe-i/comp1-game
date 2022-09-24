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
#define IMMOVABLE_MAP_ID 1
#define ENEMY_MAP_ID 3
#define FIRST_ATTACK 1

#define MAP_LIST_SIZE 10
#define MATRIX_SIZE 70
#define ATTACK_SPEED 1

typedef struct vector {
    int x;
    int y;
} Vector;


typedef struct boardIndex {
    int i;
    int j;
} BoardIndex;

typedef struct gameStateKeyboardInput {

    int quitGame;
    int pauseGame;
    int currentMapID;

} GameStateKeyboardInput;

typedef struct attackKeyboardInput {

    int attack;

} AttackKeyboardInput;

typedef struct movePlayerKeyboardInput {

    int previousInput;
    int currentInput;

} MovePlayerKeyboardInput;

typedef struct keyboardInput {

    int keyPressed;
    int keyReleased;
    int repeatedPress;

    GameStateKeyboardInput gameStateKeyboardInput;
    MovePlayerKeyboardInput movePlayerKeyboardInput;
    AttackKeyboardInput attackKeyboardInput;

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
Vector addVector(Vector vec1, Vector vec2);
Vector setVector(int x, int y);
Vector getGlobalPositionFromBoardIndex(BoardIndex boardIndex);
Vector getObjectViewPosfromGlobalPos(Vector viewPos, Vector globalPos);
BoardIndex setBoardIndex(int i, int j);
 
#endif //COMMON