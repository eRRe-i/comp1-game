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
	SDL_Event e;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window * window = SDL_CreateWindow("Menu",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

    //inicializa ttf
	if(TTF_Init() == -1){
		SDL_Log("ERROR : SDL2_ttf não foi possível inicializar > %s\n", SDL_GetError());
	} else{
		SDL_Log("SDL2_ttf foi inicializado corretamente > %s\n", SDL_GetError());
	}
    //Carregar arquivo fonte e setar o tamanho
	TTF_Font* fonteJogo = TTF_OpenFont("./fonts/KarmaFuture.ttf",16);
	TTF_Font* fonteScore = TTF_OpenFont("./fonts/ka1.ttf",16);
	TTF_Font* fonteRecord = TTF_OpenFont("./fonts/ArcadeClassic.ttf",32);
	SDL_Color preto = {0, 0, 0};
	SDL_Color branco = {255, 255, 255};
    //confirmar que foi carregado
	if(fonteJogo == NULL){
		SDL_Log("ERROR : Não foi possível carregar a fonte > %s\n", SDL_GetError());
		exit(1);
	}


	SDL_Surface* superficieTexto = TTF_RenderText_Solid(fonteJogo,"Jogo Foda", preto);
	SDL_Surface* superficieScore = TTF_RenderText_Solid(fonteScore,"Ranking:", branco);
	


	SDL_Texture * fundo = IMG_LoadTexture( renderer,"menuback.jpeg");
	SDL_Texture * nomejogo = IMG_LoadTexture( renderer,"nomejogo.jpeg");
	SDL_Texture* texturaTexto = SDL_CreateTextureFromSurface(renderer, superficieTexto);
	SDL_Texture* texturaScore = SDL_CreateTextureFromSurface(renderer, superficieScore);
	

	SDL_FreeSurface(superficieTexto);
	SDL_FreeSurface(superficieScore);
	
	/*SDL_Rect retangulo;
	retangulo.x = 10;
	retangulo.y = 10;
	retangulo.w = 400;
	retangulo.h = 100;*/

    SDL_Rect src = { SCREEN_WIDTH/2 - 340/2,50 , 350, 100};// 340/2 - metade da imagem para ficar centralizado
    //SDL_Rect src1 = { SCREEN_WIDTH/2 -340, 148 , 150, 75};
    

    SDL_Rect dstrect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, fundo, NULL, &dstrect);
   // SDL_RenderCopy(renderer, nomejogo, NULL, &src); // Titulo jogo png
    //SDL_RenderCopy(renderer, texturaTexto, NULL, &src);
    SDL_RenderCopy(renderer, texturaScore, NULL, &src);
    
    SDL_RenderPresent(renderer);

    //ler arquivo record nome
    int i = 1;
    FILE    *textfile;
    char    line[MAX_LINE_LENGTH];

    textfile = fopen("recordnome.txt", "r");
    if(textfile == NULL)
    	return 1;

    while(fgets(line, MAX_LINE_LENGTH, textfile)){
    	line[strcspn(line, "\n")] = '\0';
    	SDL_Surface* superficieRecords = TTF_RenderText_Solid(fonteRecord,line, branco);
    	SDL_Texture* texturaRecords= SDL_CreateTextureFromSurface(renderer, superficieRecords);
    	SDL_Rect src2 = { SCREEN_WIDTH/2 -340/1.4, 98 +(50 * i), superficieRecords->w, superficieRecords->h};
    	i++;
    	SDL_FreeSurface(superficieRecords);

    	SDL_RenderCopy(renderer, texturaRecords, NULL, &src2);
    	SDL_RenderPresent(renderer);

    }


    fclose(textfile);
    //ler arquivo record score
    i = 1;

    textfile = fopen("recordscore.txt", "r");
    if(textfile == NULL)
    	return 1;

    while(fgets(line, MAX_LINE_LENGTH, textfile)){
    	line[strcspn(line, "\n")] = '\0';
    	SDL_Surface* superficieRecords = TTF_RenderText_Solid(fonteRecord,line, branco);
    	SDL_Texture* texturaRecords= SDL_CreateTextureFromSurface(renderer, superficieRecords);
    	SDL_Rect src2 = { SCREEN_WIDTH/2 +340/2, 98 +(50 * i), superficieRecords->w, superficieRecords->h};
    	i++;
    	SDL_FreeSurface(superficieRecords);
    	SDL_RenderCopy(renderer, texturaRecords, NULL, &src2);
    	SDL_RenderPresent(renderer);

    }


    fclose(textfile);



    bool quit = false;

    while(!quit) {

		while(SDL_PollEvent( &e ) != 0) {

			if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN) {

				switch( e.key.keysym.sym ) {

					case SDLK_UP:
					if(j == 0 ){
						j = 3;
						printf("j - 1");
					}else{
						j -= 1;
					}
					break;

					case SDLK_DOWN:
					if(j == 3){
						j = 0;
						printf("j + 1");
					}else{
						j += 1;
					}
					break;
				}
			}
		}
	}

    SDL_Quit();
    SDL_DestroyTexture(fundo);
    SDL_DestroyTexture(nomejogo);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(fonteJogo);

    return 0;
}
