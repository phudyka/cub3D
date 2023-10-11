/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3D_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:18:00 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/11 16:40:35 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void	calculate_ceiling(int x, t_cub *game)
{
	game->ceiling.floor_x += game->ceiling.step_x * (x - (WIDTH / 2));
	game->ceiling.floor_y += game->ceiling.step_y * (x - (WIDTH / 2));
	game->ceiling.text_x = (int)(game->ceiling.floor_x * HD) % HD;
	game->ceiling.text_y = (int)(game->ceiling.floor_y * HD) % HD;
}

void	draw_ceiling(int x, t_cub *game)
{
	int		i;
	int		y;
	int		color;

	y = -1;
	while (++y < game->ray.draw_start)
	{
		game->ceiling.row_dist = (0.5 * HEIGHT) / (HEIGHT / 2 - y);
		game->ceiling.step_x = game->ceiling.row_dist * (game->ray.dir_x
				+ game->ray.plane_x - (game->ray.dir_x
					- game->ray.plane_x)) / WIDTH;
		game->ceiling.step_y = game->ceiling.row_dist * (game->ray.dir_y
				+ game->ray.plane_y - (game->ray.dir_y
					- game->ray.plane_y)) / WIDTH;
		game->ceiling.floor_x = game->ray.player_x + game->ceiling.row_dist
			* game->ray.dir_x;
		game->ceiling.floor_y = game->ray.player_y + game->ceiling.row_dist
			* game->ray.dir_y;
		calculate_ceiling(x, game);
		color = ft_colorpix_ceifloo(game->ceiling.text_x,
				game->ceiling.text_y, game->texture.ceiling, game);
		i = (y * game->img3d.size_line) + (x * game->img3d.bpp / 8);
		*(unsigned int *)(game->img3d.pixels + i) = color;
	}
}

static void	calculate_floor(int x, t_cub *game)
{
	game->floor.floor_x += game->floor.step_x * (x - (WIDTH / 2));
	game->floor.floor_y += game->floor.step_y * (x - (WIDTH / 2));
	game->floor.text_x = (int)(game->floor.floor_x * HD) % HD;
	game->floor.text_y = (int)(game->floor.floor_y * HD) % HD;
}

void	draw_floor(int x, t_cub *game)
{
	int	i;
	int	y;
	int	color;

	y = game->ray.draw_end + 1;
	while (y < HEIGHT)
	{
		game->floor.row_dist = (0.5 * HEIGHT) / (y - HEIGHT / 2);
		game->floor.step_x = game->floor.row_dist * (game->ray.dir_x
				+ game->ray.plane_x - (game->ray.dir_x
					- game->ray.plane_x)) / WIDTH;
		game->floor.step_y = game->floor.row_dist * (game->ray.dir_y
				+ game->ray.plane_y - (game->ray.dir_y
					- game->ray.plane_y)) / WIDTH;
		game->floor.floor_x = game->ray.player_x
			+ game->floor.row_dist * game->ray.dir_x;
		game->floor.floor_y = game->ray.player_y
			+ game->floor.row_dist * game->ray.dir_y;
		calculate_floor(x, game);
		color = ft_colorpix_ceifloo(game->floor.text_x,
				game->floor.text_y, game->texture.floor, game);
		i = (y * game->img3d.size_line) + (x * game->img3d.bpp / 8);
		*(unsigned int *)(game->img3d.pixels + i) = color;
		y++;
	}
}
