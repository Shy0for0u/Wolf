#include <math.h>
#include "../includes/wolf.h"

void			pixel_to_img(t_w *w, int y, int x)
{
	int 		index;

	index = (x * 4 + w->mlx.sl * y);
	w->mlx.data[index] = (char)0xff;
	w->mlx.data[index + 1] = (char)0xff;
	w->mlx.data[index + 2] = (char)0xff;
}

t_ray			*choose_ray(t_w *w, t_ray *horiz, t_ray *vert, float angle)
{

}

t_ray			*init_horiz(int x, int y, float angle)
{
	t_ray		*ray;

	ray = (t_ray *)malloc(sizeof(t_ray));
	ray->dist = 9999;
	ray->type = 1;
	if (sinf(angle) < 0)
	{
		ray->start.y = (float)((int)(y / 64) * 64 - 1);
		ray->step.y = -64;
	}
	else if (sinf(angle) > 0)
	{
		ray->start.y = (float)((int)(y / 64) * 64 + 64);
		ray->step.y = 64;
	}
	else
		return (ray);
	ray->step.x = -ray->step.y / tanf(-angle);
	ray->start.x = x + (ray->start.y - y) / tanf(angle);
	return (ray);
}

t_ray			*init_vert(int x, int y, float angle)
{
	t_ray		*ray;

	ray = (t_ray *)malloc(sizeof(t_ray));
	ray->dist = 9999;
	ray->type = 0;
	if (cosf(angle) > 0)
	{
		ray->start.x = (int)(x / 64) * 64 + 64;
		ray->step.x = 64;
	}
	else if (cosf(angle) < 0)
	{
		ray->start.x = (int)(x / 64) * 64 - 1;
		ray->step.x = -64;
	}
	else
		return (ray);
	ray->step.y = -ray->step.x * tanf(-angle);
	ray->start.y = y + (ray->start.x - x) * tanf(angle);
	return (ray);
}

t_ray 			*get_ray(t_w *w, int x, float angle)
{
	t_ray		*vert;
	t_ray		*horiz;
	t_ray		*result;

	angle = angle * M_PI_180;
	horiz = init_horiz(w->player->p_x, w->player->p_y, angle);
	vert = init_vert(w->player->p_x, w->player->p_y, angle);
	result = choose_ray(w, horiz, vert, angle);
	return (result);
}

void			cast_single_ray(t_w *w, int x, float angle)
{
	t_ray		*ray;
	t_pl		*wall;

	wall = (t_pl *)malloc(sizeof(t_pl) * 1000);
	wall->p_x = x;
	wall->p_y = w->m.index;
	ray = get_ray(w, x, angle);
//	ray->height = BOX_SIZE / ray->dist * w->dist_to_pp;
	dda(w, w->player, wall);
}

void			process_of_wolf(t_w *w)
{
	int 		x;
	float		angle;
	float		next_angle;

	x = 0;
	angle = w->player->direction - (double)(60 * 0.5);
	next_angle = 60.0 / W;
	while (x < W)
	{
		cast_single_ray(w, x, angle);
		angle = angle + next_angle;
		x++;
	}
	mlx_put_image_to_window(w->mlx.mlx, w->mlx.win, w->mlx.img, W * 0.5, H * 0.5);
}
