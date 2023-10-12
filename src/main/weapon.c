/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:25:29 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/12 10:15:58 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	check_hit(t_cub *game, int cross_x, int cross_y)
{
	int		i;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	double	sprite_screen_x;
	double	sprite_height;
	double	hit_box_x;
	double	hit_box_y;

	i = -1;
	while (++i < game->num_sprites)
	{
		inv_det = 1.0 / (game->ray.plane_x * game->ray.dir_y - game->ray.dir_x * game->ray.plane_y);
		game->params.sprite_x = game->sprite[i].relative_x;
		game->params.sprite_y = game->sprite[i].relative_y;
		game->params.transform_x = &transform_x;
		game->params.transform_y = &transform_y;
		game->params.inv_det = inv_det;
		calculate_transform(game);
		sprite_screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
		sprite_height = abs((int)(HEIGHT / transform_y));
		hit_box_x = sprite_height * 0.3;
		hit_box_y = sprite_height * 1;
		if (abs((int)sprite_screen_x - cross_x) < hit_box_x &&
			abs((HEIGHT / 2) - (int)sprite_height / 2 - cross_y) < hit_box_y)
		{
			game->sprite[i].is_alive = 0;
			break;
		}
	}
}

void	ft_shoot(t_cub *game)
{
	double	tmp;

	if (game->engine.shoot == 1 && game->engine.ammo != 0)
	{
		game->engine.current_time = clock();
		check_hit(game, WIDTH / 2, HEIGHT / 2);
		tmp = (game->engine.current_time - game->engine.time_shoot) 
			/ CLOCKS_PER_SEC;
		if (tmp > 0.06)
		{
			game->engine.shoot = 0;
			game->engine.ammo--;
			game->engine.cooldown = 0;
		}
	}
}

void	ft_empty(t_cub *game)
{
	double	tmp;

	game->engine.current_time = clock();
	if (game->engine.shoot == 1 && game->engine.ammo == 0)
	{
		tmp = (game->engine.current_time - game->engine.time_shoot)
			/ CLOCKS_PER_SEC;
		if (tmp > 0.25)
		{
			game->engine.shoot = 0;
			game->engine.cooldown = 0;
		}
	}
}

void	ft_reload(t_cub *game)
{
	double	tmp;

	game->engine.current_time = clock();
	if (game->engine.reload == 1)
	{
		tmp = (game->engine.current_time - game->engine.time_reload)
				/ CLOCKS_PER_SEC;
		if (tmp > 0.8)
			game->engine.half = 1;
		if (tmp > 1.2)
		{
			game->engine.half = 0;
			game->engine.reload = 0;
			game->engine.ammo = 31;
			game->engine.cooldown = 0;
		}
   }
}