/*
** ETNA PROJECT, 15/06/2021 by dousse_r
** /home/slowiizz/Documents/etna/SummerProject
** File description:
**      player includes
*/

#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "my_includes.h"

typedef struct player {
    int health;
    int velocity;
    SDL_Rect hitbox;
    SDL_Rect pos;
    SDL_Texture* sprite;
    SDL_Renderer* renderer;
} Player;

Player init_player(SDL_Renderer* renderer);

Player move_player(Player player);

#endif