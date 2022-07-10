/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 22:13:37 by lrandria          #+#    #+#             */
/*   Updated: 2022/07/10 22:13:37 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int g_ret;

size_t	ft_strlen(char *s)
{
	size_t	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putnbr_base(long num, char *strbase, int base)
{
	long lol = num;
	if (lol < 0)
	{
		lol = -lol;
		g_ret += write(1, "-", 1);
	}
	if (lol >= base)
		ft_putnbr_base(lol / base, strbase, base);
	g_ret += write(1, &strbase[lol % base], 1);
}

void	print_s(va_list ap)
{
	char	*s = va_arg(ap, char *);
	g_ret += write(1, s, ft_strlen(s));
}

void	print_d(va_list ap)
{
	int	d = va_arg(ap, int);
	ft_putnbr_base(d, "0123456789", 10);
}

void	print_x(va_list ap)
{
	unsigned int	x = va_arg(ap, unsigned int);
	ft_putnbr_base(x, "0123456789abcdef", 16);
}

void	convert(va_list ap, const char *s)
{
	size_t	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			if (s[i + 1] == 's')
				print_s(ap);
			else if (s[i + 1] == 'd')
				print_d(ap);
			else if (s[i + 1] == 'x')
				print_x(ap);
			else
				g_ret += write(1, &s[i], 2);
			i++;
		}
		else
			g_ret += write(1, &s[i], 1);
		i++;
	}
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;

	g_ret = 0;
	va_start(ap, s);
	convert(ap, s);
	va_end(ap);
	return (g_ret);
}

#include <stdio.h>
#include <limits.h>

int	main(void)
{
	printf("MINE: %d\n", ft_printf("HI THERE "));
	printf("REAL: %d\n", printf("HI THERE "));
	printf("============================================\n");
	printf("MINE: %d\n", ft_printf("[%s] ", "COUCOU"));
	printf("REAL: %d\n", printf("[%s] ", "COUCOU"));
	printf("============================================\n");
	printf("MINE: %d\n", ft_printf("%s", ""));
	printf("REAL: %d\n", printf("%s", ""));
	printf("============================================\n");
	printf("MINE: %d\n", ft_printf("[%d] ", 42));
	printf("REAL: %d\n", printf("[%d] ", 42));
	printf("============================================\n");
	printf("MINE: %d\n", ft_printf("[%d] ", INT_MIN));
	printf("REAL: %d\n", printf("[%d] ", INT_MIN));
	printf("============================================\n");
	printf("MINE: %d\n", ft_printf("[%d] ", INT_MAX));
	printf("REAL: %d\n", printf("[%d] ", INT_MAX));
	printf("============================================\n");
	printf("MINE: %d\n", ft_printf("[%d] ", LONG_MIN));
	printf("REAL: %d\n", printf("[%d] ", LONG_MIN));
	// printf("============================================\n");
	// printf("MINE: %d\n", ft_printf("[%d] ", LONG_MAX));
	// printf("REAL: %d\n", printf("[%d] ", LONG_MAX));
	printf("============================================\n");
	printf("MINE: %d\n", ft_printf("[%x] ", 42));
	printf("REAL: %d\n", printf("[%x] ", 42));
	printf("============================================\n");
	printf("MINE: %d\n", ft_printf("[%x] ", UINT_MAX));
	printf("REAL: %d\n", printf("[%x] ", UINT_MAX));
	printf("============================================\n");
	printf("MINE: %d\n", ft_printf("[%x] ", ""));
	printf("REAL: %d\n", printf("[%x] ", ""));
	printf("============================================\n");
	printf("MINE: %d\n", ft_printf("[%x] ", ULONG_MAX));
	printf("REAL: %d\n", printf("[%x] ", ULONG_MAX));
	printf("============================================\n");
	printf("MINE: %d\n", ft_printf("Hello: [%s] [%d] [%x] ", "moshimoshi", 255, 255));
	printf("REAL: %d\n", printf("Hello: [%s] [%d] [%x] ", "moshimoshi", 255, 255));
	printf("============================================\n");
	printf("MINE: %d\n", ft_printf("Hello: [%s] [%d] [%x]", "weiwei", 400, 400));
	printf("REAL: %d\n", printf("Hello: [%s] [%d] [%x]", "weiwei", 400, 400));
}
