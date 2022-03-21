/*
** ETNA PROJECT, 16/06/2021 by dousse_r
** /home/slowiizz/Documents/etna/SummerProject
** File description:
**      functions related to window and renderers
*/

#include "my_includes.h"

Window window_init(void)
{
    Window window;

    if (TTF_Init() != 0) {
        exit(EXIT_FAILURE);
    }
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        exit(EXIT_FAILURE);
    }


    window.window = SDL_CreateWindow("AstroRun", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDHT, SCREEN_HEIGHT, 0);
    window.renderer = SDL_CreateRenderer(window.window, -1, SDL_RENDERER_ACCELERATED);
    if (window.window == NULL) {
        exit(EXIT_FAILURE);
    }
    if (window.renderer == NULL)
        exit(EXIT_FAILURE);
    return window;
}

void window_destroy(Window window)
{
    SDL_DestroyRenderer(window.renderer);
    SDL_DestroyWindow(window.window);
    TTF_Quit();
    SDL_Quit();
}