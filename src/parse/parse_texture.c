/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 07:11:54 by kali              #+#    #+#             */
/*   Updated: 2023/10/12 10:46:12 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	floor_ceiling_color(char *line, t_cub *game)
{
	char	*ptr;
	int		rgb_count;

	rgb_count = 0;
	ptr = line + 1;
	if (*line == 'F')
	{
		game->floor_col.r = get_next_number(&ptr, &rgb_count);
		game->floor_col.g = get_next_number(&ptr, &rgb_count);
		game->floor_col.b = get_next_number(&ptr, &rgb_count);
	}
	else if (*line == 'C')
	{
		game->ceiling_col.r = get_next_number(&ptr, &rgb_count);
		game->ceiling_col.g = get_next_number(&ptr, &rgb_count);
		game->ceiling_col.b = get_next_number(&ptr, &rgb_count);
	}
	while (*ptr && !ft_isdigit(*ptr))
		ptr++;
	if (rgb_count != 3 || ft_isdigit(*ptr))
	{
		free(line);
		free_array(game->engine.cub);
		ft_error_parse("Error RGB\n", game);
	}
}

int	parse_north_texture(char *line, t_cub *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (game->texture.north)
	{
		ft_error("Error: North texture (NO) is already defined.\n");
		return (1);
	}
	while (line[i] != '.')
		i++;
	game->texture.north = malloc(sizeof(char) * ft_strlen(&line[i]) + 1);
	while (line[i])
		game->texture.north[j++] = line[i++];
	game->texture.north[j] = '\0';
	return (0);
}

int	parse_south_texture(char *line, t_cub *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (game->texture.south)
	{
		ft_error("Error: South texture (SO) is already defined.\n");
		return (1);
	}
	while (line[i] != '.')
		i++;
	game->texture.south = malloc(sizeof(char) * ft_strlen(&line[i]) + 1);
	while (line[i])
		game->texture.south[j++] = line[i++];
	game->texture.south[j] = '\0';
	return (0);
}

int	parse_west_texture(char *line, t_cub *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (game->texture.west)
	{
		ft_error("Error: West texture (WE) is already defined.\n");
		return (1);
	}
	while (line[i] != '.')
		i++;
	game->texture.west = malloc(sizeof(char) * ft_strlen(&line[i]) + 1);
	while (line[i])
		game->texture.west[j++] = line[i++];
	game->texture.west[j] = '\0';
	return (0);
}

int	parse_east_texture(char *line, t_cub *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (game->texture.east)
	{
		ft_error("Error: East texture (EA) is already defined.\n");
		return (1);
	}
	while (line[i] != '.')
		i++;
	game->texture.east = malloc(sizeof(char) * ft_strlen(&line[i]) + 1);
	while (line[i])
		game->texture.east[j++] = line[i++];
	game->texture.east[j] = '\0';
	return (0);
}
