/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:18:12 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/13 13:59:56 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	ft_destroy_img(t_cub *game)
{
	if (game->img_map3d)
		mlx_destroy_image(game->mlx, game->img_map3d);
	mlx_destroy_window(game->mlx, game->window);
}

int	ft_cub(t_cub *game)
{
	ft_init_mlx(game);
	ft_input(game);
	game->ray.z_buffer = malloc(sizeof(double) * WIDTH);
	mlx_loop_hook(game->mlx, ft_render, game);
	mlx_do_sync(game->mlx);
	mlx_loop(game->mlx);
	return (0);
}
