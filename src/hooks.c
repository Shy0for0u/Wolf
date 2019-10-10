/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 00:00:47 by dgorold-          #+#    #+#             */
/*   Updated: 2019/10/10 23:49:00 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"



int 		deal_key(int key, t_w *w)
{
	if (key == 53)
		exit(0);
	if (key == 13) // w
		w->player.direction += 3;
	if (key == 1) // s
		w->player.direction -= 3;

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
