# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/20 22:51:42 by fbabin            #+#    #+#              #
#    Updated: 2018/02/25 00:59:49 by fbabin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILLER			= fbabin.filler
VISU			= visu

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -g3

#_SRCS			= \

_F_SRCS			=	filler.c
_V_SRCS			=	visu.c visu_init.c visu_gridboard.c visu_2.c visu_utils.c

_LIBFT			=	libft.a
HEADER_DIR		=	includes
HEADER			=	$(HEADER_DIR)/filler.h
SDL_HEADER_DIR	=	~/.brew/include/SDL2/
SDL_LIB_DIR		=	~/.brew/lib

SRCS_DIR		= .
LIB_DIR			= libft
F_SRCS			= $(addprefix $(SRCS_DIR)/, $(_F_SRCS))
V_SRCS			= $(addprefix $(SRCS_DIR)/, $(_V_SRCS))
LIBFT			= $(addprefix $(LIB_DIR)/, $(_LIBFT))
F_OBJS			= $(F_SRCS:.c=.o)
V_OBJS			= $(V_SRCS:.c=.o)

#COLORS
_CYAN=\x1b[36m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_END=\x1b[0m

all: $(FILLER) $(VISU)

$(FILLER): $(HEADER) $(LIBFT) $(F_OBJS)
		@$(CC) $(CFLAGS) -o $(FILLER) $(F_OBJS) -L$(LIB_DIR) -lft -I $(HEADER_DIR)
		@echo "$(FILLER) : $(_GREEN)Done$(_END)"

$(VISU): $(HEADER) $(LIBFT) $(V_OBJS)
		@$(CC) $(CFLAGS) -o $(VISU) $(V_OBJS) -L$(LIB_DIR) -lft -L $(SDL_LIB_DIR) -lSDL2 -lSDL2_ttf -I $(HEADER_DIR)
		@echo "$(VISU) : $(_GREEN)Done$(_END)"

$(LIBFT):
		@make -C $(LIB_DIR)

%.o : %.c
		@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER_DIR)

clean:
		@make fclean -C $(LIB_DIR)
		@/bin/rm -f $(F_OBJS) $(V_OBJS)
		@echo "filler clean : $(_GREEN)Done$(_END)"

fclean: clean
		@/bin/rm -f $(FILLER) $(VISU)
		@echo "filler fclean : $(_GREEN)Done$(_END)"

re:
		@make fclean
		@make

.PHONY: all clean fclean re
