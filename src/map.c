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

void generateMaps(SDL_Renderer* renderer, Map **arrayMaps){
    char pathImg[100];
    char pathTxt[100];
    for(int i = 0; i< MAP_LIST_SIZE; i++){       
        int num = i+1;
        sprintf(pathImg, "assets/Map%d.png",num);
        sprintf(pathTxt, "assets/maps/map%d.txt",num);
        arrayMaps[i] = (Map*)malloc(sizeof(Map));

        readmatrix(MATRIX_SIZE,MATRIX_SIZE,arrayMaps[i]->matrix, pathTxt);

        /*TODO: MELHORAR QTDE DE INIMIGOS*/
        int randomMax = 5+(1*i);
        arrayMaps[i]->mapTexture = loadMapTexture(renderer, pathImg);;
        arrayMaps[i]->basicEnemy = rand() % randomMax + 5;
        arrayMaps[i]->mediumEnemy = 0;
        arrayMaps[i]->highEnemy = 0;
        if(i != 0){
            arrayMaps[i]->mediumEnemy = rand() % i;
            arrayMaps[i]->highEnemy = rand() % i -1;
        }
        if(arrayMaps[i]->highEnemy <= 0){
            arrayMaps[i]->highEnemy = 0;
        }
        geraMonstrosParaMapa(renderer, arrayMaps[i]);
      }
}

void geraMonstrosParaMapa(SDL_Renderer* renderer, Map* map){
    int size = (map->basicEnemy + map->mediumEnemy + map->highEnemy);
	for(int i = 0; i < map->basicEnemy; i++){
        map->Enemys[i] = (Enemy*)malloc(sizeof(Enemy));
		generateEnemy(renderer,map->Enemys[i], 1);
	}
	if(map->mediumEnemy > 0){
		for(int i = map->basicEnemy; i < (map->basicEnemy + map->mediumEnemy); i++){
            map->Enemys[i] = (Enemy*)malloc(sizeof(Enemy));
			generateEnemy(renderer,map->Enemys[i], 2);
		}
	}
	if(map->highEnemy > 0){
		for(int i = (map->basicEnemy + map->mediumEnemy); i < size; i++){
            map->Enemys[i] = (Enemy*)malloc(sizeof(Enemy));
			generateEnemy(renderer,map->Enemys[i], 3);
		}
	}
}