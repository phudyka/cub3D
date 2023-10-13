/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:36:48 by dtassel           #+#    #+#             */
/*   Updated: 2023/10/12 14:28:44 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void	mix_colors(unsigned int *color, float fog_factor,
		unsigned int fog_color, t_cub *game)
{
	game->mix.og_r = (*color >> 16) & 0xFF;
	game->mix.og_g = (*color >> 8) & 0xFF;
	game->mix.og_b = *color & 0xFF;
	game->mix.fog_r = (fog_color >> 16) & 0xFF;
	game->mix.fog_g = (fog_color >> 8) & 0xFF;
	game->mix.fog_b = fog_color & 0xFF;
	game->mix.new_r = (1 - fog_factor)
		* game->mix.og_r + fog_factor * game->mix.fog_r;
	game->mix.new_g = (1 - fog_factor)
		* game->mix.og_g + fog_factor * game->mix.fog_g;
	game->mix.new_b = (1 - fog_factor)
		* game->mix.og_b + fog_factor * game->mix.fog_b;
	*color = (game->mix.new_r << 16) | (game->mix.new_g << 8) | game->mix.new_b;
}

int	ft_colorpix_ceifloo(int x, int y, void *texture, t_cub *game)
{
	int				i;
	int				bpp;
	int				size;
	unsigned int	color;
	char			*pix;

	pix = mlx_get_data_addr(texture, &bpp, &size, &game->img3d.endian);
	i = y * size + x * bpp / 8;
	color = *(unsigned int *)(pix + i);
	return (color);
}

int	ft_colorpix(int x, int y, void *texture, t_cub *game)
{
	game->colorpix.pix = mlx_get_data_addr(texture, &game->colorpix.bpp,
			&game->colorpix.size, &game->img3d.endian);
	game->colorpix.i = y * game->colorpix.size + x
		* game->colorpix.bpp / 8;
	game->colorpix.color = *(unsigned int *)(game->colorpix.pix
			+ game->colorpix.i);
	if (game->ray.distance < 10)
		game->colorpix.fog = 0;
	else if (game->ray.distance < 20)
		game->colorpix.fog = 0.1 + (game->ray.distance - 10) * 0.09;
	else
		game->colorpix.fog = 1.0;
	mix_colors(&game->colorpix.color, game->colorpix.fog, 0x000000, game);
	return (game->colorpix.color);
}

static void	ft_draw_player(t_cub *game)
{
	int	i;
	int	px;
	int	py;
	int	dx;
	int	dy;

	dy = 0;
	px = game->ray.player_x * SPRITE - (7 / 2);
	py = game->ray.player_y * SPRITE - (7 / 2);
	while (dy < 7)
	{
		dx = 0;
		while (dx < 7)
		{
			i = (py + dy) * game->img2d.size_line
				+ (px + dx) * game->img2d.bpp / 8;
			*(unsigned int *)(game->img2d.pixels + i) = RED;
			dx++;
		}
		dy++;
	}
}

void	ft_draw_minimap(int x, int y, int *color, t_cub *game)
{
	int		dx;
	int		dy;
	char	*dst_pixels;
	int		dst_index;

	dst_pixels = mlx_get_data_addr(game->img_map2d, &game->img2d.bpp,
			&game->img2d.size_line, &game->img2d.endian);
	x *= SPRITE;
	y *= SPRITE;
	dy = 0;
	while (dy < SPRITE)
	{
		dx = 0;
		while (dx < SPRITE)
		{
			dst_index = (y + dy) * game->img2d.size_line
				+ (x + dx) * game->img2d.bpp / 8;
			*(unsigned int *)(dst_pixels + dst_index) = *color;
			dx++;
		}
		dy++;
	}
	ft_draw_player(game);
}
