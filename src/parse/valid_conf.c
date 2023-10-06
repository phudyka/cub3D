/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_conf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 02:14:11 by kali              #+#    #+#             */
/*   Updated: 2023/10/06 11:17:21 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int	validate_path(char *path)
{
	int	fd;

	if (!path)
		return (1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	check_valid_path(t_cub *game)
{
	if (validate_path(game->texture.north) == 1)
		return (1);
	else if (validate_path(game->texture.south) == 1)
		return (1);
	else if (validate_path(game->texture.east) == 1)
		return (1);
	else if (validate_path(game->texture.west) == 1)
		return (1);
	return (0);
}

int	check_rgb(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (1);
	return (0);
}

void	check_valid_conf(t_cub *game)
{
	if (game->count_color_c > 1 || game->count_color_c == 0
		|| game->count_color_f > 1 || game->count_color_f == 0)
	{
		free_array(game->engine.cub);
		game_over_error("Error : Invalid of 'C' and/or 'F' lines.\n", game);
	}
	if (check_rgb(game->ceiling.r, game->ceiling.g, game->ceiling.b) == 1)
	{
		free_array(game->engine.cub);
		game_over_error("Error Invalid value(s) ceiling RGB.\n", game);
	}
	if (check_rgb(game->floor.r, game->floor.g, game->floor.b) == 1)
	{
		free_array(game->engine.cub);
		game_over_error("Error Invalid value(s) floor RGB.\n", game);
	}
}
