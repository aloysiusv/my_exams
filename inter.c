/*Write a program that takes two strings and displays, without doubles, the
characters that appear in both strings, in the order they appear in the first
one.
The display will be followed by a \n.
If the number of arguments is not 2, the program displays \n.

BREBIS BRAILLE 

BREI 

*/

#include <unistd.h>
#include <stdlib.h>

size_t	find_char(char *s, char c)
{
	size_t	i = 0;

	while (s[i])
		if (s[i++] == c)
			return (1);
	return (0);
}

void	ft_inter(char *s1, char *s2)
{
	int		i = 0;
	int		j = 0;
	char	stock[1000];

	while (s1[i])
	{
		if ((find_char(stock, s1[i]) == 0) && (find_char(s2, s1[i]) == 1))
			write(1, &s1[i], 1);
		stock[j++] = s1[i++];
	}
}

int	main(int argc, char *argv[])
{
	if (argc == 3)
		ft_inter(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}
