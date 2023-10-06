/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:12:44 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/06 08:26:03 by phudyka          ###   ########.fr       */
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
    if (game->texture.south == (void *)0)
        ft_error_free("\nError ! [utils/sprite/game/south_wall.xpm]]\n", game);
    game->texture.east = mlx_xpm_file_to_image(game->mlx, E_WALL, &w, &h);
    if (game->texture.east == (void *)0)
        ft_error_free("\nError ! [utils/sprite/game/east_wall.xpm]]\n", game);
    game->texture.west = mlx_xpm_file_to_image(game->mlx, W_WALL, &w, &h);
    if (game->texture.west == (void *)0)
        ft_error_free("\nError ! [utils/sprite/game/west_wall.xpm]]\n", game);
    game->texture.floor = mlx_xpm_file_to_image(game->mlx, FLOOR, &w, &h);
    if (game->texture.floor == (void *)0)
        ft_error_free("\nError ! [utils/sprite/game/floor.xpm]]\n", game);
    game->texture.ceiling = mlx_xpm_file_to_image(game->mlx, CEILING, &w, &h);
    if (game->texture.ceiling == (void *)0)
        ft_error_free("\nError ! [utils/sprite/game/ceiling.xpm]]\n", game);
    game->texture.weapon1 = mlx_xpm_file_to_image(game->mlx, WEAPON1, &w, &h);
    if (game->texture.weapon1 == (void *)0)
        ft_error_free("\nError ! [utils/sprite/game/weapon1.xpm]]\n", game);
}

void    ft_init_mlx(t_cub *game)
{
    game->mlx = mlx_init();
    if (game->mlx == (void *)0)
        ft_error_free("\nError! [mlx_init() has failed]\n", game);
    game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "[cub3D]");
    if (game->window == (void *)0)
        ft_error_free("\nError! [Failed to init Window]", game);
    game->img_map2d = mlx_new_image(game->mlx,
        game->engine.width * SPRITE, game->engine.height * SPRITE);
    game->img2d.pixels = mlx_get_data_addr(game->img_map2d,
        &game->img2d.bpp, &game->img2d.size_line, &game->img2d.endian);
    game->img_map3d = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->img3d.pixels = mlx_get_data_addr(game->img_map3d, &game->img3d.bpp,
        &game->img3d.size_line, &game->img3d.endian);
    ft_texture_pack(game);
}