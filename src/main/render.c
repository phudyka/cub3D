/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:29 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/13 15:05:00 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void	ft_getstep(t_cub *game)
{
	if (game->ray.ray_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.dist_x = (game->ray.player_x - game->ray.mapx)
			* game->ray.delta_x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.dist_x = (game->ray.mapx + 1.0 - game->ray.player_x)
			* game->ray.delta_x;
	}
	if (game->ray.ray_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.dist_y = (game->ray.player_y - game->ray.mapy)
			* game->ray.delta_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.dist_y = (game->ray.mapy + 1.0 - game->ray.player_y)
			* game->ray.delta_y;
	}
}

void	ft_caster(t_cub *game)
{
	game->ray.hit = 0;
	while (game->ray.hit == 0)
	{
		if (game->ray.dist_x < game->ray.dist_y)
		{
			game->ray.dist_x += game->ray.delta_x;
			game->ray.mapx += game->ray.step_x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.dist_y += game->ray.delta_y;
			game->ray.mapy += game->ray.step_y;
			game->ray.side = 1;
		}
		if (game->engine.map[game->ray.mapy][game->ray.mapx] == '1')
			game->ray.hit = 1;
	}
}

void	cast_ray(t_cub *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		ft_init_dda(x, game);
		ft_getstep(game);
		ft_caster(game);
		render3d(x, game);
		render3d(x + 1, game);
		x += 2;
	}
}

int	ft_render(t_cub *game)
{
	game->engine.total_moves += ft_move(game);
	cast_ray(game);
	mlx_put_image_to_window(game->mlx, game->window, game->img_map3d, 0, 0);
	ft_fraps(game);
	return (0);
}
