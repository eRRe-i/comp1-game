#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "menu.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
SDL_Renderer* renderer = NULL;

void seleciona(int a);

Menu1* loadMenu1(SDL_Renderer* renderer) {

	Menu1* menu = (Menu1*)malloc(sizeof(Menu1));
	menu->fonteJogo = TTF_OpenFont("./fonts/IMMORTAL.ttf", 128);
	menu->fonteBotao = TTF_OpenFont("./fonts/ChocoladineDemo.ttf", 64);
	menu->fonteScore = TTF_OpenFont("./fonts/ka1.ttf",16);
	menu->fonteRecord = TTF_OpenFont("./fonts/ArcadeClassic.ttf",32);

	SDL_Color preto = {0, 0, 0};
	SDL_Color branco = {255, 255, 255};

	menu->r.x = SCREEN_WIDTH / 2 -330;
	menu->r.y = - 330;
	menu->r.y = 144;
	menu->r.w = 40;
	menu->r.h = 40;

	menu->dstrect.x = 0;
	menu->dstrect.y = 0;
	menu->dstrect.w = SCREEN_WIDTH;
	menu->dstrect.h = SCREEN_HEIGHT;
	
	menu->src.x = SCREEN_WIDTH / 2 - 340 / 2;
	menu->src.y = 0;
	menu->src.w = 340;
	menu->src.h = 148;

	menu->src1.x = SCREEN_WIDTH / 2 - 300;
	menu->src1.y = 148;
	menu->src1.w = 150;
	menu->src1.h = 50;
	
	menu->src2.x = SCREEN_WIDTH / 2 - 300;
	menu->src2.y = 148 + 75;
	menu->src2.w = 150;
	menu->src2.h = 50;

	menu->src3.x = SCREEN_WIDTH / 2 - 300;
	menu->src3.y = 148 + (75 * 2);
	menu->src3.w = 150;
	menu->src3.h = 50;

	menu->src4.x = SCREEN_WIDTH / 2 - 300;
	menu->src4.y = 148 + (75 * 3);
	menu->src4.w = 150;
	menu->src4.h = 50;

	menu->src5.x = SCREEN_WIDTH / 2 - 300;
	menu->src5.y = 148 + (75 * 4);
	menu->src5.w = 150;
	menu->src5.h = 50;

	menu->src6.x = SCREEN_WIDTH / 2 - 300;
	menu->src6.y = 148 + (75 * 5);
	menu->src6.w = 150;
	menu->src6.h = 50;

	menu->srcVolta.x= 600;
	menu->srcVolta.y = 450;
	menu->srcVolta.w = 150;
	menu->srcVolta.h = 50;


	menu->superficieFundo = IMG_Load("menuback.png");
	menu->superficieBotao = IMG_Load("botao.png");
	menu->superficieTexto = TTF_RenderText_Solid(menu->fonteJogo, "AA COMP 1", preto);
	menu->superficiePlay = TTF_RenderText_Solid(menu->fonteBotao, "Jogar", preto);
	menu->superficieOpcao = TTF_RenderText_Solid(menu->fonteBotao, "Opcoes", preto);
	menu->superficieInstrucao = TTF_RenderText_Solid(menu->fonteBotao, "Instrucoes", preto);
	menu->superficieCreditos = TTF_RenderText_Solid(menu->fonteBotao, "Creditos", preto);
	menu->superficieRanking = TTF_RenderText_Solid(menu->fonteBotao, "Ranking", preto);
	menu->superficieSair = TTF_RenderText_Solid(menu->fonteBotao, "Sair", preto);
	menu->superficieNome = IMG_Load("nomejogo.jpeg");
	menu->superficieSeta = IMG_Load("seta.png");
	menu->superficieScore = TTF_RenderText_Solid(menu->fonteScore,"Ranking:", branco);
	menu->superficieVolta = TTF_RenderText_Solid(menu->fonteJogo,"voltar", preto);

	menu->fundo = SDL_CreateTextureFromSurface(renderer, menu->superficieFundo);
	menu->texturaBotao = SDL_CreateTextureFromSurface(renderer, menu->superficieBotao);
	menu->nomejogo = SDL_CreateTextureFromSurface(renderer, menu->superficieNome);
	menu->texturaTexto = SDL_CreateTextureFromSurface(renderer, menu->superficieTexto);
	menu->texturaPlay = SDL_CreateTextureFromSurface(renderer, menu->superficiePlay);
	menu->texturaOpcao = SDL_CreateTextureFromSurface(renderer, menu->superficieOpcao);
	menu->texturaInstrucao = SDL_CreateTextureFromSurface(renderer, menu->superficieInstrucao);
	menu->texturaCreditos = SDL_CreateTextureFromSurface(renderer, menu->superficieCreditos);
	menu->texturaRanking = SDL_CreateTextureFromSurface(renderer, menu->superficieRanking);
	menu->texturaSair = SDL_CreateTextureFromSurface(renderer, menu->superficieSair);
	menu->texturaSeta = SDL_CreateTextureFromSurface(renderer, menu->superficieSeta);
	menu->texturaVolta = SDL_CreateTextureFromSurface(renderer, menu->superficieVolta);
	menu->texturaScore = SDL_CreateTextureFromSurface(renderer, menu->superficieScore);
}


