#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<unistd.h> 

#define WIDTH 800
#define HEIGHT 600
#define IMG_PATH "assets/gaia.jpeg"
#define CHARA_PATH "assets/chara.png"
#define FRONT 0
#define BACK 1
#define LEFT 2
#define RIGHT 3

typedef struct characterStats {

	int life;

} CharacterStats;

typedef struct characterImage {

	SDL_Texture* characterSheet;
    SDL_Rect spritePosition[4][4];

    int spriteWidth;
    int spriteHeight;

    int frame;
    SDL_Rect displayRect;

} CharacterImage;


typedef struct chara {

	CharacterImage characterImage;
	CharacterStats characterStats;

} Character;

typedef struct backgroundImage {
	
	SDL_Texture* backgroundImage;
	SDL_Rect displayRect;

	int width;
	int height;

} BackgroundImage;

typedef struct background {

	BackgroundImage backgroundImage;

} Background;

int waiting(void);
void updateScreen(SDL_Renderer* renderer, Background* background, Character* character);
Character* loadCharacter(SDL_Renderer* renderer);
Background* loadBackground(SDL_Renderer* renderer);
SDL_Texture* loadImage(SDL_Renderer* renderer, const char* imgPath);


int main (int argc, char *argv[])
{
	// variable declarations
	SDL_Window *win = NULL;
	SDL_Renderer *renderer = NULL;
	
	int w, h; // texture width & height
	
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
			return 1;
	
	// create the window and renderer
	// note that the renderer is accelerated
	win = SDL_CreateWindow("Image Loading", 100, 100, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	
	// load our image
	

    // get the width and height of the texture
	// put the location where we want the texture to be drawn into a rectangle
	// I'm also scaling the texture 0.25x simply by setting the width and height
	Background* background = loadBackground(renderer);
    Character* character = loadCharacter(renderer);
	
	chdir("..");

	// main loop
	while (waiting()) {
        
        updateScreen(renderer, background, character);

	}
	
	SDL_DestroyTexture(background->backgroundImage.backgroundImage);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	
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
	} 

	return 1;
}

Background* loadBackground(SDL_Renderer* renderer) {

	Background* background = (Background*)malloc(sizeof(Background));

	background->backgroundImage.backgroundImage = loadImage(renderer, IMG_PATH);
	
	SDL_QueryTexture(background->backgroundImage.backgroundImage, NULL, NULL, &background->backgroundImage.width, &background->backgroundImage.height); 

	fprintf(stderr, "%d\n", background->backgroundImage.width);
	fprintf(stderr, "%d\n", background->backgroundImage.height);


	background->backgroundImage.displayRect.x = 0;
	background->backgroundImage.displayRect.y = 0;
	background->backgroundImage.displayRect.w = background->backgroundImage.width;
	background->backgroundImage.displayRect.h = background->backgroundImage.height;

	return background;
}

Character* loadCharacter(SDL_Renderer* renderer) {

    Character* character = (Character*)malloc(sizeof(Character));

    character->characterImage.characterSheet = loadImage(renderer, CHARA_PATH);

    character->characterImage.spriteWidth = 400;
    character->characterImage.spriteHeight = 600;
    
    SDL_Rect temp;

    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {

            character->characterImage.spritePosition[i][j].x = character->characterImage.spriteWidth*j;
            character->characterImage.spritePosition[i][j].y = character->characterImage.spriteHeight*i;
            character->characterImage.spritePosition[i][j].w = character->characterImage.spriteWidth;
            character->characterImage.spritePosition[i][j].h = character->characterImage.spriteHeight;
        }
    }

    character->characterImage.frame = 0;

    character->characterImage.displayRect.x=WIDTH/2 - 50/2;
    character->characterImage.displayRect.y=HEIGHT/2 - 75/2;
    character->characterImage.displayRect.w=50;
    character->characterImage.displayRect.h=75;

    return character;
}


void updateScreen(SDL_Renderer* renderer, Background* background, Character* character) {

                
        // clear the screen
		SDL_RenderClear(renderer);
		// copy the texture to the rendering context
		SDL_RenderCopy(renderer, background->backgroundImage.backgroundImage, NULL, &background->backgroundImage.displayRect);
		// flip the backbuffer  
		// this means that everything that we prepared behind the screens is actually shown
        SDL_RenderCopy(renderer, character->characterImage.characterSheet, &character->characterImage.spritePosition[FRONT][1], &character->characterImage.displayRect);
        

		SDL_RenderPresent(renderer);

}

SDL_Texture* loadImage(SDL_Renderer* renderer, const char* imgPath) {

	SDL_Texture* texture = IMG_LoadTexture(renderer, imgPath);

	if(texture == NULL){

		printf("Erro no Carregamento da imagem %s\n", imgPath);
	} 

	return texture;

}