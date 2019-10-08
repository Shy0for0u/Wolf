#include <math.h>
#include "../includes/wolf.h"


//t_ray			*choose_ray(t_w *w, t_ray *horiz, t_ray *vert, float angle)
//{
//
//}
//
//t_ray			*init_horiz(int x, int y, float angle)
//{
//	t_ray		*ray;
//
//	ray = (t_ray *)malloc(sizeof(t_ray));
//	ray->dist = 9999;
//	ray->type = 1;
//	if (sinf(angle) < 0)
//	{
//		ray->start.y = (float)((int)(y / 64) * 64 - 1);
//		ray->step.y = -64;
//	}
//	else if (sinf(angle) > 0)
//	{
//		ray->start.y = (float)((int)(y / 64) * 64 + 64);
//		ray->step.y = 64;
//	}
//	else
//		return (ray);
//	ray->step.x = -ray->step.y / tanf(-angle);
//	ray->start.x = x + (ray->start.y - y) / tanf(angle);
//	return (ray);
//}
//
//t_ray			*init_vert(int x, int y, float angle)
//{
//	t_ray		*ray;
//
//	ray = (t_ray *)malloc(sizeof(t_ray));
//	ray->dist = 9999;
//	ray->type = 0;
//	if (cosf(angle) > 0)
//	{
//		ray->start.x = (int)(x / 64) * 64 + 64;
//		ray->step.x = 64;
//	}
//	else if (cosf(angle) < 0)
//	{
//		ray->start.x = (int)(x / 64) * 64 - 1;
//		ray->step.x = -64;
//	}
//	else
//		return (ray);
//	ray->step.y = -ray->step.x * tanf(-angle);
//	ray->start.y = y + (ray->start.x - x) * tanf(angle);
//	return (ray);
//}
//
//void			calc_wall(t_ray *ray, float angle)
//{
//	if (ray->type == 1)
//	{
//		ray->offset = (int)ray->start.x % 64;
//		ray.te
//	}
//}
//
//t_ray 			*get_ray(t_w *w, int x, float angle)
//{
//	t_ray		*vert;
//	t_ray		*horiz;
//	t_ray		*result;
//
//	angle = angle * M_PI_180;
//	horiz = init_horiz(w->player->p_x, w->player->p_y, angle);
//	vert = init_vert(w->player->p_x, w->player->p_y, angle);
//	result = choose_ray(w, horiz, vert, angle);
//	calc_wall(result, angle);
//	return (result);
//}
//
//void			cast_single_ray(t_w *w, int x, float angle)
//{
//	t_ray		*ray;
//	t_pl		*wall;
//
//	wall = (t_pl *)malloc(sizeof(t_pl) * 1000);
//	ray = get_ray(w, x, angle);
////	ray->height = BOX_SIZE / ray->dist * w->dist_to_pp;
//}
//
void			pixel_to_img(t_w *w, int y, int x)
{
	int 		index;

	index = (x * 4 + w->mlx.sl * y);
	w->mlx.data[index] = (char)(0xff >> 16);
	w->mlx.data[index + 1] = (char)(0xff >> 8);
	w->mlx.data[index + 2] = (char)0xff;
}

void			print_squire(t_w *w, int y, int x)
{
	int 	j = y;
	while (j < y + 10)
	{
		int i = x;
		while (i < x + 10)
		{
			pixel_to_img(w, j, i);
			i++;
		}
		j++;
	}

}

int			is_wall(t_w *w, int Ax, int Ay)
{
	if (Ay > w->m.map_h + 2 || Ay < 0)
		return (1);
	if (Ax > w->m.map_w + 2 || Ax < 0)
		return (1);
	if (w->array[Ay][Ax] == 0)
		return (1);
	return (0);
}

void		calc(t_w *w)
{
	int 	Ya;
	int 	Xa;
	int 	Ax;
	int 	Ay;
	if (sinf(0.785398f) > 0)
	{
		Ay = (int)(w->player->p_y / 64) * 64 - 1;
		Ya = -64;
	}
	else if (sinf(0.785398f) < 0)
	{
		Ay = (int)(w->player->p_y / 64) * 64 + 64;
		Ya = 64;
	}
	Xa = 64 / tanf(0.785398f);
	Ax = w->player->p_x + (w->player->p_y - Ay) / tanf(0.785398f);
	while (!is_wall(w, Ax / 64, Ay / 64))
	{
		Ax = Ax + Xa;
		Ay = Ay + Ya;
	}
	w->p.y = Ay;
	w->p.x = Ax;


	t_2d	player;
	player.x = w->player->p_x;
	player.y = w->player->p_y;
	dda(w, player, w->p);
}

void			process_of_wolf(t_w *w)
{
	int y = 0;
	while (y < w->m.map_h + 2)
	{
		int x = 0;
		while (x < w->m.map_w + 2)
		{
			if (w->array[y][x] == 1)
				print_squire(w, y * 5, x * 5);
			if (w->array[y][x] == 2)
				pixel_to_img(w, y * 5, x * 5);
			x++;
		}
		y++;
	}
	calc(w);

	mlx_put_image_to_window(w->mlx.mlx, w->mlx.win, w->mlx.img, W * 0.18, H * 0.18);
}
