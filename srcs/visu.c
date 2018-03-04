/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 22:01:11 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/04 16:54:05 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	get_boardinfo(t_board *b)
{
	char	*line;

	line = NULL;
	while (sget_next_line(0, &line) > 0)
	{
		if (!ft_strncmp(line, "$$$ exec p1", 11))
			b->ch1 = extract_name(line);
		else if (!ft_strncmp(line, "$$$ exec p2", 11))
			b->ch2 = extract_name(line);
		else if (!ft_strncmp(line, "Plateau", 7))
		{
			if (!check_plateau(line, b))
				return ;
			free(line);
			break ;
		}
		free(line);
	}
	b->sc1 = 0;
	b->sc2 = 0;
}

void	main_end2(t_env *env, t_board *b)
{
	char	*tmp;
	char	strr[48];

	ft_bzero(&strr, 48);
	ft_strcat((char*)&strr, b->ch1);
	ft_strcat((char*)&strr, " : ");
	tmp = ft_itoa(b->sc1);
	ft_strcat((char*)&strr, tmp);
	ft_strdel(&tmp);
	env->surface = TTF_RenderText_Blended(env->font, strr, env->white);
	env->mess = SDL_CreateTextureFromSurface(env->renderer, env->surface);
	env->m_rect = init_rect(250, 1000, 150, 60);
	SDL_RenderCopy(env->renderer, env->mess, NULL, &env->m_rect);
	free_surfacetexture(env);
	ft_bzero(&strr, 48);
	ft_strcat((char*)&strr, b->ch2);
	ft_strcat((char*)&strr, " : ");
	tmp = ft_itoa(b->sc2);
	ft_strcat((char*)&strr, tmp);
	ft_strdel(&tmp);
	env->surface = TTF_RenderText_Blended(env->font, strr, env->white);
	env->mess = SDL_CreateTextureFromSurface(env->renderer, env->surface);
	env->m_rect = init_rect(800, 1000, 150, 60);
	SDL_RenderCopy(env->renderer, env->mess, NULL, &env->m_rect);
	free_surfacetexture(env);
}

void	main_end(t_env *env, t_board *b, t_grid *grid)
{
	char		*str;

	if (b->sc1 != 0 || b->sc2 != 0)
	{
		update_grid(env->renderer, grid, b->board);
		SDL_SetRenderDrawColor(env->renderer, 193, 193, 193, SDL_ALPHA_OPAQUE);
		draw_grid(env->renderer, grid);
		if (b->sc1 == b->sc2)
			str = ft_strdup("equality !");
		else
		{
			str = (b->sc1 > b->sc2) ? ft_strjoinclr(b->ch1, " wins !", 3) :
				ft_strjoinclr(b->ch2, " wins !", 3);
		}
		env->surface = TTF_RenderText_Blended(env->font, str, env->white);
		free(str);
		env->mess = SDL_CreateTextureFromSurface(env->renderer, env->surface);
		env->m_rect = init_rect(430, 1050, 350, 100);
		SDL_RenderCopy(env->renderer, env->mess, NULL, &env->m_rect);
		SDL_FreeSurface(env->surface);
		SDL_DestroyTexture(env->mess);
		main_end2(env, b);
		SDL_RenderPresent(env->renderer);
	}
}

void	main2(t_env *env, t_board *b)
{
	env->surface = TTF_RenderText_Blended(env->font, "Filler", env->white);
	env->mess = SDL_CreateTextureFromSurface(env->renderer, env->surface);
	env->m_rect = init_rect(500, 30, 200, 100);
	SDL_SetRenderDrawColor(env->renderer, 51, 51, 77, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(env->renderer);
	SDL_RenderCopy(env->renderer, env->mess, NULL, &env->m_rect);
	free_surfacetexture(env);
	env->surface = TTF_RenderText_Blended(env->font, b->ch1, env->lred);
	env->mess = SDL_CreateTextureFromSurface(env->renderer, env->surface);
	env->m_rect = init_rect(280, 150, 100, 50);
	SDL_RenderCopy(env->renderer, env->mess, NULL, &env->m_rect);
	free_surfacetexture(env);
	env->surface = TTF_RenderText_Blended(env->font, "vs", env->white);
	env->mess = SDL_CreateTextureFromSurface(env->renderer, env->surface);
	env->m_rect = init_rect(570, 150, 50, 50);
	SDL_RenderCopy(env->renderer, env->mess, NULL, &env->m_rect);
	free_surfacetexture(env);
	env->surface = TTF_RenderText_Blended(env->font, b->ch2, env->lgreen);
	env->mess = SDL_CreateTextureFromSurface(env->renderer, env->surface);
	env->m_rect = init_rect(770, 150, 100, 50);
	SDL_RenderCopy(env->renderer, env->mess, NULL, &env->m_rect);
	free_surfacetexture(env);
}

int		main(void)
{
	t_grid		grid;
	t_env		env;
	t_board		b;

	get_boardinfo(&b);
	extract_grid(&grid, b.x, b.y);
	if (!init_env(&env))
		return (0);
	while (!env.quit)
	{
		main2(&env, &b);
		SDL_SetRenderDrawColor(env.renderer, 193, 193, 193, SDL_ALPHA_OPAQUE);
		update_disp(&env, &b, &grid);
		main_end(&env, &b, &grid);
		while (SDL_PollEvent(&env.event))
		{
			if (env.event.type == SDL_QUIT)
				env.quit = 1;
		}
	}
	close_sdlttf(&env, &b);
	sleep(60);
	return (0);
}
