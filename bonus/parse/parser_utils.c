/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:41:04 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/13 07:53:12 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int	check_all_configurations(t_cub *game)
{
	return (game->count_color_c && game->count_color_f
		&& game->texture.path_east && game->texture.path_north
		&& game->texture.path_south && game->texture.path_west);
}

int	parse_line(char *line, t_cub *game)
{
	if (!line)
		return (1);
	if (is_configuration(line))
		return (process_configuration_lines(line, game));
	else
		return (process_map_lines(line, game));
}

void	initialize_game_settings(t_cub *game)
{
	int	i;

	i = 0;
	while (game->engine.cub[i])
		parse_line(game->engine.cub[i++], game);
	check_valid_conf(game);
	if (check_valid_path(game) == 1)
	{
		free_array(game->engine.cub);
		ft_error_parse("Error: Invalid path for the texture file.\n", game);
	}
}

void	parse_all_lines(t_cub *game, char **argv)
{
	initialize_game_settings(game);
	free_array(game->engine.cub);
	get_map(game, argv);
}

long	get_next_number(char **str, int *count)
{
	long	num;

	while (**str && !ft_isdigit(**str) && **str != '-')
		(*str)++;
	if (ft_isdigit(**str) || **str == '-')
	{
		(*count)++;
		num = ft_atoi(*str);
		while (ft_isdigit(**str))
			(*str)++;
		return (num);
	}
	return (-1);
}
