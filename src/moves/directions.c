/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:59:32 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/09 15:38:08 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	ft_init_ray(t_cub *game)
{
	game->ray.ray_x = 0.0;
	game->ray.ray_y = 0.0;
	game->ray.cam_x = 0.0;
	game->ray.cam_y = 0.0;
}

static void	ft_init_poles(t_cub *game)
{
	if (game->engine.coord == 'N')
	{
		game->ray.dir_x = 0;
		game->ray.dir_y = -1;
		game->ray.plane_x = 0.66;
		game->ray.plane_y = 0;
	}
	else if (game->engine.coord == 'S')
	{
		game->ray.dir_x = 0;
		game->ray.dir_y = 1;
		game->ray.plane_x = -0.66;
		game->ray.plane_y = 0;
	}
	else
		return ;
}

static void	ft_init_cardinals(t_cub *game)
{
	if (game->engine.coord == 'E')
	{
		game->ray.dir_x = 1;
		game->ray.dir_y = 0;
		game->ray.plane_x = 0;
		game->ray.plane_y = 0.66;
	}
	else if (game->engine.coord == 'W')
	{
		game->ray.dir_x = -1;
		game->ray.dir_y = 0;
		game->ray.plane_x = 0;
		game->ray.plane_y = -0.66;
	}
	else
		return ;
}

void	ft_init_direction(t_cub *game)
{
	ft_init_poles(game);
	ft_init_cardinals(game);
}
