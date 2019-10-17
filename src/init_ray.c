/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:00:32 by dgorold-          #+#    #+#             */
/*   Updated: 2019/10/17 23:45:05 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

t_ray		*init_vert(int x, int y, double angle)
{
	t_ray	*ray;

	ray = (t_ray *)malloc(sizeof(t_ray));
	ray->type = VERT_TYPE;
	if (cos(angle) > 0)
	{
		ray->start.x = (x / 64) * 64 + 64;
		ray->step.x = 64;
	}
	else if (cos(angle) < 0)
	{
		ray->start.x = (x / 64) * 64 - 0.0001;
		ray->step.x = -64;
	}
	ray->step.y = ray->step.x * tan(angle);
	ray->start.y = y + (ray->start.x - x) * tan(angle);
	return (ray);
}

t_ray		*init_horiz(int x, int y, double angle)
{
	t_ray	*ray;

	ray = (t_ray *)malloc(sizeof(t_ray));
	ray->type = HORIZ_TYPE;
	if (sin(angle) < 0)
	{
		ray->start.y = (y / 64) * 64 - 0.0001;
		ray->step.y = -64;
	}
	else if (sin(angle) > 0)
	{
		ray->start.y = (y / 64) * 64 + 64;
		ray->step.y = 64;
	}
	ray->step.x = ray->step.y / tan(angle);
	ray->start.x = x + (ray->start.y - y) / tan(angle);
	return (ray);
}
