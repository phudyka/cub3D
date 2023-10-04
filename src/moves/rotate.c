/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:33:15 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/04 14:41:40 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../include/main.h"

static int  ft_rotation(double speed, t_cub *game)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->ray.dir_x;
	game->ray.dir_x = game->ray.dir_x * cos(speed) - game->ray.dir_y * sin(speed);
	game->ray.dir_y = old_dirx * sin(speed) + game->ray.dir_y * cos(speed);
	old_planex = game->ray.plane_x;
	game->ray.plane_x = game->ray.plane_x * cos(speed) - game->ray.plane_y * sin(speed);
    game->ray.plane_y = old_planex * sin(speed) + game->ray.plane_y * cos(speed);
	return (1);
}

static void	mouse_pos(int x, int y, t_cub *game)
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
}

static int	ft_mouse(int x, int y, t_cub *game)
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

int	ft_rotate(double direction, t_cub *game)
{
    int		move;
	double	speed;

    move = 0;
	speed = ROTSPEED * direction;
	move += ft_rotation(speed, game);
	return (move);
}

void ft_input(t_cub *game)
{
    mlx_hook(game->window, 02, (1L<<0), key_press, game);
    mlx_hook(game->window, 03, (1L<<1), key_release, game);
    mlx_hook(game->window, 06, (1L<<6), ft_mouse, game);
    mlx_hook(game->window, 17, 0, game_over, game);
}