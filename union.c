/* Write a program that takes two strings and displays, without doubles, the
characters that appear in either one of the strings.

The display will be in the order characters appear in the command line, and
will be followed by a \n.

If the number of arguments is not 2, the program displays \n. */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

size_t	find_char(char *s, char c)
{
	int	i = 0;

	while (s[i])
		if (s[i++] == c)
			return (1);
	return (0);
}

void	ft_union(char *str1, char *str2)
{
	size_t	i = 0;
	size_t	j = 0;
	char	stock[1000];

	while (str1[i])
	{
		if (find_char(stock, str1[i]) == 0)
			write(1, &str1[i], 1);
		stock[j++] = str1[i++];
	}
	i = 0;
	while (str2[i])
	{
		if (find_char(stock, str2[i]) == 0)
			write(1, &str2[i], 1);
		stock[j++] = str2[i++];
	}
}

int	main(int argc, char *argv[])
{
	if (argc == 3)
		ft_union(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}
