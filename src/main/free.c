/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:28:49 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/13 13:41:34 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

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
}
