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

void			initialization_(t_w *w)
{
	float		fov;

	w->m.map_h = w->m.map_h + 2;
	w->m.map_w = w->m.map_w + 2;
	fov = M_PI / 6.0;
//	w->projection_plane = W * H;
	w->mlx.mlx = mlx_init();
	w->mlx.win = mlx_new_window(w->mlx.mlx, W, H, T);
	w->mlx.img = mlx_new_image(w->mlx.mlx, W, H);
	w->mlx.data = mlx_get_data_addr(w->mlx.img,
			&w->mlx.bpp, &w->mlx.sl, &w->mlx.end);
	w->half_width = (int)(W * 0.5);
	w->half_height = (int)(H * 0.5);
	w->dist_to_projection_plane = (int)((float)w->half_width / tanf(fov));
	w->angle_between_rays = fov / W;
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
//		process_of_wolf(wolf);
		hooks(wolf);
		mlx_loop(wolf->mlx.mlx);
	}
	return 0;
}