// int main(int argc, char **argv)
// {

// 	int i = 0;

// 	SDL_Init(SDL_INIT_VIDEO);

// 	SDL_Window *window = SDL_CreateWindow("Menu",
// 	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

// 	renderer = SDL_CreateRenderer(window, -1, 0);

// 	// inicializa ttf
// 	if (TTF_Init() == -1)
// 	{
// 		SDL_Log("ERROR : SDL2_ttf não foi possível inicializar > %s\n", SDL_GetError());
// 	}
// 	else
// 	{
// 		SDL_Log("SDL2_ttf foi inicializado corretamente > %s\n", SDL_GetError());
// 	}
// 	// Carregar arquivo fonte e setar o tamanho
// 	Menu1* menu = loadMenu1(renderer);
	
// 	SDL_RenderPresent(renderer);
	

// 	loopMenu1(menu);

// 	SDL_DestroyRenderer(renderer);
// 	SDL_DestroyWindow(window);
// 	TTF_CloseFont(menu->fonteJogo);
// 	SDL_Quit();
// 	return 0;
// }

void moveCursor(Menu1 * menu)
{
	if (menu->posicaoCursor == 0)
	{
		menu->r.y = menu->src1.y;
	}
	if (menu->posicaoCursor == 1)
	{
		menu->r.y = menu->src2.y;
	}
	if (menu->posicaoCursor == 2)
	{

		menu->r.y = menu->src3.y;
	}
	if (menu->posicaoCursor == 3)
	{

		menu->r.y = menu->src4.y;
	}
	if (menu->posicaoCursor == 4)
	{

		menu->r.y = menu->src5.y;
	}
	if (menu->posicaoCursor == 5)
	{

		menu->r.y = menu->src6.y;
	}
}

void renderMenu1(SDL_Renderer* renderer, Menu1* menu){
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, menu->fundo, NULL, &menu->dstrect);

	SDL_RenderCopy(renderer, menu->texturaTexto, NULL, &menu->src);
	SDL_RenderCopy(renderer, menu->texturaBotao, NULL, &menu->src1);
	SDL_RenderCopy(renderer, menu->texturaPlay, NULL, &menu->src1);
	SDL_RenderCopy(renderer, menu->texturaBotao, NULL, &menu->src2);
	SDL_RenderCopy(renderer, menu->texturaOpcao, NULL, &menu->src2);
	SDL_RenderCopy(renderer, menu->texturaBotao, NULL, &menu->src3);
	SDL_RenderCopy(renderer, menu->texturaInstrucao, NULL, &menu->src3);
	SDL_RenderCopy(renderer, menu->texturaBotao, NULL, &menu->src4);
	SDL_RenderCopy(renderer, menu->texturaRanking, NULL, &menu->src4);
	SDL_RenderCopy(renderer, menu->texturaBotao, NULL, &menu->src5);
	SDL_RenderCopy(renderer, menu->texturaCreditos, NULL, &menu->src5);
	SDL_RenderCopy(renderer, menu->texturaBotao, NULL, &menu->src6);
	SDL_RenderCopy(renderer, menu->texturaSair, NULL, &menu->src6);
	SDL_RenderCopy(renderer, menu->texturaSeta, NULL, &menu->r);
}

