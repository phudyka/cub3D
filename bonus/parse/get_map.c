/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 08:05:44 by dtassel           #+#    #+#             */
/*   Updated: 2023/10/14 13:50:17 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int	is_map_line(char *line)
{
	if (!contains_map_char(line))
		return (0);
	while (*line)
	{
		if (*line != '0' && *line != '1' && *line != '2' && *line != 'N'
			&& *line != 'S' && *line != 'E' && *line != 'W'
			&& *line != ' ' && *line != '\t')
			return (0);
		line++;
	}
	return (1);
}

char	*add_line_to_map(char *map, char *line)
{
	char	*tmp;
	char	*new_map;

	tmp = ft_strjoin(map, line);
	new_map = ft_strjoin(tmp, "\n");
	return (new_map);
}

static void	process_line(char *line, char **map, int *is_map_started)
{
	char	*cpy;

	cpy = ft_strtrim(line, " ", "\t");
	if (is_configuration(cpy))
	{
		free(cpy);
		return ;
	}
	if (!*is_map_started && is_map_line(line) == 0)
		*is_map_started = 1;
	if (*is_map_started)
		*map = add_line_to_map(*map, line);
	free(cpy);
}

char	*read_and_extract_map(int fd)
{
	char	*line;
	char	*map;
	int		is_map_started;

	is_map_started = 0;
	map = ft_calloc(1, 1);
	line = get_next_line(fd);
	while (line)
	{
		process_line(line, &map, &is_map_started);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (map);
}

void	get_map(t_cub *game, char **argv)
{
	int		fd;
	char	*map;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return ;
	map = read_and_extract_map(fd);
	game->engine.map = ft_split(map, '\n');
	free(map);
	close(fd);
}
