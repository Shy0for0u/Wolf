#include "../includes/wolf.h"

//static double	percent(int start, int end, int current)
//{
//	double		placement;
//	double		distance;
//
//	placement = current - start;
//	distance = end - start;
//	return ((distance == 0) ? 1.0 : (placement / distance));
//}
//
//static int		get_light(int start, int end, double rate)
//{
//	return ((int)((1 - rate) * start + rate * end));
//}
//
//int				get_color(t_2d current, t_2d pnt1, t_2d pnt2)
//{
//	int			red;
//	int			green;
//	int			blue;
//	double		rate;
//
//	if (current.color == pnt2.color)
//		return (current.color);
//	if ((pnt2.x - pnt1.x) > (pnt2.y - pnt1.y))
//		rate = percent((int)pnt1.x, (int)pnt2.x, (int)current.x);
//	else
//		rate = percent((int)pnt1.y, (int)pnt2.y, (int)current.y);
//	red = get_light((pnt1.color >> 16) & 0xFF, (pnt2.color >> 16) & 0xFF, rate);
//	green = get_light((pnt1.color >> 8) & 0xFF, (pnt2.color >> 8) & 0xFF, rate);
//	blue = get_light(pnt1.color & 0xFF, pnt2.color & 0xFF, rate);
//	return ((red << 16) | (green << 8) | blue);
//}
//
//
//static int		ft_max(int val1, int val2)
//{
//	return ((val1 > val2) ? val1 : val2);
//}
//
//static int		get_l(int ixs, int iys, int ixe, int iye)
//{
//	int			ilx;
//	int			ily;
//
//	ilx = abs(ixe - ixs);
//	ily = abs(iye - iys);
//	return (ft_max(ilx, ily));
//}
//
//static int		check_edge(int x, int y)
//{
//	if (x > (W - 1) || x < 1)
//		return (0);
//	if (y > (H - 1) || y < 1)
//		return (0);
//	return (1);
//}

//static void		write_index(t_w *w, int index, t_2d cur)
//{
//	w->mlx.data[index] = (char)(cur.color >> 16 & 0xFF);
//	w->mlx.data[index + 1] = (char)(cur.color >> 8 & 0xFF);
//	w->mlx.data[index + 2] = (char)(cur.color & 0xFF);
//}

//void			dda(t_w *w, t_2d pnt1, t_2d pnt2)
//{
//	int			l;
//	double		dx;
//	double		dy;
//	t_2d		current;
//	int			index;
//
//	current.color = 0xffffff;
//	current.x = pnt1.x + 0.5;
//	current.y = pnt1.y + 0.5;
//	l = get_l((int)floor(current.x), (int)floor(current.y),
//			  (int)floor(pnt2.x + 0.5), (int)floor(pnt2.y + 0.5));
//	dx = ((pnt2.x - pnt1.x) / l);
//	dy = ((pnt2.y - pnt1.y) / l);
//	while (l--)
//	{
//		current.x += dx;
//		current.y += dy;
//		index = (int)(current.x) * 4 + w->mlx.sl * (int)current.y;
//		w->mlx.data[index] = (char)(current.color >> 16 & 0x1a);
//		w->mlx.data[index + 1] = (char)(current.color >> 8 & 0x2c);
//		w->mlx.data[index + 2] = (char)(current.color & 0x3d);
//		current.color = get_color(current, pnt1, pnt2);
////		if (check_edge((int)current.x, (int)current.y))
//			write_index(w, index, current);
//	}
//}

