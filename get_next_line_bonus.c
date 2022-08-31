/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 13:10:57 by kakiba            #+#    #+#             */
/*   Updated: 2022/08/31 08:14:20 by kakiba           ###   ########.fr       */
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
//		printf("remain [%s]\n", remain[fd]);
		allocate_size += ft_strlcpy_clear(buf, remain[fd], BUFFER_SIZE);
		ft_bzero(remain[fd], BUFFER_SIZE);
		new_line = ft_strchr(buf, '\n', allocate_size - 1);
	}
	if (new_line == NULL)
		buf = read_file(fd, buf, &new_line, &allocate_size);
	if (new_line)
	{
		if (new_line[1] != '\0')
			ft_strlcpy_clear(remain[fd], new_line + 1, BUFFER_SIZE);
		// ft_bzero(new_line + 1, allocate_size - 1);
		return (ft_realloc(buf, allocate_size, (new_line - buf + 2)));
	}
	else
	{
		ft_bzero(remain[fd], BUFFER_SIZE);
		return (buf);
	}
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
		ft_bzero(s_last, BUFFER_SIZE);
		read_length = read(fd, s_last, BUFFER_SIZE);
//		printf("read: [%s]", buf);
		*new_line = ft_strchr(s_last, '\n', read_length);
		if (*allocate_size == BUFFER_SIZE + 1UL && \
		read_length <= 0 && !(*new_line))
		{
			free (buf);
			buf = NULL;
			return (NULL);
		}
		*allocate_size += read_length;
	}
	if (read_length < BUFFER_SIZE && !(*new_line))
	{
		buf = ft_realloc(buf, *allocate_size, *allocate_size - BUFFER_SIZE);
//		printf("last: [%s]", buf);
	}
	//	buf = ft_realloc(buf, *allocate_size - BUFFER_SIZE, *allocate_size);
	return (buf);
}

// if remain has nothing, strchr() overflow so it must have length.
// Name is easily confused original strchr...
char	*ft_strchr(const char *s, int c, size_t length)
{
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i] && i < length && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

// to clear remain, fill src '\0'
size_t	ft_strlcpy_clear(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i + 1 < dstsize)
	{
		dst[i] = src[i];
		++i;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	while (src[i] != '\0' && i < dstsize)
		i++;
	return (i);
}

//after read, to stop Line112
//newsizw = 0 notoki
//realloc de kanketu 
//error notokimo free suru?
//error early return 
//for ha strlcpy
void	*ft_realloc(void *src, size_t src_size, size_t new_size)
{
	void	*dst;

	// dst = ft_calloc(new_size, 1);
	dst = malloc(new_size);
	if (src_size != 0 && dst)
	{
		((char *)dst)[new_size - 1] = '\0';
		if (src_size < new_size)
			ft_strlcpy_clear((char *)dst, (char *)src, src_size);
		else
			ft_strlcpy_clear((char *)dst, (char *)src, new_size);
	}
	free (src);
	src = NULL;
	return (dst);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*m;

	if (size == 0 || count == 0)
	{
		count = 1;
		size = 1;
	}
	if (count <= __SIZE_MAX__ / size)
	{
		m = malloc(count * size);
		if (m != NULL)
			ft_bzero(m, size * count);
	}
	else
		m = NULL;
	return (m);
}

void	*ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*m;

	m = (unsigned char *)s;
	i = 0;
	while (i < n)
		m[i++] = '\0';
	return (m);
}
