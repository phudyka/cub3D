/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 01:54:23 by dtassel           #+#    #+#             */
/*   Updated: 2023/10/11 11:15:50 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

bool	should_draw_pixel(int pixel_color, int color_to_ignore)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	r_ignore;
	unsigned char	g_ignore;
	unsigned char	b_ignore;

	r = (pixel_color >> 16) & 0xFF;
	g = (pixel_color >> 8) & 0xFF;
	b = pixel_color & 0xFF;
	r_ignore = (color_to_ignore >> 16) & 0xFF;
	g_ignore = (color_to_ignore >> 8) & 0xFF;
	b_ignore = color_to_ignore & 0xFF;
	return (!(r == r_ignore && g == g_ignore && b == b_ignore));
}

static void	draw_pixel(t_cub *game, int x, int y, int color)
{
	int	i;

	i = y * game->weapon.size_line + x * game->weapon.bpp / 8;
	*(unsigned int *)(game->weapon.pixels + i) = color;
}

static void	draw_or_replace_pixel(t_cub *game, int x, int y, int color, char *replace)
{
	int	i;
	int	mx;
	int	my;

	mx = WIDTH - 500;
	my = HEIGHT - 456;
	if (color)
		draw_pixel(game, x, y, color);
	else
	{
		i = (my + y) * game->img3d.size_line +
			(mx + x) * game->img3d.bpp / 8;
		draw_pixel(game, x, y, *(unsigned int *)(replace + i));
	}
}

void     ft_draw_weapon(t_cub *game)
{
   int      x;
   int      y;
   int      color;
   char  *replace;

   y = 0;
   replace = mlx_get_data_addr(game->img_map3d, &game->img3d.bpp,
         &game->img3d.size_line, &game->img3d.endian);
   while (y < 456)
   {
      x = 0;
      while (x < 500)
      {
         if (game->engine.shoot == 0 && game->engine.reload != 1)
            color = ft_colorpix_ceifloo(x, y, game->texture.weapon1, game);
         else if (game->engine.shoot == 1 && game->engine.reload != 1 && game->engine.ammo != 0)
            color = ft_colorpix_ceifloo(x, y, game->texture.shoot0, game);
         else if (game->engine.shoot == 1 && game->engine.reload != 1 && game->engine.ammo == 0)
            color = ft_colorpix_ceifloo(x, y, game->texture.shoot1, game);
         else if (game->engine.shoot != 1 && game->engine.reload == 1)
            color = ft_colorpix_ceifloo(x, y, game->texture.reload, game);
         if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
            draw_or_replace_pixel(game, x, y, color, replace);
         x++;
      }
      y++;
   }
}

void	ft_crosshair(t_cub *game)
{
	int	xy[2];
	int	start[2];
	int	dst_index;

	start[0] = WIDTH / 2;
	start[1] = HEIGHT / 2;
	xy[1] = start[1] - 15 / 2;
	while (xy[1] <= start[1] + 15 / 2)
	{
		xy[0] = start[0] - 15 / 2; 
		while (xy[0] <= start[0] + 15 / 2)
		{
			if (!((xy[0] >= start[0] - 2 && xy[0] <= start[0] + 2) && 
				  (xy[1] >= start[1] - 2 && xy[1] <= start[1] + 2)))
			{
				if ((xy[0] >= start[0] - 1 && xy[0] <= start[0] + 1) ||
					(xy[1] >= start[1] - 1 && xy[1] <= start[1] + 1))
				{
					dst_index = xy[1] * game->img3d.size_line + xy[0] * game->img3d.bpp / 8;
					*(unsigned int *)(game->img3d.pixels + dst_index) = RED;
				}
			}
			xy[0]++;
		}
		xy[1]++;
	}
}
