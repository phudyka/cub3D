/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:41:21 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/12 14:15:59 by phudyka          ###   ########.fr       */
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

void	ft_target_repop(t_cub *game)
{
	int	i;
	int	num;

	i = 0;
	num = game->num_sprites;
	if (game->texture.repop == 1)
	{
		while (num)
		{
			game->sprite[i].is_alive = 1;
			i++;
			num--;
		}
		system("aplay -q ./audio/target.wav &");
		game->texture.repop = 0;
	}
}
