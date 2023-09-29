/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:52:20 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/29 15:59:35 by phudyka          ###   ########.fr       */
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
		dst_index = (y * game->img.size_line) + (column * game->img.bpp / 8);
		*(unsigned int *)(game->img.pixels + dst_index) = color;
		y++;
	}
} 

int ft_colorpix(int x, int y, void *texture, t_cub *game)
{
    int     i;
    int     bpp;
    int     size_line;
    char    *pix;

    pix = mlx_get_data_addr(texture, &bpp, &size_line, &game->img.endian);
    i = y * size_line + x * bpp / 8;
    return *(unsigned int *)(pix + i);
}

static void draw_texture_wall(int column, int y_start, int y_end, void *texture, t_cub *game)
{
    int y;
    int color;
    double tex_x;
    double tex_y;
    double step;
    int dst_index;
	
	y = y_start;
    step =  64.0 / (double)(y_end - y_start);
    while (y < y_end)
    {
        tex_x = (column * 64.0) / game->img.width;
        tex_y = (y - y_start) * step;
        color = ft_colorpix((int)tex_x, (int)tex_y, texture, game);
        dst_index = (y * game->img.size_line) + (column * game->img.bpp / 8);
        *(unsigned int *)(game->img.pixels + dst_index) = color;
        y++;
    }
}

void	render_3D(t_cub *game, int column, double distance)
{
	int	wallHeight;
	int	drawStart;
	int	drawEnd;
	int	y;

	wallHeight = (int)(HEIGHT / distance * 10);
	drawStart = -wallHeight / 2 + HEIGHT / 2;
	drawEnd = wallHeight / 2 + HEIGHT / 2;
	if (drawStart < 0)
		drawStart = 0;
	if (drawEnd >= HEIGHT)
		drawEnd = HEIGHT - 1;
	y = 0;
	draw_column(column, y, drawStart, BLUE, game);
	//draw_column(column, drawStart, drawEnd, GREY, game);
	draw_texture_wall(column, drawStart, drawEnd, game->texture.south, game);
	draw_column(column, drawEnd, HEIGHT, BROWN, game);
}
