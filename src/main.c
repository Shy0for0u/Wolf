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
		write(2, "non valid elem\n", 15);
		exit(0);
	}
	if (key == 2)
	{
		write(2, "memory not allocated\n", 21);
		exit(0);
	}
}

void			initialization_(t_w *w)
{
	float		fov;

	fov = M_PI / 6.0;
	w->mlx.mlx = mlx_init();
	w->mlx.win = mlx_new_window(w->mlx.mlx, W, H, T);
	w->mlx.img = mlx_new_image(w->mlx.mlx, W, H);
	w->mlx.data = mlx_get_data_addr(w->mlx.img,
			&w->mlx.bpp, &w->mlx.sl, &w->mlx.end);
	w->half_width = (int)(W * 0.5);
	w->half_height = (int)(H * 0.5);
	w->dist_to_pp = (int)((float)w->half_width / tanf(fov));
}


int				main(int argc, char *argv[])
{
	t_w			wolf;

	if (argc == 2)
	{
		read_map(&wolf, argv[1]);
		initialization_(&wolf);
		player_init(&wolf, wolf.player);
		process_of_wolf(&wolf);
		hooks(&wolf);
		mlx_loop(wolf.mlx.mlx);
	}
	return 0;
}