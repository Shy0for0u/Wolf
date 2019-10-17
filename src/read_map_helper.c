/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 20:39:15 by dgorold-          #+#    #+#             */
/*   Updated: 2019/10/17 21:57:40 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

static int		c_of_words(t_w *w, const char *str)
{
	int			elem;
	int			x;

	elem = 0;
	x = 0;
	while (str[x])
	{
		if (str[x] == ' ' || str[x] == '1' || str[x] == '.' || str[x] == '2')
		{
			if (str[x] == '1' || str[x] == '.' || str[x] == '2')
				elem++;
			if (str[x] == '2')
				w->player.players++;
		}
		else
			alert_error(w, 1);
		if (str[x] == '2' && w->player.players > 1)
			alert_error(w, 4);
		x++;
	}
	return (elem);
}

static void		save_map(t_w *w, char *line, int y)
{
	if ((w->m.map[y] = (char *)malloc(sizeof(char) * ft_strlen(line))) == NULL)
	{
		while (y--)
			ft_strdel(&w->m.map[y]);
		alert_error(w, 2);
	}
	w->m.map[y] = ft_strcpy(w->m.map[y], line);
}

static int		create_standard(t_w *w, char *line)
{
	if (w->m.index == 0)
	{
		if ((w->m.map_w = c_of_words(w, line)) == 0)
		{
			ft_strdel(&line);
			alert_error(w, 1);
		}
		save_map(w, line, w->m.index);
		w->m.index++;
		return (1);
	}
	return (0);
}

void			write_data_in_map(t_w *w, char *file, int fd)
{
	char		*line;

	fd = open(file, O_RDONLY);
	if ((w->m.map = (char **)malloc(sizeof(char *) * (w->m.map_h) + 1)) == NULL)
		alert_error(w, 2);
	w->m.index = 0;
	while (get_next_line(fd, &line))
	{
		if ((create_standard(w, line)))
		{
			ft_strdel(&line);
			continue;
		}
		if (w->m.map_w != c_of_words(w, line))
		{
			ft_strdel(&line);
			alert_error(w, 1);
		}
		save_map(w, line, w->m.index);
		w->m.index++;
		ft_strdel(&line);
	}
	w->m.map[w->m.index] = NULL;
}

void			count_of_string(t_w *w, char *file)
{
	char		*line;
	int			fd;

	w->m.map_h = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		w->m.map_h++;
		ft_strdel(&line);
	}
	close(fd);
	fd = open(file, O_RDONLY);
	write_data_in_map(w, file, fd);
	close(fd);
	if (w->m.map_h < 3 || w->m.map_w < 3 || w->player.players != 1)
		alert_error(w, 1);
}
