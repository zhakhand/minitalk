/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:04:09 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/05/06 12:42:26 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

static int	ft_type(va_list args, const char type)
{
	uintptr_t	ptr;

	if (type == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (type == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (type == 'p')
	{
		ptr = va_arg(args, uintptr_t);
		if (ptr)
			return (ft_putstr("0x") + ft_putnbr_hex(ptr, 'x'));
		return (ft_putstr("(nil)"));
	}
	else if (type == 'd' || type == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (type == 'u')
		return (ft_putunsigned(va_arg(args, unsigned int)));
	else if (type == 'x' || type == 'X')
		return (ft_putnbr_hex(va_arg(args, unsigned int), type));
	else if (type == '%')
		return (ft_putchar('%'));
	else
		return (-1);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		len;

	if (!str)
		return (-1);
	i = 0;
	len = 0;
	va_start(args, str);
	while (*(str + i))
	{
		if (*(str + i) == '%' && ft_strchr("cspdiuxX%", *(str + i + 1)))
		{
			len += ft_type(args, *(str + i + 1));
			i++;
		}
		else
			len += ft_putchar(*(str + i));
		i++;
	}
	va_end(args);
	return (len);
}
/*
int	main()
{
	int x = 0;
	int *ptr = &x;

	char *str;
	str = NULL;
	//c
	ft_printf("\n%%c:\n");
	printf("%d\n", printf("Character output: %c\n", 'a'));
	ft_printf("%d\n", ft_printf("Character output: %c\n", 'a'));
	//s
	ft_printf("\n%%s:\n");
	printf("%d\n", printf("String output: %s\n", " Hello World"));
	ft_printf("%d\n", ft_printf("String output: %s\n", " Hello World"));
	//p
	ft_printf("\n%%p:\n");
	printf("%d\n",printf("Pointer output: %p %p\n", ptr, ptr));
	ft_printf("%d\n", ft_printf("Pointer output: %p %p\n", ptr, ptr));
	//d
	ft_printf("\n%%d:\n");
	printf("%d\n", printf("Integer output: %d\n", 1234567));
	ft_printf("%d\n", ft_printf("Integer output: %d\n", 1234567));
	printf("%d\n", printf("Integer output: %d\n", -1234567));
	ft_printf("%d\n", ft_printf("Integer output: %d\n", -1234567));
	//i
	ft_printf("\n%%i:\n");
	printf("%d\n", printf("Integer output: %i\n", 1234567));
	ft_printf("%d\n", ft_printf("Integer output: %i\n", 1234567));
	printf("%d\n", printf("Integer output: %i\n", -1234567));
	ft_printf("%d\n", ft_printf("Integer output: %i\n", -1234567));
	//u
	ft_printf("\n%%u:\n");
	printf("%d\n", printf("Unsigned Integer output: %u\n", 1234567));
	ft_printf("%d\n", ft_printf("Unsigned Integer output: %u\n", 1234567));
	printf("%d\n", printf("Unsigned Integer output: %u\n", -1234567));
	ft_printf("%d\n", ft_printf("Unsigned Integer output: %u\n", -1234567));
	//x
	ft_printf("\n%%x:\n");
	printf("%d\n", printf("Hexadecimal output: %x\n", 1234567));
	ft_printf("%d\n", ft_printf("Hexadecimal output: %x\n", 1234567));
	printf("%d\n", printf("Hexadecimal output: %x\n", -1234567));
	ft_printf("%d\n", ft_printf("Hexadecimal output: %x\n", -1234567));
	//X
	ft_printf("\n%%X:\n");
	printf("%d\n", printf("Hexadecimal output: %X\n", 1234567));
	ft_printf("%d\n", ft_printf("Hexadecimal output: %X\n", 1234567));
	printf("%d\n", printf("Hexadecimal output: %X\n", -1234567));
	ft_printf("%d\n", ft_printf("Hexadecimal output: %X\n", -1234567));
	//%
	ft_printf("\n%%:\n");
	printf("%d\n", printf("Percent sign output: %%\n"));
	ft_printf("%d\n", ft_printf("Percent sign output: %%\n"));

	//Special cases
	//No arg
	ft_printf("\nSpecial Cases: \n1.NO ARGUMENTS:\n");
	printf("%d\n", printf(NULL));
	ft_printf("%d\n", ft_printf(NULL));
	//Nullptr
	ft_printf("\n2.Null pointer:\n");
	printf("%d\n",printf("%p %p\n", NULL, NULL));
	ft_printf("%d\n", ft_printf("%p %p\n", NULL, NULL));
	//Empty string
	ft_printf("\n3.Empty string/null string:\n");
	printf("%d\n", printf("String output: %s\n", ""));
	ft_printf("%d\n", ft_printf("String output: %s\n", ""));
	printf("%d\n", printf("String output: %s\n", str));
	ft_printf("%d\n", ft_printf("String output: %s\n", str));
	//0 and smallest int
	x = 42;
	ft_printf("\n4.Zero and smallest INT:\n");
	printf("%d\n", printf("Integer output: %d\n", 0));
	ft_printf("%d\n", ft_printf("Integer output: %d\n", 0));
	printf("%d\n", printf("Integer output: %d\n", INT_MIN));
	ft_printf("%d\n", ft_printf("Integer output: %d\n", INT_MIN));
	//Multiple arguments
	ft_printf("\nMultiple args:\n");
	printf("\n%d\n", 
	printf(" %c  %s %p %i %d %u %x %X %%   ", 
	'H', "ello", ptr, -42, 42, 0, 124, 124));
	ft_printf("\n%d\n", 
	ft_printf(" %c  %s %p %i %d %u %x %X %%   "
	, 'H', "ello", ptr, -42, 42, 0, 124, 124));
}*/
