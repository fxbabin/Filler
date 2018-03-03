/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:30:11 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/03 19:55:14 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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

int		get_mindist(t_filler *f, t_dot *adv, int x, int y)
{
	t_dot	*tmp;
	int		dist;
	int		min;

	tmp = adv;
	min = f->y * f->x;
	dist = 0;
	(void)y;
	while (tmp)
	{
		dist = ft_abs(x - tmp->x) + ft_abs(y - tmp->y);
		if (dist < min)
			min = dist;
		tmp = tmp->next;
	}
	return (min);
}

void		get_scores(t_filler *f, t_dot *adv)
{
	int			max;
	int			dist;
	int			x;
	int			y;

	y = -1;
	max = 0;
	dist = 0;
	while (++y < f->y)
	{
		x = -1;
		while (++x < f->x)
		{
			if (f->board[y][x] >= 0)
			{
				dist = get_mindist(f, adv, x, y);
				if (dist > max)
					max = dist;
				if (dist <= 2)
					dist = 2;
				f->board[y][x] = dist;
			}
		}
	}
	set_colors(f, max);
}

void		get_heatmap(t_filler *f)
{
	t_dot		*adv;
	int			x;
	int			y;

	y = -1;
	adv = NULL;
	while (++y < f->y)
	{
		x = -1;
		while (++x < f->x)
		{
			if (f->board[y][x] == -2)
				ft_dotlstpushback(&adv, x, y);
		}
	}
	ft_display_dotlst(&adv);
	get_scores(f, adv);
	ft_dotlstdel(&adv);
}
