/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:18:12 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/28 15:52:37 by phudyka          ###   ########.fr       */
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

int key_press(int key, t_cub *game)
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

int key_release(int key, t_cub *game)
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
    ft_init_mlx(game);
    ft_input(game);
    ft_init_minimap(game);
    mlx_loop_hook(game->mlx, ft_render, game);
    mlx_do_sync(game->mlx);
    mlx_loop(game->mlx);
    return (0);
}