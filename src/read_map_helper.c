#include "../includes/wolf.h"

int 			c_of_words(const char *str)
{
    int elem;

    elem = 0;
    while (*str)
    {
        if (*str == ' ' || *str == '1' || *str == '.')
        {
            if (*str == '1' || *str == '.')
                elem++;
        }
//        }
//        else
//            return (0);
        str++;
    }
    return (elem);
}

void             save_map(t_w *w, char *line, int y)
{
    if ((w->m.map[y] = (char *)malloc(sizeof(char) * ft_strlen(line))) == NULL)
    {
        while (y--)
            ft_strdel(&w->m.map[y]);
        alert_error(2);
    }
    w->m.map[y] = ft_strcpy(w->m.map[y], line);
}

int             create_standard(t_w *w, char *line)
{
    if (w->index == 0)
    {
        if ((w->m.elem = c_of_words(line)) == 0)
        {
            ft_strdel(&line);
            alert_error (1);
        }
        save_map(w, line, w->index);
        ft_strdel(&line);
        w->index++;
        return (1);
    }
    return (0);
}

void 			count_of_string(t_w *w, char *file)
{
    char        *line;
    int         fd;

    w->m.c_of_str = 0;
    fd = open(file, O_RDONLY);
    while (get_next_line(fd, &line))
        w->m.c_of_str++;
    close(fd);


    fd = open(file, O_RDONLY);
    if ((w->m.map = (char **) malloc(sizeof(char *) * w->m.c_of_str + 1)) == NULL)
        alert_error(2);
    w->index = 0;
    while (get_next_line(fd, &line))
    {
        printf("%s     [%d]\n",  line, w->m.c_of_str);
        if ((create_standard(w, line)))
        {
            ft_strdel(&line);
            continue;
        }
        if (w->m.elem != c_of_words(line))
        {
            ft_strdel(&line);
            alert_error(1);
        }

        save_map(w, line, w->index);
        w->index++;
        ft_strdel(&line);
    }
    w->m.map[w->index] = NULL;
    close(fd);
}