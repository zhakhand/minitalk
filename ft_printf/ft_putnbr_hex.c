/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:42:39 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/05/03 16:06:32 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hexlen(unsigned long long n)
{
	int	len;

	len = 0;
	if (n == 0)
	{
		len = 1;
	}
	while (n != 0)
	{
		n /= 16;
		len++;
	}
	return (len);
}

static void	putnum(unsigned long long n, char const *base)
{
	if (n >= 16)
		putnum(n / 16, base);
	ft_putchar(base[n % 16]);
}

int	ft_putnbr_hex(unsigned long long n, char x)
{
	char	*base;

	if (x == 'x')
		base = "0123456789abcdef";
	else if (x == 'X')
		base = "0123456789ABCDEF";
	putnum(n, base);
	return (ft_hexlen(n));
}
