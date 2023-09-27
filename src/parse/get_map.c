/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 08:05:44 by dtassel           #+#    #+#             */
/*   Updated: 2023/09/21 02:26:41 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int	is_configuration(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0 || 
		ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0 ||
		line[0] == 'F' || line[0] == 'C')
		return (1);
	return (0);
}

int contains_map_char(char *line)
{
    while (*line)
    {
        if (*line == '0' || *line == '1' || *line == '2' || 
            *line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
            return (1);
        line++;
    }
    return (0);
}

int is_map_line(char *line)
{
    if (!contains_map_char(line))
        return (0);
    
    while (*line)
    {
        if (*line != '0' && *line != '1' && *line != '2' && *line != 'N' && 
            *line != 'S' && *line != 'E' && *line != 'W' && *line != ' ' && *line != '\t')
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

char	*read_and_extract_map(int fd)
{
	char	*line;
	char	*map;
	int		is_map_started;

	is_map_started = 0;
	map = ft_calloc(1, 1);
	line = "";
	while (line)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (is_configuration(line))
		{
			free(line);
			continue ;
		}
		if (!is_map_started && is_map_line(line) == 0)
			is_map_started = 1;
		if (is_map_started)
			map = add_line_to_map(map, line);
		free(line);
	}
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
