/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 23:03:43 by dgorold-          #+#    #+#             */
/*   Updated: 2019/10/16 00:20:05 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void			player_init(t_w *w)
{
	w->player.direction = 270;
	w->player.x = -1;
	w->player.y = -1;
	w->player.turn = 5;
	w->player.speed = 5;
}

SDL_Surface     *load_surface(t_w *w, char *file)
{
    SDL_Surface *surf;
    SDL_Surface *result;

    surf = SDL_LoadBMP(file);
    if (surf != NULL && surf->w == 64 && surf->h == 64)
    {
        result = SDL_ConvertSurfaceFormat(surf, SDL_PIXELFORMAT_ARGB8888, 1);
        SDL_FreeSurface(surf);
        return (result);
    }
    else
        alert_error(3);
    return (NULL);
}

void            init_textures(t_w *w)
{
    w->texture->walls[0] = load_surface(w, WALL0);
    w->texture->walls[1] = load_surface(w, WALL1);
    w->texture->walls[2] = load_surface(w, WALL2);
    w->texture->walls[3] = load_surface(w, WALL3);
}

void            malloc_stuff(t_w *w)
{
    w->sdl = (t_sdl *)malloc(sizeof(t_sdl));
    w->texture = (t_textures *)malloc(sizeof(t_textures));
    w->texture->walls = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 4);
}

void			initialization_(t_w *w)
{
    double		fov;

    malloc_stuff(w);
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        alert_error(3);
    w->sdl->window = SDL_CreateWindow(T, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, 0);
    w->sdl->surface = SDL_GetWindowSurface(w->sdl->window);
    init_textures(w);
    w->m.map_h = w->m.map_h + 2;
    w->m.map_w = w->m.map_w + 2;
    fov = (M_PI / 6.0);
    w->sdl->keyboard = SDL_GetKeyboardState(NULL);
    w->half_width = (int)(W * 0.5);
    w->half_height = (int)(H * 0.5);
    w->dist_to_projection_plane = (int)((double)w->half_width / tan(fov));
}
