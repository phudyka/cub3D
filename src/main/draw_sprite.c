/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 03:28:52 by dtassel           #+#    #+#             */
/*   Updated: 2023/10/11 17:11:19 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void	initialize_loop_limits(int *coords, int *x_end,
	t_sprite_params *params, int sprite_screen_x)
{
	coords[0] = -params->sprite_width / 2 + sprite_screen_x;
	*x_end = params->sprite_width / 2 + sprite_screen_x;
	if (coords[0] < 0)
		coords[0] = 0;
	if (*x_end >= WIDTH)
		*x_end = WIDTH - 1;
}

static void	loop_through_sprite(t_cub *game, int coords[2], int x_end,
	t_sprite_params *params)
{
	while (++coords[0] < x_end)
	{
		if ((*game->params.transform_y > 0)
			&& (*game->params.transform_y < game->ray.z_buffer[coords[0]]))
		{
			params->x = coords[0];
			params->y = coords[1];
			draw_sprite_pixel(game, params);
		}
	}
}

void	draw_sprite(t_cub *game, int sprite_screen_x, int sprite_height)
{
	t_sprite_params	params;
	int				coords[2];
	int				y_end;
	int				x_end;

	params.sprite_height = sprite_height;
	params.sprite_screen_x = sprite_screen_x;
	params.sprite_width = abs((int)(HEIGHT / (*game->params.transform_y)));
	coords[1] = -sprite_height / 2 + HEIGHT / 2;
	y_end = sprite_height / 2 + HEIGHT / 2;
	if (coords[1] < 0)
		coords[1] = 0;
	if (y_end >= HEIGHT)
		y_end = HEIGHT - 1;
	while (++coords[1] < y_end)
	{
		initialize_loop_limits(coords, &x_end, &params, sprite_screen_x);
		loop_through_sprite(game, coords, x_end, &params);
	}
}

void	project_sprite(t_cub *game, int spriteIndex)
{
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;

	inv_det = 1.0 / (game->ray.plane_x * game->ray.dir_y - game->ray.dir_x
			* game->ray.plane_y);
	game->params.sprite_x = game->sprite[spriteIndex].relative_x;
	game->params.sprite_y = game->sprite[spriteIndex].relative_y;
	game->params.transform_x = &transform_x;
	game->params.transform_y = &transform_y;
	game->params.inv_det = inv_det;
	calculate_transform(game);
	sprite_screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
	sprite_height = abs((int)(HEIGHT / transform_y));
	draw_sprite(game, sprite_screen_x, sprite_height);
}

void	render_sprite(t_cub *game)
{
	int	i;

	i = 0;
	sort_sprites(game);
	calculate_sprite_position(game);
	while (i < game->num_sprites)
	{
		if (game->sprite[i].is_alive)
			project_sprite(game, i);
		i++;
	}
}
