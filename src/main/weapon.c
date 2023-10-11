/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:25:29 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/11 02:32:59 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void    ft_shoot(t_cub *game)
{
    double tmp;
    
    game->engine.current_time = clock();
	if (game->engine.shoot == 1)
	{
		tmp = (game->engine.current_time - game->engine.time_shoot)
            / CLOCKS_PER_SEC;
		if (tmp > 0.1)
			game->engine.shoot = 0;
	}
}

/*void	ft_shoot(t_cub *game)
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
	
}*/
