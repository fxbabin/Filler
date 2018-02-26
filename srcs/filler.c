/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 22:59:08 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/27 00:04:09 by fbabin           ###   ########.fr       */
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
		ft_dprintf(2, "%3d ", f->board[i]);
	}
	ft_dprintf(2, "\n");
}

void            ft_lstdumpi(t_list **list)
{
	t_list          *l;

	if (!list || !*list)
	{
		ft_dprintf(2, "(null)\n");
		return ;
	}
	l = *list;
	while ((*list))
	{
		if ((*list)->content_size)
			ft_dprintf(2, "%3d", (*list)->content_size);
		else
			ft_dprintf(2, " (null) ");
		ft_dprintf(2, " -> ");
		*list = (*list)->next;
	}
	ft_dprintf(2, " NULL\n");
	*list = l;
}

int			ft_lstinpos(t_list **begin_list, int pos)
{
	t_list          *tmp;

	if (!begin_list)
		return (0);
	tmp = *begin_list;
	while (tmp)
	{
		if (tmp->content_size == (size_t)pos)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	get_neighbours(t_filler *f, t_list **visited, t_list **ntv, int i)
{
	if (i - 1 >= 0 && f->board[i - 1] == 46 &&
		(i % f->x != 0) && !ft_lstinpos(visited, i - 1) && !ft_lstinpos(ntv, i - 1))
		ft_lstpushback(ntv, NULL, i - 1);
	if (i + 1 < (f->x * f->y) && f->board[i + 1] == 46 &&
			((i + 1) % f->x != 0) && !ft_lstinpos(visited, i + 1) && !ft_lstinpos(ntv, i + 1) )
	{
		ft_lstpushback(ntv, NULL, i + 1);
	}
	if (i - f->x > 0 && f->board[i - f->x] == 46 &&
			!ft_lstinpos(visited, i - f->x) && !ft_lstinpos(ntv, i - f->x))
	{
		ft_lstpushback(ntv, NULL, i - f->x);
	}
	if (i + f->x < (f->x * f->y) && f->board[i + f->x] == 46 &&
			!ft_lstinpos(visited, i + f->x) && !ft_lstinpos(ntv, i + f->x))
	{
		ft_lstpushback(ntv, NULL, i + f->x);
	}
}


void	dd(t_filler *f, t_list **visited, t_list **ntv, int i)
{
	t_list		*new;
	t_list		*t;
	//t_list		*tmp;

	new = NULL;
	(void)visited;
	(void)f;
	t = *ntv;
	while (t)
	{
		f->board[t->content_size] = i;
		ft_lstpushback(visited, NULL, t->content_size);
		get_neighbours(f, visited, &new, t->content_size);
		//tmp = t;
		t = t->next;
		//return ;
		//free(tmp);
	}
	//ft_lstdumpi(&new);
	//(void)new;
	ft_lstdel(ntv, ft_eldel);
	*ntv = new;
}

void	da(t_filler *f, t_list **visited, t_list **ntv)
{
	int		i;

	i = 0;
	while (*ntv)
	{
		dd(f, visited, ntv, ++i);
	}
}

void	get_heatmap(t_filler *f)
{
	t_list		*visited;
	t_list		*ntv;
	int			i;

	i = -1;
	ntv = NULL;
	visited = NULL;
	while (f->board[++i])
	{
		if (f->board[i] == f->adv)
		{
			f->board[i] = -2;
			ft_lstpushback(&visited, NULL, i);
			get_neighbours(f, &visited, &ntv, i);
		}
		else if (f->board[i] == f->player)
		{
			f->board[i] = -1;
			ft_lstpushback(&visited, NULL, i);
			//get_neighbours(f, &visited, &ntv, i);
		}
	}
	da(f, &visited, &ntv);
	ft_lstdel(&visited, ft_eldel);
}

int		get_board2(t_filler *f)
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
		ft_memcpy(f->board + (i * f->x), tab[1], f->x);
		ft_free2((void**)tab);
		ft_strdel(&line);
	}
	return (1);
}

/*void	reduce_piece(t_filler *f)
{
	char	*new;
	int		i;
	int		x;

	x = 0;
	i = -1;
	while (f->piece[++i])
	{
		if (f->piece[i] == '*')
			x++;
		if (i % f->x == 0 && i != 0)
		{
			if (x != 0)
				ft_memcpy();
			x = 0;
		}
	}
}*/

int		get_piece2(t_filler *f)
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

int		get_piece(t_filler *f)
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
	if (f->piece)
		ft_strdel(&f->piece);
	if (!(f->piece = (char*)ft_memalloc(((f->x * f->y) + 1) * sizeof(char))))
		return (0);
	get_piece2(f);
	return (1);
}

void	ft_display_piece(t_filler *f)
{
	int		i;

	i = -1;
	while (f->piece[++i])
	{
		if ((i % f->p_x) == 0 && i != 0)
			ft_dprintf(2, "\n");
		ft_dprintf(2, "%c", f->piece[i]);
	}
	ft_dprintf(2, "\n");
}

int		get_board(t_filler *f)
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
	if (f->board)
		ft_strdel(&f->board);
	if (!(f->board = (char*)ft_memalloc(((f->x * f->y) + 1) * sizeof(char))))
		return (0);
	if (!get_board2(f))
		return (0);
	get_heatmap(f);
	get_piece(f);
	ft_display_board(f);
	ft_display_piece(f);
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
