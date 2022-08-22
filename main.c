#include "get_next_line.h"
#include <stdio.h>

int	main()
{
	char	*s;
	int		fd = open("c.txt", O_RDONLY);
	while (fd)
	{
		s = get_next_line(fd);
		if (!s)
			break ;
		printf("%s", s);
	}
	return (0);
}
