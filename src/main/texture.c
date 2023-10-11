/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:12:44 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/11 17:26:44 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	init_sprite(t_cub *game)
{
	game->num_sprites = 2;
	game->sprite = malloc(sizeof(t_sprite) * game->num_sprites);
	game->sprite[0].x = 10.0;
	game->sprite[0].y = 10.0;
	game->sprite[0].is_alive = 1;
	game->sprite[0].width = 1260;
	game->sprite[0].height = 1656;
	game->sprite[1].x = 4.0;
	game->sprite[1].y = 4.0;
	game->sprite[1].is_alive = 1;
	game->sprite[1].width = 1260;
	game->sprite[1].height = 1656;
}

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
	if (game->ray.hit == 2)
	{
		if (game->engine.door[game->ray.mapy][game->ray.mapx] == '0')
			draw_texture(x, game->texture.door, game);
	}
	else if (game->texture.direction == 'N')
		draw_texture(x, game->texture.north, game);
	else if (game->texture.direction == 'S')
		draw_texture(x, game->texture.south, game);
	else if (game->texture.direction == 'W')
		draw_texture(x, game->texture.west, game);
	else if (game->texture.direction == 'E')
		draw_texture(x, game->texture.east, game);
}
