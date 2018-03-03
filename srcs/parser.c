/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:19:37 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/04 00:05:12 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		reduce_piece(t_filler *f)
{
	t_dot	*d;
	int		min_x;
	int		min_y;

	min_x = 9999;
	min_y = 9999;
	d = f->piece;
	while (d)
	{
		if (d->x < min_x)
			min_x = d->x;
		if (d->y < min_y)
			min_y = d->y;
		d = d->next;
	}
	f->m_x = min_x;
	f->m_y = min_y;
	d = f->piece;
	while (d)
	{
		d->x -= min_x;
		d->y -= min_y;
		d = d->next;
	}
}

int			get_piece2(t_filler *f)
{
	char	*line;
	int		i;
	int		x;

	i = -1;
	line = NULL;
	while (++i < f->p_y && sget_next_line(0, &line) > 0)
	{
		x = -1;
		while (++x < f->p_x)
		{
			if (line[x] == '*')
				ft_dotlstpushback(&f->piece, x, i);
		}
		ft_strdel(&line);
	}
	return (1);
}

int			get_piece(t_filler *f)
{
	char	**tab;
	char	*line;

	line = NULL;
	while (sget_next_line(0, &line) > 0)
	{
		if (!ft_strncmp(line, "Piece ", 6))
			break ;
		ft_strdel(&line);
	}
	if (!line || !(tab = ft_split(line, " ")))
		return (0);
	ft_strdel(&line);
	if (tab_size(tab) != 3)
		return (0);
	f->p_x = ft_atoi(tab[2]);
	f->p_y = ft_atoi(tab[1]);
	ft_free2((void**)tab);
	if (f->x == 0 || f->y == 0)
		return (0);
	get_piece2(f);
	reduce_piece(f);
	return (1);
}

int			get_board2(t_filler *f)
{
	char	**tab;
	char	*line;
	int		i;
	int		x;

	i = -1;
	line = NULL;
	if (sget_next_line(0, &line) == -1)
		return (0);
	if (ft_strncmp(line, "    0", 5) != 0)
		return (0);
	ft_strdel(&line);
	while (++i < f->y && sget_next_line(0, &line) > 0)
	{
		if (!line || !(tab = ft_split(line, " ")))
			return (0);
		x = -1;
		while (++x < f->x)
		{
			if (tab[1][x] == f->player || tab[1][x] == f->player + 32)
				f->board[i][x] = -1;
			else if (tab[1][x] == f->adv || tab[1][x] == f->adv + 32)
				f->board[i][x] = -2;
			else
				f->board[i][x] = 0;
		}
		ft_free2((void**)tab);
		ft_strdel(&line);
	}
	return (1);
}

int			get_board(t_filler *f)
{
	char	**tab;
	char	*line;

	line = NULL;
	while (sget_next_line(0, &line) > 0)
	{
		if (!ft_strncmp(line, "Plateau ", 8))
			break ;
		ft_strdel(&line);
	}
	if (!line || !(tab = ft_split(line, " ")))
		return (0);
	ft_strdel(&line);
	if (tab_size(tab) != 3)
		return (0);
	f->x = ft_atoi(tab[2]);
	f->y = ft_atoi(tab[1]);
	if (f->x == 0 || f->y == 0)
		return (0);
	ft_free2((void**)tab);
	if (!(f->board = (int**)ft_int2alloc(f->y, f->x)))
		return (0);
	if (!get_board2(f))
		return (0);
	get_heatmap(f);
	ft_dprintf(2, "\e[1;1H\e[2J");
	ft_display_board(f);
	get_piece(f);
	get_pos(f);
	ft_dotlstdel(&f->piece);
	return (1);
}

int			get_player(t_filler *f)
{
	char	*line;

	line = NULL;
	if (sget_next_line(0, &line) <= 0)
		return (0);
	if (!ft_strncmp(line, "$$$ exec p", 10))
	{
		if (ft_strlen(line) < 12 || line[11] != ' ')
			return (0);
		if (line[10] != '1' && line[10] != '2')
			return (0);
		f->player = (line[10] == '1') ? 'O' : 'X';
		f->adv = (f->player == 'X') ? 'O' : 'X';
	}
	ft_strdel(&line);
	return (1);
}
