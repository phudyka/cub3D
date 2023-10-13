/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:12:44 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/13 08:25:51 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	coord_target(t_cub *game)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	x = 0;
	while (game->engine.map[i])
	{
		j = 0;
		while (game->engine.map[i][j])
		{
			if (game->engine.map[i][j] == 'T')
			{
				game->sprite[x].x = j;
				game->sprite[x].y = i;
				game->sprite[x].is_alive = 1;
				game->sprite[x].width = 1260;
				game->sprite[x].height = 1656;
				x++;
			}
			j++;
		}
		i++;
	}
}

int	count_target(t_cub *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->engine.map[i])
	{
		j = 0;
		while (game->engine.map[i][j])
		{
			if (game->engine.map[i][j] == 'T')
				game->num_sprites++;
			j++;
		}
		i++;
	}
	return (game->num_sprites);
}

void	init_sprite(t_cub *game)
{
	game->num_sprites = count_target(game);
	game->sprite = malloc(sizeof(t_sprite) * game->num_sprites + 1);
	coord_target(game);
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
