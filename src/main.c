#include <stdio.h>
#include "../includes/wolf.h"

void			alert_error(int key)
{
	if (key == 0)
	{
		write(1, "bad fd or file\n", 15);
		exit(0);
	}
	if (key == 1)
	{
		write(1, "non valid characters\n", 21);
		exit(0);
	}
	if (key == 2)
	{
		write(1, "memory not allocated\n", 21);
		exit(0);
	}
}

int 			c_of_words(const char *str)
{
	int 		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && ((str[i + 1]) == ' ' || str[i + 1] == '\0'))
		{
			if (str[i] != '1')
				return (0);
		}
		i++;
	}
	return (i);
}

void 			count_of_string(t_w *w, char *file)
{
	char		*line;
	int 		fd;

	w->m.c_of_str = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (w->m.c_of_str == 0)
		{
			if ((w->m.characters = c_of_words(line)) == 0)
			{
				ft_strdel(&line);
				alert_error (1);
			}
			w->m.c_of_str++;
			ft_strdel(&line);
			continue ;
		}
		if (w->m.characters != c_of_words(line))
		{
			ft_strdel(&line);
			alert_error (1);
		}
		ft_strdel(&line);
	}
	close(fd);
}

void			w_data_in_map(t_w *w, char *file)
{
	int 		fd;
	int 		i;
//	char 		*line;

	i = 0;
	fd = open(file, O_RDONLY);
	while ((get_next_line(fd, &w->m.map[i])))
	{
		ft_strcpy(w->m.map[i], line);
		ft_strdel(&line);
		i++;
	}
	w->m.map[i] = NULL;
	close(fd);
}

void 			validation_of_map(t_w *w, char *file)
{
	int 		fd;
	char 		buff[1];

	fd = open(file, O_RDONLY);
	if (read(fd, buff, 0) < 0 || fd < 0)
		alert_error (0);
	count_of_string(w, file);
	if (!(w->m.map = (char**)malloc(sizeof(char *) * w->m.c_of_str + 1)))
		alert_error (2);
	
	w_data_in_map(w, file);
}

int 			read_map(t_w *w, char *file)
{
	int 		i = 0;
	validation_of_map(w, file);
	while (w->m.map[i])
	{
		printf("%s\n", w->m.map[i]);
		i++;
	}
	return (0);
}

int				main(int argc, char *argv[])
{
	t_w			wolf;

	if (argc == 2)
	{
		read_map(&wolf, argv[1]);
	}
	return 0;
}