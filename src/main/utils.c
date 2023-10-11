/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:52:30 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/11 04:34:07 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	ft_init_dda(int x, t_cub *game)
{
	ft_init_ray(game);
	game->ray.cam_x = 2 * x / (double)WIDTH - 1;
	game->ray.ray_x = game->ray.dir_x + game->ray.plane_x * game->ray.cam_x;
	game->ray.ray_y = game->ray.dir_y + game->ray.plane_y * game->ray.cam_x;
	game->ray.mapx = (int)game->ray.player_x;
	game->ray.mapy = (int)game->ray.player_y;
	game->ray.delta_x = fabs(1 / game->ray.ray_x);
	game->ray.delta_y = fabs(1 / game->ray.ray_y);
}

void	print_cub(void)
{
	printf("  /$$$$$$  /$$   /$$ /$$$$$$$   /$$$$$$  /$$$$$$$\n");
	printf(" /$$__  $$| $$  | $$| $$__  $$ /$$__  $$| $$__  $$\n");
	printf("| $$  \\__/| $$  | $$| $$  \\ $$|__/  \\ $$| $$  \\ $$\n");
	printf("| $$      | $$  | $$| $$$$$$$    /$$$$$/| $$  | $$\n");
	printf("| $$      | $$  | $$| $$__  $$  |___  $$| $$  | $$\n");
	printf("| $$    $$| $$  | $$| $$  \\ $$ /$$  \\ $$| $$  | $$\n");
	printf("|  $$$$$$/|  $$$$$$/| $$$$$$$/|  $$$$$$/| $$$$$$$/\n");
	printf("\\______/  \\______/ |_______/  \\______/ |_______/\n");
	printf("\n                           by dtassel & phudyka\n");
}

void	ft_fraps(t_cub *game)
{
	static int		count = 0;
	static clock_t	last = 0;
	double			delta;
	int				fps;
	char			*display;

	game->cur = clock();
	delta = ((double)(game->cur - last)) / CLOCKS_PER_SEC;
	if (delta >= 0.1)
	{
		fps = count / delta;
		display = ft_itoa(fps);
		mlx_string_put(game->mlx, game->window, 10, 10, YELLOW, display);
		free(display);
		count = 0;
		last = game->cur;
	}
	else
		count++;
}

void	free_door(t_cub *game)
{
	int	i;

	if (game->engine.door)
	{
		i = 0;
		while (i < game->engine.height)
		{
			if (game->engine.door[i])
				free(game->engine.door[i]);
			i++;
		}
		free(game->engine.door);
		game->engine.door = NULL;
	}
}

void	ft_free_map(t_cub *game)
{
	int	i;

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

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
	array = NULL;
}
