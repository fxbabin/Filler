# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/20 22:51:42 by fbabin            #+#    #+#              #
#    Updated: 2018/02/20 23:01:14 by fbabin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILLER			= fbabin.filler

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra

_SRCS			=	filler.c \

_LIBFT			=	libft.a
HEADER_DIR		=	includes
HEADER			=	$(HEADER_DIR)/filler.h

SRCS_DIR		= .
LIB_DIR			= libft
SRCS			= $(addprefix $(SRCS_DIR)/, $(_SRCS))
LIBFT			= $(addprefix $(LIB_DIR)/, $(_LIBFT))
OBJS			= $(SRCS:.c=.o)

#COLORS
_CYAN=\x1b[36m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_END=\x1b[0m

all: $(FILLER)

$(FILLER): $(HEADER) $(LIBFT) $(OBJS)
		@$(CC) $(CFLAGS) -o $(FILLER) $(OBJS) -L$(LIB_DIR) -lft -I $(HEADER_DIR)
		@echo "$(FILLER) : $(_GREEN)Done$(_END)"

$(LIBFT):
		@make -C $(LIB_DIR)

%.o : %.c
		@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER_DIR)

clean:
		@make fclean -C $(LIB_DIR)
		@/bin/rm -f $(OBJS)
		@echo "filler clean : $(_GREEN)Done$(_END)"

fclean: clean
		@/bin/rm -f $(FILLER)
		@echo "filler fclean : $(_GREEN)Done$(_END)"

re:
		@make fclean
		@make

.PHONY: all clean fclean re
