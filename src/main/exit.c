/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:24:39 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/21 14:05:41 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/main.h"

void    free_array(char **array)
{
	int i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i++]);
	}
	free(array);
	array = NULL;
}

void    ft_error(char *msg)
{
	printf("%s", msg);
	exit(EXIT_FAILURE);
}

void  ft_error_free(char *msg, t_cub *game)
{
	ft_free_map(game);
	printf("%s", msg);
	exit(EXIT_FAILURE);
}

void ft_free_map(t_cub *game)
{
	int i;

	i = 0;
	if (!game->engine.map)
		return ;
	while (game->engine.map[i])
	{
		free(game->engine.map[i]);
		i++;
	}
	free(game->engine.map);
	game->engine.map = NULL;
}

void	free_texture(t_cub *game)
{
	free(game->texture.north);
	free(game->texture.east);
	free(game->texture.west);
	free(game->texture.south);
}

int game_over(t_cub *game)
{
	printf("\n[GAME OVER]\n");
	ft_free_map(game);
	free_texture(game);
    ft_destroy_img(game);
	free(game);
	game = NULL;
	exit(EXIT_SUCCESS);
}

void	game_over_error(char *msg, t_cub *game)
{
	ft_putstr_fd(msg, 2);
	game_over(game);
}
