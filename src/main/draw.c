/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:36:48 by dtassel           #+#    #+#             */
/*   Updated: 2023/10/11 17:20:45 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void	mix_colors(unsigned int *color, float fog_factor,
		unsigned int fog_color)
{
	unsigned char	fog_r;
	unsigned char	fog_g;
	unsigned char	fog_b;
	unsigned char	final_r;
	unsigned char	final_g;
	unsigned char	final_b;
	unsigned char	original_r;
	unsigned char	original_g;
	unsigned char	original_b;

	original_r = (*color >> 16) & 0xFF;
	original_g = (*color >> 8) & 0xFF;
	original_b = *color & 0xFF;
	fog_r = (fog_color >> 16) & 0xFF;
	fog_g = (fog_color >> 8) & 0xFF;
	fog_b = fog_color & 0xFF;
	final_r = (1 - fog_factor) * original_r + fog_factor * fog_r;
	final_g = (1 - fog_factor) * original_g + fog_factor * fog_g;
	final_b = (1 - fog_factor) * original_b + fog_factor * fog_b;
	*color = (final_r << 16) | (final_g << 8) | final_b;
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
	int				i;
	int				bpp;
	int				size;
	unsigned int	color;
	char			*pix;
	float			fog;

	pix = mlx_get_data_addr(texture, &bpp, &size, &game->img3d.endian);
	i = y * size + x * bpp / 8;
	color = *(unsigned int *)(pix + i);
	if (game->ray.distance < 10)
		fog = 0;
	else if (game->ray.distance < 20)
		fog = 0.1 + (game->ray.distance - 10) * 0.09;
	else
		fog = 1.0;
	mix_colors(&color, fog, 0x000000);
	return (color);
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
