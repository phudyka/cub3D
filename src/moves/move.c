/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:47:41 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/10 06:51:41 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void door_state(int x, int y, t_cub *game)
{
    if (game->engine.map[y][x] == 'D')
    {
        if (game->engine.door[y][x] == '0')
            game->engine.door[y][x] = '1';
        else
            game->engine.door[y][x] = '0';
    }
}

static int	move_ok(double x, double y, t_cub *game)
{
	double	player_size;
	int		x_int;
	int		y_int;

	player_size = 0.15;
	x_int = (int)x;
	y_int = (int)y;
	if (game->engine.map[y_int][x_int] == '1')
		return (1);
	if (game->engine.map[y_int][x_int] == 'D')
		if (game->engine.door[y_int][x_int] == '0')
			return (1);
	if (game->engine.map[(int)(y + player_size)][(int)(x + player_size)] == '1')
		return (1);
	if (game->engine.map[(int)(y - player_size)][(int)(x - player_size)] == '1')
		return (1);
	if (game->engine.map[(int)(y + player_size)][(int)(x - player_size)] == '1')
		return (1);
	if (game->engine.map[(int)(y - player_size)][(int)(x + player_size)] == '1')
		return (1);
	if (x < player_size || x >= game->engine.width - 1 - player_size)
		return (1);
	if (y < player_size || y >= game->engine.height - 1 - player_size)
		return (1);
	return (0);
}

int	check_move(double x, double y, t_cub *game)
{
	int	move;

	move = 0;
	if (move_ok(x, y, game) == 0)
	{
		game->ray.player_x = x;
		game->ray.player_y = y;
		move = 1;
	}
	return (move);
}
