#include "../includes/wolf.h"

void			dda(t_fdf fdf, t_2d pnt1, t_2d pnt2)
{
	int			l;
	double		dx;
	double		dy;
	t_2d		current;
	int			index;

	current.x = pnt1.x + 0.5;
	current.y = pnt1.y + 0.5;
	l = get_l((int)floor(current.x), (int)floor(current.y),
			  (int)floor(pnt2.x + 0.5), (int)floor(pnt2.y + 0.5));
	dx = ((pnt2.x - pnt1.x) / l);
	dy = ((pnt2.y - pnt1.y) / l);
	while (l--)
	{
		current.x += dx;
		current.y += dy;
		index = (int)(current.x) * 4 + fdf.sl * (int)current.y;
		current.color = get_color(current, pnt1, pnt2);
		if (check_edge(fdf, (int)current.x, (int)current.y))
			write_index(&fdf, index, current);
	}
}

//
// Created by Dremora lord Gorold goodbrother on 06/10/2019.
//

