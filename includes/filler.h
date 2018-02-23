/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 22:58:23 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/23 16:08:39 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

/*
** --------------------------------- INCLUDES -------------------------------
*/

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "/Users/fbabin/.brew/include/SDL2/SDL.h"
# include "/Users/fbabin/.brew/include/SDL2/SDL_ttf.h"

# define WIDTH 1920
# define HEIGHT 1380

/*
** -------------------------------- STRUCTURES -------------------------------
*/

typedef struct		s_board
{
	char			*board;
	int				len;
	int				x;
	int				y;
	int				pos;
	int				sc1;
	int				sc2;
}					t_board;

typedef	struct		s_grid
{
	int				max;
	int				x;
	int				y;
	int				x_coord;
	int				y_coord;
	int				sq;
}					t_grid;

typedef struct		s_env
{
	SDL_Window		*window;
	SDL_Surface		*surface;
	SDL_Renderer	*renderer;
	SDL_Event		event;
	SDL_Texture		**texture;
	SDL_Rect		**rect;
	TTF_Font		*font;
	int				quit;
}					t_env;
/*
** ----------------------------------------------------------------------------
** ---------------------------------- SOURCES ---------------------------------
** ----------------------------------------------------------------------------
*/

#endif
