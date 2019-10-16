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

t_color			get_color2(SDL_Surface *texture, int y, int x)
{
    int        offset;
    unsigned char  *pixels;
    t_color     c;

    offset = 4 * (y * 64 + x);
    pixels = (unsigned char *)texture->pixels;
    c.r = (char)pixels[offset + 2];
    c.g = (char)pixels[offset + 1];
    c.b = (char)pixels[offset];

    return (c);
}

void      pixel_to_img(SDL_Surface *screen, int y, int x, t_color c)
{
    int        offset;
    unsigned char  *pixels;

    if (out_of_border(x, y))
        return ;
    offset = 4 * (y * screen->w + x);
    pixels = (unsigned char*)screen->pixels;
    pixels[offset] = c.b;
    pixels[offset + 1] = c.g;
    pixels[offset + 2] = c.r;
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

void		draw_column(t_w *w, t_ray *ray, int x)
{
    int   min;
    int    max;
    double  ratio;
    int   y;
    t_color color;

    ratio = TEXT_SIZE / ray->height;
    min = w->half_height - (ray->height * 0.5);
    max = min + ray->height;
    if (max > H)
        max = H;
    y = (min < 0) ? 0 : min;
    while (y < max)
    {
        color = get_color2(ray->texture, (y - min) * ratio, ray->offset);
        pixel_to_img(w->sdl->surface, y, x, color);
        y++;
    }
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

void        calc_wall_data(t_w *w, t_ray *result, double angle)
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

t_ray		*get_ray(t_w *w, double angle)
{
	t_ray	*vert;
	t_ray	*horiz;
	t_ray	*result;

	angle = angle * M_PI_180;
	horiz = init_horiz(w->player.x, w->player.y, angle);
	vert = init_vert(w->player.x, w->player.y, angle);
	result = choose_ray(w, horiz, vert, angle);
    calc_wall_data(w, result, angle);
	result->dist *= cos(angle - w->player.direction * M_PI_180);
	return (result);
}



void		calc_single_ray(t_w *w, int x, double angle)
{
	t_ray	*ray;

	ray = get_ray(w, angle);
	ray->height = TEXT_SIZE / ray->dist * w->dist_to_projection_plane;
	draw_column(w, ray, x);
	free(ray);
}

void			process_of_wolf(t_w *w)
{
	double 	angle;
	double	one_angle;
    int     x;

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
