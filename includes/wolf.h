/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 20:22:36 by dgorold-          #+#    #+#             */
/*   Updated: 2019/10/17 20:52:29 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLFV1_WOLF_H
#define WOLFV1_WOLF_H

#include "../libft/includes/libft.h"
#include <stdlib.h>
#include <SDL.h>
#include "pthread.h"
#include "math.h"

# define WALL0      "./walls/1_0.bmp"
# define WALL1      "./walls/1_3.bmp"
# define WALL2      "./walls/3_3.bmp"
# define WALL3      "./walls/3_0.bmp"
# define T			"Wolf"
# define W			1200
# define H			1000

# define TEXT_SIZE	64
# define M_PI_180	0.017453292519943295
# define HORIZ_TYPE 1
# define VERT_TYPE  0
# define SDL_ATR	T, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, 0

typedef struct      s_iter
{
    int             max;
    int             min;
    int             y;
}                   t_iter;

typedef struct		s_point
{
    double 			x;
    double			y;
}					t_point;

typedef struct		s_m
{
	int             index;
	int 			map_w;
	int 			map_h;
	char			**map;
}					t_m;

typedef struct      s_color
{
    char            r;
    char            g;
    char            b;
}                   t_color;

typedef struct      s_textures
{
    SDL_Surface     **walls;
}                   t_textures;

typedef struct		s_ray
{
    SDL_Surface     *texture;
	int 			offset;
	t_point			start;
	t_point			step;
    double 			height;
	double 			dist;
	int 			type;
}					t_ray;

typedef struct		s_player
{
    int             players;
    double          turn;
    double          speed;
	double 			direction;
	int 			x;
	int 			y;
}					t_pl;

typedef struct      s_sdl
{
    const Uint8     *keyboard;
    SDL_Event		event;
    SDL_Surface     *surface;
    SDL_Window      *window;
}                   t_sdl;

typedef struct		s_w
{
    t_sdl           *sdl;
    t_textures      *texture;
    t_m				m;
    t_pl			player;
	int				half_height;
	int				half_width;
	int 			dist_to_projection_plane;
	int 			**array;
}					t_w;

int		            check_for_quit(SDL_Event *event, t_w *w);
void                keyboard_input(t_w *w);
void		    	alert_error(t_w *w, int key);
void 			    read_map(t_w *w, char *file);
//int 		    	c_of_words(t_w *w, const char *str);
//int                 create_standard(t_w *w, char *line);
void 			    count_of_string(t_w *w, char *file);
void				process_of_wolf(t_w *w);
t_ray		        *init_vert(int x, int y, double angle);
t_ray		        *init_horiz(int x, int y, double angle);
void				player_init(t_w *w);

void                malloc_stuff(t_w *w);
void			    initialization_(t_w *w);
void                init_textures(t_w *w);
SDL_Surface         *load_surface(t_w *w, char *file);

void                draw_column(t_w *w, t_ray *ray, int x);
void                print_layer(t_w *w, int start, int part, int color);

void                calc_wall_data(t_w *w, t_ray *result, double angle);
int 			    is_wall(t_w *w, int y, int x);

void                del_array(void **array);

#endif
