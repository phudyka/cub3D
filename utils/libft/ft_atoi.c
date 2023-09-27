/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:17:21 by dtassel           #+#    #+#             */
/*   Updated: 2023/09/19 04:42:43 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *str)
{
	long	atoi;
	int		sign;
	long	i;

	atoi = 0;
	sign = 1;
	i = 0;
	while ((str[i] && str[i] == ' ') || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
	{
		i++;
	}
	if (str[i] && str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		atoi = atoi * 10 + (str[i] - '0');
		i++;
	}
	return (atoi * sign);
}
/*
#include <stdio.h>

int	main()
{
	char str[] = "     +547";

	printf("%d\n", ft_atoi(str));
	return (0);
}*/
