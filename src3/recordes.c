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
	TTF_Font* fonteJogo = TTF_OpenFont("./fonts/IMMORTAL.ttf",64);
    TTF_Font* fonteBotao = TTF_OpenFont("./fonts/ChocoladineDemo.ttf",64);
	TTF_Font* fonteScore = TTF_OpenFont("./fonts/ka1.ttf",16);
	TTF_Font* fonteRecord = TTF_OpenFont("./fonts/ArcadeClassic.ttf",32);
	SDL_Color preto = {0, 0, 0};
	SDL_Color branco = {255, 255, 255};
    //confirmar que foi carregado
	if(fonteJogo == NULL){
		SDL_Log("ERROR : Não foi possível carregar a fonte > %s\n", SDL_GetError());
		exit(1);
	}

	SDL_Surface * superficieBotao = IMG_Load("botao.png");
	SDL_Surface* superficieTexto = TTF_RenderText_Solid(fonteJogo,"Jogo Foda", preto);
	SDL_Surface* superficieScore = TTF_RenderText_Solid(fonteScore,"Ranking:", branco);
	SDL_Surface* superficieVolta = TTF_RenderText_Solid(fonteJogo,"voltar", preto);
	SDL_Surface * superficieSeta = IMG_Load("seta.png");


	SDL_Texture * fundo = IMG_LoadTexture( renderer,"menuback.png");
	SDL_Texture * nomejogo = IMG_LoadTexture( renderer,"nomejogo.jpeg");
	SDL_Texture* texturaTexto = SDL_CreateTextureFromSurface(renderer, superficieTexto);
	SDL_Texture* texturaVolta = SDL_CreateTextureFromSurface(renderer, superficieVolta);
	SDL_Texture* texturaBotao = SDL_CreateTextureFromSurface( renderer,superficieBotao);

	SDL_Texture* texturaScore = SDL_CreateTextureFromSurface(renderer, superficieScore);
	SDL_Texture* texturaSeta = SDL_CreateTextureFromSurface(renderer, superficieSeta);
	

	SDL_FreeSurface(superficieTexto);
	SDL_FreeSurface(superficieScore);
	//SDL_FreeSurface(superficieVolta);
	
	

    SDL_Rect src = { SCREEN_WIDTH/2 - 340/2,50 , 350, 100};// 340/2 - metade da imagem para ficar centralizado
    //SDL_Rect src1 = { SCREEN_WIDTH/2 -340, 148 , 150, 75};

	SDL_Rect srcVolta = { 600 ,450 ,superficieVolta->w,superficieVolta->h};
	SDL_Rect srcBotao = { 575 ,450 ,225,superficieVolta->h};
	SDL_Rect rSeta = { 545 ,450 , 65, 80};

    SDL_Rect dstrect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, fundo, NULL, &dstrect);
   // SDL_RenderCopy(renderer, nomejogo, NULL, &src); // Titulo jogo png
    //SDL_RenderCopy(renderer, texturaTexto, NULL, &src);
    SDL_RenderCopy(renderer, texturaScore, NULL, &src);
    SDL_RenderCopy(renderer, texturaBotao, NULL, &srcBotao);
    SDL_RenderCopy(renderer, texturaVolta, NULL, &srcVolta);
    SDL_RenderCopy(renderer, texturaSeta, NULL, &rSeta);
    
    SDL_RenderPresent(renderer);

    while(listenEventMenu2(menu) == 0) {

		
	}

    SDL_Quit();
    SDL_DestroyTexture(fundo);
    SDL_DestroyTexture(nomejogo);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(fonteJogo);

    return 0;
}

int listenEventMenu2(Menu menu){
	SDL_Event e;
	while(SDL_PollEvent( &e ) != 0) {
		if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
			return 1;
		}
		else if (e.type == SDL_KEYDOWN) {
			switch( e.key.keysym.sym ) {
				case SDLK_RETURN:
					return 1;
				break;
			}
		}
	}
}


void lerRecords(SDL_Renderer* renderer, Menu* menu){
	SDL_Color branco = {255, 255, 255};
	FILE    *textfile;
    char    line[MAX_LINE_LENGTH];

    textfile = fopen("records.txt", "r");
    if(textfile == NULL)
    	return 1;

    while(fgets(line, MAX_LINE_LENGTH, textfile)){
    	line[strcspn(line, "\n")] = '\0';
    	SDL_Surface* superficieRecords = TTF_RenderText_Solid(menu->fonteRecord,line, branco);
    	SDL_Texture* texturaRecords= SDL_CreateTextureFromSurface(renderer, menu->superficieRecords);
    	SDL_Rect src2 = { 50, 200, 700, 400};
    	SDL_FreeSurface(menu->superficieRecords);
    	SDL_RenderCopy(renderer, texturaRecords, NULL, &src2);
    	SDL_RenderPresent(renderer);
    }
    fclose(textfile);
}