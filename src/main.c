#include "common.h"
#include "textures.h"
#include "map.h"

int waiting(void);
void updateScreen(SDL_Renderer* renderer, Map* map, CharacterTexture* character, EnemyTexture* EnemyTexture);
void updateMap(SDL_Renderer* renderer, Map* map);
void updateEnemy(SDL_Renderer* renderer, EnemyTexture* enemyTexture);

// int handleEvent(Player* Player, Background* background);
// variable declarations
SDL_Window *win = NULL;
SDL_Renderer *renderer = NULL;
CharacterTexture* characterTexture = NULL;
EnemyTexture* enemyTexture = NULL;
Map *mapas[MAP_LIST_SIZE];
int mapIndex = 0;
int actionFrame = 0;
SDL_RendererFlip flipType = SDL_FLIP_NONE;

int main (int argc, char *argv[]) 
{

	
	int w, h; // texture width & height
	
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("ERROR : SDL Initialization > %s\n", SDL_GetError());
		return 1;
	}
	
	win = SDL_CreateWindow("Image Loading", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	generateMaps(renderer, mapas);

	updateMap(renderer, mapas[0]);
    characterTexture = loadCharacterTexture(renderer);

	enemyTexture = loadEnemyTexture(renderer,1);

	chdir("..");

	
	// main loop
	while (waiting()) {
        
		moveCharacter(characterTexture);
		moveEnemy(enemyTexture);
        updateScreen(renderer, mapas[mapIndex], characterTexture, enemyTexture);

	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	
	SDL_Quit();

	return 0;
}

int waiting(void)
{
	// event handling
	SDL_Event e;
	if(SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			return 0;
		else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
			return 0;
		else if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_F1){
			if(mapIndex > 0){
				mapIndex -= 1;
				updateMap(renderer, mapas[mapIndex]);
			}
		}
		else if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_F2){
			if(mapIndex < MAP_LIST_SIZE-1){
				mapIndex += 1;
				updateMap(renderer, mapas[mapIndex]);
			}
		}
		else if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_F3){
			actionFrame = 0;
		}
		else if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_F4){
			actionFrame = 1;
		}
		else if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_q){
			flipType = SDL_FLIP_HORIZONTAL;
		}
	}
	return 1;
}
 
void updateScreen(SDL_Renderer* renderer, Map* map, CharacterTexture* character, EnemyTexture* enemyTexture) {

        // clear the screen
		SDL_RenderClear(renderer);
		// copy the texture to the rendering context
		// SDL_RenderCopy(	renderer, 
		// 				map->mapTexture, 
		// 				NULL, 
		// 				&map->displayRect);
		updateMap(renderer, map);
		// flip the backbuffer  
		// this means that everything that we prepared behind the screens is actually shown
        SDL_RenderCopy	(renderer, 
						character->characterSheet,
						&character->spritePosition[CHARACTER_FRONT][character->frame], 
						&character->displayRect);

		SDL_RenderPresent(renderer);

}



void updateMap(SDL_Renderer* renderer, Map* map){

	SDL_RenderCopy(renderer,
		map->mapTexture->mapTexture,
		NULL,
		&map->mapTexture->displayRect);
	for(int i = 0; i < (map->basicEnemy + map->mediumEnemy + map->highEnemy); i++){
		updateEnemy(renderer, map->Enemys[i]->enemyTexture);
	}
}
void updateEnemy(SDL_Renderer* renderer, EnemyTexture* enemyTexture){
	moveEnemy(enemyTexture);
	SDL_RenderCopyEx	(renderer, 
			enemyTexture->EnemySheet,
			&enemyTexture->spritePosition[actionFrame][enemyTexture->frame], 
			&enemyTexture->displayRect,
			0,
			NULL,
			flipType);
}