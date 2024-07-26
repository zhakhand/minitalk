/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:16:01 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/07/26 15:47:01 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char(int server, char c)
{
	int	bit;
	
	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
		{
			if (kill(server, SIGUSR1) == -1)
				exit (ERROR);
		}
		else
		{
			if (kill(server, SIGUSR2) == -1)
				exit (ERROR);
		}
		usleep(500);
		bit++;
	}
}

void	send_msg(int server, char *msg)
{
	int	i;

	i = 0;
	while (i <= ft_strlen(msg))
	{
		send_char(server, msg[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	int		server;
	char	*msg;

	if (ac != 3)
		return (ERROR);
	server = ft_atoi(av[1]);
	msg = av[2];
	send_msg(server, msg);
	return (SUCCESS);
}