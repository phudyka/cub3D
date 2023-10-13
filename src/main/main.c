/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:42:03 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/13 08:25:31 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void	ft_init_keys(t_cub *game)
{
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.right = 0;
	game->keys.left = 0;
}

static void	ft_init_texture(t_cub *game)
{
	game->floor_col.r = 0;
	game->floor_col.g = 0;
	game->floor_col.b = 0;
	game->ceiling_col.r = 0;
	game->ceiling_col.g = 0;
	game->ceiling_col.b = 0;
	game->texture.north = NULL;
	game->texture.south = NULL;
	game->texture.east = NULL;
	game->texture.west = NULL;
	game->texture.ceiling = NULL;
	game->texture.floor = NULL;
	game->texture.door = NULL;
	game->texture.weapon1 = NULL;
	game->texture.reload0 = NULL;
	game->texture.reload1 = NULL;
	game->texture.shoot0 = NULL;
	game->texture.shoot1 = NULL;
	game->texture.path_north = NULL;
	game->texture.path_south = NULL;
	game->texture.path_west = NULL;
	game->texture.path_east = NULL;
}

static void	ft_init_engine(t_cub *game)
{
	game->engine.total_moves = 0;
	game->engine.rotate = 0;
	game->engine.move_x = 0.0;
	game->engine.move_y = 0.0;
	game->engine.cub = NULL;
	game->engine.map = NULL;
	game->engine.coord = 0;
	game->engine.width = 0;
	game->engine.height = 0;
	game->engine.ammo = 31;
	game->engine.shoot = 0;
	game->engine.reload = 0;
	game->engine.half = 0;
	game->engine.time_shoot = 0.0;
	game->engine.time_reload = 0.0;
	game->engine.door = NULL;
	game->engine.cooldown = 0.0;
}

static void	ft_init_game(t_cub *game)
{
	game->mlx = NULL;
	game->window = NULL;
	game->mini = 0;
	game->count_color_c = 0;
	game->count_color_f = 0;
	game->ray.dir_x = 0.0;
	game->ray.dir_x = 0.0;
	game->ray.player_x = 0.0;
	game->ray.player_y = 0.0;
	game->num_sprites = 0;
	game->texture.repop = 0;
	ft_init_engine(game);
	ft_init_texture(game);
	ft_init_keys(game);
}

int	main(int argc, char **argv)
{
	t_cub	*game;

	game = malloc(sizeof(t_cub));
	if (!game)
		ft_error("\nError! [Cub3D Malloc Failed]\n");
	ft_init_game(game);
	if (master_parser(game, argc, argv))
		ft_error("\nError! [Bad arguments]\n");
	print_cub();
	ft_init_direction(game);
	ft_cub(game);
	game_over(game);
	return (0);
}
