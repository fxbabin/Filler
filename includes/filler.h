/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 22:58:23 by fbabin            #+#    #+#             */
/*   Updated: 2018/03/01 00:49:43 by fbabin           ###   ########.fr       */
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

typedef struct		s_dot
{
	int				x;
	int				y;
	struct s_dot	*next;
}					t_dot;

typedef struct		s_filler
{
	char			**board;
	char			**piece;
	int				**colors;
	int				x;
	int				y;
	int				p_x;
	int				p_y;
	char			player;
	char			adv;
}					t_filler;

typedef struct		s_board
{
	char			*board;
	int				len;
	int				x;
	int				y;
	int				pos;
	int				sc1;
	int				sc2;
	char			*ch1;
	char			*ch2;
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
	SDL_Texture		*mess;
	SDL_Rect		m_rect;
	SDL_Color		white;
	SDL_Color		lred;
	SDL_Color		lgreen;
	TTF_Font		*font;
	int				quit;
}					t_env;
/*
** ----------------------------------------------------------------------------
** ---------------------------------- SOURCES ---------------------------------
** ----------------------------------------------------------------------------
*/

void				get_dots(t_filler *f, int nb);
int					get_piece2(t_filler *f);
int					get_piece(t_filler *f);
int					get_board2(t_filler *f);
int					get_board(t_filler *f);
int					get_player(t_filler *f);



t_dot				*ft_dotlstcreate(int x, int y);
void				ft_dotlstpushback(t_dot **begin_list, int x, int y);
void				ft_dotlstpushfront(t_dot **begin_list, int x, int y);
/*
** ---------------------------------- HEATMAP -------------------------------
*/

void				get_neighbours(t_filler *f, t_dot **visited, t_dot **ntv, t_dot *v);
void				dd(t_filler *f, t_list **visited, t_list **ntv, int i);
void				set_colors(t_filler *f, int i);
void				da(t_filler *f, t_list **visited, t_list **ntv);
void				get_heatmap(t_filler *f);

/*
** ---------------------------------- DISPLAY -------------------------------
*/

void				ft_display_board(t_filler *f);
void				ft_lstdumpi(t_list **list);
void				ft_display_piece(t_filler *f);

/*
** ---------------------------------- UTILS ----------------------------------
*/

int					tab_size(char **tab);
int					ft_lstinpos(t_dot **begin_list, int x, int y);

/*
** -------------------------------- VISU_FILLER -------------------------------
*/

SDL_Color			init_color(int r, int g, int b, int op);
SDL_Rect			init_rect(int x, int y, int w, int h);
int					init_env(t_env *env);
void				free_surfacetexture(t_env *env);
void				close_sdlttf(t_env *env);

void				update_board(t_board *b, char *line);
void				update_grid(SDL_Renderer *renderer, t_grid *grid,
						char *board);
void				draw_grid(SDL_Renderer *renderer, t_grid *grid);
void				extract_grid(t_grid *grid, int x, int y);
void				update_disp(t_env *env, t_board *b, t_grid *grid);

void				extract_line(t_board *b, char *line);
void				extract_score(t_board *b, char *line);
void				get_rectcoords(SDL_Rect *rect, int x, int y, int sq);
void				set_color(SDL_Renderer *renderer, char c);
char				*extract_name(char *line);

void				ft_bchar(void *s, size_t n, char c);
int					check_plateau(char *line, t_board *b);
void				display_board(t_board *b);

#endif
