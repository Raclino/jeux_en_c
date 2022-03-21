/*
** ETNA PROJECT, 16/06/2021 by dousse_r
** /home/slowiizz/Documents/etna/SummerProject
** File description:
**      window header
*/

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <SDL2/SDL.h>

#define SCREEN_WIDHT 1600
#define SCREEN_HEIGHT 800

typedef struct window {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Window;

Window window_init(void);

void window_destroy(Window window);

#endif