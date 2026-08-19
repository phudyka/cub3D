/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:52:20 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/13 08:26:19 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static inline unsigned int	darken(unsigned int c, float keep)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = ((c >> 16) & 0xFF) * keep;
	g = ((c >> 8) & 0xFF) * keep;
	b = (c & 0xFF) * keep;
	return ((r << 16) | (g << 8) | b);
}

void	draw_texture(int x, void *texture, t_cub *game)
{
	char			*tpix;
	int				tbpp;
	int				tsize;
	int				tend;
	double			tex_pos;
	double			step;
	float			fog;
	float			keep;
	int				y;
	unsigned int	color;

	y = game->ray.draw_start;
	step = (double)HD / game->ray.wall_height;
	tex_pos = (y - HEIGHT / 2 + game->ray.wall_height / 2) * step;
	if (game->ray.side == 0)
		game->ray.tex_x = (int)(game->ray.wall_x * (double)HD);
	else
		game->ray.tex_x = HD - (int)(game->ray.wall_x * (double)HD) - 1;
	fog = wall_fog(game->ray.distance);
	keep = 1.0f - fog;
	tpix = mlx_get_data_addr(texture, &tbpp, &tsize, &tend);
	while (y < game->ray.draw_end)
	{
		if (fog >= 1.0f)
			color = 0;
		else
		{
			color = *(unsigned int *)(tpix + ((int)tex_pos & (HD - 1))
					* tsize + (int)game->ray.tex_x * tbpp / 8);
			if (fog > 0.0f)
				color = darken(color, keep);
		}
		*(unsigned int *)(game->img3d.pixels + y * game->img3d.size_line
			+ x * game->img3d.bpp / 8) = color;
		tex_pos += step;
		y++;
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
	choose_texture(x, game);
	draw_ceiling(x, game);
	draw_floor(x, game);
}
