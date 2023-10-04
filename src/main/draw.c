/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:36:48 by dtassel           #+#    #+#             */
/*   Updated: 2023/10/04 15:32:15 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void ft_draw_player(t_cub *game)
{
    int px;
    int py;
    int dx;
    int dy;
    int dst_index;

    px = game->ray.player_x * SPRITE - (SPRITE / 2);
    py = game->ray.player_y * SPRITE - (SPRITE / 2);
    dy = 0;
    while (dy < SPRITE)
    {
        dx = 0;
        while (dx < SPRITE)
        {
            dst_index = (py + dy) * game->img2d.size_line + (px + dx) * game->img2d.bpp / 8;
            *(unsigned int *)(game->img2d.pixels + dst_index) = ft_colorpix(dx, dy, game->texture.player_map, game);
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
