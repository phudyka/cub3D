/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:52:20 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/02 07:32:25 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void	draw_column(int column, int y_start, int y_end, int color, t_cub *game)
{
	int	y;
	int	dst_index;

	y = y_start;
	while (y < y_end)
	{
		dst_index = (y * game->img3D.size_line) + (column * game->img3D.bpp / 8);
		*(unsigned int *)(game->img3D.pixels + dst_index) = color;
		y++;
	}
} 

int ft_colorpix(int x, int y, void *texture, t_cub *game)
{
    int     i;
    int     bpp;
    int     size_line;
	int		endian;
    char    *pix;

    pix = mlx_get_data_addr(texture, &bpp, &size_line, &endian);
    i = y * size_line + x * bpp / 8;
    return *(unsigned int *)(pix + i);
}

static void draw_texture(int column, int drawStart, int drawEnd, void *texture, t_cub *game)
{
	int	i;
    int y;
    int color;
    int texture_y;
	int	texture_x;
    double step;
    double tex_pos;

    y = drawStart;
    step = 1.0 * 64 / game->ray.wallHeight;
    tex_pos = (drawStart - HEIGHT / 2 + game->ray.wallHeight / 2) * step;
	texture_x = (int)(game->ray.ray_x) % 64;
    while (y < drawEnd)
    {
        texture_y = (int)tex_pos % 64;
        color = ft_colorpix(texture_x, texture_y, texture, game);
        i = (y * game->img3D.size_line) + (column * game->img3D.bpp / 8);
        *(unsigned int *)(game->img3D.pixels + i) = color;
        tex_pos += step;
        y++;
    }
}

void render_3D(t_cub *game, int column, double distance)
{
    int y;
    int drawStart;
    int drawEnd;

    game->ray.wallHeight = (int)(HEIGHT / distance * 15);
    drawStart = -game->ray.wallHeight / 2 + HEIGHT / 2;
    drawEnd = game->ray.wallHeight / 2 + HEIGHT / 2;

    if (drawStart < 0)
        drawStart = 0;
    if (drawEnd >= HEIGHT)
        drawEnd = HEIGHT - 1;

    y = 0;
    draw_column(column, y, drawStart, BLUE, game);
    draw_texture(column, drawStart, drawEnd, game->texture.east, game);
    draw_column(column, drawEnd, HEIGHT, BROWN, game);
}
