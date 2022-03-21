/*
** ETNA PROJECT, 15/06/2021 by dousse_r
** /home/slowiizz/Documents/etna/SummerProject
** File description:
**      functions related to asteroids
*/

#include "my_includes.h"

extern int score;



Asteroid* move_asteroid(Asteroid* asteroid)
{
    Asteroid* head = asteroid;
    while (asteroid != NULL) {
        asteroid->pos.x += asteroid->velocity;
        if (asteroid->pos.x > SCREEN_WIDHT) {
            asteroid = destroy(asteroid);
            score++;
        }
        asteroid = asteroid->next;
    }
    return(head);
}



Asteroid* destroy(Asteroid* asteroid)
{
    Asteroid* prev;
    prev = asteroid->prev;
    if (asteroid->next != NULL)
        asteroid->next->prev = asteroid->prev;
    if (asteroid->prev != NULL)
        asteroid->prev->next = asteroid->next;
    SDL_DestroyTexture(asteroid->sprite);
    free(asteroid);
    return(prev);
}


Asteroid* push_front(Asteroid* next, SDL_Renderer* renderer)
{
    Asteroid* current;
    current = malloc(sizeof(*current));
    current->next = next;
    if (next == NULL)
        current->prev = NULL;
    else {
        current->prev = next->prev;
        next->prev = current;
    }
    current->sprite = IMG_LoadTexture(renderer, "./sprites/asteroid.png");
    SDL_QueryTexture(current->sprite, NULL, NULL, &current->pos.w, &current->pos.h);
    current->pos.h = SCREEN_HEIGHT / 15;
    current->pos.w = current->pos.h;
    current->pos.y = random(0, SCREEN_HEIGHT - current->pos.h);
    current->pos.x = -current->pos.w;
    current->velocity = random(10, 15);
    current->running = SDL_FALSE;
    return(current);
}