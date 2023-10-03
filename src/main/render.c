/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:29 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/03 14:26:17 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void init_dda(int x, t_cub *game)
{
	game->ray.cam_x = 2 * x / (double)WIDTH - 1;
	game->ray.ray_x = game->ray.dir_x + game->ray.plane_x * game->ray.cam_x;
	game->ray.ray_y = game->ray.dir_y + game->ray.plane_y * game->ray.cam_x;
	game->ray.mapx = (int)game->ray.player_x;
	game->ray.mapy = (int)game->ray.player_y;
	game->ray.delta_x = fabs(1 / game->ray.dir_x);
	game->ray.delta_x = fabs(1 / game->ray.dir_y);

}
int	is_wall(int x, int y, t_cub *game)
{
	int	mapx;
	int	mapy;

	mapx = x / SPRITE;
	mapy = y / SPRITE;
	if (mapx < 0 || mapx >= game->engine.width || mapy < 0
		|| mapy >= game->engine.height)
		return (0);
	if (game->engine.map[mapy][mapx] == '1')
		return (1);
	return (0);
}

static void	ft_getstep(t_cub *game)
{
	if (game->ray.ray_x < 0)
	{
		game->ray.stepX = -1;
		game->ray.dist_x = (game->ray.player_x - game->ray.mapx) * game->ray.delta_x;
	}
	else
	{
		game->ray.stepX = 1;
		game->ray.dist_x = (game->ray.mapx + 1.0 - game->ray.player_x) * game->ray.delta_x;
	}
	if (game->ray.ray_y < 0)
	{
		game->ray.stepY = -1;
		game->ray.dist_y = (game->ray.player_y - game->ray.mapy) * game->ray.delta_y;
	}
	else
	{
		game->ray.stepY = 1;
		game->ray.dist_y = (game->ray.mapy + 1.0 - game->ray.player_y) * game->ray.delta_y;
	}
}

void	ft_caster(t_cub *game)
{
	int		hit;

	hit = 0;
	while (hit == 0)
	{
		if (game->ray.dist_x < game->ray.dist_y)
		{
			game->ray.dist_x += game->ray.delta_x;
			game->ray.mapx += game->ray.stepX;
			game->ray.side = 0;
		}
		else
		{
			game->ray.dist_y += game->ray.delta_y;
			game->ray.mapy += game->ray.stepY;
			game->ray.side = 1;	
		}
		if (game->ray.mapy < 0.25 || game->ray.mapx < 0.25
			|| game->ray.mapy > game->engine.height - 0.25
			|| game->ray.mapx > game->engine.width - 1.25)
			break ;
		else if (game->engine.map[game->ray.mapy][game->ray.mapx] == 1)
			hit = 1;
	}
}

void	cast_ray(t_cub *game)
{
	int		x;
	
	x = 0;
	while (x < WIDTH)
	{
		init_dda(x, game);
		ft_getstep(game);
		ft_caster(game);
		render_3D(x, game);
		x++;
	}
}

void	draw(t_cub *game)
{
	int		x;
	int		y;
	char	*img;

	y = 0;
	while (game->engine.map[y])
	{
		x = 0;
		while (game->engine.map[y][x])
		{
			if (game->engine.map[y][x] == '0')
				img = game->texture.floor_map;
			else if (game->engine.map[y][x] == '1')
				img = game->texture.wall_map;
			ft_draw_minimap(x, y, img, game);
			x++;
		}
		y++;
	}
	cast_ray(game);
}

int	ft_render(t_cub *game)
{
	game->engine.total_moves += ft_move(game);
	draw(game);
	mlx_put_image_to_window(game->mlx, game->window,
		game->img_map3D, 0, 0);
	mlx_put_image_to_window(game->mlx, game->window, game->img_map2D, 0, HEIGHT - (game->engine.height * SPRITE));
	return (0);
}
