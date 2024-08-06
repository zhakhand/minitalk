/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:36:08 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/05/03 16:06:47 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int	ft_numlen(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
	{
		len = 1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	putnbr(unsigned int n)
{
	if (n >= 10)
		putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

int	ft_putunsigned(unsigned int n)
{
	putnbr(n);
	return (ft_numlen(n));
}

/*int main(){
	printf("%d\n", printf("%u\n", 0));
	ft_printf("%d\n", ft_printf("%u\n", 0));
	printf("%d\n", printf("%u\n", 15));
	ft_printf("%d\n", ft_printf("%u\n", 15));
	printf("%d\n", printf("%u\n", 12312424));
	ft_printf("%d\n", ft_printf("%u\n", 12312424));
	printf("%d\n", printf("%u\n", -15));
	ft_printf("%d\n", ft_printf("%u\n", -15));
}*/
