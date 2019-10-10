#include <math.h>
#include "../includes/wolf.h"



void			pixel_to_img(t_w *w, int y, int x)
{
	int 		index;

	index = (x * 4 + w->mlx.sl * y);
	w->mlx.data[index] = 0xff;
	w->mlx.data[index + 1] = 0xff;
	w->mlx.data[index + 2] = 0xff;
}

void			print_squire(t_w *w, int y, int x)
{
	t_2d TL;
	t_2d TR;
	t_2d BL;
	t_2d BR;

	TL.color= 0xff0000;
	TR.color= 0xff0000;
	BL.color= 0xff0000;
	BR.color= 0xff0000;
	TL.y = y * 64;
	TL.x = x * 64;
	TR.y = y * 64;
	TR.x = x * 64 + 64;
	BL.y = y * 64 + 64;
	BL.x = x * 64;
	BR.y = y * 64 + 64;
	BR.x = x * 64 + 64;
	dda(w, TL, TR);
	dda(w, TL, BL);
	dda(w, TR, BR);
	dda(w, BL, BR);
}

void			print_map(t_w *w)
{
	int y = 0;
	while (y < w->m.map_h)
	{
		int x = 0;
		while (x < w->m.map_w)
		{
			if (w->array[y][x] == 1)
				print_squire(w, y, x);
			if (w->array[y][x] == 2)
				pixel_to_img(w, y, x);
			x++;
		}
		y++;
	}
}

int 			is_wall(t_w *w, int y, int x)
{
	if (x < 0 || y < 0)
		return (1);
	if (y >= (w->m.map_h) || x >= (w->m.map_w))
		return (1);
	if (w->array[y][x] == 1)
		return (1);
	return (0);
}

void		draw_column(t_w *w, t_ray *ray, int x, double angle)
{
	int 	min;
	int		max;

	int 	i;
	w->half_height = (!(w->half_height % 2)) ? w->half_height : w->half_height--;
	min = w->half_height - (ray->height * 0.5);
	max = min + ray->height;
	if (max > H)
		max = H;
	i = (min < 0) ? 0 : min;
	while (i < max)
	{
		pixel_to_img(w, i, x);
		i++;
	}



}

void		draw_ray(t_w *w, t_ray *ray, double angle)
{
	t_2d	tail;
	t_2d	player;

	player.x = w->player.x;
	player.y = w->player.y;
	tail.x = (int)ray->start.x;
	tail.y = (int)ray->start.y;
	dda(w, player, tail);
}



t_ray 		*choose_ray(t_w *w, t_ray *horiz, t_ray *vert, double angle)
{
	while (!is_wall(w, horiz->start.y / 64, horiz->start.x / 64))
	{
		horiz->start.x += horiz->step.x;
		horiz->start.y += horiz->step.y;
	}
	while (!is_wall(w, vert->start.y / 64, vert->start.x / 64))
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

t_ray		*get_ray(t_w *w, double angle)
{
	t_ray	*vert;
	t_ray	*horiz;
	t_ray	*result;

	angle = angle * M_PI_180;
	horiz = init_horiz(w->player.x, w->player.y, angle);
	vert = init_vert(w->player.x, w->player.y, angle);
	result = choose_ray(w, horiz, vert, angle);

	result->dist *= cos(angle - w->angle_between_rays * M_PI_180);
//	w->view->dist_for_x[x] = result->dist;
	return (result);
}



void		calc_single_ray(t_w *w, int x, double angle)
{
	t_ray	*ray;

	ray = get_ray(w, angle);

	ray->height = TEXT_SIZE / ray->dist * w->dist_to_projection_plane;

	draw_column(w, ray, x, angle);
//	draw_ray(w, ray, angle); //adsfads
	free(ray);
}



void			process_of_wolf(t_w *w)
{
	double 	angle;
	double	one_angle;

	mlx_clear_window(w->mlx.mlx, w->mlx.win);
	mlx_destroy_image(w->mlx.mlx, w->mlx.img);
	w->mlx.img = mlx_new_image(w->mlx.mlx, W, H);
	w->mlx.data = mlx_get_data_addr(w->mlx.img,
									&w->mlx.bpp, &w->mlx.sl, &w->mlx.end);



//	print_map(w);

	angle = w->player.direction - (double)(60 * 0.5);
	one_angle = 60.0 / W;
	int x = 0;
	while (x < W)
	{
		calc_single_ray(w, x, angle);
		angle = angle + one_angle;
		x++;
	}
	mlx_put_image_to_window(w->mlx.mlx, w->mlx.win, w->mlx.img, 0, 0);
}
