/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 00:57:47 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/04 20:33:38 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	the_norm(t_env *env)
{
	env->mess = SDL_CreateTextureFromSurface(env->renderer, env->surface);
	env->m_rect = init_rect(800, 1000, 150, 60);
	SDL_RenderCopy(env->renderer, env->mess, NULL, &env->m_rect);
	free_surfacetexture(env);
}

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
