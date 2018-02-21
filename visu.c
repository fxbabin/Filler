/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 22:01:11 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/22 00:35:06 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_bchar(void *s, size_t n, char c)
{
	char	*tmp;

	tmp = (char*)s;
	while (n--)
		*(tmp++) = c;
}

int		check_plateau(char *line, t_board *b)
{
	char	**tab;
	int		i;

	if (!(tab = ft_split(line, " ")))
		return (0);
	i = -1;
	while (tab[++i])
		;
	b->x = ft_atoi(tab[2]);
	b->y = ft_atoi(tab[1]);
	if (i != 3 || b->x < 2 || (b->y < 2))
		return (0);
	if (!(b->board = (char*)malloc(((b->x * b->y) + 1) * sizeof(char))))
		return (0);
	ft_bchar(b->board, (b->x * b->y) + 1, '.');
	ft_free2((void**)tab);
	return (1);
}

void	display_board(t_board *b)
{
	int		i;
	int		len;

	i = -1;
	len = b->x * b->y;
	while (++i < len)
	{
		if ((i % b->x) == 0 && i != 0)
		{
			ft_printf("\n");
		}
		ft_printf("%c", b->board[i]);
	}
	ft_printf("\n--------------------------------------\n");
}

void	extract_line(t_board *b, char *line)
{
	int		i;

	i = -1;
	//ft_printf("%s\n", line);
	while(line[++i])
		b->board[b->pos++] = line[i];
}

void	update_board(t_board *b, char *line)
{
	char	**tab;
	int		l_nb;

	l_nb = 0;
	b->pos = 0;
	if (!(tab = ft_split(line, " ")))
		return ;
	extract_line(b, tab[1]);
	//free(line);
	while (sget_next_line(0, &line) > 0)
	{
		if (!ft_strncmp(line, "Piece", 5))
			break ;
		if (!(tab = ft_split(line, " ")))
			return ;
		extract_line(b, tab[1]);
		ft_free2((void**)tab);
		free(line);
	}
}
void	extract_score(t_board *b, char *line)
{
	char	**tab;

	if (!(tab = ft_split(line, " ")))
		return ;
	free(line);
	b->sc1 = ft_atoi(tab[3]);
	sget_next_line(0, &line);
	ft_free2((void**)tab);
	if (!(tab = ft_split(line, " ")))
		return ;
	b->sc2 = ft_atoi(tab[3]);
	ft_free2((void**)tab);
}

int		main(void)
{
	char		*line;
	t_board		b;
	int			boo;

	boo = 0;
	line = NULL;
	while (sget_next_line(0, &line) > 0)
	{
		if (!boo && !ft_strncmp(line, "Plateau", 7))
		{
			boo = 1;
			if (!check_plateau(line, &b))
				return (0);
		}
		if (!ft_strncmp(line, "==", 2))
		{
			extract_score(&b, line);
			break ;
		}
		if (!ft_strncmp(line, "000", 3))
		{
			update_board(&b, line);
			display_board(&b);
			//return (0);
		}
		free(line);
	}
	ft_printf("score 1: %d\nscore 2: %d\n", b.sc1, b.sc2);
	//free(line);
	return (0);
}
