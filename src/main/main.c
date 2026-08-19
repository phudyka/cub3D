/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:42:03 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/13 16:29:21 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

/*
** calloc, not malloc: every pointer, counter and timestamp in t_cub starts
** zeroed. This replaces about fifty lines that set each field by hand and
** still missed some -- dt, now and current_time were read uninitialised
** before valgrind pointed it out. Only genuinely non-zero defaults are set
** here, so a new field can never be forgotten again.
*/
static t_cub	*ft_init_game(void)
{
	t_cub	*game;

	game = calloc(1, sizeof(t_cub));
	if (!game)
		ft_error("Error!\n[Cub3D Malloc Failed]\n");
	game->engine.ammo = 31;
	return (game);
}

int	main(int argc, char **argv)
{
	t_cub	*game;

	game = ft_init_game();
	if (master_parser(game, argc, argv))
		ft_error("Error!\n[Bad arguments]\n");
	print_cub();
	ft_init_direction(game);
	ft_cub(game);
	game_over(game);
	return (0);
}
