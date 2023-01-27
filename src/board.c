#include "board.h"

Board* loadBoardInitialState(int boardId) {

    Board* board = (Board*)malloc(sizeof(Board));

    board->boardId = boardId;

    readmatrix(MATRIX_SIZE,MATRIX_SIZE, board->map_matrix, board->boardId);

    return board;
}

int readmatrix(size_t rows, size_t cols, int (*a)[cols], int id)
{
    FILE *pf;
    char filename[MAX_SIZE];
    id +=1;
    sprintf(filename, "assets/maps/map%d.txt",id);
    pf = fopen (filename, "r");
    if (pf == NULL){
        fprintf(stderr, "Erro ao ler %s", filename);
        return 0;
    }
    for(size_t i = 0; i < rows; ++i){
        for(size_t j = 0; j < cols; ++j){
            fscanf(pf, "%d", a[i] + j);
        }
    }
    
    fclose (pf); 
    return 1; 
}