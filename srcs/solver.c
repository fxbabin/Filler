/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:28:55 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/01 23:25:12 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			is_dotvalid(t_filler *f, int i)
{
	int		nb;

	nb = 4;
	if (i - 1 < 0 || (i % f->x == 0) || f->board[i - 1] == f->player)
		nb--;
	if (i + 1 >= (f->x * f->y) || ((i + 1) % f->x == 0) || f->board[i + 1] == f->player)
		nb--;
	if (i - f->x < 0 || f->board[i - f->x] == f->player)
		nb--;
	if (i + f->x >= (f->x * f->y) || f->board[i + f->x] == f->player)
		nb--;
	if (nb == 0)
		return (0);
	return (1);
}

void  get_minpos(t_filler *f, int pos)
{
	int		min;
	int		min_pos;
	int		cost;
	int		i;
	int		x;

	i = -1;
	min = 1000;
	min_pos = 0;
	while (f->piece[++i])
	{
		if (f->piece[i] == '.')
			continue ;
		y = -1;
		cost = 0;
		while (f->piece[++y])
		{
			if (y != i)
			{
				if (f->piece[y] == '*')
				{
					x = pos + (((y - i) / f->p_x) * f->x) + ((y - i) % f->p_x)
						if(f->board[x] < 0)
							cost += 1000;
						else
							cost += f->board[x];
				}
			}
		}
		if (cost < min)
		{
			min = cost;
			min_pos =
		}
	}
}

int		calc_score(t_filler *f, t_dot *curr, t_dot *pos)
{
	t_dot		*d;
	int			score;

	score = 0;
	d = f->piece;
	while (d)
	{
		if (d->x != curr->x || d->y != curr->y && f->board[pos->y - d->y][pos->x - d->x] < 0)
			score += 9999;
		else if (d->x != curr->x || d->y != curr->y)
			score += f->board[d->y][d->x];
		d = d->next;
	}
	return (score);
}

void	get_minscore(t_filler *f, t_dot *d)
{
	t_dot*		tmp;
	int			min;
	int			tmp;

	min = 9999;
	tmp = f->piece;
	while (tmp)
	{
		tmp = calc_score(f->piece, tmp, d);
		if (tmp < min)
			min = tmp;
		tmp = tmp->next;
	}
	if (min == 9999)
		return (-1)
	return (min);
}

void	get_dots(t_filler *f)
{
	t_dot		*tmp;
	t_dot		*ntv;
	int			x;
	int			y;

	y = -1;
	ntv = NULL;
	while (++y < f->y)
	{
		x = -1;
		while (++x < f->x)
		{
			if (f->board[y][x] == -1)
				ft_dotlstpushback(&ntv, x, y);
		}
	}
	tmp = ntv;
	x = 9999;
	while (tmp)
	{
		y = get_minscore(tmp);
		if (y != -1 && y < x)
			x = y;
		tmp = tmp->next;
	}
}
