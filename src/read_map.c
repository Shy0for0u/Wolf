#include "../includes/wolf.h"

void			w_data_in_map(t_w *w, char *file)
{
    int 		fd;
    int 		index;
    char 		*line;

    index = 0;
    fd = open(file, O_RDONLY);
    while ((get_next_line(fd, &line)))
    {
        ft_strcpy(w->m.map[index], line);
        ft_strdel(&line);
        index++;
    }
    close(fd);
}

void            get_memory_for_map(t_w *w)
{
    int         index;

    index = 0;
    if (!(w->m.map = (char**)malloc(sizeof(char *) * w->m.c_of_str + 1)))
        alert_error (2);
    while (index < w->m.c_of_str)
    {
        if ((w->m.map[index] = (char*)malloc(sizeof(char) * w->m.characters + 1)) == NULL)
        {
            while (--index)
            {
                ft_strdel(&w->m.map[index]);
            }
            free(w->m.map);
            alert_error(2);
        }
        index++;
    }
    w->m.map[index] = NULL;
}

void 			validation_of_map(t_w *w, char *file)
{
    int 		fd;
    char 		buff[1];

    fd = open(file, O_RDONLY);
    if (read(fd, buff, 0) < 0 || fd < 0)
        alert_error (0);
    count_of_string(w, file);
    get_memory_for_map(w);
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
//
// Created by pavtr on 04.10.2019.
//

