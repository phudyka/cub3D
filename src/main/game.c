/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:18:12 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/22 16:37:51 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/main.h"

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
    mlx_destroy_window(game->mlx, game->window);
}

int  ft_cub(t_cub *game)
{
    int w;
    int h;

    w = 25;
    h = 14;
    game->mlx = mlx_init();
    if (game->mlx == (void *)0)
        ft_error_free("\nError! [mlx_init() has failed]\n", game);
    game->window = mlx_new_window(game->mlx, w * 64, h * 64, "[cub3D]");
    if (game->window == (void *)0)
        ft_error_free("\nError! [Failed to init Window]", game);
    ft_init_minimap(game);
    ft_input(game);
    mlx_loop_hook(game->mlx, ft_render, game);
    mlx_do_sync(game->mlx);
    mlx_loop(game->mlx);
    return (0);
}