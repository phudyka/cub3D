/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:52:20 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/27 03:25:50 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

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

static void draw_column(int column, int y_start, int y_end, int color, t_cub *game, int offsetX, int offsetY)
{
    int y;

    y = y_start;
    while (y < y_end)
    {
        mlx_pixel_put(game->mlx, game->window, column + offsetX, y + offsetY, color);
        y++;
    }
}

void render_3D(t_cub *game, int column, double distance)
{
    int wallHeight;
    int drawStart;
    int drawEnd;
    int y;

    int offsetX = game->engine.width * SPRITE; // Décalage pour la minimap
    int offsetY = 0;

    wallHeight = (int)(HEIGHT / distance * 5);

    drawStart = -wallHeight / 2 + HEIGHT / 2;
    drawEnd = wallHeight / 2 + HEIGHT / 2;

    if (drawStart < 0)
        drawStart = 0;
    if (drawEnd >= HEIGHT)
        drawEnd = HEIGHT - 1;

    y = 0;
    draw_column(column, y, drawStart, BLUE, game, offsetX, offsetY);
    draw_column(column, drawStart, drawEnd, GREY, game, offsetX, offsetY);
    draw_column(column, drawEnd, HEIGHT, BROWN, game, offsetX, offsetY);
}

static void ft_draw_minimap(int x, int y, char *img, t_cub *game)
{
    int px;
    int py;
    int dx;
    int dy;
    int size;

    dy = 0;
    size = 10;
    px = game->ray.player_x * SPRITE - (size / 2);
    py = game->ray.player_y * SPRITE - (size / 2);
    x *= SPRITE;
    y *= SPRITE;
    mlx_put_image_to_window(game->mlx, game->window, img, x, y);
    while (dy < size)
    {
        dx = 0;
        while (dx < size)
        {
            mlx_pixel_put(game->mlx, game->window, px + dx,
                py + dy, GREEN_WALL);
            dx++;
        }
        dy++;
    }
}

void draw_ray(t_cub *game, int ray_x, int ray_y)
{
    int dx; // longueur du rayon.
    int dy;
    int steps;   // nombre de pixel a allumer;
    double Xinc; // sert pour incrementer X.
    double Yinc;
    double X; // pixel a allumer.
    double Y;
    int i;

    i = 0;
    dx = ray_x - (game->ray.player_x * SPRITE);
    dy = ray_y - (game->ray.player_y * SPRITE);
    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);
    Xinc = (double)dx / (double)steps;
    Yinc = (double)dy / (double)steps;
    X = game->ray.player_x * SPRITE;
    Y = game->ray.player_y * SPRITE;
    while (i <= steps)
    {
        mlx_pixel_put(game->mlx, game->window, (int)X, (int)Y, RED);
        X += Xinc;
        Y += Yinc;
        i++;
    }
}

int is_wall(int x, int y, t_cub *game)
{
    int mapx;
    int mapy;

    mapx = x / SPRITE;
    mapy = y / SPRITE;
    if (mapx < 0 || mapx >= game->engine.width || mapy < 0 || mapy >= game->engine.height)
        return (0);
    if (game->engine.map[mapy][mapx] == '1')
        return (1);
    return (0);
}

void ft_caster(t_cub *game, double ray_angle)
{
    int hit;
    double ray;

    hit = 0;
    ray = ray_angle;

    game->ray.ray_x = game->ray.player_x * SPRITE;
    game->ray.ray_y = game->ray.player_y * SPRITE;
    game->ray.delta_x = cos(ray);
    game->ray.delta_y = sin(ray);

    while (hit == 0)
    {
        game->ray.ray_x += game->ray.delta_x * 0.1;
        game->ray.ray_y += game->ray.delta_y * 0.1;

        if (is_wall((int)game->ray.ray_x, (int)game->ray.ray_y, game) == 1)
        {
            game->ray.distance = sqrt(pow((game->ray.ray_x - game->ray.player_x * SPRITE), 2) + pow((game->ray.ray_y - game->ray.player_y * SPRITE), 2));
            game->ray.distance *= cos(ray - game->ray.p_angle);

            draw_ray(game, (int)game->ray.ray_x, (int)game->ray.ray_y);
            hit = 1;
        }
    }
}

void cast_ray(t_cub *game)
{
    int i;
    int rays;
    double ray;
    double angle;
    double start;

    i = 0;
    rays = WIDTH;
    angle = FOV / (double)rays;
    game->ray.p_angle = atan2(game->ray.dir_y, game->ray.dir_x);

    start = game->ray.p_angle - (FOV / 2.0);

    while (i < rays)
    {
        ray = start + i * angle;
        ft_caster(game, ray);
        render_3D(game, i, game->ray.distance);
        i++;
    }
}

void ft_minimap(t_cub *game)
{
    int x;
    int y;
    char *img;

    y = 0;
    while (game->engine.map[y])
    {
        x = 0;
        while (game->engine.map[y][x])
        {
            if (game->engine.map[y][x] == '0')
                img = game->texture.floor_map;
            else if (game->engine.map[y][x] == '1')
                img = game->texture.wall_map;
            ft_draw_minimap(x, y, img, game);
            x++;
        }
        y++;
    }
    cast_ray(game);
}