#include "../includes/wolf.h"

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

int             create_standard(t_w *w, char *line)
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
        return (1) ;
    }
    return (0);
}

void 			count_of_string(t_w *w, char *file)
{
    char		*line;
    int 		fd;

    w->m.c_of_str = 0;
    fd = open(file, O_RDONLY);
    while (get_next_line(fd, &line))
    {
        if (create_standard(w, line))
            continue ;
        if (w->m.characters != c_of_words(line))
        {
            ft_strdel(&line);
            alert_error (1);
        }
        w->m.c_of_str++;
        ft_strdel(&line);
    }
    close(fd);
}
//
// Created by pavtr on 04.10.2019.
//

