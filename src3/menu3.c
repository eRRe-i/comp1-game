#include<SDL2/SDL.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

#define MAX_LINE_LENGTH 1000


int main(int argc, char ** argv)
{
	int j = 0;
	int v[] = {0,1,2,3};
	SDL_Rect rect[3];
	int i = 0;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window * window = SDL_CreateWindow("Menu",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);



	SDL_Surface * superficieFundo = IMG_Load("menuback.jpeg");
	SDL_Surface * superficieNome = IMG_Load("nomejogo.jpeg");
	SDL_Surface * superficiePlay = IMG_Load("play.jpeg");
	SDL_Surface * superficieOpcao = IMG_Load("opcao.jpeg");
	/*SDL_Surface * superficieCreditos = IMG_Load("creditos.jpeg");
	SDL_Surface * superficieSair = IMG_Load("sair.jpeg");*/

	SDL_Texture * fundo = SDL_CreateTextureFromSurface( renderer,superficieFundo);
	SDL_Texture * nomejogo = SDL_CreateTextureFromSurface( renderer,superficieNome);
	SDL_Texture* texturaPlay = SDL_CreateTextureFromSurface(renderer, superficiePlay);
	SDL_Texture* texturaOpcao = SDL_CreateTextureFromSurface(renderer, superficieOpcao);
	/*SDL_Texture* texturaCreditos = SDL_CreateTextureFromSurface(renderer, superficieCreditos);
	SDL_Texture* texturaSair = SDL_CreateTextureFromSurface(renderer, superficieSair);*/

	SDL_Rect src = { SCREEN_WIDTH/2 - 340/2, 0 , 340, 148};// 340/2 - metade da imagem para ficar centralizado
	SDL_Rect src1 = { SCREEN_WIDTH/2 -340, 148 , 150, 75};


	SDL_Rect dstrect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };


	SDL_RenderCopy(renderer, fundo, NULL, &dstrect);
    SDL_RenderCopy(renderer, nomejogo, NULL, &src); // Titulo jogo png
	SDL_RenderCopy(renderer, texturaPlay, NULL, &src);
	SDL_RenderCopy(renderer, texturaOpcao, NULL, &src);
	/*SDL_RenderCopy(renderer, texturaPlay, NULL, &src);
	SDL_RenderCopy(renderer, texturaPlay, NULL, &src);*/
    //SDL_RenderCopy(renderer, texturaScore, NULL, &src1);
	SDL_RenderPresent(renderer);

	 SDL_Event e;

    bool quit = false;

    while(!quit) {

    	while(SDL_PollEvent( &e ) != 0) {

    		if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
    			quit = true;
    		}
    	}
    }

	SDL_DestroyTexture(fundo);
    SDL_DestroyTexture(nomejogo);

    SDL_DestroyTexture(texturaPlay);
    SDL_DestroyTexture(texturaOpcao);


    SDL_FreeSurface(superficieFundo);
    SDL_FreeSurface(superficieNome);
    
    SDL_FreeSurface(superficiePlay);
    SDL_FreeSurface(superficieOpcao);
  


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();


    return 0;
}
