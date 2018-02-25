/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_gridboard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 00:44:03 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/25 00:47:54 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	update_board(t_board *b, char *line)
{
	char	**tab;
	int		l_nb;

	l_nb = 0;
	b->pos = 0;
	if (!(tab = ft_split(line, " ")))
		return ;
	extract_line(b, tab[1]);
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

void	update_grid(SDL_Renderer *renderer, t_grid *grid, char *board)
{
	SDL_Rect	rect;
	int			x;
	int			y;

	y = -1;
	while (++y < grid->y)
	{
		x = -1;
		while (++x < grid->x)
		{
			set_color(renderer, board[(y * grid->x) + x]);
			get_rectcoords(&rect, grid->x_coord + (x * grid->sq),
					grid->y_coord + (y * grid->sq), grid->sq);
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}

void	draw_grid(SDL_Renderer *renderer, t_grid *grid)
{
	int		x;
	int		y;
	int		i;
	int		end;

	x = grid->x_coord;
	y = grid->y_coord;
	i = -1;
	end = (grid->max == grid->y) ? 800 : 800 - ((grid->x - grid->y)) * grid->sq;
	while (++i <= grid->x)
	{
		SDL_RenderDrawLine(renderer, x, y, x, y + end);
		x += grid->sq;
	}
	i = -1;
	x = grid->x_coord;
	end = (grid->max == grid->x) ? 800 : 800 - ((grid->y - grid->x)) * grid->sq;
	while (++i <= grid->y)
	{
		SDL_RenderDrawLine(renderer, x, y, x + end, y);
		y += grid->sq;
	}
}

void	extract_grid(t_grid *grid, int x, int y)
{
	grid->max = (x > y) ? x : y;
	grid->sq = 800 / grid->max;
	grid->x_coord = (grid->max == x) ? 200 : 200 + ((y - x) / 2) * grid->sq;
	grid->y_coord = (grid->max == y) ? 200 : 200 + ((x - y) / 2) * grid->sq;
	grid->x = x;
	grid->y = y;
}

void	update_disp(t_env *env, t_board *b, t_grid *grid)
{
	char	*line;

	line = NULL;
	while (sget_next_line(0, &line) > 0)
	{
		if (!ft_strncmp(line, "==", 2))
		{
			extract_score(b, line);
			break ;
		}
		if (!ft_strncmp(line, "000", 3))
		{
			update_board(b, line);
			update_grid(env->renderer, grid, b->board);
			SDL_SetRenderDrawColor(env->renderer, 193, 193, 193,
					SDL_ALPHA_OPAQUE);
			draw_grid(env->renderer, grid);
			SDL_RenderPresent(env->renderer);
			SDL_Delay(5);
			free(line);
			break ;
		}
		free(line);
	}
}
