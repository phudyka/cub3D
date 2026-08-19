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
	int		y;
	char	*cpix;
	int		cbpp;
	int		csize;
	int		cend;

	cpix = mlx_get_data_addr(game->texture.ceiling, &cbpp, &csize, &cend);
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
		*(unsigned int *)(game->img3d.pixels + y * game->img3d.size_line
			+ x * game->img3d.bpp / 8) = *(unsigned int *)(cpix
				+ (int)game->ceiling.text_y * csize
				+ (int)game->ceiling.text_x * cbpp / 8);
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
	int		y;
	char	*fpix;
	int		fbpp;
	int		fsize;
	int		fend;

	fpix = mlx_get_data_addr(game->texture.floor, &fbpp, &fsize, &fend);
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
		*(unsigned int *)(game->img3d.pixels + y * game->img3d.size_line
			+ x * game->img3d.bpp / 8) = *(unsigned int *)(fpix
				+ (int)game->floor.text_y * fsize
				+ (int)game->floor.text_x * fbpp / 8);
		y++;
	}
}
