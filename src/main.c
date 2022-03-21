/*
** ETNA PROJECT, 14/06/2021 by dousse_r
** /home/slowiizz/Documents/etna/SummerProject
** File description:
**      main
*/

#include "my_includes.h"

int score;

void limit_frames(unsigned int limit)
{
    unsigned int elapsed = SDL_GetTicks();
    if (limit < elapsed)
        return;
    else if (limit > elapsed + MY_FPS)
        SDL_Delay(MY_FPS);
    else
        SDL_Delay(limit - elapsed);
}

int main(void)
{
    Window window;
    SDL_bool running = SDL_TRUE;
    SDL_bool leader = SDL_FALSE;
    unsigned int my_limit = 0;
    int difficulty_array[5] = {-1,100,150,200,300};
    int array_index = 3;

    srand(time(NULL));
    window = window_init();

    main_menu(window.renderer, array_index);
    running = SDL_TRUE;
    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                    array_index--;
                    if (array_index < 0)
                        array_index = 4;
                    SDL_RenderClear(window.renderer);

                    main_menu(window.renderer, array_index);

                    break;
                case SDLK_DOWN:
                    array_index++;
                    if (array_index > 4)
                        array_index = 0;
                    SDL_RenderClear(window.renderer);
                    main_menu(window.renderer, array_index);
                    break;
                case SDLK_ESCAPE:
                    running = SDL_FALSE;
                    break;
                case SDLK_TAB:
                    if (!leader) {
                        SDL_RenderClear(window.renderer);
                        leaderboard(window.renderer);
                        leader = SDL_TRUE;
                    }
                    break;
                case SDLK_SPACE:
                    score = 0;
                    if (run(window.renderer, difficulty_array[array_index])) {
                        running = SDL_FALSE;
                    } else {
                        draw_things_center(window.renderer, "./sprites/game_over.png", NULL, NULL);
                        SDL_RenderPresent(window.renderer);
                        SDL_Delay(2000);
                        SDL_RenderClear(window.renderer);
                        main_menu(window.renderer, array_index);
                    }
                    printf("Score : %d\n", score);
                    add_score_to_ladder(array_index);
                    break;

                default:
                    break;
                }
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_TAB) {
                    SDL_RenderClear(window.renderer);
                    main_menu(window.renderer, array_index);
                    leader = SDL_FALSE;
                }
                break;
            case SDL_QUIT:
                running = SDL_FALSE;
            break;
            default:
                break;
            }
        }
        limit_frames(my_limit);
        my_limit = SDL_GetTicks() + MY_FPS;
    }
    window_destroy(window);
    return EXIT_SUCCESS;
}