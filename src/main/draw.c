/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:36:48 by dtassel           #+#    #+#             */
/*   Updated: 2023/10/09 15:26:11 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void    mix_colors(unsigned int *color, float fog_factor,
						  unsigned int fog_color)
{
	unsigned char original_r = (*color >> 16) & 0xFF;
	unsigned char original_g = (*color >> 8) & 0xFF;
	unsigned char original_b = *color & 0xFF;
	unsigned char fog_r = (fog_color >> 16) & 0xFF;
	unsigned char fog_g = (fog_color >> 8) & 0xFF;
	unsigned char fog_b = fog_color & 0xFF;
	unsigned char final_r = (1 - fog_factor) * original_r + fog_factor * fog_r;
	unsigned char final_g = (1 - fog_factor) * original_g + fog_factor * fog_g;
	unsigned char final_b = (1 - fog_factor) * original_b + fog_factor * fog_b;
	*color = (final_r << 16) | (final_g << 8) | final_b;
}

int ft_colorpix_ceifloo(int x, int y, void *texture, t_cub *game)
{
	int             i;
	int				bpp;
	int				size_line;
	unsigned int    color;
	char            *pix;
	float           fog_factor;
	
	pix = mlx_get_data_addr(texture, &bpp, &size_line, &game->img3d.endian);
	i = y * size_line + x * bpp / 8;
	color = *(unsigned int *)(pix + i);
	return (color);
}

int ft_colorpix(int x, int y, void *texture, t_cub *game)
{
	int             i;
	int				bpp;
	int				size_line;
	unsigned int    color;
	char            *pix;
	float           fog_factor;
	
	pix = mlx_get_data_addr(texture, &bpp, &size_line, &game->img3d.endian);
	i = y * size_line + x * bpp / 8;
	color = *(unsigned int *)(pix + i);
	if (game->ray.distance < 10)
		fog_factor = 0;
	else if (game->ray.distance < 20)
		fog_factor = 0.1 + (game->ray.distance - 10) * 0.09;
	else
		fog_factor = 1.0;
	mix_colors(&color, fog_factor, 0x000000);
	return (color);
}

static void     ft_draw_player(t_cub *game)
{
        int     px;
        int     py;
        int     dx;
        int     dy;
        int     dst_index;

        px = game->ray.player_x * SPRITE - (7 / 2);
        py = game->ray.player_y * SPRITE - (7 / 2);
        dy = 0;
        while (dy < 7)
        {
                dx = 0;
                while (dx < 7)
                {
                        dst_index = (py + dy) * game->img2d.size_line + (px + dx) * game->img2d.bpp / 8;
                        *(unsigned int *)(game->img2d.pixels + dst_index) = RED;
                        dx++;
                }
                dy++;
        }
}

void	ft_draw_minimap(int x, int y, int *color, t_cub *game)
{
	int		dx;
	int		dy;
	char	*dst_pixels;
	int		dst_index;

	dst_pixels = mlx_get_data_addr(game->img_map2d, &game->img2d.bpp, &game->img2d.size_line, &game->img2d.endian);
	x *= SPRITE;
	y *= SPRITE;
	dy = 0;
	while (dy < SPRITE)
	{
		dx = 0;
		while (dx < SPRITE)
		{
			dst_index = (y + dy) * game->img2d.size_line + (x + dx) * game->img2d.bpp / 8;
			*(unsigned int *)(dst_pixels + dst_index) = *color;
			dx++;
		}
		dy++;
	}
	ft_draw_player(game);
}
