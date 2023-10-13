/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:24:31 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/13 17:25:35 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void	ft_init_walls(t_cub *game)
{
	int	w;
	int	h;

	game->texture.north = mlx_xpm_file_to_image(game->mlx,
			game->texture.path_north, &w, &h);
	if (game->texture.north == (void *)0)
		ft_error_free("Error!\n[sprite/game/north_wall.xpm]\n", game);
	game->texture.south = mlx_xpm_file_to_image(game->mlx,
			game->texture.path_south, &w, &h);
	if (game->texture.south == (void *)0)
		ft_error_free("Error!\n[sprite/game/south_wall.xpm]\n", game);
	game->texture.east = mlx_xpm_file_to_image(game->mlx,
			game->texture.path_west, &w, &h);
	if (game->texture.east == (void *)0)
		ft_error_free("Error!\n[sprite/game/east_wall.xpm]\n", game);
	game->texture.west = mlx_xpm_file_to_image(game->mlx,
			game->texture.path_east, &w, &h);
	if (game->texture.west == (void *)0)
		ft_error_free("Error!\n[sprite/game/west_wall.xpm]\n", game);
}

void	ft_init_mlx(t_cub *game)
{
	game->mlx = mlx_init();
	if (game->mlx == (void *)0)
		ft_error_free("Error!\n[mlx_init() has failed]\n", game);
	game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "[cub3D]");
	if (game->window == (void *)0)
		ft_error_free("Error!\n[Failed to init Window]", game);
	game->img_map3d = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img3d.pixels = mlx_get_data_addr(game->img_map3d, &game->img3d.bpp,
			&game->img3d.size_line, &game->img3d.endian);
	ft_init_walls(game);
}
