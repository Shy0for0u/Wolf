/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:45:28 by dgorold-          #+#    #+#             */
/*   Updated: 2019/10/17 21:30:17 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

static t_ray	*choose_ray(t_w *w, t_ray *horiz, t_ray *vert, double angle)
{
	while (!is_wall(w, horiz->start.y / 64, horiz->start.x / 64))
	{
		horiz->start.x += horiz->step.x;
		horiz->start.y += horiz->step.y;
	}
	while (!is_wall(w, vert->start.y / (64), vert->start.x / (64)))
	{
		vert->start.x += vert->step.x;
		vert->start.y += vert->step.y;
	}
	horiz->dist = fabs((w->player.y - horiz->start.y) / sin(angle));
	vert->dist = fabs((w->player.x - vert->start.x) / cos(angle));
	if (horiz->dist <= vert->dist)
	{
		free(vert);
		return (horiz);
	}
	else
	{
		free(horiz);
		return (vert);
	}
}

static t_ray	*get_ray(t_w *w, double angle)
{
	t_ray		*vert;
	t_ray		*horiz;
	t_ray		*result;

	angle = angle * M_PI_180;
	horiz = init_horiz(w->player.x, w->player.y, angle);
	vert = init_vert(w->player.x, w->player.y, angle);
	result = choose_ray(w, horiz, vert, angle);
	calc_wall_data(w, result, angle);
	result->dist *= cos(angle - w->player.direction * M_PI_180);
	return (result);
}

static void		calc_single_ray(t_w *w, int x, double angle)
{
	t_ray		*ray;

	ray = get_ray(w, angle);
	ray->height = TEXT_SIZE / ray->dist * w->dist_to_projection_plane;
	draw_column(w, ray, x);
	free(ray);
}

void			process_of_wolf(t_w *w)
{
	double		angle;
	double		one_angle;
	int			x;

	angle = (w->player.direction - (60.0 * 0.5));
	one_angle = (60.0 / W);
	x = 0;
	while (x < W)
	{
		calc_single_ray(w, x, angle);
		angle = angle + one_angle;
		x++;
	}
}
