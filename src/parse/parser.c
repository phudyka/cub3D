/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:13:22 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/21 05:21:25 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int	check_all_configurations(t_cub *game)
{
	return (game->count_color_c && game->count_color_f
		&& game->texture.east && game->texture.north
		&& game->texture.south && game->texture.west);
}

int	process_map_lines(char *line, t_cub *game)
{
	static int	is_map_started;

	is_map_started = 0;
	if (is_map_line(line))
	{
		if (!check_all_configurations(game))
		{
			free_array(game->engine.cub);
			game_over_error("Error: Missing configurations before map starts.\n",
				game);
		}
		is_map_started = 1;
	}
	else if (is_map_started)
	{
		free_array(game->engine.cub);
		ft_putstr_fd("Error: Invalid configs ", 2);
		game_over_error("or lines found after map started.\n", game);
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
		ft_putstr_fd("Error: Invalid path for the texture file.\n", 2);
		free_array(game->engine.cub);
		game_over(game);
	}
}

void	parse_all_lines(t_cub *game, char **argv)
{
	initialize_game_settings(game);
	free_array(game->engine.cub);
	get_map(game, argv);
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
	//int	i;

	//i = 0;
	if (argc != 2 || !argv[1])
		return (1);
	if (ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		get_cub(game, argv);
	if (!game->engine.cub)
		return (1);
	parse_all_lines(game, argv);
	check_valid_path(game);
	check_map(game);
	/*while (game->engine.map[i])
		printf("%s\n", game->engine.map[i++]);
	printf("%s\n", game->texture.east);
	printf("%s\n", game->texture.north);
	printf("%s\n", game->texture.west);
	printf("%s\n", game->texture.south);
	printf("Ceiling : %d, %d, %d\n", game->ceiling.r, game->ceiling.g, game->ceiling.b);
	printf("Floor : %d, %d, %d\n", game->floor.r, game->floor.g, game->floor.b);*/
	return (0);
}
