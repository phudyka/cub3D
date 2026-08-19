/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:51:03 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/13 14:17:34 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The three string helpers with no C standard library equivalent. Everything
** else the project took from libft (strlen, atoi, calloc, strncmp, isdigit,
** substr, strlcpy, strlcat) is now the real thing.
**
** Note ft_strjoin frees s1: callers rely on that, it is how the original
** libft here behaved.
*/

#include "../../include/main.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	size_t	len;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		((char *)s1)[0] = '\0';
	}
	if (!s2)
	{
		free((char *)s1);
		return (NULL);
	}
	len = strlen(s1) + strlen(s2);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	strlcpy(str, s1, len + 1);
	strlcat(str, s2, len + 1);
	free((char *)s1);
	return (str);
}

char	*ft_strtrim(const char *s1, const char *set, const char *setb)
{
	size_t	len;

	if (!s1 || !set || !setb)
		return (NULL);
	while ((*s1 && strchr(set, *s1)) || strchr(setb, *s1))
		s1++;
	len = strlen(s1);
	while ((strchr(set, s1[len]) || strchr(setb, s1[len])) && len > 0)
		len--;
	return (strndup(s1, len + 1));
}

static unsigned int	count_words(const char *str, char c)
{
	unsigned int	i;
	int				t;

	i = 0;
	t = 0;
	while (*str)
	{
		if (*str != c && t == 0)
		{
			t = 1;
			i++;
		}
		else if (*str == c)
			t = 0;
		str++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	i = 0;
	strs = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!strs)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		while (*s && *s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				s++;
			strs[i++] = strndup(s - len, len);
		}
	}
	strs[i] = NULL;
	return (strs);
}
