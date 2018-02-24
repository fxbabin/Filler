/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 22:01:11 by fbabin            #+#    #+#             */
/*   Updated: 2018/02/24 01:08:54 by fbabin           ###   ########.fr       */
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
		SDL_SetRenderDrawColor(renderer, 15, 136, 21, SDL_ALPHA_OPAQUE);
	else if (c == 'X')
		SDL_SetRenderDrawColor(renderer, 29, 189, 36, SDL_ALPHA_OPAQUE);
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

char	*extract_name(char *line)
{
	int		i;
	int		len;
	i = ft_strlen(line);
	while (i > 0 && line[i] != '/')
	{
		ft_printf("%c\n", line[i]);
		i--;
	}
	len = ft_strcspn(line + i, ".");
	
	//ft_printf("%s\n", line + ft_strlen(line) - i);
	//ft_printf("%s\n", line + ft_strlen(line) - i);
	char	*str;

	if (!(str = (char*)malloc(len * sizeof(char))))
		return (NULL);
	ft_bzero(str, len);
	ft_memcpy(str, line + i + 1, len - 1);
	//ft_printf("voila %s\n", str);
	return (str);
}

int		main(void)
{
	t_env		env;
	t_board		b;
	t_grid		grid;
	TTF_Init();
	//TTF_Font *font = TTF_OpenFont("./bioshock.ttf", 200);
	//int		done;
	//$$$ exec p1 : [resources/players/carli.filler]
	char	*line;

	line = NULL;
	while (sget_next_line(0, &line) > 0)
	{
		if (!ft_strncmp(line, "$$$ exec p1", 11))
			b.ch1 = extract_name(line);
		else if (!ft_strncmp(line, "$$$ exec p2", 11))
			b.ch2 = extract_name(line);
		else if (!ft_strncmp(line, "Plateau", 7))
		{
			if (!check_plateau(line, &b))
				return (0);
			free(line);
			break ;
		}
	}
	ft_printf("name 1 : %s name 2 :%s\n", b.ch1, b.ch2);
	env.quit = 0;
	extract_grid(&grid, b.x, b.y);
	char	*str;

	if (!(str = (char*)malloc((b.x * b.y) * sizeof(char))))
		return (0);
	b.sc1 = 0;
	b.sc2 = 0;
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
				SDL_Surface *surface = TTF_RenderText_Blended(env.font, "Filler", color);
				SDL_Texture *Message = SDL_CreateTextureFromSurface(env.renderer, surface);
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


					SDL_Surface * surface1 = TTF_RenderText_Blended(env.font, b.ch1, color);
					SDL_Texture* Message1 = SDL_CreateTextureFromSurface(env.renderer, surface1);
					SDL_FreeSurface(surface1);
					SDL_Rect Message_rect1; //create a rect
					Message_rect1.x = 280;  //controls the rect's x coordinate 
					Message_rect1.y = 150; // controls the rect's y coordinte
					Message_rect1.w = 100; // controls the width of the rect
					Message_rect1.h = 50; // controls the height of the rect
					SDL_RenderCopy(env.renderer, Message1, NULL, &Message_rect1);
					SDL_DestroyTexture(Message1);

					SDL_Surface * surface2 = TTF_RenderText_Blended(env.font, "vs", color);
					SDL_Texture* Message2 = SDL_CreateTextureFromSurface(env.renderer, surface2);
					SDL_FreeSurface(surface2);
					SDL_Rect Message_rect2; //create a rect
					Message_rect2.x = 570;  //controls the rect's x coordinate 
					Message_rect2.y = 150; // controls the rect's y coordinte
					Message_rect2.w = 50; // controls the width of the rect
					Message_rect2.h = 50; // controls the height of the rect
					SDL_RenderCopy(env.renderer, Message2, NULL, &Message_rect2);
					SDL_DestroyTexture(Message2);

					SDL_Surface * surface3 = TTF_RenderText_Blended(env.font, b.ch2, color);
					SDL_Texture* Message3 = SDL_CreateTextureFromSurface(env.renderer, surface3);
					SDL_FreeSurface(surface3);
					SDL_Rect Message_rect3; //create a rect
					Message_rect3.x = 770;  //controls the rect's x coordinate 
					Message_rect3.y = 150; // controls the rect's y coordinte
					Message_rect3.w = 100; // controls the width of the rect
					Message_rect3.h = 50; // controls the height of the rect
					SDL_RenderCopy(env.renderer, Message3, NULL, &Message_rect3);
					SDL_DestroyTexture(Message3);

				SDL_SetRenderDrawColor(env.renderer, 193, 193, 193, SDL_ALPHA_OPAQUE);
				while (sget_next_line(0, &line) > 0)
				{
					//if (env.event.type == SDL_QUIT)
					//	end = 1;
					if (!ft_strncmp(line, "==", 2))
					{
						extract_score(&b, line);
						break ;
					}
					if (!ft_strncmp(line, "000", 3))
					{
						update_board(&b, line);
						update_grid(env.renderer, &grid, b.board);
						SDL_SetRenderDrawColor(env.renderer, 193, 193, 193, SDL_ALPHA_OPAQUE);
						draw_grid(env.renderer, &grid);
						SDL_RenderPresent(env.renderer);
						SDL_Delay(50);
						display_board(&b);
						//SDL_RenderPresent(env.renderer);
						break ;
					}
					free(line);
				}
				if (b.sc1 != 0)
				{
					update_grid(env.renderer, &grid, b.board);
					SDL_SetRenderDrawColor(env.renderer, 193, 193, 193, SDL_ALPHA_OPAQUE);
					draw_grid(env.renderer, &grid);
					char	*str;

					str = (b.sc1 >= b.sc2) ? ft_strjoinclr(b.ch1, " wins !", 3) : ft_strjoinclr(b.ch2, " wins !", 3);
					SDL_Surface * surface = TTF_RenderText_Blended(env.font, str, color);
					free(str);
					SDL_Texture* Message = SDL_CreateTextureFromSurface(env.renderer, surface);
					SDL_FreeSurface(surface);
					SDL_Rect Message_rect; //create a rect
					Message_rect.x = 430;  //controls the rect's x coordinate 
					Message_rect.y = 1050; // controls the rect's y coordinte
					Message_rect.w = 350; // controls the width of the rect
					Message_rect.h = 100; // controls the height of the rect
					SDL_RenderCopy(env.renderer, Message, NULL, &Message_rect);
					SDL_DestroyTexture(Message);
					
					str = ft_strjoin(b.ch1, " : ");
					str = ft_strjoinclr(str, ft_itoa(b.sc1), 2);
					SDL_Surface * surface4 = TTF_RenderText_Blended(env.font, str, color);
					free(str);
					SDL_Texture* Message4 = SDL_CreateTextureFromSurface(env.renderer, surface4);
					SDL_FreeSurface(surface4);
					SDL_Rect Message_rect4; //create a rect
					Message_rect4.x = 250;  //controls the rect's x coordinate 
					Message_rect4.y = 1000; // controls the rect's y coordinte
					Message_rect4.w = 150; // controls the width of the rect
					Message_rect4.h = 60; // controls the height of the rect
					SDL_RenderCopy(env.renderer, Message4, NULL, &Message_rect4);
					SDL_DestroyTexture(Message4);

					str = ft_strjoin(b.ch2, " : ");
					str = ft_strjoinclr(str, ft_itoa(b.sc2), 2);
					SDL_Surface * surface5 = TTF_RenderText_Blended(env.font, str, color);
					free(str);
					SDL_Texture* Message5 = SDL_CreateTextureFromSurface(env.renderer, surface5);
					SDL_FreeSurface(surface5);
					SDL_Rect Message_rect5; //create a rect
					Message_rect5.x = 800;  //controls the rect's x coordinate 
					Message_rect5.y = 1000; // controls the rect's y coordinte
					Message_rect5.w = 150; // controls the width of the rect
					Message_rect5.h = 60; // controls the height of the rect
					SDL_RenderCopy(env.renderer, Message5, NULL, &Message_rect5);
					SDL_DestroyTexture(Message5);
					SDL_RenderPresent(env.renderer);




					/*SDL_Surface * surface1 = TTF_RenderText_Blended(env.font, "toto", color);
					SDL_Texture* Message1 = SDL_CreateTextureFromSurface(env.renderer, surface);
					SDL_FreeSurface(surface1);
					SDL_Rect Message_rect1; //create a rect
					Message_rect1.x = 450;  //controls the rect's x coordinate 
					Message_rect1.y = 950; // controls the rect's y coordinte
					Message_rect1.w = 300; // controls the width of the rect
					Message_rect1.h = 100; // controls the height of the rect
					SDL_RenderCopy(env.renderer, Message1, NULL, &Message_rect1);
					SDL_DestroyTexture(Message1);
					SDL_RenderPresent(env.renderer);*/
					//env.quit = 1;
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
