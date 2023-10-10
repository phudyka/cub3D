/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:12:44 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/10 01:27:00 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	init_sprite(t_cub *game)
{
	game->num_sprites = 2;
	game->sprite = malloc(sizeof(t_sprite) * game->num_sprites);
	game->sprite[0].x = 10.0;
	game->sprite[0].y = 10.0;
	game->sprite[0].width = 1260;
	game->sprite[0].height = 1656;
	game->sprite[1].x = 4.0;
	game->sprite[1].y = 4.0;
	game->sprite[1].width = 1260;
	game->sprite[1].height = 1656;
}

static void	ft_init_walls(t_cub *game)
{
	int	w;
	int	h;

	game->texture.north = mlx_xpm_file_to_image(game->mlx, N_WALL, &w, &h);
	if (game->texture.north == (void *)0)
		ft_error_free("\nError ! [utils/sprite/game/north_wall.xpm]]\n", game);
	game->texture.south = mlx_xpm_file_to_image(game->mlx, S_WALL, &w, &h);
	if (game->texture.south == (void *)0)
		ft_error_free("\nError ! [utils/sprite/game/south_wall.xpm]]\n", game);
	game->texture.east = mlx_xpm_file_to_image(game->mlx, E_WALL, &w, &h);
	if (game->texture.east == (void *)0)
		ft_error_free("\nError ! [utils/sprite/game/east_wall.xpm]]\n", game);
	game->texture.west = mlx_xpm_file_to_image(game->mlx, W_WALL, &w, &h);
	if (game->texture.west == (void *)0)
		ft_error_free("\nError ! [utils/sprite/game/west_wall.xpm]]\n", game);
	game->texture.floor = mlx_xpm_file_to_image(game->mlx, FLOOR, &w, &h);
	if (game->texture.floor == (void *)0)
		ft_error_free("\nError ! [utils/sprite/game/floor.xpm]]\n", game);
	game->texture.ceiling = mlx_xpm_file_to_image(game->mlx, CEILING, &w, &h);
	if (game->texture.ceiling == (void *)0)
		ft_error_free("\nError ! [utils/sprite/game/ceiling.xpm]]\n", game);
}

static void	ft_init_assets(t_cub *game)
{
	int	h;
	int	w;

	game->texture.door = mlx_xpm_file_to_image(game->mlx, DOOR, &w, &h);
	if (game->texture.door == (void *)0)
		ft_error_free("\nError ! [utils/sprite/game/door.xpm]]\n", game);
	game->texture.weapon1 = mlx_xpm_file_to_image(game->mlx, WEAPON1, &w, &h);
	if (game->texture.weapon1 == (void *)0)
		ft_error_free("\nError ! [utils/sprite/game/weapon1.xpm]]\n", game);
}

static void ft_texture_sprite(t_cub *game)
{
    int w;
    int h;

    game->texture.target = mlx_xpm_file_to_image(game->mlx, TARGET, &w, &h);
    if (game->texture.target == (void *)0)
        ft_error_free("\nError ! [utils/sprite/map/cible.xpm]]\n", game);
}

void	ft_init_mlx(t_cub *game)
{
	game->mlx = mlx_init();
	if (game->mlx == (void *)0)
		ft_error_free("\nError! [mlx_init() has failed]\n", game);
	game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "[cub3D]");
	if (game->window == (void *)0)
		ft_error_free("\nError! [Failed to init Window]", game);
	game->img_map2d = mlx_new_image(game->mlx,
			game->engine.width * SPRITE, game->engine.height * SPRITE);
	game->img2d.pixels = mlx_get_data_addr(game->img_map2d,
			&game->img2d.bpp, &game->img2d.size_line, &game->img2d.endian);
	game->img_map3d = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img3d.pixels = mlx_get_data_addr(game->img_map3d, &game->img3d.bpp,
			&game->img3d.size_line, &game->img3d.endian);
	game->weapon_3d = mlx_new_image(game->mlx, 500, 456);
	game->weapon.pixels = mlx_get_data_addr(game->weapon_3d, &game->weapon.bpp,
			&game->weapon.size_line, &game->weapon.endian);
	ft_init_walls(game);
	ft_init_assets(game);
	ft_texture_sprite(game);
}

static void ft_texture_index(t_cub *game)
{
	if (game->ray.side == 1)
	{
		if (game->ray.ray_y < 0)
			game->texture.direction = 'N';
		else 
			game->texture.direction = 'S';
	}
	else
	{
		if (game->ray.ray_x < 0)
			game->texture.direction = 'W';
		else 
			game->texture.direction = 'E';
	}
}

void    choose_texture(int x, t_cub *game)
{
	ft_texture_index(game);
	if (game->texture.direction == 'N')
		draw_texture(x, game->texture.north, game);
	else if (game->texture.direction == 'S')
		draw_texture(x, game->texture.south, game);
	else if (game->texture.direction == 'W')
		draw_texture(x, game->texture.west, game);
	else if (game->texture.direction == 'E')
		draw_texture(x, game->texture.east, game);
	else if (game->texture.direction == 'D')
		draw_texture(x, game->texture.door, game);
}