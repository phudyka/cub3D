/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:24:39 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/11 11:52:00 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	ft_error(char *msg)
{
	printf("%s", msg);
	exit(EXIT_FAILURE);
}

int	game_over(t_cub *game)
{
	ft_free_map(game);
	free_door(game);
	free_texture(game);
	ft_destroy_img(game);
	free(game->ray.z_buffer);
	free(game->sprite);
	free(game);
	game = NULL;
	system("pkill aplay\n");
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
