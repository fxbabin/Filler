/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:28:55 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/04 14:02:57 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	check_score2(t_filler *f, int score, int x, int y)
{
	f->min_score = score;
	((t_dot*)f->result)->x = x;
	((t_dot*)f->result)->y = y;
}

void	check_score(t_filler *f, int x, int y)
{
	t_dot	*tmp;
	int		score;
	int		b;

	b = 0;
	score = 0;
	tmp = f->piece;
	while (tmp)
	{
		if (y + tmp->y < f->y && x + tmp->x < f->x &&
			f->board[y + tmp->y][x + tmp->x] == -1)
			b++;
		if ((y + tmp->y >= f->y || x + tmp->x >= f->x) && (b = 3))
			break ;
		if (y + tmp->y < f->y && x + tmp->x < f->x)
		{
			if (f->board[y + tmp->y][x + tmp->x] == -2 && (b = 3))
				break ;
			score += f->board[y + tmp->y][x + tmp->x];
		}
		tmp = tmp->next;
	}
	if (b == 1 && score < f->min_score)
		check_score2(f, score, x, y);
}

void	get_max(t_filler *f)
{
	int		max_x;
	int		max_y;
	t_dot	*d;

	d = f->piece;
	max_x = 0;
	max_y = 0;
	while (d)
	{
		if (d->x > max_x)
			max_x = d->x;
		if (d->y > max_y)
			max_y = d->y;
		d = d->next;
	}
	f->max_x = max_x;
	f->max_y = max_y;
}

void	get_pos(t_filler *f)
{
	int		x;
	int		y;

	y = -1;
	f->result = NULL;
	ft_dotlstpushback(&f->result, 0, 0);
	while (++y < f->y)
	{
		x = -1;
		while (++x < f->x)
			check_score(f, x, y);
	}
	ft_dprintf(1, "%d %d\n", ((t_dot*)f->result)->y - f->m_y,
		((t_dot*)f->result)->x - f->m_x);
}
