# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/05 15:51:03 by phudyka           #+#    #+#              #
#    Updated: 2023/09/28 01:12:11 by dtassel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= cub3D

CC 				= gcc

CFLAGS 			= -Wall -Wextra -Werror

SRC				= src/main/main.c src/parse/parser.c src/main/game.c 	\
				  src/main/exit.c src/main/render.c 					\
				  src/parse/parse_texture.c src/main/draw3D.c 			\
				  src/parse/valid_conf.c src/moves/move.c 			    \
				  src/moves/player_move.c src/moves/directions.c 		\
				  src/parse/get_map.c  src/parse/check_map.c            \
				  src/moves/rotate.c src/main/utils.c 					\
				  src/main/draw.c                                       \

OBJ_DIR 		= obj
OBJ 			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

LIBFT_DIR		= utils/libft
LIBFT			= $(LIBFT_DIR)/libft.a

GNL_DIR			= utils/get_next_line
GNL				= get_next_line.c get_next_line_utils.c
GNL_OBJS        = $(addprefix $(GNL_DIR)/, $(GNL:.c=.o))

LFLAGS 			= -lmlx -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(OBJ) $(GNL_OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(GNL_OBJS) $(LIBFT) $(LFLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re