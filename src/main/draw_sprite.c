/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 03:28:52 by dtassel           #+#    #+#             */
/*   Updated: 2023/10/10 01:18:50 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	calculate_sprite_position(t_cub *game)
{
	int		i;

	i = 0;
	while (i < game->num_sprites)
	{
		game->sprite[i].relative_x = game->sprite[i].x - game->ray.player_x;
		game->sprite[i].relative_y = game->sprite[i].y - game->ray.player_y;
		i++;
	}
}

void	sort_sprites(t_cub *game)
{
	double		distance1;
	double		distance2;
	int			i;
	int			j;
	t_sprite	temp;

	i = -1;
	while (++i < game->num_sprites)
	{
		j = i + 1;
		while (++j < game->num_sprites)
		{
			distance1 = pow(game->ray.player_x - game->sprite[i].x, 2)
				+ pow(game->ray.player_y - game->sprite[i].y, 2);
			distance2 = pow(game->ray.player_x - game->sprite[j].x, 2)
				+ pow(game->ray.player_y - game->sprite[j].y, 2);
			if (distance1 < distance2)
			{
				temp = game->sprite[i];
				game->sprite[i] = game->sprite[j];
				game->sprite[j] = temp;
			}
		}
	}
}

void	calculate_transform(t_cub *game)
{
	*game->params.transform_x = game->params.inv_det
		* (game->ray.dir_y * game->params.sprite_x
			- game->ray.dir_x * game->params.sprite_y);
	*game->params.transform_y = game->params.inv_det
		* (-game->ray.plane_y * game->params.sprite_x
			+ game->ray.plane_x * game->params.sprite_y);
}

void	draw_sprite_pixel(t_cub *game, t_sprite_params *params)
{
	int		tex_x;
	int		tex_y;
	int		color;
	int		dst_index;

	tex_x = (params->x - (-params->sprite_width / 2 + params->sprite_screen_x))
		* game->sprite[0].width / params->sprite_width;
	tex_y = (params->y - (-params->sprite_height / 2 + HEIGHT / 2))
		* game->sprite[0].height / params->sprite_height;
	color = ft_colorpix_ceifloo(tex_x, tex_y, game->texture.target, game);
	if (color != 0)
	{
		dst_index = params->y * game->img3d.size_line + params->x
			* game->img3d.bpp / 8;
		*(unsigned int *)(game->img3d.pixels + dst_index) = color;
	}
}

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
		project_sprite(game, i);
		i++;
	}
}
