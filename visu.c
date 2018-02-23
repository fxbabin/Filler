/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 22:01:11 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/23 21:17:41 by fbabin           ###   ########.fr       */
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
		SDL_SetRenderDrawColor(renderer, 33, 154, 37, SDL_ALPHA_OPAQUE);
	else if (c == 'X')
		SDL_SetRenderDrawColor(renderer, 85, 218, 89, SDL_ALPHA_OPAQUE);
}

void	update_grid(SDL_Renderer *renderer, t_grid *grid, char *board)
{
	SDL_Rect rect;
	int		x;
	int		y;

	y = -1;
	(void)board;
	while (++y < grid->y)
	{
		x = -1;
		while (++x < grid->x)
		{
			set_color(renderer, board[(y * grid->x) + x]);
			//SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
			get_rectcoords(&rect, grid->x_coord + (x * grid->sq), grid->y_coord + (y * grid->sq), grid->sq);
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}

void	extract_grid(t_grid *grid, int x, int y)
{
	grid->max = (x > y) ? x : y;
	grid->sq = 800 / grid->max;
	grid->x_coord = (grid->max == x) ? 200 : 200 + ((y - x) / 2) * grid->sq ;
	grid->y_coord = (grid->max == y) ? 200 : 200 + ((x - y) / 2) * grid->sq ;
	grid->x = x;
	grid->y = y;
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

int		main(void)
{
	t_env		env;
	t_board		b;
	t_grid		grid;
	TTF_Init();
	//TTF_Font *font = TTF_OpenFont("./bioshock.ttf", 200);
	//int		done;
	char	*line;

	line = NULL;
	while (sget_next_line(0, &line) > 0)
	{
		if (!ft_strncmp(line, "Plateau", 7))
		{
			if (!check_plateau(line, &b))
				return (0);
			free(line);
			break ;
		}
	}
	env.quit = 0;
	extract_grid(&grid, b.x, b.y);
	char	*str;

	if (!(str = (char*)malloc((b.x * b.y) * sizeof(char))))
		return (0);
	ft_bchar(str, (b.x * b.y), '.');
	env.font = TTF_OpenFont("./bioshock.ttf", 200);
	//env.window = SDL_CreateWindow("Filler fbabin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	//int		i;
	//if (env.window && env.font)
	//	env.renderer = SDL_CreateRenderer(env.window,-1, SDL_RENDERER_ACCELERATED);
	
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		//SDL_Window* window = NULL;
		//SDL_Renderer* renderer = NULL;

		if (SDL_CreateWindowAndRenderer(1200, 1200, 0, &env.window, &env.renderer) == 0) {
			//SDL_bool done = SDL_FALSE;

			while (!env.quit) {
				//SDL_Event event;
			
				SDL_Color color = {255, 255, 255, 255};
				SDL_Surface * surface = TTF_RenderText_Blended(env.font, "Filler", color);
				SDL_Texture* Message = SDL_CreateTextureFromSurface(env.renderer, surface);
				SDL_FreeSurface(surface);
				SDL_Rect Message_rect; //create a rect
				Message_rect.x = 500;  //controls the rect's x coordinate 
				Message_rect.y = 30; // controls the rect's y coordinte
				Message_rect.w = 200; // controls the width of the rect
				Message_rect.h = 100; // controls the height of the rect
				//SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_SetRenderDrawColor(env.renderer, 51, 51, 77, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(env.renderer);
				SDL_RenderCopy(env.renderer, Message, NULL, &Message_rect);
				SDL_DestroyTexture(Message);
				SDL_SetRenderDrawColor(env.renderer, 193, 193, 193, SDL_ALPHA_OPAQUE);
				while (sget_next_line(0, &line) > 0)
				{
					/*if (env.event.type == SDL_QUIT)
						end = 1;
					if (!ft_strncmp(line, "==", 2))
					{
						extract_score(&b, line);
						break ;
					}*/
					if (!ft_strncmp(line, "000", 3))
					{
						update_board(&b, line);
						update_grid(env.renderer, &grid, b.board);
						SDL_SetRenderDrawColor(env.renderer, 193, 193, 193, SDL_ALPHA_OPAQUE);
						draw_grid(env.renderer, &grid);
						SDL_RenderPresent(env.renderer);
						SDL_Delay(100);
						//display_board(&b);
						//SDL_RenderPresent(env.renderer);
						break ;
					}
					free(line);
				}	
				//update_grid(env.renderer, &grid, str);
				//SDL_SetRenderDrawColor(env.renderer, 193, 193, 193, SDL_ALPHA_OPAQUE);
				//draw_grid(env.renderer, &grid);
				//SDL_RenderPresent(env.renderer);

				while (SDL_PollEvent(&env.event)) {
					if (env.event.type == SDL_QUIT) {
						env.quit = 1;
					}
				}
			}
		}

		if (env.renderer) {
			SDL_DestroyRenderer(env.renderer);
		}
		if (env.window) {
			SDL_DestroyWindow(env.window);
		}
	}
	TTF_Quit();
	SDL_Quit();
	return 0;
}

/*int		main(void)
{
	char		*line;
	t_board		b;
	int			boo;
	t_env		env;

	(void)env;
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		ft_dprintf(2, "Erreur d'initialisation de la SDL\n");
		exit (0);
	}
	if (TTF_Init() == -1)
	{
		ft_dprintf(2, "Erreur d'initialisation de la SDL\n");
		exit (0);
	}
	//if (!(env.texture = 

	boo = 0;
	line = NULL;
	while (sget_next_line(0, &line) > 0)
	{
		if (!boo && !ft_strncmp(line, "Plateau", 7))
		{
			boo = 1;
			if (!check_plateau(line, &b))
				return (0);
			free(line);
			break ;
		}
	}
	//if (!(env.texture
	//env.rect = init_rect();
	env.font = TTF_OpenFont("./bioshock.ttf", 14);
	env.window = SDL_CreateWindow("Filler 42 - fbabin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	//int		i;
	if (env.window && env.font)
		env.renderer = SDL_CreateRenderer(env.window,-1, SDL_RENDERER_ACCELERATED);
	SDL_RenderClear(env.renderer);
	SDL_RenderPresent(env.renderer);
	SDL_Quit();
	TTF_Quit();
	while (!end && sget_next_line(0, &line) > 0)
	{
		if (env.event.type == SDL_QUIT)
			end = 1;
		if (!ft_strncmp(line, "==", 2))
		{
			extract_score(&b, line);
			break ;
		}
		if (!ft_strncmp(line, "000", 3))
		{
			update_board(&b, line);
			display_board(&b);
			SDL_RenderPresent(env.renderer);
			//return (0);
		}
		free(line);
	}

	SDL_DestroyWindow(env.window);
	ft_printf("score 1: %d\nscore 2: %d\n", b.sc1, b.sc2);
	//free(line);
	return (0);
}*/
