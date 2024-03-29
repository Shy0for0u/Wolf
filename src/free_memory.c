/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:59:41 by dgorold-          #+#    #+#             */
/*   Updated: 2019/10/18 00:14:25 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void			del_array(void **array)
{
	int			i;

	i = -1;
	while (array[++i])
		ft_memdel(&array[i]);
	free(array);
}
