/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:24:39 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/10 00:38:26 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	ft_error(char *msg)
{
	printf("%s", msg);
	exit(EXIT_FAILURE);
}

void	ft_error_free(char *msg, t_cub *game)
{
	ft_free_map(game);
	printf("%s", msg);
	exit(EXIT_FAILURE);
}

void	free_texture(t_cub *game)
{
	free(game->texture.north);
	free(game->texture.east);
	free(game->texture.west);
	free(game->texture.south);
	free(game->texture.ceiling);
	free(game->texture.floor);
	free(game->texture.door);
	free(game->texture.weapon1);
	free(game->texture.target);
}

int	game_over(t_cub *game)
{
	ft_free_map(game);
	free_texture(game);
	ft_destroy_img(game);
	free(game->ray.z_buffer);
	free(game->sprite);
	free(game);
	game = NULL;
	exit(EXIT_SUCCESS);
}

void	game_over_error(char *msg, t_cub *game)
{
	ft_putstr_fd(msg, 2);
	game_over(game);
}
