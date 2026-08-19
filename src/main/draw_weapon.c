/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 01:54:23 by dtassel           #+#    #+#             */
/*   Updated: 2023/10/13 08:24:40 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

/*
** Which weapon frame to show depends only on the shoot/reload state, so it
** is picked once per frame rather than once per pixel -- and its pixel
** address is fetched once too. This loop used to call
** mlx_get_data_addr 500 * 456 times a frame, for an address that never
** moves.
*/
static void	*weapon_frame(t_cub *game)
{
	if (game->engine.reload == 1)
	{
		if (game->engine.half == 1)
			return (game->texture.reload0);
		return (game->texture.reload1);
	}
	if (game->engine.shoot == 1)
	{
		if (game->engine.ammo != 0)
			return (game->texture.shoot0);
		return (game->texture.shoot1);
	}
	return (game->texture.weapon1);
}

void	ft_draw_weapon(t_cub *game)
{
	char			*scene;
	char			*tex;
	int				tbpp;
	int				tsize;
	int				tend;
	unsigned int	color;
	int				x;
	int				y;

	scene = mlx_get_data_addr(game->img_map3d, &game->img3d.bpp,
			&game->img3d.size_line, &game->img3d.endian);
	tex = mlx_get_data_addr(weapon_frame(game), &tbpp, &tsize, &tend);
	y = -1;
	while (++y < 456)
	{
		x = -1;
		while (++x < 500)
		{
			color = *(unsigned int *)(tex + y * tsize + x * tbpp / 8);
			if (color == 0)
				color = *(unsigned int *)(scene
						+ (HEIGHT - 456 + y) * game->img3d.size_line
						+ (WIDTH - 500 + x) * game->img3d.bpp / 8);
			*(unsigned int *)(game->weapon.pixels + y * game->weapon.size_line
				+ x * game->weapon.bpp / 8) = color;
		}
	}
}

void	ft_crosshair(t_cub *game)
{
	int	i;
	int	xy[2];
	int	start[2];
	int	delta;

	start[0] = WIDTH / 2;
	start[1] = HEIGHT / 2;
	delta = 15 / 2;
	xy[1] = start[1] - delta;
	while (++xy[1] <= start[1] + delta)
	{
		xy[0] = start[0] - delta;
		while (++xy[0] <= start[0] + delta)
		{
			if (!((xy[0] >= start[0] - 2 && xy[0] <= start[0] + 2)
					&& (xy[1] >= start[1] - 2 && xy[1] <= start[1] + 2))
				&& ((xy[0] >= start[0] - 1 && xy[0] <= start[0] + 1)
					|| (xy[1] >= start[1] - 1 && xy[1] <= start[1] + 1)))
			{
				i = xy[1] * game->img3d.size_line + xy[0] * game->img3d.bpp / 8;
				*(unsigned int *)(game->img3d.pixels + i) = RED;
			}
		}
	}
}
