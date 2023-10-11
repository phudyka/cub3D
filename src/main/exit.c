/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:24:39 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/11 04:35:06 by dtassel          ###   ########.fr       */
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

void free_texture(t_cub *game)
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
    if (game->texture.weapon1)
        mlx_destroy_image(game->mlx, game->texture.weapon1);
    if (game->texture.shoot)
        mlx_destroy_image(game->mlx, game->texture.shoot);
    if (game->texture.reload)
        mlx_destroy_image(game->mlx, game->texture.reload);
    if (game->texture.target)
        mlx_destroy_image(game->mlx, game->texture.target);
}

int	game_over(t_cub *game)
{
	system("pkill aplay");
	ft_free_map(game);
	free_door(game);
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

void	ft_error_parse(char *msg, t_cub *game)
{
	ft_putstr_fd(msg, 2);
	ft_free_map(game);
	free(game->texture.north);
	free(game->texture.east);
	free(game->texture.west);
	free(game->texture.south);
	free(game);
	game = NULL;
	exit(EXIT_SUCCESS);
}
