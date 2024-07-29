/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:03:13 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/07/29 14:27:32 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_kill(int pid, int sig)
{
	if (sig == 1)
	{
		if (kill(pid, SIGUSR1) == -1)
			exit (ERROR);
	}
	if (sig == 2)
	{
		if (kill(pid, SIGUSR2) == -1)
			exit (ERROR);
	}
}

void	send_null_char(int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		ft_kill(pid, 1);
		pause();
		i++;
	}
}

void	send_message(int pid, char *msg)
{
	int	pos;
	int	bit;

	pos = 0;
	while (msg[pos] != '\0')
	{
		bit = 7;
		while (bit >= 0)
		{
			if (((msg[pos] >> bit) & 1) == 0)
				ft_kill(pid, 1);
			if (((msg[pos] >> bit) & 1) == 1)
				ft_kill(pid, 2);
			pause();
			bit--;
		}
		pos++;
	}
	send_null_char(pid);
}
