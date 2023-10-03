/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:52:20 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/03 14:27:18 by phudyka          ###   ########.fr       */
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
    int     endian;
    char    *pix;

    pix = mlx_get_data_addr(texture, &bpp, &size_line, &endian);
    i = y * size_line + x * bpp / 8;
    return *(unsigned int *)(pix + i);
}

static void ft_texture_index(t_cub *game)
{
    if (game->ray.side == 1)
    {
        if (game->ray.dir_y < 0)
            game->texture.direction = 'N';
        else 
            game->texture.direction = 'S';
    }
    else
    {
        if (game->ray.dir_x < 0)
            game->texture.direction = 'W';
        else 
            game->texture.direction = 'E';
    }
}

static void draw_texture(int x, void *texture, t_cub *game)
{
    int     y;
    int     color;
    int     texture_x;
    int     texture_y;
    double  step;
    double  pos;

    ft_texture_index(game);
    texture_x = (int)(game->ray.wallHeight * HD);
    if ((game->ray.side == 0 && game->ray.dir_x < 0)
        || (game->ray.side == 1 && game->ray.dir_y > 0))
         texture_x = HD - texture_x - 1;
    step = 1.0 * HD / HEIGHT;
    pos = (game->ray.drawStart - HEIGHT / 2 + game->ray.wallHeight / 2) * step;
    y = game->ray.drawStart;
    while (y < game->ray.drawEnd)
    {
        texture_y = (int)pos & (HD - 1);
        pos += step;
        color = ft_colorpix(texture_x, texture_y, texture, game);
        if (game->texture.direction == 'N' || game->texture.direction == 'E')
            color = (color >> 1) & 8355711;
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
        game->ray.wallX = game->ray.player_y + game->ray.distance *game->ray.dir_y;
    else
        game->ray.wallX = game->ray.player_x + game->ray.distance *game->ray.dir_x;
    game->ray.wallX -= floor(game->ray.wallX);
    //draw_column(x, 0, game->ray.drawStart, BLUE, game);
    draw_texture(x, game->texture.north, game);
    //draw_column(x, game->ray.drawEnd, HEIGHT, BROWN, game);
}
