/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:52:30 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/11 17:38:26 by phudyka          ###   ########.fr       */
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
	static struct timespec	last = {0, 0};
	static int				count = 0;
	static int				fps = 0;
	struct timespec			now;
	double					delta;
	char					*display;

	clock_gettime(CLOCK_MONOTONIC, &now);
	if (last.tv_sec == 0)
		last = now;
	count++;
	delta = (now.tv_sec - last.tv_sec)
		+ (now.tv_nsec - last.tv_nsec) / 1000000000.0;
	if (delta >= 0.25)
	{
		fps = count / delta;
		count = 0;
		last = now;
	}
	display = ft_itoa(fps);
	mlx_string_put(game->mlx, game->window, 10, 10, YELLOW, display);
	free(display);
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
