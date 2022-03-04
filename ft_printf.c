/* Write a function named `ft_printf` that will mimic the real printf but 
it will manage only the following conversions: s,d and x.

Your function must be declared as follows:

int ft_printf(const char *, ... );

Before you start we advise you to read the `man 3 printf` and the `man va_arg`.
To test your program compare your results with the true printf.

Exemples of the function output:
 
call: ft_printf("%s\n", "toto");
out: toto$

call: ft_printf("Magic %s is %d", "number", 42);
out: Magic number is 42%

call: ft_printf("Hexadecimal for %d is %x\n", 42, 42);
out: Hexadecimal for 42 is 2a$ */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct s_info
{
	int		nbytes;
}				t_info;

void	putnbr_base(t_info *t, long long num, char *str, int base)
{
	long long	lol;

	lol = num;
	if (num < 0)
	{
		lol = -lol;
		t->nbytes += write(1, "-", 1);
	}
	if (lol >= base)
		putnbr_base(t, lol / base, str, base);
	t->nbytes += write(1, &str[lol % base], 1);
}

void	print_s(t_info *t, va_list ap)
{
	size_t	i = 0;
	char	*s = va_arg(ap, char *);
	if (s == NULL)
		t->nbytes += write(1, "(null)", 6);
	else
		while (s[i])
			t->nbytes += write(1, &s[i++], 1);
}

void	print_d(t_info *t, va_list ap)
{
	int d = va_arg(ap, int);
	putnbr_base(t, d, "0123456789", 10);
}

void	print_x(t_info *t, va_list ap)
{
	unsigned long x = va_arg(ap, unsigned long);
	putnbr_base(t, x, "0123456789abcdef", 16);
}

int	magic_kaboom(const char *str, t_info *t, va_list ap)
{
	size_t	i = 0;

	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == 's')
			 	print_s(t, ap);
			else if (str[i + 1] == 'd')
				print_d(t, ap);
			else if (str[i + 1] == 'x')
				print_x(t, ap);
			i++;
		}
		else
			t->nbytes += write(1, &str[i], 1);
		i++;
	 }
	 return (t->nbytes);
}

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	t_info		t[1];

	t->nbytes = 0;
	va_start(ap, str);
	magic_kaboom(str, t, ap);
	va_end(ap);
	return (t->nbytes);
}

#include <stdio.h>
#include <limits.h>

int	main(void)
{
	printf("my ret = %d\n", ft_printf("Hello\n"));
	printf("ret = %d\n", printf("Hello\n"));
	printf("my ret = %d\n", ft_printf("%s\n", "U ok?"));
	printf("ret = %d\n", printf("%s\n", "U ok?"));
	printf("my ret = %d\n", ft_printf("%s\n", ""));
	printf("ret = %d\n", printf("%s\n", "");
	printf("my ret = %d\n", ft_printf("%d\n", 42));
	printf("ret = %d\n", printf("%d\n", 42));
	printf("my ret = %d\n", ft_printf("%x\n", 42));
	printf("ret = %d\n", printf("%x\n", 42));
	printf("my ret = %d\n", ft_printf("%s, %d, %x\n", "Hello", 42, 42));
	printf("ret = %d\n", printf("%s, %d, %x\n", "Hello", 42, 42));
	printf("my ret = %d\n", ft_printf("%d\n", 42));
	printf("my ret = %d\n", ft_printf("%d\n", INT_MIN));
	printf("ret = %d\n", printf("%d\n", INT_MIN));
	printf("my ret = %d\n", ft_printf("%d\n", INT_MAX));
	printf("ret = %d\n", printf("%d\n", INT_MAX));
	return (0);
}
