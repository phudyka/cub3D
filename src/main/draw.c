/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:36:48 by dtassel           #+#    #+#             */
/*   Updated: 2023/09/28 02:16:08 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	draw_ray(t_cub *game, int ray_x, int ray_y)
{
	int		dxy[2]; /*longueur du rayon.*/
	int		steps;  /*nombre de pixel à allumer*/
	int 	dst_i;
	double	Xinc; /*sert pour incrémenter X*/
	double	Yinc;
	double	X; /*pixel à allumer.*/
	double	Y;
	int		i;

	i = 0;
	dxy[1] = ray_x - (game->ray.player_x * SPRITE);
	dxy[2] = ray_y - (game->ray.player_y * SPRITE);
	steps = abs(dxy[2]);
	if (abs(dxy[1]) > abs(dxy[2]))
		steps = abs(dxy[1]);
	Xinc = (double)dxy[1] / (double)steps;
	Yinc = (double)dxy[2] / (double)steps;
	X = game->ray.player_x * SPRITE;
	Y = game->ray.player_y * SPRITE;
	while (i++ <= steps)
	{
		dst_i = ((int)Y) * game->img2D.size_line + ((int)X) * game->img2D.bpp / 8;
		*(unsigned int *)(game->img2D.pixels + dst_i) = RED;
		X += Xinc;
		Y += Yinc;
	}
}

static void	ft_draw_player(t_cub *game)
{
	int	px;
	int	py;
	int	dx;
	int	dy;
	int	dst_index;

	px = game->ray.player_x * SPRITE - (10 / 2);
	py = game->ray.player_y * SPRITE - (10 / 2);
	dy = 0;
	while (dy < 10)
	{
		dx = 0;
		while (dx < 10)
		{
			dst_index = (py + dy) * game->img2D.size_line + (px + dx) * game->img2D.bpp / 8;
			*(unsigned int *)(game->img2D.pixels + dst_index) = GREEN_WALL;
			dx++;
		}
		dy++;
	}
}

void	ft_draw_minimap(int x, int y, void *img_src, t_cub *game)
{
	char	*src_pixels;
	char	*dst_pixels;
	int		src_dst_info[6];
	int		src_index;
	int		dst_index;
	int		dx;
	int		dy;

	src_pixels = mlx_get_data_addr(img_src, &src_dst_info[0], &src_dst_info[1], &src_dst_info[2]);
	dst_pixels = mlx_get_data_addr(game->img_map2D, &src_dst_info[3], &src_dst_info[4], &src_dst_info[5]);
	x *= SPRITE;
	y *= SPRITE;
	dy = 0;
	while (dy < SPRITE)
	{
		dx = 0;
		while (dx < SPRITE)
		{
			src_index = dy * src_dst_info[1] + dx * src_dst_info[0] / 8;
			dst_index = (y + dy) * src_dst_info[4] + (x + dx) * src_dst_info[3] / 8;
			*(unsigned int *)(dst_pixels + dst_index) = *(unsigned int *)(src_pixels + src_index);
			dx++;
		}
		dy++;
	}
	ft_draw_player(game);
}
