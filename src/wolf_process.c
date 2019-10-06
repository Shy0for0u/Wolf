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

t_ray 			*get_ray(t_w *w, int x, double angle)
{
	t_ray		*vert;
	t_ray		*horz;
	t_ray		*result;

	angle = angle * M_PI_180;
}

void			cast_single_ray(t_w *w, int x, double angle)
{
	t_ray		*ray;

	ray = get_ray(w, x, angle);
	ray->height = BOX_SIZE / ray->dist * w->dist_to_pp;
	dda(w, );
}

void			process_of_wolf(t_w *w)
{
//	int		y;
	int 		x;
	double		angle;
	double		next_angle;

	x = 0;
	angle = w->player->direction - (double)(60 * 0.5);
	next_angle = 60.0 / W;
	while (x < W)
	{
		cast_single_ray(w, x, angle);
		angle = angle + next_angle;
		x++;
	}

//	y = 0;
//	while (y < (w->m.c_of_str + 2))
//	{
//		x = 0;
//		while (x < (w->m.elem + 2))
//		{
//			if (w->array[y][x] == 1)
//				pixel_to_img(w, y, x);
//			x++;
//		}
//		y++;
//	}
	mlx_put_image_to_window(w->mlx.mlx, w->mlx.win, w->mlx.img, W * 0.5, H * 0.5);
}
