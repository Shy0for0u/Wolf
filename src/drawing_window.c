/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:45:05 by dgorold-          #+#    #+#             */
/*   Updated: 2019/10/17 22:41:02 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void				print_layer(t_w *w, int start, int part, int color)
{
	unsigned char	*pixels;
	int				x;
	int				index;

	pixels = w->sdl->surface->pixels;
	while (start < part)
	{
		x = 0;
		while (x++ < W)
		{
			index = x * 4 + w->sdl->surface->w * start * 4;
			pixels[index] = (color >> 16);
			pixels[index + 1] = (color >> 8);
			pixels[index + 2] = (color);
		}
		start++;
	}
}

static int			out_of_border(int x, int y)
{
	if (x < 0 || x > W - 1)
		return (1);
	if (y < 0 || y > H - 1)
		return (1);
	return (0);
}

static t_color		get_color(SDL_Surface *texture, int y, int x)
{
	int				offset;
	unsigned char	*pixels;
	t_color			c;

	offset = 4 * (y * 64 + x);
	pixels = (unsigned char *)texture->pixels;
	c.r = (char)pixels[offset + 2];
	c.g = (char)pixels[offset + 1];
	c.b = (char)pixels[offset];
	return (c);
}

static void			pixel_to_img(SDL_Surface *screen, int y, int x, t_color c)
{
	int				offset;
	unsigned char	*pixels;

	if (out_of_border(x, y))
		return ;
	offset = 4 * (y * screen->w + x);
	pixels = (unsigned char*)screen->pixels;
	pixels[offset] = c.b;
	pixels[offset + 1] = c.g;
	pixels[offset + 2] = c.r;
}

void				draw_column(t_w *w, t_ray *ray, int x)
{
	t_iter			i;
	t_color			color;
	double			ratio;

	ratio = TEXT_SIZE / ray->height;
	i.min = w->half_height - (ray->height * 0.5);
	i.max = i.min + ray->height;
	if (i.max > H)
		i.max = H;
	i.y = (i.min < 0) ? 0 : i.min;
	while (i.y < i.max)
	{
		color = get_color(ray->texture, (i.y - i.min) * ratio, ray->offset);
		pixel_to_img(w->sdl->surface, i.y, x, color);
		i.y++;
	}
}
