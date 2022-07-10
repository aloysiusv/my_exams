/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 22:16:17 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/10 22:16:17 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// gcc -Wall -Wextra -Werror -fsanitize=address -g3 -D BUFFER_SIZE=whatever

char	*get_next_line(int fd)
{
	size_t	i;
	char	*line;
	char	buf[1];
	char	stock[999999];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 0;
	stock[i] = '\0';
	while (read(fd, buf, 1) == 1)
	{
		stock[i] = buf[0];
		stock[i + 1] = '\0';
		if (stock[i] == '\n')
			break ;
		i++;
	}
	if (stock[0] == '\0')
		return (NULL);
	line = malloc(i + 2);
	i = 0;
	while (stock[i])
	{
		line[i] = stock[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

#include <stdio.h>

int	main(void)
{
	char	*line;
	int		fd = 0;
	int		loop = 1;

	fd =  open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	while (loop)
	{
		line = get_next_line(fd);
		if (line)
		{
			printf("%s", line);
			free(line);
		}
		else
			loop = 0;
	}
	free(line);
	close(fd);
	return (0);
}
