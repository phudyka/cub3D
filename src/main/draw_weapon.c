/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 01:54:23 by dtassel           #+#    #+#             */
/*   Updated: 2023/10/07 01:54:58 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

bool should_draw_pixel(int pixel_color, int color_to_ignore)
{
	unsigned char r, g, b;
	unsigned char r_ignore, g_ignore, b_ignore;

	r = (pixel_color >> 16) & 0xFF;
	g = (pixel_color >> 8) & 0xFF;
	b = pixel_color & 0xFF;

	r_ignore = (color_to_ignore >> 16) & 0xFF;
	g_ignore = (color_to_ignore >> 8) & 0xFF;
	b_ignore = color_to_ignore & 0xFF;

	return !(r == r_ignore && g == g_ignore && b == b_ignore);
}

static void	draw_pixel(t_cub *game, int x, int y, int pixel_color)
{
	int	dst_index;

	dst_index = y * game->weapon.size_line + x * game->weapon.bpp / 8;
	*(unsigned int *)(game->weapon.pixels + dst_index) = pixel_color;
}

static void	draw_or_replace_pixel(t_cub *game, int x, int y, int pixel_color, char *replace)
{
	int	src_index;
	int	map_start_x;
	int	map_start_y;

	map_start_x = WIDTH - 456;
	map_start_y = HEIGHT - 500;
	if (pixel_color != 0)
		draw_pixel(game, x, y, pixel_color);
	else
	{
		src_index = (map_start_y + y) * game->img3d.size_line +
			(map_start_x + x) * game->img3d.bpp / 8;
		draw_pixel(game, x, y, *(unsigned int *)(replace + src_index));
	}
}

void		ft_draw_weapon(t_cub *game)
{
	int		x;
	int		y;
	int		pixel_color;
	char	*replace;

	y = 0;
	replace = mlx_get_data_addr(game->img_map3d, &game->img3d.bpp,
			&game->img3d.size_line, &game->img3d.endian);
	while (y < 500)
	{
		x = 0;
		while (x < 456)
		{
			pixel_color = ft_colorpix_ceifloo(x, y, game->texture.weapon1, game);
			if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
				draw_or_replace_pixel(game, x, y, pixel_color, replace);
			x++;
		}
		y++;
	}
}