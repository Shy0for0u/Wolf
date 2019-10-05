/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 20:22:36 by dgorold-          #+#    #+#             */
/*   Updated: 2019/10/02 23:48:08 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLFV1_WOLF_H
#define WOLFV1_WOLF_H

#include "../libft/includes/libft.h"
#include <stdlib.h>
#include "pthread.h"
#include "../sdl2/win32/include/SDL2/begin_code.h"
#include "../sdl2/win32/include/SDL2/close_code.h"

typedef struct		s_m
{
    int             size_str;
	int 			elem;
	int 			c_of_str;
	char			**map;

}					t_m;

typedef struct      s_p
{
    int             val;
}                   t_p;

typedef struct		s_w
{
    int             index;
    t_p             **p;
	t_m				m;
}					t_w;

void		    	alert_error(int key);
int 			    read_map(t_w *w, char *file);
int 		    	c_of_words(const char *str);
int                 create_standard(t_w *w, char *line);
void 			    count_of_string(t_w *w, char *file);

#endif //WOLFV1_WOLF_H
