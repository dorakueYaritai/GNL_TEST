/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 13:10:57 by kakiba            #+#    #+#             */
/*   Updated: 2022/08/31 20:47:34 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

//static kouzoutai ni ireru
char	*get_next_line(int fd)
{
	char		*buf;
	char		*new_line;
	size_t		allocate_size;
	static char	remain[OPEN_MAX][BUFFER_SIZE + 1UL];

	allocate_size = BUFFER_SIZE + 1UL;
	buf = malloc(allocate_size);
	if (!buf)
		return (NULL);
	new_line = NULL;
	if (remain[fd][0] != '\0')
	{
		allocate_size += ft_strlcpy(buf, remain[fd], BUFFER_SIZE);
		ft_bzero(remain[fd], BUFFER_SIZE);
		new_line = ft_strchr(buf, '\n', BUFFER_SIZE);
	}
	buf = read_file(fd, buf, &new_line, &allocate_size);
	if (new_line)
	{
		if (new_line[1] != '\0')
			ft_strlcpy(remain[fd], new_line + 1, BUFFER_SIZE);
		return (ft_realloc(buf, allocate_size, (new_line - buf + 2)));
	}
	ft_bzero(remain[fd], BUFFER_SIZE);
	return (buf);
}

// read error to seijoukei ga same syori
char	*read_file(int fd, char *buf, char **new_line,
				size_t *allocate_size)
{
	ssize_t	read_length;
	char	*s_last;

	read_length = BUFFER_SIZE;
	while (*new_line == NULL && read_length == BUFFER_SIZE)
	{
		buf = ft_realloc(buf, *allocate_size - BUFFER_SIZE, *allocate_size);
		if (!buf)
			return (NULL);
		s_last = buf + *allocate_size - BUFFER_SIZE - 1;
		ft_bzero(s_last, BUFFER_SIZE + 1);
		read_length = read(fd, s_last, BUFFER_SIZE);
		*new_line = ft_strchr(s_last, '\n', read_length);
		if (*allocate_size == BUFFER_SIZE + 1UL && \
		read_length <= 0)
		{
			free (buf);
			buf = NULL;
			return (NULL);
		}
		*allocate_size += read_length;
	}
	return (buf);
}
