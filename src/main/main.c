/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:42:03 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/25 11:26:52 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void ft_init_keys(t_cub *game)
{
    game->keys.w = 0;
    game->keys.a = 0;
    game->keys.s = 0;
    game->keys.d = 0;
    game->keys.right = 0;
    game->keys.left = 0;
    ft_init_direction(game);
}

static void ft_init_texture(t_cub *game)
{
    game->floor.r = 0;
    game->floor.g = 0;
    game->floor.b = 0;
    game->ceiling.r = 0;
    game->ceiling.g = 0;
    game->ceiling.b = 0;
    game->texture.north = NULL;
    game->texture.south = NULL;
    game->texture.east = NULL;
    game->texture.west = NULL;
}

static void ft_init_engine(t_cub *game)
{
    game->engine.total_moves = 0;
    game->engine.rotate = 0;
    game->engine.move_x = 0.0;
    game->engine.move_y = 0.0;
    game->engine.cub = NULL;
    game->engine.map = NULL;
    game->engine.coord = 'N';
    game->engine.width = 0;
    game->engine.height = 0;
}

static void ft_init_game(t_cub *game)
{
    game->mlx = NULL;
    game->window = NULL;
    game->mini = 0;
    game->count_color_c = 0;
    game->count_color_f = 0;
    game->ray.dir_x = 0.0;
    game->ray.dir_x = 0.0;
    game->ray.player_x = 2.0;
    game->ray.player_y = 2.0;
    ft_init_engine(game);
    ft_init_texture(game);
    ft_init_keys(game);
}

int main(int argc, char **argv)
{
    t_cub   *game;

    game = malloc(sizeof(t_cub));
    if (!game)
        ft_error("\nError! [Cub3D Malloc Failed]\n");
    ft_init_game(game);
    if (master_parser(game, argc, argv))
        ft_error("\nError! [Bad arguments]\n");
    ft_cub(game);
    game_over(game);
    return (0);
}
