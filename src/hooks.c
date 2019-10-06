/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 00:00:47 by dgorold-          #+#    #+#             */
/*   Updated: 2019/10/06 00:01:51 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

int 		deal_key(int key, t_w *w)
{
	if (key == 53)
		exit(0);

	process_of_wolf(w);
	return (0);
}

void		hooks(t_w *w)
{
	mlx_hook(w->mlx.win, 2, 5, deal_key, &w); /*  fail  */
}
