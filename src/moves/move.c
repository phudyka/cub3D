/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:47:41 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/09 15:39:15 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static int	move_ok(double x, double y, t_cub *game)
{
	double	player_size;

	player_size = 0.15;
	if (game->engine.map[(int)(y)][(int)(x)] == '1')
		return (1);
	if (game->engine.map[(int)(y + player_size)][(int)(x + player_size)] == '1')
		return (1);
	if (game->engine.map[(int)(y - player_size)][(int)(x - player_size)] == '1')
		return (1);
	if (game->engine.map[(int)(y + player_size)][(int)(x - player_size)] == '1')
		return (1);
	if (game->engine.map[(int)(y - player_size)][(int)(x + player_size)] == '1')
		return (1);
	if (x < player_size || x >= game->engine.width - 1.0 - player_size)
		return (1);
	if (y < player_size || y >= game->engine.height - 1.0 - player_size)
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
