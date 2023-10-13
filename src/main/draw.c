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
