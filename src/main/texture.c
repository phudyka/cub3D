/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:12:44 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/02 05:23:21 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void ft_texture_pack(t_cub *game)
{
    int w;
    int h;

    game->texture.north = mlx_xpm_file_to_image(game->mlx, N_WALL, &w, &h);
    if (game->texture.north == (void *)0)
        ft_error_free("\nError ! [utils/sprite/game/north_wall.xpm]]\n", game);
    game->texture.south = mlx_xpm_file_to_image(game->mlx, S_WALL, &w, &h);
    if (game->texture.north == (void *)0)
        ft_error_free("\nError ! [utils/sprite/game/south_wall.xpm]]\n", game);
    game->texture.east = mlx_xpm_file_to_image(game->mlx, E_WALL, &w, &h);
    if (game->texture.north == (void *)0)
        ft_error_free("\nError ! [utils/sprite/game/east_wall.xpm]]\n", game);
    game->texture.west = mlx_xpm_file_to_image(game->mlx, W_WALL, &w, &h);
    if (game->texture.north == (void *)0)
        ft_error_free("\nError ! [utils/sprite/game/west_wall.xpm]]\n", game);
    game->texture.floor = mlx_xpm_file_to_image(game->mlx, FLOOR, &w, &h);
    if (game->texture.north == (void *)0)
        ft_error_free("\nError ! [utils/sprite/game/floor.xpm]]\n", game);
    game->texture.ceiling = mlx_xpm_file_to_image(game->mlx, CEILING, &w, &h);
    if (game->texture.north == (void *)0)
        ft_error_free("\nError ! [utils/sprite/game/ceiling.xpm]]\n", game);
}

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
    game->img2D.pixels = mlx_get_data_addr(game->img_map2D,
        &game->img2D.bpp, &game->img2D.size_line, &game->img2D.endian);
    game->img_map3D = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->img3D.pixels = mlx_get_data_addr(game->img_map3D, &game->img3D.bpp,
        &game->img3D.size_line, &game->img3D.endian);
    ft_texture_pack(game);
}