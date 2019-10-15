/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 00:00:47 by dgorold-          #+#    #+#             */
/*   Updated: 2019/10/15 22:41:29 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

int		check_for_quit(SDL_Event *event, t_sdl *sdl)
{
    if (event->type == SDL_QUIT || sdl->keyboard[SDL_SCANCODE_ESCAPE])
        return (1);
    return (0);
}

int             check_position(t_w *w, int x, int y)
{
    if (w->array[(y / 64)][(x / 64)] != 1)
        return (1);
    return (0);
}

void             player_move(t_w *w, int dir)
{
    int     tmp_x;
    int     tmp_y;

    tmp_x = w->player.x;
    tmp_y = w->player.y;
    w->player.x = w->player.x + dir * cos(w->player.direction * M_PI_180) * w->player.speed;
    if (!check_position(w, w->player.x, w->player.y))
        w->player.x = tmp_x;
    w->player.y = w->player.y + dir * sin(w->player.direction * M_PI_180) * w->player.speed;
    if (!check_position(w, w->player.x, w->player.y))
        w->player.y = tmp_y;
}

void            keyboard_input(t_w *w)
{
    const Uint8 *key;

    key = w->sdl->keyboard;
    if (key[SDL_SCANCODE_W] || key[SDL_SCANCODE_UP])
        player_move(w, 1);
    if (key[SDL_SCANCODE_A] || key[SDL_SCANCODE_LEFT])
        w->player.direction -= w->player.turn;
    if (key[SDL_SCANCODE_S] || key[SDL_SCANCODE_DOWN])
        player_move(w, -1);
    if (key[SDL_SCANCODE_D] || key[SDL_SCANCODE_RIGHT])
        w->player.direction += w->player.turn;
}
