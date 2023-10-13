/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:24:39 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/13 14:57:47 by phudyka          ###   ########.fr       */
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
	free_texture(game);
	ft_destroy_img(game);
	free(game->ray.z_buffer);
	free(game->texture.path_north);
	free(game->texture.path_south);
	free(game->texture.path_west);
	free(game->texture.path_east);
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
	free(game->texture.path_north);
	free(game->texture.path_south);
	free(game->texture.path_west);
	free(game->texture.path_east);
	free(game);
	game = NULL;
	exit(EXIT_SUCCESS);
}
