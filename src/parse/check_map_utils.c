/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:32:21 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/14 05:28:37 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int	is_configuration(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0
		|| line[0] == 'F' || line[0] == 'C')
		return (1);
	return (0);
}

void	ft_check_one(int i, int j, t_cub *game)
{
	if (game->engine.map[i][j - 1] != '1')
		game_over_error("Error!\n[Map not valid]\n", game);
	if (game->engine.map[i][0] != '1')
		game_over_error("Error!\n[Map not valid]\n", game);
}

void	ft_check_len(size_t j, t_cub *game)
{
	if (j != ft_strlen(game->engine.map[0]))
		game_over_error("Error!\n[Map too long]\n", game);
}

void	ft_check_close(int i, t_cub *game)
{
	int	j;

	j = 0;
	while (game->engine.map[i][j])
	{
		if (game->engine.map[i][j] != '1')
			game_over_error("Error!\n[Map not closed]\n", game);
		j++;
	}
}

int	contains_map_char(char *line)
{
	while (*line)
	{
		if (*line == '0' || *line == '1' || *line == '2'
			|| *line == 'N' || *line == 'S' || *line == 'E'
			|| *line == 'W')
			return (1);
		line++;
	}
	return (0);
}
