/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42nice.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 09:58:24 by dtassel           #+#    #+#             */
/*   Updated: 2022/05/24 13:47:09 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

size_t	f_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*f_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == 0)
		return ((char *)s + ft_strlen(s));
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			return ((char *)s + i);
		}
		i++;
	}
	return (NULL);
}

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	i;
	size_t	len_r;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	len_r = len_dest;
	i = 0;
	if (n <= len_dest)
		return (n + len_src);
	while (len_dest < n - 1 && src[i])
	{
		dest[len_dest] = src[i];
		i++;
		len_dest++;
	}
	dest[len_dest] = '\0';
	return (len_r + len_src);
}

unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = 0;
	}
	return (ft_strlen(src));
}

char	*f_strjoin(const char *s1, const char *s2)
{
	char	*str;
	size_t	len;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		((char *)s1)[0] = '\0';
	}
	if (!s1 || !s2)
	{
		free((char *)s1);
		return (0);
	}
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len + 1);
	ft_strlcat(str, s2, len + 1);
	free ((char *)s1);
	return (str);
}
