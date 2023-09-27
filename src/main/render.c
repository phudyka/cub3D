/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:17:29 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/25 01:17:19 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

/*static void ft_draw_frame(int start, int end, t_cub *game)
{
    while (start <= end)
    {     
        mlx_pixel_put(game->mlx, game->window, game->ray.mapx, game->ray.mapy, RED);
        start++;
    }
}

static void ft_init_dda(int ray, t_cub *game)
{
    game->ray.mapx = (int)game->ray.player_x;
    game->ray.mapy = (int)game->ray.player_y;
    game->ray.cam_x = 2 * ray / WIDTH - 1;
    game->ray.ray_x = game->ray.dir_x + game->ray.plane_x * game->ray.cam_x;
    game->ray.ray_y = game->ray.dir_y + game->ray.plane_y * game->ray.cam_x;
    if (game->ray.dir_x == 0)
        game->ray.delta_x = 0;
    else
        game->ray.dir_x = ft_abs(1 / game->ray.dir_x);
    if (game->ray.dir_x == 0)
        game->ray.delta_y = 0;
    else
        game->ray.dir_y = ft_abs(1 / game->ray.dir_y);           
    if (game->ray.dir_x < 0)
        game->ray.dist_x = (game->ray.mapx - game->ray.dir_x) * game->ray.delta_x;
    else
        game->ray.dist_x = (game->ray.dir_x + 1.0 - game->ray.mapx) * game->ray.delta_x;      
    if (game->ray.dir_y < 0)
        game->ray.dist_y = (game->ray.mapy - game->ray.dir_y) * game->ray.delta_y;
    else
        game->ray.dist_y = (game->ray.dir_y + 1.0 - game->ray.mapy) * game->ray.delta_y;
}

static void ft_dda(t_cub * game)
{
    game->ray.hit = 0;
    while (game->ray.hit == 0)
    {
        if (game->ray.dist_x < game->ray.dist_y)
        {
            game->ray.dist_x += game->ray.delta_x;
            game->ray.mapx += game->engine.move_x;
            game->engine.wall_side = 0;
        }
        else
        {
            game->ray.dist_y += game->ray.delta_y;
            game->ray.mapy += game->engine.move_y;
            game->engine.wall_side = 1;
        }
        if (game->ray.mapx < 0.15 || game->ray.mapx < 0.15
            || game->ray.mapx > game->engine.height - 0.95
            || game->ray.mapy > game->engine.width - 0.95)
            break ;
        if (game->engine.map[game->ray.mapx][game->ray.mapy] > 0)
            game->ray.hit = 1;
    }
}

static void ft_getside(t_cub *game)
{
    int start;          // -- drawStart
    int end;            // -- drawEnd
    int line_height;    // -- lineHeight
    
    if (game->engine.wall_side == 0)
        game->ray.wall_dist = (game->ray.dist_x - game->ray.delta_x);
    else
        game->ray.wall_dist = (game->ray.dist_y - game->ray.delta_y);
    line_height = (int)game->engine.height - game->ray.wall_dist;
    start = -line_height / 2 + game->engine.height / 2;
    if (start < 0)
        start = 0;
    end = line_height / 2 + game->engine.height / 2;
    if (end >= 0)
        end = game->engine.height - 1;
    ft_draw_frame(start, end, game);
}*/

int ft_render(t_cub *game)
{
    //int ray;

    //ray = -1;
    game->engine.total_moves += ft_move(game);
    //ft_init_ray(game);
    /*while (++ray < WIDTH / 2)
    {
       ft_init_dda(ray, game);  
        ft_dda(game);
        ft_getside(game);
    }*/
    ft_minimap(game);
    return (0);
}