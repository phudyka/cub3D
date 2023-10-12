# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/05 15:51:03 by phudyka           #+#    #+#              #
#    Updated: 2023/10/12 10:42:23 by phudyka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom du binaire
NAME            = cub3D

# Compilateur
CC              = gcc -g -o

# Flags de compilation
CFLAGS          = -Wall -Wextra -Werror -I./minilibx-linux 

# Source files et Object files
SRC             = src/main/main.c src/parse/parser.c src/main/game.c 	\
                  src/main/exit.c src/main/render.c 					\
                  src/parse/parse_texture.c src/main/draw3D.c 			\
                  src/parse/valid_conf.c src/moves/move.c 				\
                  src/moves/player_move.c src/moves/directions.c 		\
                  src/parse/get_map.c  src/parse/check_map.c 			\
                  src/moves/rotate.c src/main/utils.c 					\
                  src/main/draw.c src/main/texture.c 					\
				  src/main/draw_weapon.c src/main/draw_sprite.c 		\
				  src/moves/mouse.c src/main/input.c 					\
				  src/main/weapon.c	src/main/free.c						\
				  src/main/draw3D_utils.c src/main/texture_utils.c 		\
				  src/main/draw_sprite_utils.c							\
				  src/parse/check_map_utils.c src/parse/parser_utils.c	\

OBJ_DIR         = obj
OBJ             = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Bibliothèque Libft
LIBFT_DIR       = utils/libft
LIBFT           = $(LIBFT_DIR)/libft.a

# Get Next Line
GNL_DIR         = utils/get_next_line
GNL             = get_next_line.c get_next_line_utils.c
GNL_OBJS        = $(addprefix $(GNL_DIR)/, $(GNL:.c=.o))

# Minilibx
MLX_DIR         = minilibx-linux
MLX             = libmlx.a

# Flags de linkage
LFLAGS          = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

# Règles

all: $(NAME)

$(NAME): $(OBJ) $(GNL_OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(GNL_OBJS) $(LIBFT) $(LFLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@  # Inclusion du header de minilibx

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re