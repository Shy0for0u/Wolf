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

int				main(int argc, char *argv[])
{
	t_w			wolf;

	if (argc == 2)
	{
		read_map(&wolf, argv[1]);
	}
	return 0;
}