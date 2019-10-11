#include "../includes/wolf.h"

void			player_init(t_w *w)
{
	w->player.direction = 270;
	w->player.max_dist = 25;
	w->player.x = -1;
	w->player.y = -1;
	w->player.angle = 4.71239f;
	w->player.fov = M_PI / 6.0;
	w->player.turn = 3;
	w->player.speed = 4;

}
