/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 22:59:08 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/25 22:20:53 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <fcntl.h>

int		tab_size(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_display_board(t_filler *f)
{
	int		i;

	i = -1;
	ft_dprintf(2, "starting display\n");
	while (f->board[++i])
	{
		if ((i % f->x) == 0 && i != 0)
			ft_dprintf(2, "\n");
		ft_dprintf(2, "%d ", f->board[i]);
	}
	ft_dprintf(2, "\n");
}

void	get_heatmap(t_filler *f)
{
	int		i;

	i = -1;
	while (f->board[++i])
	{
		if (f->board[i] == f->adv)
			f->board[i] = -1;
		if (f->board[i] == f->player)
			f->board[i] = -2;
	}
}

int		get_board2(t_filler *f)
{
	char	**tab;
	char	*line;
	int		i;

	i = -1;
	line = NULL;
	ft_dprintf(2, "qq\n");
	if (sget_next_line(0, &line) == -1)
		return (0);
	ft_dprintf(2, "qq\n");
	if (ft_strncmp(line, "    0", 5) != 0)
		return (0);
	ft_strdel(&line);
	ft_dprintf(2, "qq\n");
	while (++i < f->y && sget_next_line(0, &line) > 0)
	{
		if (!line || !(tab = ft_split(line, " ")))
			return (0);
		ft_memcpy(f->board + (i * f->x), tab[1], f->x);
		ft_free2((void**)tab);
		ft_strdel(&line);
	}
	ft_dprintf(2, "qq\n");
	return (1);
}

int		get_board(t_filler *f)
{
	char	**tab;
	char	*line;

	line = NULL;
	ft_dprintf(2, "oo\n");
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
	ft_dprintf(2, "oo\n");
	f->x = ft_atoi(tab[2]);
	f->y = ft_atoi(tab[1]);
	if (f->x == 0 || f->y == 0)
		return (0);
	ft_free2((void**)tab);
	if (f->board)
		ft_strdel(&f->board);
	if (!(f->board = (char*)ft_memalloc(((f->x * f->y) + 1) * sizeof(char))))
		return (0);
	ft_dprintf(2, "oo\n");
	if (!get_board2(f))
		return (0);
	ft_dprintf(2, "oo\n");
	get_heatmap(f);
	ft_display_board(f);
	return (1);
}

int		get_player(t_filler *f)
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

/*void	loop(t_filler *f)
{

	while (1)
	{
		if (
	}

}*/

int		main(void)
{
	t_filler	f;

	ft_bzero(&f, sizeof(t_filler));
	if (!get_player(&f))
		return (0);
	while (1)
	{
		if (!f.x && !get_board(&f))
			return (-1);
		ft_dprintf(2, "x %d y %d\n", f.x, f.y); 
		return (0);
	}
	//ft_dprintf(2, "player %c\n", f.player + 48); 
	return (0);
}
