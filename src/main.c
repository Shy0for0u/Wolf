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
    SDL_Surface *result;

    surf = SDL_LoadBMP(file);
    if (surf != NULL && surf->w == 64 && surf->h == 64)
    {
        result = SDL_ConvertSurfaceFormat(surf, SDL_PIXELFORMAT_ARGB8888, 1);
        SDL_FreeSurface(surf);
        return (result);
    }
    else
    {
        w->error = 4;
        return (NULL);
    }
}

void            init_textures(t_w *w)
{
    w->texture->walls[0] = load_surface(w, WALL0);
    w->texture->walls[1] = load_surface(w, WALL1);
    w->texture->walls[2] = load_surface(w, WALL2);
    w->texture->walls[3] = load_surface(w, WALL3);
}

void            malloc_stuff(t_w *w)
{
    w->error = 0;
    w->sdl = (t_sdl *)malloc(sizeof(t_sdl));
    w->texture = (t_textures *)malloc(sizeof(t_textures));
    w->texture->walls = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 4);
}

void			initialization_(t_w *w)
{
	double		fov;

	malloc_stuff(w);
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        alert_error(3);
    w->sdl->window = SDL_CreateWindow(T, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, 0);
    w->sdl->surface = SDL_GetWindowSurface(w->sdl->window);
    init_textures(w);
	w->m.map_h = w->m.map_h + 2;
	w->m.map_w = w->m.map_w + 2;
	fov = (M_PI / 6.0);
    w->sdl->keyboard = SDL_GetKeyboardState(NULL);
	w->half_width = (int)(W * 0.5);
	w->half_height = (int)(H * 0.5);
	w->dist_to_projection_plane = (int)((double)w->half_width / tan(fov));
	init_textures(w);
}

int		check_for_quit(SDL_Event *event, t_sdl *sdl)
{
    if (event->type == SDL_QUIT)
        return (1);
    if (sdl->keyboard[SDL_SCANCODE_ESCAPE])
        return (1);
    return (0);
}

int             check_position(t_w *w, int x, int y)
{
    if (w->array[(y / 64)][(x / 64)] != 1)
        return (1);
    return (0);
}

void            keyboard_input(t_w *w)
{
    const Uint8 *key;
    int     tmp_x;
    int     tmp_y;

    key = w->sdl->keyboard;
    if (key[SDL_SCANCODE_W] || key[SDL_SCANCODE_UP])
    {
        tmp_x = w->player.x;
        tmp_y = w->player.y;
        w->player.x = w->player.x + cos(w->player.direction * M_PI_180) * w->player.speed;
        if (!check_position(w, w->player.x, w->player.y))
            w->player.x = tmp_x;
        w->player.y = w->player.y + sin(w->player.direction * M_PI_180) * w->player.speed;
        if (!check_position(w, w->player.x, w->player.y))
            w->player.y = tmp_y;
    }
    if (key[SDL_SCANCODE_A] || key[SDL_SCANCODE_LEFT])
    {
        w->player.direction -= w->player.turn;
    }
    if (key[SDL_SCANCODE_S] || key[SDL_SCANCODE_DOWN])
    {
        tmp_x = w->player.x;
        tmp_y = w->player.y;
        w->player.x = w->player.x - cos(w->player.direction * M_PI_180) * w->player.speed;
        if (!check_position(w, w->player.x, w->player.y))
            w->player.x = tmp_x;
        w->player.y = w->player.y - sin(w->player.direction * M_PI_180) * w->player.speed;
        if (!check_position(w, w->player.x, w->player.y))
            w->player.y = tmp_y;
    }
    if (key[SDL_SCANCODE_D] || key[SDL_SCANCODE_RIGHT])
    {
        w->player.direction += w->player.turn;
    }
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
            ft_memset(wolf->sdl->surface->pixels, 0, W * H * 4);
	        SDL_PollEvent(&wolf->sdl->event);
	        if (check_for_quit(&wolf->sdl->event, wolf->sdl))
                break ;
	        keyboard_input(wolf);
            process_of_wolf(wolf);
            SDL_UpdateWindowSurface(wolf->sdl->window);
        }
	}
	return 0;
}