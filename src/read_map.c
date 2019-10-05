#include "../includes/wolf.h"

void            print_map_int(t_w *w)
{
    int         y;
    int         x;

    y = 0;
    printf("\n");
    while (y < w->m.c_of_str + 2)
    {
        x = 0;
        while (x < w->m.elem + 2)
        {
            printf("%d ", w->p[y][x].val);
            x++;
        }
        printf("\n");
        y++;
    }
}

void			w_data_in_map2(t_w *w, char *file)
{
    int 		fd;
    int 		index;
    char 		*line;

    index = 0;
    fd = open(file, O_RDONLY);
    while ((get_next_line(fd, &line)))
    {
        ft_strdel(&line);
        index++;
    }
    close(fd);
}

void            map_around(t_w *w)
{
    int         x;
    int         y;

    y = 0;
    x = 0;
    while (x < w->m.elem + 1)
    {
        w->p[0][x].val = 1;
        w->p[w->m.c_of_str + 1][x].val = 1;
        x++;
    }
    while (y < w->m.c_of_str + 2)
    {
        w->p[y][0].val = 1;
        w->p[y][w->m.elem + 1].val = 1;
        y++;
    }
}

void			w_data_in_map(t_w *w)
{
    int 		y;
    int         x;
    char        **array;

    y = 0;
    map_around(w);
    while (w->m.map[y])
    {
        array = ft_strsplit(w->m.map[y], ' ');
        x = 0;
        while (array[x])
        {
            if (array[x][0] == '1')
                w->p[y + 1][x + 1].val = 1;
            else if (array[x][0] == '.')
                w->p[y + 1][x + 1].val = 0;
            x++;
        }

        y++;
    }
}

void            get_memory_for_map(t_w *w)
{
    int         i;

    i = 0;
    if ((w->p = (t_p **)malloc(sizeof(t_p *) * w->m.c_of_str + 3)) == NULL)
        alert_error(2);
    while (i < w->m.c_of_str + 2)
    {
        if ((w->p[i] = (t_p *)malloc(sizeof(t_p) * w->m.elem + 2)) == NULL)
        {
            while (--i)
            {
                ft_memdel((void *)&w->p[i]);
            }
            alert_error(2);
        }
        i++;
    }
    w->p[i] = NULL;
}

//void            get_memory_for_map2(t_w *w)
//{
//    int         index;
//
//    index = 0;
//    if (!(w->m.map = (char**)malloc(sizeof(char *) * w->m.c_of_str + 1)))
//        alert_error (2);
//    while (index < w->m.c_of_str)
//    {
//        if ((w->m.map[index] = (char*)malloc(sizeof(char) * w->m.elem + 1)) == NULL)
//        {
//            while (--index)
//            {
//                ft_strdel(&w->m.map[index]);
//            }
//            free(w->m.map);
//            alert_error(2);
//        }
//        index++;
//    }
//    w->m.map[index] = NULL;
//}

void 			validation_of_map(t_w *w, char *file)
{
//    int 		fd;
//    char 		buff[1];

//    fd = open(file, O_RDONLY);
//    if (read(fd, buff, 0) < 0 || fd < 0)
//        alert_error (0);
    count_of_string(w, file);
    get_memory_for_map(w);
    w_data_in_map(w);
}

int 			read_map(t_w *w, char *file)
{
    int 		i = 0;
    validation_of_map(w, file);
    print_map_int(w);    // delete

    printf("\nmap data \n");
    while (w->m.map[i])
    {
        printf("%s\n", w->m.map[i]);
        i++;
    }
    return (0);
}
