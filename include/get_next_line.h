/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:14:18 by dtassel           #+#    #+#             */
/*   Updated: 2023/09/19 13:29:39 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <stdlib.h>
# include <unistd.h>
# include "../utils/libft/libft.h"

size_t			f_strlen(const char *str);
char			*f_strchr(const char *s, int c);
char			*f_strjoin(const char *s1, const char *s2);
char			*get_next_line(int fd);
char			*ft_line(char *reader);
char			*ft_save(char *reader);
char			*ft_read(int fd, char *reader);

#endif
