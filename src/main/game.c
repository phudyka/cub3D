/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:18:12 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/10 13:05:45 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

// PENSER A FREE // // PENSER A FREE //
void	initialize_door(t_cub *game)
{
	int	i;
	int j;

	game->engine.door = malloc(sizeof(char *) * game->engine.height);
	i = 0;
	while (i < game->engine.height)
	{
		game->engine.door[i] = ft_substr(game->engine.map[i], 0, ft_strlen(game->engine.map[i]));
		j = 0;
		while (game->engine.door[i][j])
		{
			if (game->engine.door[i][j] == 'D')
				game->engine.door[i][j] = '0';
			else
				game->engine.door[i][j] = ' ';
			j++;
		}
		i++;
	}
}
// PENSER A FREE // // PENSER A FREE //

int	key_press(int key, t_cub *game)
{
	if (key == E)
    {
        door_state(game->ray.player_x + 1, game->ray.player_y, game);
        door_state(game->ray.player_x - 1, game->ray.player_y, game);
        door_state(game->ray.player_x, game->ray.player_y + 1, game);
        door_state(game->ray.player_x, game->ray.player_y - 1, game);
    }
	if (key == ESC)
		game_over(game);
	if (key == W)
		game->engine.move_y = 1;
	else if (key == A)
		game->engine.move_x = -1;
	else if (key == S)
		game->engine.move_y = -1;
	else if (key == D)
		game->engine.move_x = 1;
	else if (key == LEFT)
		game->engine.rotate -= 1;
	else if (key == RIGHT)
		game->engine.rotate += 1;
	return (0);
}

int	key_release(int key, t_cub *game)
{
	if (key == ESC)
		game_over(game);
	else if (key == W && game->engine.move_y == 1)
		game->engine.move_y = 0;
	else if (key == A && game->engine.move_x == -1)
		game->engine.move_x += 1;
	else if (key == S && game->engine.move_y == -1)
		game->engine.move_y = 0;
	else if (key == D && game->engine.move_x == 1)
		game->engine.move_x -= 1;
	else if (key == LEFT && game->engine.rotate <= 1)
		game->engine.rotate = 0;
	else if (key == RIGHT && game->engine.rotate >= -1)
		game->engine.rotate = 0;
	return (0);
}

void	ft_destroy_img(t_cub *game)
{
	if (game->img_map2d)
		mlx_destroy_image(game->mlx, game->img_map2d);
	if (game->img_map3d)
		mlx_destroy_image(game->mlx, game->img_map3d);
	if (game->weapon_3d)
		mlx_destroy_image(game->mlx, game->weapon_3d);
	mlx_destroy_window(game->mlx, game->window);
}

int	ft_cub(t_cub *game)
{
	ft_init_mlx(game);
	ft_input(game);
	game->ray.z_buffer = malloc(sizeof(double) * WIDTH); // PENSER A FREE
	init_sprite(game);
	initialize_door(game);
	mlx_loop_hook(game->mlx, ft_render, game);
	mlx_do_sync(game->mlx);
	system("aplay -q ./audio/ambience.wav &");
	mlx_loop(game->mlx);
	return (0);
}
