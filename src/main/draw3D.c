/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:52:20 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/04 11:49:45 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void	draw_column(int x, int y_start, int y_end, int color, t_cub *game)
{
	int	y;
	int	dst_index;

	y = y_start;
	while (y < y_end)
	{
		dst_index = (y * game->img3D.size_line) + (x * game->img3D.bpp / 8);
		*(unsigned int *)(game->img3D.pixels + dst_index) = color;
		y++;
	}
} 

int ft_colorpix(int x, int y, void *texture, t_cub *game)
{
    int     i;
    int     bpp;
    int     size_line;
    char    *pix;

    pix = mlx_get_data_addr(texture, &bpp, &size_line, &game->img3D.endian);
    i = y * size_line + x * bpp / 8;
    return *(unsigned int *)(pix + i);
}

static void ft_texture_index(t_cub *game)
{
    if (game->ray.side == 1)
    {
        if (game->ray.ray_y < 0)
            game->texture.direction = 'N';
        else 
            game->texture.direction = 'S';
    }
    else
    {
        if (game->ray.ray_x < 0)
            game->texture.direction = 'W';
        else 
            game->texture.direction = 'E';
    }
}

static void draw_texture(int column, int drawStart, int drawEnd, void *texture, t_cub *game)
{
    int i;
    int y;
    int color;
    int texture_y;
    double step;
    double tex_pos;

    y = drawStart;
    step = (double)HD / game->ray.wallHeight;
    tex_pos = (y - HEIGHT / 2 + game->ray.wallHeight / 2) * step;
    if (game->ray.side == 0)
        game->ray.tex_X = (int)(game->ray.wallX * (double)HD);
    else
        game->ray.tex_X = HD - (int)(game->ray.wallX * (double)HD) - 1;

    while (y < drawEnd)
    {
        texture_y = (int)tex_pos & (HD - 1);
        color = ft_colorpix(game->ray.tex_X, texture_y, texture, game);
        i = (y * game->img3D.size_line) + (column * game->img3D.bpp / 8);
        *(unsigned int *)(game->img3D.pixels + i) = color;
        tex_pos += step;
        y++;
    }
}

void render_3D(int x, t_cub *game)
{
    if (game->ray.side == 0)
		game->ray.distance = (game->ray.dist_x - game->ray.delta_x);
	else
		game->ray.distance = (game->ray.dist_y - game->ray.delta_y);
    game->ray.wallHeight = (int)(HEIGHT / game->ray.distance);
    game->ray.drawStart = -(game->ray.wallHeight) / 2 + HEIGHT / 2;
    if (game->ray.drawStart < 0)
        game->ray.drawStart = 0;
    game->ray.drawEnd = game->ray.wallHeight / 2 + HEIGHT / 2;
    if (game->ray.drawEnd >= HEIGHT)
        game->ray.drawEnd = HEIGHT - 1;
    if (game->ray.side == 0)
        game->ray.wallX = game->ray.player_y + game->ray.distance * game->ray.ray_y;
    else
        game->ray.wallX = game->ray.player_x + game->ray.distance * game->ray.ray_x;
    game->ray.wallX -= floor(game->ray.wallX);
    // draw_texture(x, game->ray.drawStart, game->ray.drawEnd, game->texture.ceiling, game);
    // draw_texture(x, game->ray.drawStart, game->ray.drawEnd, game->texture.floor, game);
    draw_column(x, 0, game->ray.drawStart, BLUE, game);
    //draw_column(x, game->ray.drawStart, game->ray.drawEnd, RED, game);
    draw_texture(x, game->ray.drawStart, game->ray.drawEnd, game->texture.south, game);
    draw_column(x, game->ray.drawEnd, HEIGHT, BROWN, game);
}
