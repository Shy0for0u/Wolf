/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 20:22:36 by dgorold-          #+#    #+#             */
/*   Updated: 2019/10/11 01:06:40 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLFV1_WOLF_H
#define WOLFV1_WOLF_H

#include "../libft/includes/libft.h"
#include <stdlib.h>
#include <SDL_surface.h>
#include "pthread.h"
#include "mlx.h"
#include "math.h"
#include "../sdl2/win32/include/SDL2/begin_code.h"
#include "../sdl2/win32/include/SDL2/close_code.h"

# define T			"Wolf"
# define W			1200
# define H			1000

# define TEXT_SIZE	64
# define M_PI_180	0.017453292519943295

typedef struct	s_2d
{
	double		x;
	double		y;
	int			color;

}				t_2d;

typedef struct		s_mlx
{
	int 			sl;
	int 			bpp;
	int				end;
	char 			*data;
	void			*mlx;
	void			*img;
	void			*win;
}					t_mlx;

typedef struct		s_point
{
	double 			x;
	double			y;
}					t_point;

//typedef struct		s_view
//{
//	double			*dist_for_x;
//}					t_view;

typedef struct		s_m
{
	int             index;
	int 			map_w;
	int 			map_h;
	char			**map;
}					t_m;

typedef struct		s_ray
{
	int 			offset;
	t_point			start;
	t_point			step;
	int 			height;
	double 			dist;
	int 			type;
}					t_ray;

typedef struct		s_player
{
	double 			angle;
	double 			direction;
	int				max_dist;
	double 			fov;
	int 			x;
	int 			y;
}					t_pl;

typedef struct		s_w
{
	t_2d			p;
	t_ray			**ray_tmp;
	double 			projection_plane;
	double 			angle_between_rays;
	char 			*image_data;
	int				half_height;
	int				half_width;
	int 			dist_to_projection_plane;
	t_pl			player;
	t_mlx			mlx;
	int 			**array;
	t_m				m;
//	t_view			*view;
}					t_w;

void            print_map_int(t_w *w);

void		    	alert_error(int key);
int 			    read_map(t_w *w, char *file);
int 		    	c_of_words(t_w *w, const char *str);
int                 create_standard(t_w *w, char *line);
void 			    count_of_string(t_w *w, char *file);
void			dda2(t_w *w, t_2d pnt1, t_2d pnt2);
void				hooks(t_w *w);
void				process_of_wolf(t_w *w);
t_ray		*init_vert(int x, int y, double angle);
t_ray		*init_horiz(int x, int y, double angle);
void				player_init(t_w *w);
void			dda(t_w *w, t_2d pnt1, t_2d pnt2);
void		calc(t_w *w);

#endif
