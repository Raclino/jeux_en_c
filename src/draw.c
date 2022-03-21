/*
** ETNA PROJECT, 16/06/2021 by dousse_r
** /home/slowiizz/Documents/etna/SummerProject
** File description:
**      drawing functions
*/

#include "my_includes.h"

extern int score;

Text draw_game(Text score_t, SDL_Renderer* renderer, Player player, Asteroid* asteroid_array, SDL_bool* running)
{
    SDL_RenderClear(renderer);
    while (asteroid_array != NULL && *running) {
        SDL_RenderCopy(renderer, asteroid_array->sprite, NULL, &asteroid_array->pos);
        *running = !check_colision(player, asteroid_array);
        asteroid_array = asteroid_array->next;
    }
    sprintf(score_t.string, "Score : %d", score);
    score_t = draw_text(score_t);
    SDL_RenderCopy(renderer, player.sprite, NULL, &player.pos);
    return score_t;
}

void draw_things_center(SDL_Renderer* renderer, char* path_to_image, int* w, int* h)
{
    SDL_Texture* sprite = NULL;
    SDL_Rect rect;

    sprite = IMG_LoadTexture(renderer, path_to_image);
    if (h != NULL)
        rect.h = *h;
    if (w != NULL)
        rect.w = *w;
    SDL_QueryTexture(sprite, NULL, NULL, &rect.w, &rect.h);
    rect.x = SCREEN_WIDHT / 2 - rect.w / 2;
    rect.y = SCREEN_HEIGHT / 2 - rect.h / 2;
    SDL_RenderCopy(renderer, sprite, NULL, &rect);
    SDL_DestroyTexture(sprite);
}

Text draw_text(Text text)
{
    text.surface = TTF_RenderText_Solid(text.font, text.string, text.color);
    text.texture = SDL_CreateTextureFromSurface(text.renderer, text.surface);
    if (text.texture == NULL)
        exit(EXIT_FAILURE);
    SDL_RenderCopy(text.renderer, text.texture, NULL, &text.rect);
    return text;
};

void pause_screen(SDL_Renderer* renderer)
{
    Text pause;
    SDL_Rect pause_rect = {SCREEN_WIDHT / 2 - 300, SCREEN_HEIGHT / 2 - 300,600,600};
    Text stop;
    SDL_Rect stop_rect = {SCREEN_WIDHT / 2 - 150, pause_rect.y + 600,300,30};
    Text resume;
    SDL_Rect resume_rect = {SCREEN_WIDHT / 2 - 200, stop_rect.y + 40,400,30};

    pause = text_init(renderer, "PAUSE", pause_rect, 600);
    stop = text_init(renderer, "Press [ESC] to QUIT", stop_rect, 600);
    resume = text_init(renderer, "Press ANY KEY to continue", resume_rect, 600);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    SDL_RenderFillRect(renderer, &pause_rect);
    pause = draw_text(pause);
    stop = draw_text(stop);
    resume = draw_text(resume);
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    destroy_text(pause);
    destroy_text(stop);
    destroy_text(resume);
}

void main_menu(SDL_Renderer* renderer, int diffculty)
{
    SDL_Color choosen = {255,0,0,255};
    Text name;
    SDL_Rect name_rect = {SCREEN_WIDHT / 2 - 300, SCREEN_HEIGHT / 2 - 300,600,100};
    name = text_init(renderer, "AstroRun", name_rect, 600);
    name = draw_text(name);

    Text stop;
    SDL_Rect stop_rect = {SCREEN_WIDHT / 2 - 150, name_rect.y + 600,300,30};
    stop = text_init(renderer, "Press [ESC] to QUIT", stop_rect, 600);
    stop = draw_text(stop);
    




    Text resume;
    SDL_Rect resume_rect = {SCREEN_WIDHT / 2 - 200, stop_rect.y + 40,400,30};
    resume = text_init(renderer, "Press [SPACE] to START", resume_rect, 600);
    resume = draw_text(resume);

    Text adapt;
    SDL_Rect adapt_rect = {SCREEN_WIDHT / 2 - 90, SCREEN_HEIGHT / 2 + 40,180,30};
    adapt = text_init(renderer, "Adaptative", adapt_rect, 600);

    Text insane;
    SDL_Rect insane_rect = {SCREEN_WIDHT / 2 - 65, adapt_rect.y + 40,130,30};
    insane = text_init(renderer, "Insane", insane_rect, 600);

    Text hard;
    SDL_Rect hard_rect = {SCREEN_WIDHT / 2 - 40, insane_rect.y + 40,80,30};
    hard = text_init(renderer, "Hard", hard_rect, 600);

    Text normal;
    SDL_Rect normal_rect = {SCREEN_WIDHT / 2 - 65, hard_rect.y + 40,130,30};
    normal = text_init(renderer, "Normal", normal_rect, 600);

    Text easy;
    SDL_Rect easy_rect = {SCREEN_WIDHT / 2 - 35, normal_rect.y + 40,80,30};
    easy = text_init(renderer, "Easy", easy_rect, 600);

    Text text_array[5] = {adapt, insane,hard,normal,easy};

    destroy_text(stop);
    stop_rect.y -= 75 - stop_rect.h;
    stop = text_init(renderer, "Press [TAB] to see ladder", stop_rect, 600);
    stop = draw_text(stop);

    text_array[diffculty].color = choosen;
    for (int i = 0; i < 5; i++) {
        text_array[i] = draw_text(text_array[i]);
        destroy_text(text_array[i]);
    }
    SDL_RenderPresent(renderer);
    destroy_text(name);
    destroy_text(stop);
    destroy_text(resume);
}

void leaderboard(SDL_Renderer* renderer)
{
    int** score_array;
    char my_string[20];
    char* modes[5] = {"ADAPTATIVE",
    "INSANE",
    "HARD",
    "NORMAL",
    "EASY"};
    Text leader;
    SDL_Rect leader_rect = {SCREEN_WIDHT / 2 - 300, 0,600,200};

    Text mode;
    SDL_Rect mode_rect = {SCREEN_WIDHT / 6, 300,200,25};

    Text score_r;
    SDL_Rect score_rect;

    score_array = files_to_scores_array();
    leader = text_init(renderer, "Best Scores", leader_rect, 600);
    draw_text(leader);
    destroy_text(leader);
    for (int i = 0; i < 5; i++) {
        mode = text_init(renderer, modes[i], mode_rect, 600);
        score_rect = mode_rect;
        score_rect.h = 20;
        score_rect.w = 80;
        score_rect.x += 50;
        draw_text(mode);
        for (int j = 0; j < 5 && score_array[i][j] != -1; j++) {
            score_rect.y += 50 + score_rect.h;
            sprintf(my_string, "#%d : %d", j + 1, score_array[i][j]);
            score_r = text_init(renderer, my_string, score_rect, 600);
            draw_text(score_r);
            destroy_text(score_r);

        }
        mode_rect.x += 50 + mode_rect.w;;
        destroy_text(mode);
    };
    SDL_RenderPresent(renderer);
    for (int i = 0; i < 5; i++)
        free(score_array[i]);
    free(score_array);
}