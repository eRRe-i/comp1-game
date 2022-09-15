#include "character.h"

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

    character->characterImage.displayRect.x=WINDOW_WIDTH/2 - 48/2;
    character->characterImage.displayRect.y=WINDOW_HEIGHT/2 - 72/2;
    character->characterImage.displayRect.w=48;
    character->characterImage.displayRect.h=72;

    return character;
}

void move_Character(Character* character) {

    character->characterImage.frame = (character->characterImage.frame + 1)%4;

}