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
		ray->start.x = (x / 64) * 64 - 1;
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
		ray->start.y = (y / 64) * 64 - 1;
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
