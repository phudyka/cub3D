/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:12:44 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/28 16:19:42 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void    ft_init_mlx(t_cub *game)
{
    game->mlx = mlx_init();
    if (game->mlx == (void *)0)
        ft_error_free("\nError! [mlx_init() has failed]\n", game);
    game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "[cub3D]");
    if (game->window == (void *)0)
        ft_error_free("\nError! [Failed to init Window]", game);
    game->img_map2D = mlx_new_image(game->mlx,
        game->engine.width * SPRITE, game->engine.height * SPRITE);
    game->img.pixels = mlx_get_data_addr(game->img_map2D,
        &game->img.bpp, &game->img.size_line, &game->img.endian);
    game->img_map3D = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->img.pixels = mlx_get_data_addr(game->img_map3D, &game->img.bpp,
        &game->img.size_line, &game->img.endian);
}