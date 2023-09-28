/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:52:20 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/28 16:18:14 by phudyka          ###   ########.fr       */
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
	draw_column(column, drawStart, drawEnd, GREY, game);
	draw_column(column, drawEnd, HEIGHT, BROWN, game);
}
