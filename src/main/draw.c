/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:36:48 by dtassel           #+#    #+#             */
/*   Updated: 2023/10/13 14:19:13 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

/*
** Fog factor for a wall column. Depends only on ray distance, so it is
** computed once per column instead of once per pixel. 0 = no fog (raw
** texel), 1 = fully black (far walls skip texture sampling entirely).
*/
float	wall_fog(double dist)
{
	if (dist < 10)
		return (0.0f);
	if (dist < 20)
		return (0.1f + (dist - 10.0f) * 0.09f);
	return (1.0f);
}
