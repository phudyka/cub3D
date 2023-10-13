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

static void	draw_pixel(int x, int y, int color, t_cub *game)
{
	int	i;

	i = y * game->weapon.size_line + x * game->weapon.bpp / 8;
	*(unsigned int *)(game->weapon.pixels + i) = color;
}

static void	draw_or_replace_pixel(t_cub *game, int x, int y, char *replace)
{
	int	i;
	int	mx;
	int	my;

	mx = WIDTH - 500;
	my = HEIGHT - 456;
	if (game->texture.color)
		draw_pixel(x, y, game->texture.color, game);
	else
	{
		i = (my + y) * game->img3d.size_line
			+ (mx + x) * game->img3d.bpp / 8;
		draw_pixel(x, y, *(unsigned int *)(replace + i), game);
	}
}

static int	ft_sprite_select(int x, int y, t_cub *game)
{
	int	color;

	if (game->engine.shoot == 0 && game->engine.reload != 1)
		color = ft_colorpix_ceifloo(x, y, game->texture.weapon1, game);
	else if (game->engine.shoot == 1
		&& game->engine.reload != 1 && game->engine.ammo != 0)
		color = ft_colorpix_ceifloo(x, y, game->texture.shoot0, game);
	else if (game->engine.shoot == 1
		&& game->engine.reload != 1 && game->engine.ammo == 0)
		color = ft_colorpix_ceifloo(x, y, game->texture.shoot1, game);
	else if (game->engine.shoot != 1
		&& game->engine.reload == 1 && game->engine.half == 1)
		color = ft_colorpix_ceifloo(x, y, game->texture.reload0, game);
	else if (game->engine.shoot != 1
		&& game->engine.reload == 1 && game->engine.half == 0)
		color = ft_colorpix_ceifloo(x, y, game->texture.reload1, game);
	return (color);
}

void	ft_draw_weapon(t_cub *game)
{
	int		x;
	int		y;
	char	*replace;

	y = 0;
	replace = mlx_get_data_addr(game->img_map3d, &game->img3d.bpp,
			&game->img3d.size_line, &game->img3d.endian);
	while (y < 456)
	{
		x = 0;
		while (x < 500)
		{
			game->texture.color = ft_sprite_select(x, y, game);
			if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
				draw_or_replace_pixel(game, x, y, replace);
			x++;
		}
		y++;
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
