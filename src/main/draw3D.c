/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:52:20 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/14 09:20:07 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	draw_texture(int x, void *texture, t_cub *game)
{
	int		i;
	int		y;
	int		color;
	int		texture_y;
	double	tex_pos;

	y = game->ray.draw_start;
	tex_pos = (y - HEIGHT / 2 + game->ray.wall_height / 2)
		* (double)HD / game->ray.wall_height;
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
		tex_pos += (double)HD / game->ray.wall_height;
		y++;
	}
}

static void	draw_column(int x, int flag, int color, t_cub *game)
{
	int	i;
	int	end;
	int	start;

	if (flag)
	{
		start = game->ray.draw_end;
		end = HEIGHT;
	}
	else
	{
		start = 0;
		end = game->ray.draw_start;
	}
	while (start < end)
	{
		i = (start * game->img3d.size_line) + (x * game->img3d.bpp / 8);
		*(unsigned int *)(game->img3d.pixels + i) = color;
		start++;
	}
}

void	render3d(int x, t_cub *game)
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
		game->ray.wall_x = game->ray.player_y
			+ game->ray.distance * game->ray.ray_y;
	else
		game->ray.wall_x = game->ray.player_x
			+ game->ray.distance * game->ray.ray_x;
	game->ray.wall_x -= floor(game->ray.wall_x);
	game->ray.z_buffer[x] = game->ray.distance;
	draw_column(x, 0, game->ceiling_col.c_color, game);
	choose_texture(x, game);
	draw_column(x, 1, game->floor_col.f_color, game);
}
