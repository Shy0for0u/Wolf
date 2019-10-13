/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 00:00:47 by dgorold-          #+#    #+#             */
/*   Updated: 2019/10/13 17:45:43 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void        player_move(int key, t_w *w)
{

    if (key == 126)
    {
        if (w->array[(w->player.y / 64)][(w->player.x / 64)] != 1)
        {
            w->player.x = w->player.x + cos(w->player.direction * M_PI_180) * w->player.speed;
            w->player.y = w->player.y + sin(w->player.direction * M_PI_180) * w->player.speed;
        }
    }
    if (key == 125)
    {
        if (w->array[(w->player.y / 64)][(w->player.x / 64)] != 1)
        {
            w->player.x = w->player.x - cos(w->player.direction * M_PI_180) * w->player.speed;
            w->player.y = w->player.y - sin(w->player.direction * M_PI_180) * w->player.speed;
        }
    }
    if (key == 124) // right
        w->player.direction += w->player.turn;
    if (key == 123) // left
        w->player.direction -= w->player.turn;
}

int 		deal_key(int key, t_w *w)
{
	if (key == 53)
		exit(0);
	if (key == 13) // w
		w->player.direction += 3;
	if (key == 1) // s
		w->player.direction -= 3;
    player_move(key, w);
	return (0);
}

int      update(t_w *w)
{

	process_of_wolf(w);
	return (0);
}

void		hooks(t_w *w)
{
	mlx_hook(w->mlx.win, 2, 5, deal_key, w);
	mlx_loop_hook(w->mlx.mlx, update, w);
}
