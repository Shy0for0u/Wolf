#include "../includes/wolf.h"

void			alert_error(int key)
{
	if (key == 0)
	{
		write(2, "bad fd or file\n", 15);
		exit(0);
	}
	if (key == 1)
	{
		write(2, "non valid map_w\n", 15);
		exit(0);
	}
	if (key == 2)
	{
		write(2, "memory not allocated\n", 21);
		exit(0);
	}
	if (key == 3)
    {
        write(2, "SDL drop\n", 9);
        exit(0);
    }
}

void                print_layer(t_w *w, int start, int part, int color)
{
    unsigned char   *pixels;
    int             x;

    pixels = w->sdl->surface->pixels;
    while (start < part)
    {
        x = 0;
        while (x++ < W)
        {
            int index = x * 4 + w->sdl->surface->w * start * 4;
            pixels[index] = (color >> 16);
            pixels[index + 1] = (color >> 8);
            pixels[index + 2] = (color);
        }
        start++;
    }
}

int				    main(int argc, char *argv[])
{
	t_w			    *wolf;

	wolf = (t_w*)malloc(sizeof(t_w));
	if (argc == 2)
	{
        player_init(wolf);
        read_map(wolf, argv[1]);
        initialization_(wolf);
	    while (!check_for_quit(&wolf->sdl->event, wolf->sdl))
        {
            ft_memset(wolf->sdl->surface->pixels, 0, W * H * 4);
            print_layer(wolf, 0, H * 0.5, 0x0c2c56);
            print_layer(wolf, H * 0.5, H, 0x000000);
	        SDL_PollEvent(&wolf->sdl->event);
	        keyboard_input(wolf);
            process_of_wolf(wolf);
            SDL_UpdateWindowSurface(wolf->sdl->window);
        }
	}
	return 0;
}