/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:07:23 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/11 02:30:56 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

/*static int	mouse_press(int key, t_cub *game)
{
	if (key == MOUSE_R && game->engine.reloading == false)
		ft_shoot(game);
	return (0);
}*/

/*static int	mouse_release(int key, t_cub *game)
{
	if (key == MOUSE_R)
		game->engine.shooting = false;
	return (0);
}*/

static int	key_press(int key, t_cub *game)
{
	if (key == ESC)
		game_over(game);
	if (key == E)
		ft_doors(game);
	/*if (key == R && game->engine.shooting == false
			&& game->engine.reloading == false)
		ft_reload(game);*/
	if (key == 32)
	{
		game->engine.shoot = 1;
		system("aplay -q ./audio/shoot0.wav &");
		game->engine.time_shoot = game->engine.current_time;
	}
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

static int	key_release(int key, t_cub *game)
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

void	ft_input(t_cub *game)
{
	mlx_hook(game->window, 02, (1L << 0), key_press, game);
	mlx_hook(game->window, 03, (1L << 1), key_release, game);
	mlx_hook(game->window, 06, (1L << 6), ft_mouse, game);
	//mlx_hook(game->window, 03, (1L << 2), mouse_press, game);
	//mlx_hook(game->window, 05, (1L << 3), mouse_release, game);
	mlx_hook(game->window, 17, 0, game_over, game);
}