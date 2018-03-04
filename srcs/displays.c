/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:16:32 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/04 17:49:43 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_display_board(t_filler *f)
{
	int		x;
	int		y;

	y = -1;
	ft_dprintf(2, "%k------------- HEATMAP -------------%k\n\n   ",
		LYELLOW, EOC);
	x = -1;
	while (++x < f->x)
		ft_dprintf(2, "%+k%3d%k", EOC, x, RESET);
	while (++y < f->y)
	{
		x = -1;
		ft_dprintf(2, "\n%+k%3d%k", EOC, y, RESET);
		while (++x < f->x)
		{
			if (f->board[y][x] == -1)
				ft_dprintf(2, "%k  △%k", MAGENTA, EOC);
			else if (f->board[y][x] == -2)
				ft_dprintf(2, "%k  ▽%k", CYAN, EOC);
			else
				ft_dprintf(2, "%k%3d%k", f->colors[y][x], f->board[y][x], EOC);
		}
	}
	ft_dprintf(2, "\n");
}

void	ft_lstdumpi(t_list **list)
{
	t_list		*l;

	if (!list || !*list)
	{
		ft_dprintf(2, "(null)\n");
		return ;
	}
	l = *list;
	while ((*list))
	{
		if ((*list)->content_size)
			ft_dprintf(2, "%3d", (*list)->content_size);
		else
			ft_dprintf(2, " (null) ");
		ft_dprintf(2, " -> ");
		*list = (*list)->next;
	}
	ft_dprintf(2, " NULL\n");
	*list = l;
}

void	ft_display_dotlst(t_dot **f)
{
	t_dot		*t;

	t = *f;
	while (t)
	{
		ft_dprintf(2, " x %d y %d; ", t->x, t->y);
		t = t->next;
	}
	ft_dprintf(2, "\n");
}
