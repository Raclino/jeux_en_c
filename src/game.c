/*
** ETNA PROJECT, 15/06/2021 by dousse_r
** /home/slowiizz/Documents/etna/SummerProject
** File description:
**      game loop
*/

#include "my_includes.h"

extern int score;

int run(SDL_Renderer* renderer, int difficulty)
{
    Player player;
    SDL_Rect score_rect = {SCREEN_WIDHT / 2 - 150,0,300,50};
    Text score_t;
    SDL_bool running = SDL_TRUE;
    Asteroid* asteroid_list = NULL;
    unsigned int asteroid_tick = 0;
    unsigned int asteroid_next_tick = 1000;
    int velocity = 7;
    unsigned int my_limit = 0;
    SDL_bool quit = SDL_FALSE;
    SDL_bool adapt = SDL_FALSE;
    if (difficulty == -1) {
        adapt = SDL_TRUE;
        difficulty = 300;
    };
    player = init_player(renderer);
    score_t = text_init(renderer, "Score : %d", score_rect, 15);
    while (running) {
        SDL_Event event;
        if (asteroid_next_tick - asteroid_tick > (unsigned int) difficulty) {
            asteroid_tick = SDL_GetTicks();
            asteroid_list = push_front(asteroid_list, renderer);
        }
        asteroid_next_tick = SDL_GetTicks();
        asteroid_list = move_asteroid(asteroid_list);
        player = move_player(player);
        score_t = draw_game(score_t, renderer, player, asteroid_list, &running);
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_z:
                    player.velocity = -velocity;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    player.velocity = velocity;
                    break;
                default:
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_z:
                    player.velocity = 0;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    player.velocity = 0;
                    break;
                case SDLK_ESCAPE:
                    if (pause_game(renderer)) {
                        running = SDL_FALSE;
                        quit = SDL_TRUE;
                    }
                    break;
                default:
                    break;
                }
                break;
            case SDL_QUIT:
                running = SDL_FALSE;
                quit = SDL_TRUE;
                break;
            default:
                break;
            }
        }
        if (adapt)
            difficulty = 300 - score / 2;
        if (difficulty < 100)
            difficulty = 100;


        limit_frames(my_limit);
        my_limit = SDL_GetTicks() + MY_FPS;
    }
    while (asteroid_list != NULL) {
        Asteroid* next = asteroid_list->next;
        SDL_DestroyTexture(asteroid_list->sprite);
        free(asteroid_list);
        asteroid_list = next;
    }
    destroy_text(score_t);
    SDL_DestroyTexture(player.sprite);
    //add_score_to_ladder();
    return(quit);
}

Text text_init(SDL_Renderer* renderer, char* string, SDL_Rect rect, int font_size)
{
    Text text;
    SDL_Color color = {255,255,255,255};
    text.color = color;
    text.font = TTF_OpenFont("./fonts/arial.ttf", font_size);
    text.rect = rect;
    sprintf(text.string, string);
    text.renderer = renderer;
    return(text);
}

void destroy_text(Text text)
{
    SDL_DestroyTexture(text.texture);
    TTF_CloseFont(text.font);
}

void update_score(Text score_t)
{
    sprintf(score_t.string, "Score : %d", score);
    score_t.surface = TTF_RenderText_Solid(score_t.font, score_t.string, score_t.color);
    score_t.texture = SDL_CreateTextureFromSurface(score_t.renderer, score_t.surface);
    SDL_RenderCopy(score_t.renderer, score_t.texture, NULL, &score_t.rect);
}


SDL_bool check_colision(Player player, Asteroid* asteroid)
{
    if (player.hitbox.x > asteroid->pos.x + asteroid->pos.w)
        return SDL_FALSE;
    else if (player.hitbox.y < asteroid->pos.y + asteroid->pos.h && player.hitbox.y + player.hitbox.h > asteroid->pos.y)
        return SDL_TRUE;
    else
        return SDL_FALSE;
}

int random(int  min, int max)
{
    return (min + rand() % (max - min + 1));
}



SDL_bool pause_game(SDL_Renderer* renderer)
{
    SDL_bool running = SDL_TRUE;
    SDL_bool quit = SDL_FALSE;
    unsigned int my_limit = 0;

    pause_screen(renderer);

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    quit = SDL_TRUE;
                running = SDL_FALSE;
                break;
            case SDL_QUIT:
                running = SDL_FALSE;
                quit = SDL_TRUE;
                break;
            default:
                break;
            }
        }
        limit_frames(my_limit);
        my_limit = SDL_GetTicks() + MY_FPS;
    }
    return quit;
}