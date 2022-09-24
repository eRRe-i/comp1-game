#include<SDL2/SDL.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int j = 0;


void seleciona(int a);


SDL_Renderer* renderer = NULL;

SDL_Texture * fundo = NULL;
SDL_Texture * nomejogo = NULL;
SDL_Texture* texturaBotao = NULL;
SDL_Texture* texturaTexto = NULL;
SDL_Texture* texturaPlay = NULL;
SDL_Texture* texturaOpcao = NULL;
SDL_Texture* texturaInstrucao = NULL;
SDL_Texture* texturaRanking = NULL;
SDL_Texture* texturaCreditos = NULL;
SDL_Texture* texturaSair = NULL;
SDL_Texture* texturaSeta = NULL;



SDL_Rect r = {SCREEN_WIDTH/2 - 330, 143, 40, 40};

SDL_Rect dstrect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_Rect src = { SCREEN_WIDTH/2 - 340/2, 0 , 340, 148};// 340/2 - metade da imagem para ficar centralizado
    SDL_Rect src1 = { SCREEN_WIDTH/2 - 300, 148 ,150,50};
    SDL_Rect src2 = { SCREEN_WIDTH/2 -300, 148+75 , 150, 50};
    SDL_Rect src3 = { SCREEN_WIDTH/2 -300, 148+(75*2),150, 50};
    SDL_Rect src4 = { SCREEN_WIDTH/2 -300, 148+(75*3), 150, 50};
    SDL_Rect src5 = { SCREEN_WIDTH/2 -300, 148+(75*4), 150, 50};
    SDL_Rect src6 = { SCREEN_WIDTH/2 -300, 148+(75*5), 150, 50};



    int main(int argc, char ** argv)
    {

    	int i = 0;

    	SDL_Init(SDL_INIT_VIDEO);

    	SDL_Window * window = SDL_CreateWindow("Menu",
    		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    	renderer = SDL_CreateRenderer(window, -1, 0);

    //inicializa ttf
    	if(TTF_Init() == -1){
    		SDL_Log("ERROR : SDL2_ttf não foi possível inicializar > %s\n", SDL_GetError());
    	} else{
    		SDL_Log("SDL2_ttf foi inicializado corretamente > %s\n", SDL_GetError());
    	}
    //Carregar arquivo fonte e setar o tamanho
    	TTF_Font* fonteJogo = TTF_OpenFont("./fonts/IMMORTAL.ttf",128);
    	TTF_Font* fonteBotao = TTF_OpenFont("./fonts/ChocoladineDemo.ttf",64);
	//TTF_Font* fonteScore = TTF_OpenFont("./fonts/ka1.ttf",16);
	//TTF_Font* fonteRecord = TTF_OpenFont("./fonts/ArcadeClassic.ttf",32);
    	SDL_Color preto = {0, 0, 0};
    	SDL_Color branco = {255, 255, 255};
    //confirmar que foi carregado
    	if(fonteJogo == NULL){
    		SDL_Log("ERROR : Não foi possível carregar a fonte > %s\n", SDL_GetError());
    		exit(1);
    	}

    	SDL_Surface * superficieFundo = IMG_Load("menuback.png");
    	SDL_Surface * superficieBotao = IMG_Load("botao.png");
    	SDL_Surface* superficieTexto = TTF_RenderText_Solid(fonteJogo,"Jogo Foda", preto);
    	SDL_Surface* superficiePlay = TTF_RenderText_Solid(fonteBotao,"Jogar", preto);
    	SDL_Surface* superficieOpcao = TTF_RenderText_Solid(fonteBotao,"Opções", preto);
    	SDL_Surface* superficieInstrucao = TTF_RenderText_Solid(fonteBotao,"Instruções", preto);
    	SDL_Surface* superficieCreditos = TTF_RenderText_Solid(fonteBotao,"Créditos", preto);
    	SDL_Surface* superficieRanking = TTF_RenderText_Solid(fonteBotao,"Ranking", preto);
    	SDL_Surface* superficieSair = TTF_RenderText_Solid(fonteBotao,"Sair", preto);

	
	SDL_Surface * superficieNome = IMG_Load("nomejogo.jpeg");
	/*SDL_Surface * superficiePlay = IMG_Load("play.jpeg");
	SDL_Surface * superficieOpcao = IMG_Load("instrucao.png");
	SDL_Surface * superficieInstrucao = IMG_Load("opcao.jpeg");
	SDL_Surface * superficieCreditos = IMG_Load("botao1.png");
	SDL_Surface * superficieSair = IMG_Load("botao.png");*/
    	SDL_Surface * superficieSeta = IMG_Load("seta.png");



	//SDL_Surface* superficieScore = TTF_RenderText_Solid(fonteScore,"Scores:", branco);



    	fundo = SDL_CreateTextureFromSurface( renderer,superficieFundo);
    	texturaBotao = SDL_CreateTextureFromSurface( renderer,superficieBotao);
    	nomejogo = SDL_CreateTextureFromSurface( renderer,superficieNome);
    	texturaTexto = SDL_CreateTextureFromSurface(renderer, superficieTexto);
    	texturaPlay = SDL_CreateTextureFromSurface(renderer, superficiePlay);
    	texturaOpcao = SDL_CreateTextureFromSurface(renderer, superficieOpcao);
    	texturaInstrucao = SDL_CreateTextureFromSurface(renderer, superficieInstrucao);
    	texturaCreditos = SDL_CreateTextureFromSurface(renderer, superficieCreditos);
    	texturaRanking = SDL_CreateTextureFromSurface(renderer, superficieRanking);
    	texturaSair = SDL_CreateTextureFromSurface(renderer, superficieSair);
    	texturaSeta = SDL_CreateTextureFromSurface(renderer, superficieSeta);

	//SDL_Texture* texturaScore = SDL_CreateTextureFromSurface(renderer, superficieScore);


	//SDL_FreeSurface(superficieScore);
    	

	/*SDL_Rect r;
    r.x = SCREEN_WIDTH/2 - 305;
    r.y = 142;
    r.w = 160;
    r.h =60;

    SDL_Rect dstrect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_Rect src = { SCREEN_WIDTH/2 - 340/2, 0 , 340, 148};// 340/2 - metade da imagem para ficar centralizado
    SDL_Rect src1 = { SCREEN_WIDTH/2 - 300, 148 , 150,50};
    SDL_Rect src2 = { SCREEN_WIDTH/2 -300, 148+75 , 150, 50};
    SDL_Rect src3 = { SCREEN_WIDTH/2 -300, 148+(75*2), 150, 50};
    SDL_Rect src4 = { SCREEN_WIDTH/2 -300, 148+(75*3), 150, 50};
    SDL_Rect src5 = { SCREEN_WIDTH/2 -300, 148+(75*4), 150, 50};*/


    	SDL_RenderCopy(renderer, fundo, NULL, &dstrect);
    	

    //SDL_RenderCopy(renderer, nomejogo, NULL, &src); // Titulo jogo png

    //SDL_SetRenderDrawColor( renderer,255, 0, 0, 255 );
    //SDL_RenderFillRect( renderer, &r );

    	SDL_RenderCopy(renderer, texturaTexto, NULL, &src);
    	SDL_RenderCopy(renderer, texturaBotao,NULL, &src1);
    	SDL_RenderCopy(renderer, texturaPlay, NULL, &src1);
    	SDL_RenderCopy(renderer, texturaBotao,NULL, &src2);
    	SDL_RenderCopy(renderer, texturaOpcao, NULL, &src2);
    	SDL_RenderCopy(renderer, texturaBotao,NULL, &src3);
    	SDL_RenderCopy(renderer, texturaInstrucao, NULL, &src3);
    	SDL_RenderCopy(renderer, texturaBotao,NULL, &src4);
    	SDL_RenderCopy(renderer, texturaRanking,NULL, &src4);
    	SDL_RenderCopy(renderer, texturaBotao,NULL, &src5);
    	SDL_RenderCopy(renderer, texturaCreditos, NULL, &src5);
    	SDL_RenderCopy(renderer, texturaBotao,NULL, &src6);
    	SDL_RenderCopy(renderer, texturaSair, NULL, &src6);
    	SDL_RenderCopy(renderer, texturaSeta, NULL, &r);





    //SDL_RenderCopy(renderer, texturaScore, NULL, &src1);
    	SDL_RenderPresent(renderer);





   /* //ler arquivo record nome
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
    	SDL_Rect src2 = { SCREEN_WIDTH/2 -340/2, 98 +(50 * i), superficieRecords->w, superficieRecords->h};
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


    fclose(textfile);*/

    	SDL_Event e;

    	bool quit = false;

    	while(!quit) {

    		while(SDL_PollEvent( &e ) != 0) {

    			if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
    				quit = true;
    			}
    			else if (e.type == SDL_KEYDOWN) {

    				switch( e.key.keysym.sym ) {

    					case SDLK_UP:
    					if(j > 0){
    						j -=1;
    					}
    					break;

    					case SDLK_DOWN:
    					if(j < 6){
    						j += 1;
    					}
    					break;
    					case SDLK_RETURN:
    					printf("dfa");
    					break;
    				}


    			}




    		}
    		seleciona(j);
    		SDL_RenderPresent(renderer);

    	}


    	SDL_DestroyTexture(fundo);
    	SDL_DestroyTexture(nomejogo);
    	SDL_DestroyTexture(texturaTexto);
    	SDL_DestroyTexture(texturaPlay);
    	SDL_DestroyTexture(texturaOpcao);
    	SDL_DestroyTexture(texturaInstrucao);
    	SDL_DestroyTexture(texturaRanking);
    	SDL_DestroyTexture(texturaCreditos);
    	SDL_DestroyTexture(texturaSair);

    	SDL_FreeSurface(superficieFundo);
    	SDL_FreeSurface(superficieNome);
    	SDL_FreeSurface(superficieTexto);
    	SDL_FreeSurface(superficiePlay);
    	SDL_FreeSurface(superficieOpcao);
    	SDL_FreeSurface(superficieInstrucao);
    	SDL_FreeSurface(superficieRanking);
    	SDL_FreeSurface(superficieCreditos);
    	SDL_FreeSurface(superficieSair);


    	SDL_DestroyRenderer(renderer);
    	SDL_DestroyWindow(window);
    	TTF_CloseFont(fonteJogo);

    	SDL_Quit();


    	return 0;
    }

    void seleciona(int a){
    	if(a == 0){
    		r.y = src1.y;
    	}
    	if(a == 1){

    		r.y = src2.y;
    	}
    	if(a == 2){

    		r.y = src3.y;
    	}
    	if(a == 3){

    		r.y = src4.y;
    	}if(a == 4){

    		r.y = src5.y;
    	}
    	if(a == 5){

    		r.y = src6.y;
    	}
    	SDL_RenderClear(renderer);
    	SDL_RenderCopy(renderer, fundo, NULL, &dstrect);
    	SDL_RenderCopy(renderer, texturaTexto, NULL, &src);
    	SDL_RenderCopy(renderer, texturaBotao,NULL, &src1);
    	SDL_RenderCopy(renderer, texturaPlay, NULL, &src1);
    	SDL_RenderCopy(renderer, texturaBotao,NULL, &src2);
    	SDL_RenderCopy(renderer, texturaOpcao, NULL, &src2);
    	SDL_RenderCopy(renderer, texturaBotao,NULL, &src3);
    	SDL_RenderCopy(renderer, texturaInstrucao, NULL, &src3);
    	SDL_RenderCopy(renderer, texturaBotao,NULL, &src4);
    	SDL_RenderCopy(renderer, texturaRanking,NULL, &src4);
    	SDL_RenderCopy(renderer, texturaBotao,NULL, &src5);
    	SDL_RenderCopy(renderer, texturaCreditos, NULL, &src5);
    	SDL_RenderCopy(renderer, texturaBotao,NULL, &src6);
    	SDL_RenderCopy(renderer, texturaSair, NULL, &src6);
    	SDL_RenderCopy(renderer, texturaSeta, NULL, &r);



    }