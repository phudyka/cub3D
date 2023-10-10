/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:52:20 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/10 00:26:27 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void draw_ceiling(int x, t_cub *game)
{
	double posZ = 0.5 * HEIGHT; 
	int y = 0;

	while (y < game->ray.draw_start)
	{
		double p = HEIGHT / 2 - y; 
		double rowDistance = posZ / p;
		double floorStepX = rowDistance * (game->ray.dir_x + game->ray.plane_x - (game->ray.dir_x - game->ray.plane_x)) / WIDTH;
		double floorStepY = rowDistance * (game->ray.dir_y + game->ray.plane_y - (game->ray.dir_y - game->ray.plane_y)) / WIDTH;
		double floorX = game->ray.player_x + rowDistance * game->ray.dir_x;
		double floorY = game->ray.player_y + rowDistance * game->ray.dir_y;
		floorX += floorStepX * (x - (WIDTH / 2));
		floorY += floorStepY * (x - (WIDTH / 2));
		int textureX = (int)(floorX * HD) % HD;
		int textureY = (int)(floorY * HD) % HD;
		int color = ft_colorpix_ceifloo(textureX, textureY, game->texture.ceiling, game);
		int index_ceiling = (y * game->img3d.size_line) + (x * game->img3d.bpp / 8);
		*(unsigned int *)(game->img3d.pixels + index_ceiling) = color;
		y++;
	}
}

void draw_floor(int x, t_cub *game)
{
	double posZ = 0.5 * HEIGHT; 
	int y = game->ray.draw_end + 1;

	while (y < HEIGHT)
	{
		double p = y - HEIGHT / 2;
		double rowDistance = posZ / p;
		double floorStepX = rowDistance * (game->ray.dir_x + game->ray.plane_x - (game->ray.dir_x - game->ray.plane_x)) / WIDTH;
		double floorStepY = rowDistance * (game->ray.dir_y + game->ray.plane_y - (game->ray.dir_y - game->ray.plane_y)) / WIDTH;
		double floorX = game->ray.player_x + rowDistance * game->ray.dir_x;
		double floorY = game->ray.player_y + rowDistance * game->ray.dir_y;
		floorX += floorStepX * (x - (WIDTH / 2));
		floorY += floorStepY * (x - (WIDTH / 2));
		int textureX = (int)(floorX * HD) % HD;
		int textureY = (int)(floorY * HD) % HD;
		int color = ft_colorpix_ceifloo(textureX, textureY, game->texture.floor, game);
		int index_floor = (y * game->img3d.size_line) + (x * game->img3d.bpp / 8);
		*(unsigned int *)(game->img3d.pixels + index_floor) = color;
		y++;
	}
}

void	draw_texture(int x, void *texture, t_cub *game)
{
	int		i;
	int		y;
	int		color;
	int		texture_y;
	double	step;
	double	tex_pos;

	y = game->ray.draw_start;
	step = (double)HD / game->ray.wall_height;
	tex_pos = (y - HEIGHT / 2 + game->ray.wall_height / 2) * step;
	if (game->ray.side == 0)
		game->ray.tex_x = (int)(game->ray.wall_x * (double)HD);
	else
		game->ray.tex_x = HD - (int)(game->ray.wall_x * (double)HD) - 1;
	while (y < game->ray.draw_end)
	{
		texture_y = (int)tex_pos & (HD - 1);
		color = ft_colorpix(game->ray.tex_x, texture_y, texture, game);
		i = (y * game->img3d.size_line) + (x * game->img3d.bpp / 8);
		*(unsigned int *)(game->img3d.pixels + i) = color;
		tex_pos += step;
		y++;
	}
}

void	draw_texture_weapon(int x, int wx, int wy, void *texture, t_cub *game)
{
	int		i;
	int		y;
	int		color;
	int		texture_y;
	double	step;
	double	tex_pos;

	y = wx;
	step = (double)HD / game->ray.wall_height;
	tex_pos = (y - HEIGHT / 2 + game->ray.wall_height / 2) * step;
	if (game->ray.side == 0)
		game->ray.tex_x = (int)(game->ray.wall_x * (double)HD);
	else
		game->ray.tex_x = HD - (int)(game->ray.wall_x * (double)HD) - 1;
	while (y < wy)
	{
		texture_y = (int)tex_pos & (HD - 1);
		color = ft_colorpix(game->ray.tex_x, texture_y, texture, game);
		i = (y * game->img3d.size_line) + (x * game->img3d.bpp / 8);
		*(unsigned int *)(game->img3d.pixels + i) = color;
		tex_pos += step;
		y++;
	}
}

void render_3D(int x, t_cub *game)
{
	if (game->ray.side == 0)
		game->ray.distance = (game->ray.dist_x - game->ray.delta_x);
	else
		game->ray.distance = (game->ray.dist_y - game->ray.delta_y);
	game->ray.wall_height = (int)(HEIGHT / game->ray.distance);
	game->ray.draw_start = -(game->ray.wall_height) / 2 + HEIGHT / 2;
	if (game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	game->ray.draw_end = game->ray.wall_height / 2 + HEIGHT / 2;
	if (game->ray.draw_end >= HEIGHT)
		game->ray.draw_end = HEIGHT - 1;
	if (game->ray.side == 0)
		game->ray.wall_x = game->ray.player_y + game->ray.distance * game->ray.ray_y;
	else
		game->ray.wall_x = game->ray.player_x + game->ray.distance * game->ray.ray_x;
	game->ray.wall_x -= floor(game->ray.wall_x);
	game->ray.z_buffer[x] = game->ray.distance;
	choose_texture(x, game);
	draw_ceiling(x, game);
	draw_floor(x, game);
}