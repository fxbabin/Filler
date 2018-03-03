/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:28:55 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/04 00:06:06 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void    check_score(t_filler *f, int x, int y)
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
		{
			b++;
		}
		if (y + tmp->y >= f->y || x + tmp->x >= f->x)
		{
			b = 3;
			break ;
		}
		if (y + tmp->y < f->y && x + tmp->x < f->x)
		{
			if (f->board[y + tmp->y][x + tmp->x] == -2)
			{
				b = 3;
				//score += 9999;
				break ;
				continue ;
			}
			score += f->board[y + tmp->y][x + tmp->x];
			/*if (y + f->p_y > f->y || x + f->p_x > f->x)
				score += 9999;
			else if (y - f->m_y < 0 || x - f->m_x < 0)
				score += 9999;
			else if (f->board[y + tmp->y][x + tmp->x] == -2)
			{
				score += 9999;
			}
			else if (f->board[y + tmp->y][x + tmp->x] < 0)
			{
				if (b == 1)
				{
					score += 9999;
					break ;
				}
				else
					b = 1;
			}
			else
				score += f->board[y + tmp->y][x + tmp->x];
			*/
		}
		tmp = tmp->next;
	}
	//ft_dprintf(2, "score %d\n", score);
	if (b == 1 && score < f->min_score)
	{
		f->min_score = score;
		((t_dot*)f->result)->x = x;
		((t_dot*)f->result)->y = y;
	}
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

void    get_pos(t_filler *f)
{
	//t_dot         *tmp;
	//t_dot         *ntv;
	int                   x;
	int                     y;

	y = -1;
	//ntv = NULL;
	//f->min_score = 9999;
	f->result = NULL;
	ft_dotlstpushback(&f->result, 0, 0);
	//ft_dprintf(2, "ff x %d y %d\n", f->x, f->y);
	while (++y < f->y)
	{
		x = -1;
		while (++x < f->x)
		{
			//ft_dprintf(2, "ff x %d y %d\n", x, y);
			check_score(f, x, y);
		}
	}
	//ft_dprintf(2, "min_x %d min_y %d\n", f->m_x, f->m_y);
	//ft_dprintf(2, "return x %d y %d %d\n", ((t_dot*)f->result)->x - f->m_x, ((t_dot*)f->result)->y - f->m_y, f->y);
	ft_dprintf(1, "%d %d\n", ((t_dot*)f->result)->y - f->m_y, ((t_dot*)f->result)->x - f->m_x);
	
	//ft_dprintf(2, "%d %d\n", ((t_dot*)f->result)->y - f->m_y, ((t_dot*)f->result)->x - f->m_x);
	/*tmp = ntv;
	  x = 9999;
	  while (tmp)
	  {
	  y = get_minscore(tmp);
	  if (y != -1 && y < x)
	  x = y;
	  tmp = tmp->next;
	  }*/
}
