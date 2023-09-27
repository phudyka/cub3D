/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:10:21 by dtassel           #+#    #+#             */
/*   Updated: 2023/09/18 01:19:59 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include "../libft/libft.h"

char	*ft_save(char *reader)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (reader[i] && reader[i] != '\n')
		i++;
	if (!reader[i])
	{
		free (reader);
		return (NULL);
	}
	str = malloc(sizeof(char) * ft_strlen(reader) - i + 1);
	if (!str)
		return (NULL);
	i++;
	while (reader[i])
	{
		str[j++] = reader[i++];
	}
	str[j] = '\0';
	free(reader);
	return (str);
}

char	*ft_line(char *reader)
{
	char	*str;
	int		i;

	i = 0;
	if (!reader[i])
		return (NULL);
	str = malloc(sizeof(char) * ft_strlen(reader) + 1);
	if (!str)
		return (NULL);
	while (reader[i] && reader[i] != '\n')
	{
		str[i] = reader[i];
		i++;
	}
	if (reader[i] == '\n')
	{
		str[i] = reader[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_read(int fd, char *reader)
{
	char	*str;
	int		i;

	i = 1;
	str = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	while (!f_strchr(reader, '\n') && i != 0)
	{
		i = read(fd, str, BUFFER_SIZE);
		if (i == -1)
		{
			free(str);
			return (NULL);
		}
		str[i] = '\0';
		reader = f_strjoin(reader, str);
	}
	free(str);
	return (reader);
}

char	*get_next_line(int fd)
{
	static char	*reader;
	char		*str;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	reader = ft_read(fd, reader);
	if (!reader)
		return (NULL);
	str = ft_line(reader);
	reader = ft_save(reader);
	return (str);
}
/*
int	main()
{
	int		fd;
	char	*str;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	str = get_next_line(fd);
	printf("%s", str);
	close(fd);
	return (0);
}*/
