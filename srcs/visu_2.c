/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 00:52:06 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/04 16:55:16 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	extract_line(t_board *b, char *line)
{
	int		i;

	i = -1;
	while (line[++i])
		b->board[b->pos++] = line[i];
}

void	extract_score(t_board *b, char *line)
{
	char	**tab;
	int		ret;

	ret = 1;
	if (!(tab = ft_split(line, " ")))
		return ;
	free(line);
	b->sc1 = ft_atoi(tab[3]);
	ft_free2((void**)tab);
	ret = sget_next_line(0, &line);
	if (!ret)
		return ;
	if (!(tab = ft_split(line, " ")))
		return ;
	b->sc2 = ft_atoi(tab[3]);
	ft_free2((void**)tab);
	ft_strdel(&line);
}

void	get_rectcoords(SDL_Rect *rect, int x, int y, int sq)
{
	rect->x = x;
	rect->y = y;
	rect->w = sq;
	rect->h = sq;
}

void	set_color(SDL_Renderer *renderer, char c)
{
	if (c == '.')
		SDL_SetRenderDrawColor(renderer, 120, 120, 120, SDL_ALPHA_OPAQUE);
	else if (c == 'o')
		SDL_SetRenderDrawColor(renderer, 231, 16, 16, SDL_ALPHA_OPAQUE);
	else if (c == 'O')
		SDL_SetRenderDrawColor(renderer, 243, 102, 77, SDL_ALPHA_OPAQUE);
	else if (c == 'x')
		SDL_SetRenderDrawColor(renderer, 15, 136, 21, SDL_ALPHA_OPAQUE);
	else if (c == 'X')
		SDL_SetRenderDrawColor(renderer, 29, 189, 36, SDL_ALPHA_OPAQUE);
}

char	*extract_name(char *line)
{
	int		i;
	int		len;
	char	*str;

	i = ft_strlen(line);
	while (i > 0 && line[i] != '/')
		i--;
	len = ft_strcspn(line + i, ".");
	if (!(str = (char*)malloc(len * sizeof(char))))
		return (NULL);
	ft_bzero(str, len);
	ft_memcpy(str, line + i + 1, len - 1);
	return (str);
}
