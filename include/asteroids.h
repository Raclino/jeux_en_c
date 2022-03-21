/*
** ETNA PROJECT, 15/06/2021 by dousse_r
** /home/slowiizz/Documents/etna/SummerProject
** File description:
**      asteroids header
*/

#ifndef _ASTEROIDS_H_
#define _ASTEROIDS_H_

#include "my_includes.h"

typedef struct asteroid {
    int velocity;
    SDL_bool running;
    SDL_Rect pos;
    SDL_Texture* sprite;
    SDL_Renderer* renderer;
    struct asteroid* next;
    struct asteroid* prev;
} Asteroid;

Asteroid* move_asteroid(Asteroid* asteroid);

Asteroid* destroy(Asteroid* asteroid);
Asteroid* push_front(Asteroid* next, SDL_Renderer* renderer);


#endif