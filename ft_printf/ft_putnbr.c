/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:18:35 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/05/03 15:42:00 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int	ft_numlen(long long n)
{
	int	len;

	len = 0;
	if (n == 0)
	{
		len = 1;
	}
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	putnbr(long long n)
{
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	if (n >= 10)
		putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

int	ft_putnbr(long long n)
{
	putnbr(n);
	return (ft_numlen(n));
}

/*int main(){
	printf("%d\n", printf("%d\n", 0));
	ft_printf("%d\n", ft_printf("%d\n", 0));
	printf("%d\n", printf("%d\n", 15));
	ft_printf("%d\n", ft_printf("%d\n", 15));
	printf("%d\n", printf("%d\n", 12312424));
	ft_printf("%d\n", ft_printf("%d\n", 12312424));
	printf("%d\n", printf("%d\n", -15));
	ft_printf("%d\n", ft_printf("%d\n", -15));
}*/
