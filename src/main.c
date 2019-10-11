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
}

void            init_textures(t_w *w)
{
    int         height;
    int         width;

    w->t.walls[0] = (t_walls*)malloc(sizeof(t_walls));
    w->t.walls[1] = (t_walls*)malloc(sizeof(t_walls));
//    w->t.walls[0]->wall = (char*)malloc(sizeof(char) * 64 * 64); // malloc delete memory
//    w->t.walls[1]->wall = (char*)malloc(sizeof(char) * 64 * 64); // malloc delete memory

    w->t.walls[0]->wall = mlx_xpm_file_to_image(w->mlx.mlx, WALL0, &width, &height);
    w->t.walls[1]->wall = mlx_xpm_file_to_image(w->mlx.mlx, WALL1, &width, &height);
}

void			initialization_(t_w *w)
{
	double		fov;

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



int				main(int argc, char *argv[])
{
	t_w			*wolf;

	int 		val = 64;

	wolf = (t_w*)malloc(sizeof(t_w));
	if (argc == 2)
	{
		player_init(wolf);
    	read_map(wolf, argv[1]);
		initialization_(wolf);
		hooks(wolf);
		mlx_loop(wolf->mlx.mlx);
	}
	return 0;
}