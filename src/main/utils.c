/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:52:30 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/07 02:42:02 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void ft_init_dda(int x, t_cub *game)
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
	clock_t			cur;
	static clock_t	last = 0;
	double			delta;
	char			*display;

	cur = clock();
	delta = ((double)(cur - last)) / CLOCKS_PER_SEC;
	if (delta >= 0.1)
	{
		int fps = count / delta;
		display = ft_itoa(fps);
		mlx_string_put(game->mlx, game->window, 10, 10, YELLOW, ft_itoa(fps));
		free(display);
		count = 0;
		last = cur;
	}
	else
		count++;
}

int	ft_abs(int nbr)
{
	if (nbr < 0)
		return (nbr * -1);
	return (nbr);
}