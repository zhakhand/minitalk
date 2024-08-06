/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:13:14 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/05/03 16:05:02 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char const *s)
{
	int	count;

	count = 0;
	if (!s)
	{
		write(1, &"(null)", 6);
		return (6);
	}
	while (*s)
	{
		ft_putchar(*s);
		s++;
		count++;
	}
	return (count);
}
