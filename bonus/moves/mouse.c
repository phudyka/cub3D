/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:55:32 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/12 10:48:09 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	mouse_pos(int x, int y, t_cub *game)
{
	if (x > WIDTH - WRAP)
	{
		x = WRAP;
		mlx_mouse_move(game->mlx, game->window, x, y);
	}
	if (x < WRAP)
	{
		x = WIDTH - WRAP;
		mlx_mouse_move(game->mlx, game->window, x, y);
	}
	mlx_mouse_hide(game->mlx, game->window);
}

int	ft_mouse(int x, int y, t_cub *game)
{
	static int	old_x = WIDTH / 2;

	mouse_pos(x, y, game);
	if (x == old_x)
		return (0);
	else if (x < old_x)
		game->engine.total_moves += ft_rotate(-1, game);
	else if (x > old_x)
		game->engine.total_moves += ft_rotate(1, game);
	old_x = x;
	return (0);
}
