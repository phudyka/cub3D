/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:36:48 by dtassel           #+#    #+#             */
/*   Updated: 2023/10/13 14:19:13 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

/*
** Fog factor for a wall column. Depends only on ray distance, so it is
** computed once per column instead of once per pixel. 0 = no fog (raw
** texel), 1 = fully black (far walls skip texture sampling entirely).
*/
float	wall_fog(double dist)
{
	if (dist < 10)
		return (0.0f);
	if (dist < 20)
		return (0.1f + (dist - 10.0f) * 0.09f);
	return (1.0f);
}

#ifdef BONUS

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

void	ft_draw_minimap(int x, int y, int *color, t_cub *game)
{
	int		dx;
	int		dy;

	x *= SPRITE;
	y *= SPRITE;
	dy = -1;
	while (++dy < SPRITE)
	{
		dx = -1;
		while (++dx < SPRITE)
			*(unsigned int *)(game->img2d.pixels
				+ (y + dy) * game->img2d.size_line
				+ (x + dx) * game->img2d.bpp / 8) = *color;
	}
}

void	ft_draw_player(t_cub *game)
{
	int	px;
	int	py;
	int	dx;
	int	dy;

	px = game->ray.player_x * SPRITE - (7 / 2);
	py = game->ray.player_y * SPRITE - (7 / 2);
	dy = -1;
	while (++dy < 7)
	{
		dx = -1;
		while (++dx < 7)
			*(unsigned int *)(game->img2d.pixels
				+ (py + dy) * game->img2d.size_line
				+ (px + dx) * game->img2d.bpp / 8) = RED;
	}
}

#endif
