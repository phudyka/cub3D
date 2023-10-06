/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:52:20 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/06 00:05:48 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void     draw_column(int x, int y_start, int y_end, int color, t_cub *game)
{
		int     y;
		int     dst_index;

		y = y_start;
		while (y < y_end)
		{
				dst_index = (y * game->img3d.size_line) + (x * game->img3d.bpp / 8);
				*(unsigned int *)(game->img3d.pixels + dst_index) = color;
				y++;
		}
} 


void draw_ceiling(int x, int draw_end, t_cub *game)
{
	double posZ = 0.5 * HEIGHT; 
	int y = 0;

	while (y < draw_end)
	{
		double p = HEIGHT / 2 - y; 
		double rowDistance = posZ / p;
		double floorStepX = rowDistance * (game->ray.dir_x + game->ray.plane_x - (game->ray.dir_x - game->ray.plane_x)) / WIDTH;
		double floorStepY = rowDistance * (game->ray.dir_y + game->ray.plane_y - (game->ray.dir_y - game->ray.plane_y)) / WIDTH;
		double floorX = game->ray.player_x + rowDistance * game->ray.dir_x;
		double floorY = game->ray.player_y + rowDistance * game->ray.dir_y;
		floorX += floorStepX * (x - (WIDTH / 2));
		floorY += floorStepY * (x - (WIDTH / 2));
		int textureX = (int)(floorX * 256) % 256;
		int textureY = (int)(floorY * 256) % 256;
		int color = ft_colorpix_ceifloo(textureX, textureY, game->texture.ceiling, game);
		int index_ceiling = (y * game->img3d.size_line) + (x * game->img3d.bpp / 8);
		*(unsigned int *)(game->img3d.pixels + index_ceiling) = color;

		y++;
	}
}

void draw_floor(int x, int draw_end, t_cub *game)
{
	double posZ = 0.5 * HEIGHT; 
	int y = draw_end + 1;

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
		int textureX = (int)(floorX * 256) % 256;
		int textureY = (int)(floorY * 256) % 256;
		int color = ft_colorpix_ceifloo(textureX, textureY, game->texture.floor, game);
		int index_floor = (y * game->img3d.size_line) + (x * game->img3d.bpp / 8);
		*(unsigned int *)(game->img3d.pixels + index_floor) = color;

		y++;
	}
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

static void draw_texture(int column, int draw_start, int draw_end, void *texture, t_cub *game)
{
	int i;
	int y;
	int color;
	int texture_y;
	double step;
	double tex_pos;

	y = draw_start;
	step = (double)HD / game->ray.wall_height;
	tex_pos = (y - HEIGHT / 2 + game->ray.wall_height / 2) * step;
	if (game->ray.side == 0)
		game->ray.tex_x = (int)(game->ray.wall_x * (double)HD);
	else
		game->ray.tex_x = HD - (int)(game->ray.wall_x * (double)HD) - 1;

	while (y < draw_end)
	{
		texture_y = (int)tex_pos & (HD - 1);
		color = ft_colorpix(game->ray.tex_x, texture_y, texture, game);
		i = (y * game->img3d.size_line) + (column * game->img3d.bpp / 8);
		*(unsigned int *)(game->img3d.pixels + i) = color;
		tex_pos += step;
		y++;
	}
}

static void    choose_texture(int column, int drawStart, int drawEnd, t_cub *game)
{
	ft_texture_index(game);
	if (game->texture.direction == 'N')
		draw_texture(column, game->ray.draw_start, game->ray.draw_end, game->texture.north, game);
	else if (game->texture.direction == 'S')
		draw_texture(column, game->ray.draw_start, game->ray.draw_end, game->texture.south, game);
	else if (game->texture.direction == 'W')
		draw_texture(column, game->ray.draw_start, game->ray.draw_end, game->texture.west, game);
	else if (game->texture.direction == 'E')
		draw_texture(column, game->ray.draw_start, game->ray.draw_end, game->texture.east, game);
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
	choose_texture(x, game->ray.draw_start, game->ray.draw_end, game);
	draw_ceiling(x, game->ray.draw_start, game);
	draw_floor(x, game->ray.draw_end, game);
	//draw_column(x, 0, game->ray.draw_start, GREY, game);
	//draw_texture(x, 0, game->ray.drawStart, CEILING, game);
	//draw_column(x, game->ray.draw_end, HEIGHT, BROWN, game);
}