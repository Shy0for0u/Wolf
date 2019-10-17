/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_for_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:54:30 by dgorold-          #+#    #+#             */
/*   Updated: 2019/10/17 22:33:47 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		calc_wall_data(t_w *w, t_ray *result, double angle)
{
	if (result->type == HORIZ_TYPE)
	{
		result->offset = (int)(result->start.x) % TEXT_SIZE;
		result->texture = w->texture->walls[(sin(angle) > 0 ? 0 : 1)];
	}
	else
	{
		result->offset = (int)(result->start.y) % TEXT_SIZE;
		result->texture = w->texture->walls[(cos(angle) < 0 ? 2 : 3)];
	}
}

int			is_wall(t_w *w, int y, int x)
{
	if (x < 0 || y < 0)
		return (1);
	if (y >= (w->m.map_h) || x >= (w->m.map_w))
		return (1);
	if (w->array[y][x] == 1)
		return (1);
	return (0);
}