int listenEventMenu1(Menu1* menu){
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
		{

			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)){
				return 1;
			}
			else if (e.type == SDL_KEYDOWN){
				switch (e.key.keysym.sym){

				case SDLK_UP:
					if (menu->posicaoCursor > 0){
						menu->posicaoCursor -= 1;
					}
					break;

				case SDLK_DOWN:
					if (menu->posicaoCursor < 6)
					{
						menu->posicaoCursor += 1;
					}
					break;
					case SDLK_RETURN:
						fprintf(stderr, "MENU 1 OPCAO %i ", menu->posicaoCursor);
						if(menu->posicaoCursor == 5)
							return 1;
					break;
				}
			}
		}
		return 0;
}
int loopMenu1(Menu1* menu){
	
	while (listenEventMenu1(menu) == 0)
	{
		moveCursor(menu);
		renderMenu1(renderer, menu);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(menu->fundo);
	SDL_DestroyTexture(menu->nomejogo);
	SDL_DestroyTexture(menu->texturaTexto);
	SDL_DestroyTexture(menu->texturaPlay);
	SDL_DestroyTexture(menu->texturaOpcao);
	SDL_DestroyTexture(menu->texturaInstrucao);
	SDL_DestroyTexture(menu->texturaRanking);
	SDL_DestroyTexture(menu->texturaCreditos);
	SDL_DestroyTexture(menu->texturaSair);

	SDL_FreeSurface(menu->superficieFundo);
	SDL_FreeSurface(menu->superficieNome);
	SDL_FreeSurface(menu->superficieTexto);
	SDL_FreeSurface(menu->superficiePlay);
	SDL_FreeSurface(menu->superficieOpcao);
	SDL_FreeSurface(menu->superficieInstrucao);
	SDL_FreeSurface(menu->superficieRanking);
	SDL_FreeSurface(menu->superficieCreditos);
	SDL_FreeSurface(menu->superficieSair);
	return 1;
}
void lerRecords(SDL_Renderer* renderer, Menu1* menu){
	SDL_Color branco = {255, 255, 255};
	FILE    *textfile;
    char    line[50];

    textfile = fopen("records.txt", "r");
    if(textfile == NULL)
    	return 1;

    while(fgets(line, 50, textfile)){
    	line[strcspn(line, "\n")] = '\0';
    	SDL_Surface* superficieRecords = TTF_RenderText_Solid(menu->fonteRecord,line, branco);
    	SDL_Texture* texturaRecords= SDL_CreateTextureFromSurface(renderer, superficieRecords);
    	SDL_Rect src2 = { 50, 200, 700, 400};
    	SDL_FreeSurface(superficieRecords);
    	SDL_RenderCopy(renderer, texturaRecords, NULL, &src2);
    	SDL_RenderPresent(renderer);
    }
    fclose(textfile);
}
int listenEventMenu2(Menu1* menu){
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
void renderMenu2(SDL_Renderer* renderer, Menu1* menu){
	menu->r.x = 545;
	menu->r.y = 450;
	SDL_Rect srcBotao = { 575 ,450 ,225,80};
	SDL_RenderClear(renderer);
	lerRecords(renderer, menu);
	SDL_RenderCopy(renderer, menu->fundo, NULL, &menu->dstrect);
	// SDL_RenderCopy(renderer, menu->texturaTexto, NULL, &menu->src);
	SDL_RenderCopy(renderer, menu->texturaScore, NULL, &menu->src);
    SDL_RenderCopy(renderer, menu->texturaBotao, NULL, &srcBotao);
    SDL_RenderCopy(renderer, menu->texturaVolta, NULL, &menu->srcVolta);
	SDL_RenderCopy(renderer, menu->texturaSeta, NULL, &menu->r);
}

int loopMenu2(SDL_Renderer* renderer, Menu1* menu){
	while (listenEventMenu2(menu) == 0)
	{
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyTexture(menu->fundo);
	SDL_DestroyTexture(menu->nomejogo);
	SDL_DestroyTexture(menu->texturaTexto);
	SDL_DestroyTexture(menu->texturaPlay);
	SDL_DestroyTexture(menu->texturaOpcao);
	SDL_DestroyTexture(menu->texturaInstrucao);
	SDL_DestroyTexture(menu->texturaRanking);
	SDL_DestroyTexture(menu->texturaCreditos);
	SDL_DestroyTexture(menu->texturaSair);

	SDL_FreeSurface(menu->superficieFundo);
	SDL_FreeSurface(menu->superficieNome);
	SDL_FreeSurface(menu->superficieTexto);
	SDL_FreeSurface(menu->superficiePlay);
	SDL_FreeSurface(menu->superficieOpcao);
	SDL_FreeSurface(menu->superficieInstrucao);
	SDL_FreeSurface(menu->superficieRanking);
	SDL_FreeSurface(menu->superficieCreditos);
	SDL_FreeSurface(menu->superficieSair);
	return 1;
}