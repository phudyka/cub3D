/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:18:12 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/28 03:15:17 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/main.h"

void ft_init_minimap(t_cub *game)
{
    int w;
    int h;

    game->texture.wall_map = mlx_xpm_file_to_image(game->mlx, WALL_MM, &w, &h);
    if (game->texture.wall_map == (void *)0)
        ft_error_free("\nError!: [WALL image not found]\n", game);
    game->texture.floor_map = mlx_xpm_file_to_image(game->mlx, FLOOR_MM, &w, &h);
    if (game->texture.floor_map == (void *)0)
        ft_error_free("\nError!: [FLOOR image not found]\n", game);
    game->texture.player_map = mlx_xpm_file_to_image(game->mlx, PLAYER_MM, &w, &h);
    if (game->texture.player_map == (void *)0)
        ft_error_free("\nError!: [PLAYER image not found]\n", game);
}

static int key_press(int key, t_cub *game)
{
    if(key == ESC)
        game_over(game);
    if (key == W)
        game->engine.move_y = 1;
    else if (key == A)
        game->engine.move_x = -1;
    else if (key == S)
        game->engine.move_y = -1;
    else if (key == D)
        game->engine.move_x = 1;
    else if (key == LEFT)
        game->engine.rotate -= 1;
    else if (key == RIGHT)
        game->engine.rotate += 1;
    return (0);
}

static int key_release(int key, t_cub *game)
{
    if (key == ESC)
        game_over(game);
    else if (key == W && game->engine.move_y == 1)
        game->engine.move_y = 0;
    else if (key == A && game->engine.move_x == -1)
        game->engine.move_x += 1;
    else if (key == S && game->engine.move_y == -1)
        game->engine.move_y = 0;
    else if (key == D && game->engine.move_x == 1)
        game->engine.move_x -= 1;
    else if (key == LEFT && game->engine.rotate <= 1)
        game->engine.rotate = 0;
    else if (key == RIGHT && game->engine.rotate >= -1)
        game->engine.rotate = 0;
    return (0);
}

static void ft_input(t_cub *game)
{
    mlx_hook(game->window, 02, (1L<<0), key_press, game);
    mlx_hook(game->window, 03, (1L<<1), key_release, game);
    mlx_hook(game->window, 17, 0, game_over, game);
}

void ft_destroy_img(t_cub *game)
{
    if (game->texture.wall_map)
        mlx_destroy_image(game->mlx, game->texture.wall_map);
    if (game->texture.floor_map)
        mlx_destroy_image(game->mlx, game->texture.floor_map);
    if (game->texture.player_map)
        mlx_destroy_image(game->mlx, game->texture.player_map);
    if (game->img_map2D)
        mlx_destroy_image(game->mlx, game->img_map2D);
    if (game->img_map3D)
        mlx_destroy_image(game->mlx, game->img_map3D);
    mlx_destroy_window(game->mlx, game->window);
}

int  ft_cub(t_cub *game)
{
    //int     w;
    //int     h;

    //w = 25;
    //h = 14;
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
    ft_input(game);
    ft_init_minimap(game);
    mlx_loop_hook(game->mlx, ft_render, game);
    mlx_do_sync(game->mlx);
    mlx_loop(game->mlx);
    return (0);
}