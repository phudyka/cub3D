# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/05 15:51:03 by phudyka           #+#    #+#              #
#    Updated: 2023/10/13 14:17:34 by phudyka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom du binaire
NAME            = cub3D
BONUS_NAME      = cub3D_bonus

# Compilateur
CC              = gcc

# Flags de compilation
CFLAGS          = -Wall -Wextra -Werror -O3 -march=native -funroll-loops -flto -ffast-math -pthread -Wno-incompatible-pointer-types -Wno-unused-result -I$(MLX_DIR)

# Source files (single tree; bonus features behind -D BONUS)
SRC             = src/main/main.c src/parse/parser.c src/main/game.c 	\
                  src/main/exit.c src/main/render.c 					\
                  src/parse/parse_texture.c src/main/draw3D.c 			\
                  src/parse/valid_conf.c src/moves/move.c 				\
                  src/moves/player_move.c src/moves/directions.c 		\
                  src/parse/get_map.c src/parse/check_map.c 			\
                  src/moves/rotate.c src/main/utils.c 					\
                  src/main/draw.c src/main/texture.c 					\
                  src/main/input.c src/main/free.c 						\
                  src/main/texture_utils.c 								\
                  src/parse/check_map_utils.c src/parse/parser_utils.c \
                  src/utils/str.c src/utils/audio.c

# Compiled only into the bonus binary
BONUS_SRC       = src/main/draw_weapon.c src/main/draw_sprite.c 		\
                  src/main/draw_sprite_utils.c src/main/weapon.c 		\
                  src/moves/mouse.c src/main/draw3D_utils.c

OBJ_DIR         = obj
OBJ             = $(addprefix $(OBJ_DIR)/std/, $(SRC:.c=.o))
BONUS_OBJ       = $(addprefix $(OBJ_DIR)/bonus/, $(SRC:.c=.o)) \
                  $(addprefix $(OBJ_DIR)/bonus/, $(BONUS_SRC:.c=.o))

# Get_Next_Line
GNL_DIR         = utils/get_next_line
GNL             = get_next_line.c
GNL_OBJS        = $(addprefix $(GNL_DIR)/, $(GNL:.c=.o))

# Minilibx
MLX_DIR         = mlx
MLX             = libmlx.a

# Flags de linkage
LFLAGS          = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

# Règles
all: $(NAME)

$(NAME): $(OBJ) $(GNL_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(GNL_OBJS) $(LFLAGS)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(GNL_OBJS)
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJ) $(GNL_OBJS) $(LFLAGS)

$(OBJ_DIR)/std/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/bonus/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -D BONUS -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(GNL_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean bonus re
