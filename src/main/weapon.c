/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:25:29 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/10 17:55:04 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	ft_shoot(t_cub *game)
{
	if (game->engine.ammo != 0)
	{
		game->engine.shooting = true;
		system("aplay -q ./audio/shoot0.wav &");
		game->engine.ammo--;
	}
	else
		system("aplay -q ./audio/shoot1.wav &");
}

void ft_reload(t_cub *game)
{
    game->engine.reloading = true;
    system("aplay -q ./audio/reload0.wav &");
    game->engine.ammo = 31;
	
}
