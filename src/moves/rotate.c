/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:33:15 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/25 11:50:22 by phudyka          ###   ########.fr       */
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

int	ft_rotate(double direction, t_cub *game)
{
    int		move;
	double	speed;

    move = 0;
	speed = ROTSPEED * direction;
	move += ft_rotation(speed, game);
	return (move);
}