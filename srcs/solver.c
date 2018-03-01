/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:28:55 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/28 21:36:52 by fbabin           ###   ########.fr       */
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
