/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:28:36 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/01 00:42:28 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		tab_size(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		ft_lstinpos(t_dot **begin_list, int x, int y)
{
	t_dot		*tmp;

	if (!begin_list)
		return (0);
	tmp = *begin_list;
	while (tmp)
	{
		if (tmp->x == x && tmp->y == y)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
