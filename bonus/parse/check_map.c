/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 05:04:57 by dtassel           #+#    #+#             */
/*   Updated: 2023/10/13 08:36:06 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	add_char_map(t_cub *game, size_t max)
{
	int		i;
	size_t	j;
	char	*tmp;
	char	*new_line;

	i = -1;
	while (game->engine.map[++i])
	{
		if (ft_strlen(game->engine.map[i]) < max)
		{
			tmp = game->engine.map[i];
			new_line = malloc(sizeof(char) * (max + 1));
			j = -1;
			while (tmp[++j])
				new_line[j] = tmp[j];
			while (j < max)
				new_line[j++] = '1';
			new_line[j] = '\0';
			free(tmp);
			game->engine.map[i] = new_line;
		}
	}
}

void	format_map(t_cub *game)
{
	int		i;
	size_t	max;

	i = 0;
	max = 0;
	while (game->engine.map[i])
	{
		if (max < ft_strlen(game->engine.map[i]))
			max = ft_strlen(game->engine.map[i]);
		i++;
	}
	game->engine.width = max;
	add_char_map(game, max);
}

int	replace_spaces(t_cub *game, int c)
{
	int	i;
	int	j;

	i = -1;
	while (game->engine.map[++i])
	{
		j = -1;
		while (game->engine.map[i][++j])
		{
			if (game->engine.map[i][j] == 'N' || game->engine.map[i][j] == 'E'
				|| game->engine.map[i][j] == 'W'
				|| game->engine.map[i][j] == 'S')
			{
				game->engine.coord = game->engine.map[i][j];
				game->ray.player_x = (double)j + 0.5;
				game->ray.player_y = (double)i + 0.5;
				game->engine.map[i][j] = '0';
				c++;
			}
			if (game->engine.map[i][j] == ' ')
				game->engine.map[i][j] = '1';
		}
	}
	return (c);
}

void	ft_check(int i, int j, t_cub *game)
{
	if (game->engine.map[i][j] != '1' && game->engine.map[i][j] != 'N'
		&& game->engine.map[i][j] != 'E' && game->engine.map[i][j] != '0'
		&& game->engine.map[i][j] != 'W' && game->engine.map[i][j] != 'S'
		&& game->engine.map[i][j] != 'D' && game->engine.map[i][j] != 'T')
		ft_error_parse("Map not valid\n", game);
}

void	check_map(t_cub *game)
{
	unsigned long	i;
	unsigned long	j;
	int				c;

	i = -1;
	c = 0;
	c = replace_spaces(game, c);
	if (c == 0 || c > 1)
		ft_error_parse("Map not valid\n", game);
	format_map(game);
	ft_check_close(++i, game);
	while (game->engine.map[++i])
	{
		j = -1;
		game->engine.height++;
		while (game->engine.map[i][++j])
			ft_check(i, j, game);
		ft_check_len(j, game);
		ft_check_one(i, j, game);
	}
	if (i == j)
		ft_error_parse("Map not valid\n", game);
	ft_check_close((i - 1), game);
}
