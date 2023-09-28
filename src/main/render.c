/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:29 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/28 04:00:51 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

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

void	ft_caster(t_cub *game, double ray_angle)
{
	int		hit;
	double	ray;

	hit = 0;
	ray = ray_angle;
	game->ray.ray_x = game->ray.player_x * SPRITE;
	game->ray.ray_y = game->ray.player_y * SPRITE;
	game->ray.delta_x = cos(ray);
	game->ray.delta_y = sin(ray);
	while (hit == 0)
	{
		game->ray.ray_x += game->ray.delta_x * 0.1;
		game->ray.ray_y += game->ray.delta_y * 0.1;
		if (is_wall((int)game->ray.ray_x, (int)game->ray.ray_y, game) == 1)
		{
			game->ray.distance = sqrt(pow((game->ray.ray_x - game->ray.player_x * SPRITE), 2) + pow((game->ray.ray_y - game->ray.player_y * SPRITE), 2));
			game->ray.distance *= cos(ray - game->ray.p_angle);
			draw_ray(game, (int)game->ray.ray_x, (int)game->ray.ray_y);
			hit = 1;
		}
	}
}

void	cast_ray(t_cub *game)
{
	int		i;
	int		rays;
	double	ray;
	double	angle;
	double	start;

	i = 0;
	rays = WIDTH;
	angle = FOV / (double)rays;
	game->ray.p_angle = atan2(game->ray.dir_y, game->ray.dir_x);
	start = game->ray.p_angle - (FOV / 2.0);
	while (i < rays)
	{
		ray = start + i * angle;
		ft_caster(game, ray);
		render_3D(game, i, game->ray.distance);
		i++;
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
