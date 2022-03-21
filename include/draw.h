/*
** ETNA PROJECT, 16/06/2021 by dousse_r
** /home/slowiizz/Documents/etna/SummerProject
** File description:
**      drawing header
*/

#ifndef _DRAW_H_
#define _DRAW_H_

#include "my_includes.h"

Text draw_game(Text score_t, SDL_Renderer* renderer, Player player, Asteroid* asteroid_array, SDL_bool *running);

void draw_things_center(SDL_Renderer* renderer, char* path_to_image, int* w, int* h);

Text  draw_text(Text text);

void pause_screen(SDL_Renderer* renderer);

void main_menu(SDL_Renderer* renderer, int difficulty);

void leaderboard(SDL_Renderer* renderer);


#endif