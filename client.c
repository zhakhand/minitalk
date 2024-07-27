/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:16:01 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/07/27 14:48:59 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_null_char(int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR1);
		usleep(300);
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
				kill(pid, SIGUSR1);
			if (((msg[pos] >> bit) & 1) == 1)
				kill(pid, SIGUSR2);
			usleep(300);
			bit--;
		}
		pos++;
	}
	send_null_char(pid);
}

int	main(int ac, char **av)
{
	char	*msg;
	int		pid;

	if (ac != 3)
	{
		ft_printf("Not enough arguments provided! Please write ");
		ft_printf("./client <PID> <Message>\n");
		return (ERROR);
	}
	pid = ft_atoi(av[1]);
	msg = av[2];
	if (!pid)
	{
		ft_printf("Wrong PID!\n");
		return (ERROR);
	}
	if (msg[0] == 0)
	{
		ft_printf("Please provide a message!\n");
		return (ERROR);
	}
	send_message(pid, msg);
	return (SUCCESS);
}
