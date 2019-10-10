#include "../includes/wolf.h"

void            print_map_int(t_w *w)
{
    int         y;
    int         x;

    y = 0;
    printf("\n");
    while (y < w->m.map_h + 2)
    {
        x = 0;
        while (x < w->m.map_w + 2)
        {
            printf("%d ", w->array[y][x]);
            x++;
        }
        printf("\n");
        y++;
    }
}

void            map_around(t_w *w)
{
    int         x;
    int         y;

    y = 0;
    x = 0;
    while (x < (w->m.map_w + 2))
    {
        w->array[0][x] = 1;
        w->array[w->m.map_h + 1][x] = 1;
        x++;
    }
    while (y < (w->m.map_h + 2))
    {
        w->array[y][0] = 1;
        w->array[y][w->m.map_w + 1] = 1;
        y++;
    }
}

void			w_data_in_map(t_w *w) // it is no end
{
    int 		y;
    int         x;
    char        **array_c;

    y = 0;
    map_around(w);
    while (w->m.map[y])
    {
        array_c = ft_strsplit(w->m.map[y], ' ');
        x = 0;
        while (array_c[x])
        {
            if (array_c[x][0] == '1')   // ft_itoa.c
                w->array[y + 1][x + 1] = 1;
            else if (array_c[x][0] == '2')
			{
            	w->array[y + 1][x + 1] = 2;
            	w->player.x = ((x + 1) * 64 + 32);
            	w->player.y = ((w->m.index - 1) * 64 + 32);
//				w->player.x = (BOX_SIZE * (x + 1)) / 32;
//				w->player.y = (BOX_SIZE  * ((w->m.index - 1))) / 32;
			}
            else if (array_c[x][0] == '.')
                w->array[y + 1][x + 1] = 0;
            x++;
        }
		// delete memory
        y++;
    }
	print_map_int(w);
}

void            get_memory_for_map(t_w *w)
{
	int         i;

	i = 0;

	if ((w->array = (int **)malloc(sizeof(int *) * (w->m.map_h + 2))) == NULL)
		alert_error(2);
	while (i < (w->m.map_h + 2))
	{
		if ((w->array[i] = (int *)malloc(sizeof(int) * (w->m.map_w + 2))) == NULL)
		{
			while (--i)
			{
				ft_memdel((void *)&w->array[i]);
			}
			alert_error(2);
		}
		i++;
	}
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
    w_data_in_map(w);
}

int 			read_map(t_w *w, char *file)
{
    int 		i = 0;
    validation_of_map(w, file);
//    print_map_int(w);    // delete

    printf("\nmap data \n");
    while (w->m.map[i])
    {
        printf("%s\n", w->m.map[i]);
        i++;
    }
    return (0);
}
