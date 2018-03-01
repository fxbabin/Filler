/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:16:32 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/01 01:19:30 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_display_board(t_filler *f)
{
	int		x;
	int		y;

	y = -1;
	ft_dprintf(2, "%k------------- HEATMAP -------------%k\n\n", YELLOW, EOC);
	while (++y < f->y)
	{
		x = -1;
		while (++x < f->x)
			ft_dprintf(2, "%3d", f->board[y][x]);
		//ft_dprintf(2, "%k%3d%k", f->colors[y][x], f->board[y][x], EOC);

		//if ((i % f->x) == 0 && i != 0)
		ft_dprintf(2, "\n");
		/*if (f->board[i] < 0)
		{
			if (f->board[i] == -2)
				ft_dprintf(2, "%k%3c%k ", CYAN, f->adv, EOC);
			if (f->board[i] == -1)
				ft_dprintf(2, "%k%3c%k ", MAGENTA, f->player, EOC);
		}
		else
			ft_dprintf(2, "%k%3d%k ", f->colors[(int)f->board[i] - 1], f->board[i], EOC);*/
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

void    ft_display_piece(t_filler *f)
{
	int		i;

	i = -1;
	while (f->piece[++i])
	{
		if ((i % f->p_x) == 0 && i != 0)
			ft_dprintf(2, "\n");
		ft_dprintf(2, "%c", f->piece[i]);
	}
	ft_dprintf(2, "\n");
}
