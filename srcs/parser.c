/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:19:37 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/01 01:18:55 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*void		get_dots(t_filler *f, int nb)
{
	t_list		*l;
	int			i;

	i = -1;
	l = NULL;
	(void)nb;
	while (f->board[++i])
	{
		if (f->board[i] == -1 && is_dotvalid(f, i))
		{
			ft_lstpushback(&l, NULL, i);
		}
	}
	ft_lstdumpi(&l);
}*/

int			get_piece2(t_filler *f)
{
	char	*line;
	int		i;

	i = -1;
	line = NULL;
	while (++i < f->p_y && sget_next_line(0, &line) > 0)
	{
		ft_memcpy(f->piece + (i * f->p_x), line, f->p_x);
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
	if (f->x == 0 || f->y == 0)
		return (0);
	ft_free2((void**)tab);
	//if (f->piece)
	//	ft_strdel(&f->piece);
	//if (!(f->piece = (char*)ft_memalloc(((f->x * f->y) + 1) * sizeof(char))))
	//	return (0);
	get_piece2(f);
	return (1);
}

int			get_board2(t_filler *f)
{
	char	**tab;
	char	*line;
	int		i;

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
		ft_memcpy(f->board[i], tab[1], f->x);
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
	//if (f->board)
	//	ft_strdel(&f->board);
	if (!(f->board = (char**)ft_char2alloc(f->y, f->x)))
		return (0);
	if (!get_board2(f))
		return (0);
	get_heatmap(f);
	ft_display_board(f);
	/*get_piece(f);
	ft_dprintf(2, "\e[1;1H\e[2J");
	ft_display_piece(f);
	get_dots(f, 0);*/
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
