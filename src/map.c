#include <stdio.h>
#include "map.h"
#include "textures.h"
#include <stdlib.h>
#include <string.h>

int readmatrix(size_t rows, size_t cols, int (*a)[cols], const char* filename)
{
    FILE *pf;
    pf = fopen (filename, "r");
    if (pf == NULL)
        return 0;

    for(size_t i = 0; i < rows; ++i){
        for(size_t j = 0; j < cols; ++j)
            fscanf(pf, "%d", a[i] + j);
    }

    
    fclose (pf); 
    return 1; 
}

Map* generateMaps(SDL_Renderer* renderer){

    Map *arrayMaps = malloc(sizeof(Map) *MAP_LIST_SIZE);
    char pathImg[100];
    char pathTxt[100];
    for(int i = 0; i< MAP_LIST_SIZE; i++){
        int num = i+1;
        sprintf(pathImg, "assets/Map%d.png",num);
        sprintf(pathTxt, "assets/maps/map%d.txt",num);

        MapTexture* mapTexture  = loadMapTexture(renderer, pathImg);

        readmatrix(MATRIX_SIZE,MATRIX_SIZE,arrayMaps[i].matrix, pathTxt);

        /*TODO: MELHORAR QTDE DE INIMIGOS*/
        int randomMax = 5+(1*i);

        arrayMaps[i].mapTexture = mapTexture;
        arrayMaps[i].basicEnemy = rand() % randomMax + 5;
        arrayMaps[i].mediumEnemy = 0;
        arrayMaps[i].highEnemy = 0;
        if(i != 0){
            arrayMaps[i].mediumEnemy = rand() % i;
            arrayMaps[i].highEnemy = rand() % i -1;
        }
        if(arrayMaps[i].highEnemy <= 0){
            arrayMaps[i].highEnemy = 0;
        }
      }
    return arrayMaps;
}