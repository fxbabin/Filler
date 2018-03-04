/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_board.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 14:28:52 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/04 14:59:54 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			get_board2(t_filler *f, char *line, int i, int x)
{
	char	**tab;

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

int			get_boardbis(t_filler *f)
{
	char	*line;
	int		i;
	int		x;

	i = -1;
	x = 0;
	line = NULL;
	if (sget_next_line(0, &line) == -1)
		return (0);
	if (ft_strncmp(line, "    0", 5) != 0)
		return (0);
	ft_strdel(&line);
	if (!(f->board = (int**)ft_int2alloc(f->y, f->x)))
		return (0);
	if (!get_board2(f, line, i, x))
		return (0);
	get_heatmap(f);
	ft_dprintf(2, "\e[1;1H\e[2J");
	ft_display_board(f);
	get_piece(f);
	get_pos(f);
	ft_dotlstdel(&f->piece);
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
	if (!get_boardbis(f))
		return (0);
	ft_free2((void**)tab);
	return (1);
}
