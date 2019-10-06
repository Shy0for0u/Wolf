/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 20:22:36 by dgorold-          #+#    #+#             */
/*   Updated: 2019/10/06 20:43:54 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLFV1_WOLF_H
#define WOLFV1_WOLF_H

#include "../libft/includes/libft.h"
#include <stdlib.h>
#include "pthread.h"
#include "mlx.h"
#include "math.h"
#include "../sdl2/win32/include/SDL2/begin_code.h"
#include "../sdl2/win32/include/SDL2/close_code.h"

# define T			"Wolf"
# define H			200
# define W			320
# define BOX_SIZE	64
# define M_PI_180	0.017453292519943295

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
	float 			x;
	float			y;
}					t_point;

typedef struct		s_m
{
	int             index;
	int 			elem;
	int 			c_of_str;
	char			**map;
}					t_m;

typedef struct		s_ray
{
	t_point			start;
	t_point			step;
	int 			height;
	float 			dist;
	int 			type;
}					t_ray;

typedef struct		s_player
{
	double 			direction;
	int				max_dist;
	int 			p_x;
	int 			p_y;
}					t_pl;

typedef struct		s_w
{
	int				half_height;
	int				half_width;
	int 			dist_to_pp;
	t_pl			*player;
	t_mlx			mlx;
	int 			**array;
	t_m				m;
}					t_w;

void		    	alert_error(int key);
int 			    read_map(t_w *w, char *file);
int 		    	c_of_words(t_w *w, const char *str);
int                 create_standard(t_w *w, char *line);
void 			    count_of_string(t_w *w, char *file);

void				hooks(t_w *w);
void				process_of_wolf(t_w *w);

void				player_init(t_w *w, t_pl *player);
void				dda(t_w *w, t_pl *pnt1, t_pl *pnt2);

#endif
