/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 13:10:57 by kakiba            #+#    #+#             */
/*   Updated: 2022/08/26 21:20:54 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	(size * count);
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
