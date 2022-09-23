#include <stdio.h>
#include "map.h"
#include "textures.h"
#include <stdlib.h>
#include <string.h>


int readmatrix(size_t rows, size_t cols, int (*a)[cols], int id)
{
    FILE *pf;
    char filename[MAX_SIZE];
    sprintf(filename, "assets/maps/map%d.txt",id);
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
    
    for(int i = 0; i< MAP_LIST_SIZE; i++){
        int num = i+1;
        

        arrayMaps[i] = loadMapInitialState();
        arrayMaps[i]->id=num;
        /*TODO: MELHORAR QTDE DE INIMIGOS*/
        int randomMax = MIN_Enemies+(1*i);
        arrayMaps[i]->basicEnemy = rand() % randomMax + MIN_Enemies;
        arrayMaps[i]->mediumEnemy = 0;
        arrayMaps[i]->highEnemy = 0;
        arrayMaps[i]->total_enemy = (arrayMaps[i]->basicEnemy + arrayMaps[i]->mediumEnemy + arrayMaps[i]->highEnemy);
        if(i != 0){
            arrayMaps[i]->mediumEnemy = rand() % i;
            arrayMaps[i]->highEnemy = rand() % i -1;
        }
        if(arrayMaps[i]->highEnemy <= 0)
            arrayMaps[i]->highEnemy = 0;
    }
}

void geraMonstrosParaMapa(SDL_Renderer* renderer, Map* map){
    int size = map->total_enemy;
	for(int i = 0; i < map->basicEnemy; i++){
        map->Enemies[i] = (Enemy*)malloc(sizeof(Enemy));
		generateEnemy(renderer,map->Enemies[i], 1);
        geraPosicao(map->matrix, map->Enemies[i]);
	}
	if(map->mediumEnemy > 0){
		for(int i = map->basicEnemy; i < (map->basicEnemy + map->mediumEnemy); i++){
            map->Enemies[i] = (Enemy*)malloc(sizeof(Enemy));
			generateEnemy(renderer,map->Enemies[i], 2);
            geraPosicao(map->matrix, map->Enemies[i]);
		}
	}
	if(map->highEnemy > 0){
		for(int i = (map->basicEnemy + map->mediumEnemy); i < size; i++){
            map->Enemies[i] = (Enemy*)malloc(sizeof(Enemy));
			generateEnemy(renderer,map->Enemies[i], 3);
            geraPosicao(map->matrix, map->Enemies[i]);
		}
	}
}