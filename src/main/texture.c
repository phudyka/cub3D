/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:12:44 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/13 13:43:34 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void	ft_texture_index(t_cub *game)
{
	if (game->ray.side == 1)
	{
		if (game->ray.ray_y < 0)
			game->texture.direction = 'N';
		else 
			game->texture.direction = 'S';
	}
	else
	{
		if (game->ray.ray_x < 0)
			game->texture.direction = 'W';
		else 
			game->texture.direction = 'E';
	}
}

void	choose_texture(int x, t_cub *game)
{
	ft_texture_index(game);
	if (game->texture.direction == 'N')
		draw_texture(x, game->texture.north, game);
	else if (game->texture.direction == 'S')
		draw_texture(x, game->texture.south, game);
	else if (game->texture.direction == 'W')
		draw_texture(x, game->texture.west, game);
	else if (game->texture.direction == 'E')
		draw_texture(x, game->texture.east, game);
}
