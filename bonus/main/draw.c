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

float	wall_fog(double dist)
{
	if (dist < 10)
		return (0.0f);
	if (dist < 20)
		return (0.1f + (dist - 10.0f) * 0.09f);
	return (1.0f);
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
