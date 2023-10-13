/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:28:49 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/11 17:38:30 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	free_door(t_cub *game)
{
	int	i;

	if (game->engine.door)
	{
		i = 0;
		while (i < game->engine.height)
		{
			if (game->engine.door[i])
				free(game->engine.door[i]);
			i++;
		}
		free(game->engine.door);
		game->engine.door = NULL;
	}
}

void	ft_free_map(t_cub *game)
{
	int	i;

	i = 0;
	if (!game->engine.map)
		return ;
	while (game->engine.map[i])
	{
		free(game->engine.map[i]);
		i++;
	}
	free(game->engine.map);
	game->engine.map = NULL;
}

void	ft_error_free(char *msg, t_cub *game)
{
	ft_free_map(game);
	printf("%s", msg);
	exit(EXIT_FAILURE);
}

static void	free_assets(t_cub *game)
{
	if (game->texture.weapon1)
		mlx_destroy_image(game->mlx, game->texture.weapon1);
	if (game->texture.shoot0)
		mlx_destroy_image(game->mlx, game->texture.shoot0);
	if (game->texture.shoot1)
		mlx_destroy_image(game->mlx, game->texture.shoot1);
	if (game->texture.reload0)
		mlx_destroy_image(game->mlx, game->texture.reload0);
	if (game->texture.reload1)
		mlx_destroy_image(game->mlx, game->texture.reload1);
	if (game->texture.target)
		mlx_destroy_image(game->mlx, game->texture.target);
}

void	free_texture(t_cub *game)
{
	if (game->texture.north)
		mlx_destroy_image(game->mlx, game->texture.north);
	if (game->texture.south)
		mlx_destroy_image(game->mlx, game->texture.south);
	if (game->texture.east)
		mlx_destroy_image(game->mlx, game->texture.east);
	if (game->texture.west)
		mlx_destroy_image(game->mlx, game->texture.west);
	if (game->texture.floor)
		mlx_destroy_image(game->mlx, game->texture.floor);
	if (game->texture.ceiling)
		mlx_destroy_image(game->mlx, game->texture.ceiling);
	if (game->texture.door)
		mlx_destroy_image(game->mlx, game->texture.door);
	free_assets(game);
}
