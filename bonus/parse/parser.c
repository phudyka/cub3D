/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:13:22 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/13 07:42:53 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int	process_map_lines(char *line, t_cub *game)
{
	static int	is_map_started;

	is_map_started = 0;
	if (is_map_line(line))
	{
		if (!check_all_configurations(game))
		{
			free_array(game->engine.cub);
			ft_error_parse("Error!: [Missing config before map starts]\n", game);
		}
		is_map_started = 1;
	}
	else if (is_map_started)
	{
		free_array(game->engine.cub);
		ft_error_parse("Error!: [Invalid configs after map started]\n", game);
	}
	return (0);
}

int	process_configuration_lines(char *line, t_cub *game)
{
	char	*tmp;

	tmp = ft_strtrim(line, " ", "\t");
	if (tmp[0] == 'N' && tmp[1] == 'O')
		parse_north_texture(tmp, game);
	else if (tmp[0] == 'S' && tmp[1] == 'O')
		parse_south_texture(tmp, game);
	else if (tmp[0] == 'E' && tmp[1] == 'A')
		parse_east_texture(tmp, game);
	else if (tmp[0] == 'W' && tmp[1] == 'E')
		parse_west_texture(tmp, game);
	else if (tmp[0] == 'F' || tmp[0] == 'C')
	{
		floor_ceiling_color(tmp, game);
		if (tmp[0] == 'F')
			game->count_color_f++;
		if (tmp[0] == 'C')
			game->count_color_c++;
	}
	free(tmp);
	return (0);
}

void	get_cub(t_cub *game, char **argv)
{
	char	*line;
	char	*map;
	int		fd;
	char	*cpy;

	line = "";
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return ;
	map = ft_calloc(1, 1);
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		cpy = ft_strtrim(line, " ", "\t");
		free(line);
		map = ft_strjoin(map, cpy);
		free(cpy);
	}
	free(line);
	game->engine.cub = ft_split(map, '\n');
	free(map);
	close(fd);
}

int	master_parser(t_cub *game, int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 2 || !argv[1])
		return (1);
	i = ft_strlen(argv[1]);
	i = i - 4;
	if (argv[1][i] == '.' && argv[1][i + 1] == 'c'
		&& argv[1][i + 2] == 'u' && argv[1][i + 3] == 'b')
		get_cub(game, argv);
	if (!game->engine.cub)
		return (1);
	parse_all_lines(game, argv);
	check_valid_path(game);
	check_map(game);
	return (0);
}
