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
    if ((w->m.map[w->m.c_of_str] = (char *)malloc(sizeof(char) * w->m.elem + 1)) == NULL)
    {
        while (y--)
            ft_strdel(&w->m.map[y]);
        alert_error(2);
    }
    w->m.map[y] = ft_strcpy(w->m.map[y], line);
}

int             create_standard(t_w *w, char *line)
{
    if (w->m.c_of_str == 0)
    {
        if ((w->m.elem = c_of_words(line)) == 0)
        {
            ft_strdel(&line);
            alert_error (1);
        }
        save_map(w, line, w->m.c_of_str);
        w->m.c_of_str++;
        return (1);
    }
    return (0);
}

void 			count_of_string(t_w *w, char *file)
{
    char *line;
    int fd;

    w->m.c_of_str = 0;
    fd = open(file, O_RDONLY);
    if ((w->m.map = (char **) malloc(sizeof(char *) * w->m.c_of_str + 1)) == NULL)
        alert_error(2);
    while (get_next_line(fd, &line))
    {
        printf("%s     [%d]\n",  line, w->m.c_of_str);
        if (create_standard(w, line))
        {
            ft_strdel(&line);
            continue;
        }
        if (w->m.elem != c_of_words(line))
        {
            ft_strdel(&line);
            alert_error(1);
        }
        save_map(w, line, w->m.c_of_str);
        w->m.c_of_str++;
        ft_strdel(&line);
    }
    w->m.map[w->m.c_of_str] = NULL;
    close(fd);
}