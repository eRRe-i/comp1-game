#ifndef BOARD
#define BOARD

#include "common.h"

typedef struct board {

    int boardId;
    int map_matrix[MATRIX_SIZE][MATRIX_SIZE];

} Board;

int readmatrix(size_t rows, size_t cols, int (*a)[cols], int id);
Board* loadBoardInitialState(int idMap);

#endif //BOARD