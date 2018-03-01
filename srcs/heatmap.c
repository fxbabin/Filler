/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:30:11 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/01 14:35:28 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		get_neighbours(t_filler *f, t_dot **visited, t_dot **ntv, t_dot *v)
{
	if ((v->x - 1 >= 0) && f->board[v->y][v->x - 1] == 0 && !ft_lstinpos(visited, v->x - 1, v->y) && !ft_lstinpos(ntv, v->x - 1, v->y))
		ft_dotlstpushback(ntv, v->x - 1, v->y);
	if ((v->x + 1 < f->x) && f->board[v->y][v->x + 1] == 0 && !ft_lstinpos(visited, v->x + 1, v->y) && !ft_lstinpos(ntv, v->x + 1, v->y))
		ft_dotlstpushback(ntv, v->x + 1, v->y);
	if (v->y - 1 >= 0 && f->board[v->y - 1][v->x] == 0 &&
			!ft_lstinpos(visited, v->x, v->y - 1) && !ft_lstinpos(ntv, v->x, v->y - 1))
		ft_dotlstpushback(ntv, v->x, v->y - 1);
	if (v->y + 1 < f->y && f->board[v->y + 1][v->x] == 0 &&
			!ft_lstinpos(visited, v->x, v->y + 1) && !ft_lstinpos(ntv, v->x, v->y + 1))
		ft_dotlstpushback(ntv, v->x, v->y + 1);
}

void		expand_heatmap(t_filler *f, t_dot **visited, t_dot **ntv, int i)
{
	t_dot		*new;
	t_dot		*t;

	t = *ntv;
	new = NULL;
	while (t)
	{
		f->board[t->y][t->x] = i;
		ft_dotlstpushfront(visited, t->x, t->y);
		get_neighbours(f, visited, &new, t);
		t = t->next;
	}
	//ft_lstdel(ntv, ft_eldel);
	*ntv = new;
}

void	set_colors(t_filler *f, int i)
{
	int		inter;
	int		n;
	int		x;
	int		y;

	y = -1;
	inter = 510 / i;
	n = (510 / inter) + (510 % inter) + 1;
	if (!(f->colors = (int**)ft_int2alloc(f->y, f->x)))
		return ;
	while (++y < f->y)
	{
		x = -1;
		while (++x < f->x)
		{
			n = -255 + f->board[y][x] * inter;
			if (n < 0)
				f->colors[y][x] = ft_abs(n) * 65536 + (255 - ft_abs(n)) * 256;
			else
				f->colors[y][x] = ft_abs(n) + (255 - ft_abs(n)) * 256;
		}
	}
}

void    ft_lstdumpdot(t_dot **list)
{
	t_dot          *l;

	if (!list || !*list)
	{
		ft_dprintf(2, "(null)\n");
		return ;
	}
	l = *list;
	while ((*list))
	{
		if ((*list)->x && (*list)->y)
			ft_dprintf(2, "x %d y %d", (*list)->x, (*list)->y);
		else
			ft_dprintf(2, " (null) ");
		ft_dprintf(2, " -> ");
		*list = (*list)->next;
	}
	ft_dprintf(2, " NULL\n");
	*list = l;
}

void    create_heatmap(t_filler *f, t_dot **visited, t_dot **ntv)
{
	int             i;

	i = 0;
	while (*ntv)
	{
		expand_heatmap(f, visited, ntv, ++i);
	}
	//ft_dprintf(2, "%d\n", i);
	set_colors(f, i);
}

t_dot		*ft_dotlstcreate(int x, int y)
{
	t_dot  *t;

	if ((t = (t_dot*)malloc(sizeof(t_dot))) == NULL)
		return (NULL);
	t->x = x;
	t->y = y;
	t->next = NULL;
	return (t);
}

void		ft_dotlstpushback(t_dot **begin_list, int x, int y)
{
	t_dot          *tmp;

	if (!begin_list)
		return ;
	if (*begin_list)
	{
		tmp = *begin_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_dotlstcreate(x, y);
	}
	else
		*begin_list = ft_dotlstcreate(x, y);
}

void            ft_dotlstpushfront(t_dot **begin_list, int x, int y)
{
	t_dot  *t;

	if (!begin_list)
		return ;
	if (*begin_list)
	{
		t = ft_dotlstcreate(x, y);
		t->next = (*begin_list);
		(*begin_list) = t;
	}
	else
	{
		t = ft_dotlstcreate(x, y);
		(*begin_list) = t;
	}
}

void		get_heatmap(t_filler *f)
{
	t_dot		*visited;
	t_dot		*ntv;
	int			x;
	int			y;
	//t_dot		*dot;

	y = -1;
	ntv = NULL;
	visited = NULL;
	while (++y < f->y)
	{
		x = -1;
		while (++x < f->x)
		{
			if (f->board[y][x] == -2)
			{
				//f->board[y][x] = -2;
				//if (dot)
				//	free(dot);
				/*if (!(dot = (t_dot*)ft_memalloc(sizeof(t_dot))))
				  return ;
				  dot->x = x;
				  dot->y = y;*/
				ft_dotlstpushfront(&visited, x, y);
				get_neighbours(f, &visited, &ntv, visited);
			}
			else if (f->board[y][x] == -1)
			{
				//f->board[y][x] = -1;
				ft_dotlstpushfront(&visited, x, y);
				/*if (!(dot = (t_dot*)ft_memalloc(sizeof(t_dot))))
				  return ;
				  dot->x = x;
				  dot->y = y;*/
				//ft_lstpushback(&visited, dot, 0);
			}
		}
	}
	create_heatmap(f, &visited, &ntv);
	//ft_lstdumpdot(&visited);
	//ft_lstdel(&visited, ft_eldel);
}
