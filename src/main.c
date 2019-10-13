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

SDL_Surface     *load_surface(t_w *w, char *file)
{
    SDL_Surface *surf;

    surf = SDL_LoadBMP(file);
    if (surf != NULL && surf->w == 64 && surf->h == 64)
        return (surf);
    else
    {
        w->error = 4;
        return (NULL);
    }
}

void            init_textures(t_w *w)
{
    int         height;
    int         width;

    w->texture->walls[0] = load_surface(w, WALL0);
    w->texture->walls[1] = load_surface(w, WALL1);
    w->texture->walls[2] = load_surface(w, WALL2);
    w->texture->walls[3] = load_surface(w, WALL3);
//    w->wall[0] = mlx_xpm_file_to_image(w->mlx.mlx, WALL0, &width, &height);
//    w->wall[1] = mlx_xpm_file_to_image(w->mlx.mlx, WALL1, &width, &height);
//    void        **ptr_texture;
//
//    ptr_texture = (void **)malloc(sizeof(void *) * 2);
//    ptr_texture[0] = mlx_xpm_file_to_image(w->mlx.mlx, WALL0, &width, &height);
//    ptr_texture[1] = mlx_xpm_file_to_image(w->mlx.mlx, WALL1, &width, &height);
//
//    w->text_data = (int **)malloc(sizeof(int *) * 2);
//
//    int     i = 0;
//    while (i < 2)
//    {
//        w->text_data[i] = (int *)mlx_get_data_addr(w->mlx.mlx, &w->mlx.bpp, &w->mlx.sl, &w->mlx.end);
//        i++;
//    }
}

void            malloc_stuff(t_w *w)
{

    w->error = 0;
    w->sdl = (t_sdl *)malloc(sizeof(t_sdl));
    w->texture = (t_textures *)malloc(sizeof(t_textures));
    w->texture->walls = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 4);
    w->inputs = (t_inputs *)malloc(sizeof(t_inputs));
}

void			initialization_(t_w *w)
{
	double		fov;

	malloc_stuff(w);
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        alert_error(3);
    w->sdl->window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, 0);
    w->sdl->renderer = SDL_CreateRenderer(w->sdl->window, -1, SDL_RENDERER_SOFTWARE);
    w->sdl->texture = SDL_CreateTexture(w->sdl->renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STATIC, W, H);
    init_textures(w);
    w->sdl->pixels = (Uint32 *)malloc(sizeof(Uint32) * W * H);

	w->draw_dist = 800;
	w->m.map_h = w->m.map_h + 2;
	w->m.map_w = w->m.map_w + 2;
	fov = (M_PI / 6.0);
	w->mlx.mlx = mlx_init();
	w->mlx.win = mlx_new_window(w->mlx.mlx, W, H, T);
	w->mlx.img = mlx_new_image(w->mlx.mlx, W, H);
	w->mlx.data = mlx_get_data_addr(w->mlx.img,
			&w->mlx.bpp, &w->mlx.sl, &w->mlx.end);
	w->half_width = (int)(W * 0.5);
	w->half_height = (int)(H * 0.5);
	w->dist_to_projection_plane = (int)((double)w->half_width / tan(fov));
	w->angle_between_rays = fov / W;
	init_textures(w);
}

int		check_for_quit(SDL_Event *event, t_inputs *inputs)
{
    if (event->type == SDL_QUIT)
        return (1);
    if (inputs->keyboard[SDL_SCANCODE_ESCAPE])
        return (1);
    return (0);
}

int             is_move_input(const Uint8 *key)
{
    if (key[SDL_SCANCODE_W] || key[SDL_SCANCODE_UP])
        return (1);
    if (key[SDL_SCANCODE_A] || key[SDL_SCANCODE_LEFT])
        return (1);
    if (key[SDL_SCANCODE_S] || key[SDL_SCANCODE_DOWN])
        return (1);
    if (key[SDL_SCANCODE_D] || key[SDL_SCANCODE_RIGHT])
        return (1);
    return (0);
}

void            keyboard_input(t_w *w)
{
    const Uint8 *key;

    key = w->inputs->keyboard;
    if (is_move_input(key) && w->player.speed < 3.5)
        w->player.speed += 0.8;
    else if (!is_move_input(key) && w->player.speed > 0)
        w->player.speed -= 1.5;
}

int				main(int argc, char *argv[])
{
	t_w			*wolf;

	wolf = (t_w*)malloc(sizeof(t_w));
	if (argc == 2)
	{
        player_init(wolf);
        read_map(wolf, argv[1]);
        initialization_(wolf);
	    while (1)
        {
	        SDL_PollEvent(&wolf->sdl->event);
	        if (check_for_quit(&wolf->sdl->event, wolf->inputs))
                break ;
	        wolf->inputs->keyboard = SDL_GetKeyboardState(NULL);
	        keyboard_input(wolf);
            process_of_wolf(wolf);
            SDL_RenderPresent(wolf->sdl->renderer);
//            hooks(wolf);
        }
//        mlx_loop(wolf->mlx.mlx);
	}
	return 0;
}