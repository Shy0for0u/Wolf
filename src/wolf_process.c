#include <math.h>
#include "../includes/wolf.h"

int    out_of_border(int x, int y)
{
    if (x < 0 || x > W - 1)
        return (1);
    if (y < 0 || y > H - 1)
        return (1);
    return (0);
}

t_color			get_color2(t_w *w, int y, int x)
{
    int        offset;
    unsigned char  *pixels;
    t_color     c;

    c.r = (char)255;
    c.g = (char)255;
    c.b = (char)255;

    offset = 4 * (y * w->sdl->surface->w + x);
    pixels = (unsigned char*)w->sdl->surface->pixels;
    pixels[offset] = c.b;
    pixels[offset + 1] = c.g;
    pixels[offset + 2] = c.r;
    return (c);
}

void			pixel_to_img(t_w *w, int y, int x, t_color c)
{
    int        offset;
    unsigned char  *pixels;

    if (out_of_border(x, y))
        return ;
    offset = 4 * (y * w->sdl->surface->w + x);
    pixels = (unsigned char*)w->sdl->surface->pixels;
    pixels[offset] = c.b;
    pixels[offset + 1] = c.g;
    pixels[offset + 2] = c.r;
}

//void  set_pixel(SDL_Surface *surface, int x, int y, t_color c)
//{
//    int        offset;
//    unsigned char  *pixels;
//
//    if (out_of_border(x, y))
//        return ;
//    offset = 4 * (y * surface->w + x);
//    pixels = (unsigned char*)surface->pixels;
//    pixels[offset] = c.b;
//    pixels[offset + 1] = c.g;
//    pixels[offset + 2] = c.r;
//}

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

//void			print_map(t_w *w)w
//{
//	int y = 0;
//	while (y < w->m.map_h)
//	{
//		int x = 0;
//		while (x < w->m.map_w)
//		{
//			if (w->array[y][x] == 1)
//				print_squire(w, y, x);
//			if (w->array[y][x] == 2)
//				pixel_to_img(w, y, x);
//			x++;
//		}
//		y++;
//	}
//}

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
    double  ratio;
	int 	i;
	t_color color;

	ratio = TEXT_SIZE / ray->height;
	color.r = (char)150;
	color.g = (char)150;
	color.b = (char)150;
	w->half_height = (!(w->half_height % 2)) ? w->half_height : w->half_height--; // ?
	min = w->half_height - (ray->height * 0.5);
	max = min + ray->height;
	if (max > H)
		max = H;
	i = (min < 0) ? 0 : min;
	while (i < max)
	{
	    color = get_color2(w, (i - min) * ratio, x);
		pixel_to_img(w, i, x, color);
		i++;
	}
}

void		draw_ray(t_w *w, t_ray *ray, double angle)
{
	t_2d	tail;
	t_2d	player;

	player.x = w->player.x;
	player.y = w->player.y;
	tail.x = ray->start.x;
	tail.y = ray->start.y;
	dda(w, player, tail);
}



t_ray 		*choose_ray(t_w *w, t_ray *horiz, t_ray *vert, double angle)
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

void        calc_wall_data(t_w *w, t_ray *result)
{
    if (result->type == HORIZ_TYPE)
        result->offset = (int)(result->start.x) % TEXT_SIZE;
    else
        result->offset = (int)(result->start.y) % TEXT_SIZE;
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
    calc_wall_data(w, result);
	result->dist *= cos(angle - w->player.direction * M_PI_180);
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

//	print_map(w);

	angle = (w->player.direction - (double)(60 * 0.5));
	one_angle = (60.0 / W); // * M_PI_180;
	int x = 0;
	while (x < W)
	{
		calc_single_ray(w, x, angle);
		angle = angle + one_angle;
		x++;
	}
}
