/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:47:53 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/09 15:40:42 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static int	ft_forward(t_cub *game)
{
	int		move;
	double	new_x;
	double	new_y;

	move = 0;
	new_x = game->ray.player_x + game->ray.dir_x * MOVESPEED;
	new_y = game->ray.player_y + game->ray.dir_y * MOVESPEED;
	move = check_move(new_x, new_y, game);
	return (move);
}

static int	ft_backward(t_cub *game)
{
	int		move;
	double	new_x;
	double	new_y;

	move = 0;
	new_x = game->ray.player_x - game->ray.dir_x * MOVESPEED;
	new_y = game->ray.player_y - game->ray.dir_y * MOVESPEED;
	move = check_move(new_x, new_y, game);
	return (move);
}

static int	ft_left(t_cub *game)
{
	int		move;
	double	new_x;
	double	new_y;

	move = 0;
	new_x = game->ray.player_x + game->ray.dir_y * MOVESPEED;
	new_y = game->ray.player_y - game->ray.dir_x * MOVESPEED;
	move = check_move(new_x, new_y, game);
	return (move);
}

static int	ft_right(t_cub *game)
{
	int		move;
	double	new_x;
	double	new_y;

	move = 0;
	new_x = game->ray.player_x - game->ray.dir_y * MOVESPEED;
	new_y = game->ray.player_y + game->ray.dir_x * MOVESPEED;
	move = check_move(new_x, new_y, game);
	return (move);
}

int	ft_move(t_cub *game)
{
	int	move;

	move = 0;
	if (game->engine.move_y == 1)
		move += ft_forward(game);
	if (game->engine.move_y == -1)
		move += ft_backward(game);
	if (game->engine.move_x == -1)
		move += ft_left(game);
	if (game->engine.move_x == 1)
		move += ft_right(game);
	if (game->engine.rotate != 0)
		move += ft_rotate(game->engine.rotate, game);
	return (move);
}
