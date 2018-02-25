/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 00:37:21 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/25 01:03:14 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

SDL_Color		init_color(int r, int g, int b, int op)
{
	SDL_Color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = op;
	return (color);
}

SDL_Rect		init_rect(int x, int y, int w, int h)
{
	SDL_Rect	rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return (rect);
}

int				init_env(t_env *env)
{
	TTF_Init();
	env->quit = 0;
	env->font = TTF_OpenFont("./K.ttf", 200);
	env->white = init_color(255, 255, 255, 255);
	env->lred = init_color(243, 102, 77, 255);
	env->lgreen = init_color(29, 189, 36, 255);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (0);
	if (SDL_CreateWindowAndRenderer(1200, 1200, 0,
				&env->window, &env->renderer) != 0)
	{
		return (0);
	}
	return (1);
}

void			free_surfacetexture(t_env *env)
{
	SDL_FreeSurface(env->surface);
	SDL_DestroyTexture(env->mess);
}

void			close_sdlttf(t_env *env)
{
	if (env->renderer)
		SDL_DestroyRenderer(env->renderer);
	if (env->window)
		SDL_DestroyWindow(env->window);
	TTF_Quit();
	SDL_Quit();
}
