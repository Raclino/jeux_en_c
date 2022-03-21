/*
** ETNA PROJECT, 16/06/2021 by dousse_r
** /home/slowiizz/Documents/etna/SummerProject
** File description:
**      functions related to player
*/

#include "my_includes.h"

Player move_player(Player player)
{
    player.pos.y += player.velocity;
    player.hitbox.y = player.pos.y + player.hitbox.h;
    if (player.pos.y < 0)
        player.pos.y = 0;
    if (player.pos.y > SCREEN_HEIGHT - player.pos.h)
        player.pos.y = SCREEN_HEIGHT - player.pos.h;
    return(player);
}

Player init_player(SDL_Renderer* renderer)
{
    Player player;
    player.velocity = 0;
    player.sprite = IMG_LoadTexture(renderer, "sprites/smallfighter0006.png");
    SDL_QueryTexture(player.sprite, NULL, NULL, &player.pos.w, &player.pos.h);
    player.pos.x = SCREEN_WIDHT - player.pos.w;
    player.pos.y = SCREEN_HEIGHT / 2;
    player.hitbox.h = player.pos.h / 3;
    player.hitbox.w = player.pos.w * 0.8;
    player.hitbox.y = player.pos.y + player.hitbox.h;
    player.hitbox.x = player.pos.x + player.hitbox.w * 0.2;
    return player;
}