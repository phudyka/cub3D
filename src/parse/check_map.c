/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 05:04:57 by dtassel           #+#    #+#             */
/*   Updated: 2023/09/22 03:54:15 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	add_char_map(t_cub *game, size_t max)
{
	int		i;
	size_t	j;
	char	*tmp;
	char	*new_line;

	i = 0;
	while (game->engine.map[i])
	{
		if (ft_strlen(game->engine.map[i]) < max)
		{
			tmp = game->engine.map[i];
			new_line = malloc(sizeof(char) * (max + 1));
			j = 0;
			while (tmp[j])
			{
				new_line[j] = tmp[j];
				j++;
			}
			while (j < max)
				new_line[j++] = '1';
			new_line[j] = '\0';
			free(tmp);
			game->engine.map[i] = new_line;
		}
		i++;
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

void    replace_spaces(t_cub *game)
{
	int i;
	int j;

	i = 0;
	while (game->engine.map[i])
	{
		j = 0;
		while (game->engine.map[i][j])
		{
			if (game->engine.map[i][j] == 'N' || game->engine.map[i][j] == 'E'
				|| game->engine.map[i][j] == 'W' || game->engine.map[i][j] == 'S')
				game->engine.coord = game->engine.map[i][j];
			if (game->engine.map[i][j] == ' ')
				game->engine.map[i][j] = '1';
			j++;
		}
		i++;  
	}
}

void    ft_check_one(int i, int j, t_cub *game)
{
		if (game->engine.map[i][j - 1] != '1')
			game_over_error("Map not valid\n", game);
		if (game->engine.map[i][0] != '1')
			game_over_error("Map not valid\n", game);
}

void    ft_check_len(size_t j, t_cub *game)
{
		if (j != ft_strlen(game->engine.map[0]))
			game_over_error("Map not valid\n", game);
}

void    ft_check_close(int i, t_cub *game)
{
		int     j;

		j = 0;
		while (game->engine.map[i][j])
		{
				if (game->engine.map[i][j] != '1')
					game_over_error("Map not valid\n", game);
				j++;
		}
}

void    ft_check(int i, int j, t_cub *game)
{
		if (game->engine.map[i][j] != '1' && game->engine.map[i][j] != 'N'
						&& game->engine.map[i][j] != 'E' && game->engine.map[i][j] != '0'
								&& game->engine.map[i][j] != 'W'
									&& game->engine.map[i][j] != 'S')
			game_over_error("Map not valid\n", game);
}

void    check_map(t_cub *game)
{
		unsigned long   i;
		unsigned long   j;

		i = 0;
		replace_spaces(game);
		format_map(game);
		i = 0;
		ft_check_close(i, game);
		while (game->engine.map[i])
		{
				game->engine.height++;
				j = 0;
				while (game->engine.map[i][j])
				{
						ft_check(i, j, game);
						j++;
				}
				ft_check_len(j, game);
				ft_check_one(i, j, game);
				i++;
		}
		if (i == j)
			game_over_error("Map not valid\n", game);
		ft_check_close((i - 1), game);
		printf("%c\n", game->engine.coord);
}
