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

#ifdef BONUS

void	initialize_door(t_cub *game)
{
	int	i;
	int	j;

	game->engine.door = malloc(sizeof(char *) * game->engine.height);
	i = 0;
	while (i < game->engine.height)
	{
		game->engine.door[i] = strdup(game->engine.map[i]);
		j = 0;
		while (game->engine.door[i][j])
		{
			if (game->engine.door[i][j] == 'D')
				game->engine.door[i][j] = '0';
			else
				game->engine.door[i][j] = ' ';
			j++;
		}
		i++;
	}
}

void	ft_doors(t_cub *game)
{
	door_state(game->ray.player_x + 1, game->ray.player_y, game);
	door_state(game->ray.player_x - 1, game->ray.player_y, game);
	door_state(game->ray.player_x, game->ray.player_y + 1, game);
	door_state(game->ray.player_x, game->ray.player_y - 1, game);
}

#endif

void	ft_destroy_img(t_cub *game)
{
	if (game->img_map3d)
		mlx_destroy_image(game->mlx, game->img_map3d);
#ifdef BONUS
	if (game->img_map2d)
		mlx_destroy_image(game->mlx, game->img_map2d);
	if (game->weapon_3d)
		mlx_destroy_image(game->mlx, game->weapon_3d);
#endif
	mlx_destroy_window(game->mlx, game->window);
}

int	ft_cub(t_cub *game)
{
	ft_init_mlx(game);
	ft_input(game);
	game->ray.z_buffer = malloc(sizeof(double) * WIDTH);
#ifdef BONUS
	init_sprite(game);
	initialize_door(game);
#endif
	mlx_loop_hook(game->mlx, ft_render, game);
	mlx_do_sync(game->mlx);
#ifdef BONUS
	ft_audio_init();
	ft_play(AMBIENCE_WAV);
#endif
	mlx_loop(game->mlx);
	return (0);
}
