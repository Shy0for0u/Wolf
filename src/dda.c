#include "../includes/wolf.h"

static int		ft_max(int val1, int val2)
{
	return ((val1 > val2) ? val1 : val2);
}


static int		get_l(int ixs, int iys, int ixe, int iye)
{
	int			ilx;
	int			ily;

	ilx = abs(ixe - ixs);
	ily = abs(iye - iys);
	return (ft_max(ilx, ily));
}

//void			pixel_to_img(t_w *w, int y, int x)
//{
//	int 		index;
//
//	index = (x * 4 + w->mlx.sl * y);
//	w->mlx.data[index] = (char)0xff;
//	w->mlx.data[index + 1] = (char)0xff;
//	w->mlx.data[index + 2] = (char)0xff;
//}

void			dda(t_w *w, t_pl *pnt1, t_pl *pnt2)
{
	int			l;
	double		dx;
	double		dy;
	t_pl		current;
	int			index;

	current.p_x = (int)((double)(pnt1->p_x) + 0.5);
	current.p_y = (int)((double)(pnt1->p_y) + 0.5);
	l = get_l((int)floor(current.p_x), (int)floor(current.p_y),
			  (int)floor(pnt2->p_x + 0.5), (int)floor(pnt2->p_y + 0.5));
	dx = ((pnt2->p_x - pnt1->p_x) / l);
	dy = ((pnt2->p_y - pnt1->p_y) / l);
	while (l--)
	{
		current.p_x += dx;
		current.p_y += dy;
		index = (int)(current.p_x) * 4 + w->mlx.sl * (int)current.p_y;
		w->mlx.data[index] = (char)0xff;
		w->mlx.data[index + 1] = (char)0xff;
		w->mlx.data[index + 2] = (char)0xff;
	}
}

//
// Created by Dremora lord Gorold goodbrother on 06/10/2019.
//

