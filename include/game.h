/*
** ETNA PROJECT, 14/06/2021 by dousse_r
** /home/slowiizz/Documents/etna/SummerProject
** File description:
**      Header du joyeur
*/

#ifndef _ENTITIES_H
#define _ENTITIES_H

#include "my_includes.h"

typedef struct text {
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Color color;
    SDL_Rect rect;
    TTF_Font* font;
    char string[30];
    SDL_Renderer* renderer;
} Text;

void limit_frames(unsigned int limit);

int run(SDL_Renderer* renderer, int difficulty);

Text text_init(SDL_Renderer* renderer, char* string, SDL_Rect rect, int font_size);

SDL_bool check_colision(Player player, Asteroid* asteroid);

int random(int min, int max);

SDL_bool pause_game(SDL_Renderer* renderer);

void destroy_text(Text text);

#endif /*_ENTITIES_H*/