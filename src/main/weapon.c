/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:25:29 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/11 11:57:22 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	ft_shoot(t_cub *game)
{
	double	tmp;

	game->engine.current_time = clock();
	if (game->engine.shoot == 1 && game->engine.ammo != 0)
	{
		tmp = (game->engine.current_time - game->engine.time_shoot)
			/ CLOCKS_PER_SEC;
		if (tmp > 0.08)
		{
			system("aplay -q ./audio/shoot1.wav > /dev/null 2>&1 &");
			system("aplay -q ./audio/reload.wav > /dev/null 2>&1 &");
			game->engine.ammo--;
			game->engine.shoot = 0;
		}
	}
}

void	ft_empty(t_cub *game)
{
	double	tmp;

	game->engine.current_time = clock();
	if (game->engine.shoot == 1 && game->engine.ammo == 0)
	{
		system("aplay -q ./audio/shoot0.wav > /dev/null 2>&1 &");
		system("aplay -q ./audio/shoot1.wav > /dev/null 2>&1 &");
		tmp = (game->engine.current_time - game->engine.time_shoot)
			/ CLOCKS_PER_SEC;
		if (tmp > 0.08)
		{
			game->engine.shoot = 0;
			system("aplay -q ./audio/reload.wav > /dev/null 2>&1 &");
		}
	}
}

void	ft_reload(t_cub *game)
{
	double	tmp;

	game->engine.current_time = clock();
	if (game->engine.reload == 1)
	{
		tmp = (game->engine.current_time - game->engine.time_reload)
				/ CLOCKS_PER_SEC;
		if (tmp > 1.2)
		{
			game->engine.reload = 0;
			system("aplay -q ./audio/shoot1.wav > /dev/null 2>&1 &");
			system("aplay -q ./audio/shoot0.wav > /dev/null 2>&1 &");
			system("aplay -q ./audio/reload.wav > /dev/null 2>&1 &");
		}
		game->engine.ammo = 31;
   }
}
