#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
 
#define WIDTH 800
#define HEIGHT 600
#define IMG_PATH "gaia.png"
#define CHARA_PATH "chara.png"
#define FRONT 0
#define BACK 1
#define LEFT 2
#define RIGHT 3
 
 
 #define CHARA_WALK_RATE 10
 
typedef struct chara {
 
    SDL_Texture* characterSheet;
    SDL_Rect spritePosition[4][4];
    int spriteWidth;
    int spriteHeight;
    int frame;
    SDL_Rect displayRect;
 
} Chara;
 
 
int waiting(void);
 
void update(SDL_Renderer* renderer, SDL_Texture* background, Chara* character);
 
Chara* loadCharacter(SDL_Renderer* renderer);
 
void move_chara(Chara *, int, int, int, int);
 
int main (int argc, char *argv[])
{
    // variable declarations
    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *background = NULL;
    int w, h; // texture width & height
       
    // Initialize SDL.
    (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;
       
    // create the window and renderer
    // note that the renderer is accelerated
    win = SDL_CreateWindow("Image Loading", 100, 100, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
       
    //Carrega a imagem
        character = IMG_LoadTexture(renderer, IMG_PATH); //Diferença para o Load Character?
       
        // pegar a largura e o comprimento da textura
        // colocar a localização onde você quer que a textura seja desenhada no retângulo
        // escalonando a textura em duas vezes(2x) ao settar largura e comprimento/altura
        SDL_QueryTexture(character, NULL, NULL, &w, &h);
       
       
    // load our image
    background = IMG_LoadTexture(renderer, IMG_PATH);
 
    // get the width and height of the texture
    // put the location where we want the texture to be drawn into a rectangle
    // I'm also scaling the texture 0.25x simply by setting the width and height
 
 
    Chara* character = loadCharacter(renderer);
   
   
    Chara character;
        // pos inicial
        character.x = 200;
        character.y = 200;
        character.img = imagem_do_character;
        character.w = w;
        character.h = h;
       
   
    while (waiting()) {
           
    SDL_Event movimento;
               
        if(SDL_PollEvent(&movimento))
    {
                if (movimento.type == SDL_QUIT)
                        break;
                else if (movimento.type == SDL_KEYUP && movimento.key.keysym.sym == SDLK_ESCAPE)
                        break;
                else if (movimento.type == SDL_KEYDOWN && movimento.key.keysym.sym == SDLK_w)
                        move_hero(&hero, 1, 0, 0, 0);// como esses int se relacionam com a matriz, mapa, rect e position?
                else if (movimento.type == SDL_KEYDOWN && movimento.key.keysym.sym == SDLK_s)
                        move_hero(&hero, 0, 1, 0, 0);
                else if (movimento.type == SDL_KEYUP && movimento.key.keysym.sym == SDLK_a)
                        move_hero(&hero, 0, 0, 1, 0);
                else if (movimento.type == SDL_KEYUP && movimento.key.keysym.sym == SDLK_d)
                        move_hero(&hero, 0, 0, 0, 1);
        }
        // Limpar a tela
        SDL_RenderClear(renderizador);
               
        // copiar a textura para o contexto de renderização
        SDL_RenderCopy(renderizador, img, NULL, &texr);
 
        print_hero(&character, renderizador);
 
        // flip the backbuffer
        // this means that everything that we prepared behind the screens is actually shown
        SDL_RenderPresent(renderizador);
       
    update(renderer, background, character);
 
    }
       
    SDL_DestroyTexture(background);
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
 
Chara* loadCharacter(SDL_Renderer* renderer) {
 
    Chara* character = (Chara*)malloc(sizeof(Chara));
    character->characterSheet = NULL;
 
    character->characterSheet = IMG_LoadTexture(renderer, CHARA_PATH);
 
    character->spriteWidth = 400;
    character->spriteHeight = 600;
   
    SDL_Rect temp;
 
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
 
            character->spritePosition[i][j].x = character->spriteWidth*j;
            character->spritePosition[i][j].y = character->spriteHeight*i;
            character->spritePosition[i][j].w = character->spriteWidth;
            character->spritePosition[i][j].h = character->spriteHeight;
        }
    }
 
    character->frame = 0;
 
    character->displayRect.x=WIDTH/2 - 50/2;
    character->displayRect.y=HEIGHT/2 - 75/2;
    character->displayRect.w=50;
    character->displayRect.h=75;
 
 
    return character;
}
 
void update(SDL_Renderer* renderer, SDL_Texture* background, Chara* character) {
 
       
 
        int w, h;
        SDL_QueryTexture(background, NULL, NULL, &w, &h);
 
        SDL_Rect texr; texr.x = 0; texr.y = 0; texr.w = w; texr.h = h;
 
 
       
        // clear the screen
                SDL_RenderClear(renderer);
                // copy the texture to the rendering context
                SDL_RenderCopy(renderer, background, NULL, &texr);
                // flip the backbuffer  
                // this means that everything that we prepared behind the screens is actually shown
        SDL_RenderCopy(renderer, character->characterSheet, &character->spritePosition[0][1], &character->displayRect);
       
 
                SDL_RenderPresent(renderer);
 
}
 
void move_character(Chara *character, int up, int down, int left, int right)
{
        character->y -= up * Chara_WALK_RATE;
        character->y += down * Chara_WALK_RATE;
        character->x -= left * Chara_WALK_RATE;
        character->x += right * Chara_WALK_RATE;
}
 
void print_character(Chara *character, SDL_Renderer *renderer)
{
        SDL_Rect texr;
        texr.x = character->x;
        texr.y = character->y;
        texr.w = character->w / 4;
        texr.h = character->h / 4;
 
        SDL_RenderCopy(renderer, character->img, NULL, &texr);
}