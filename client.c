/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:16:01 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/08/06 14:07:09 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_signal = 0;

void	send_null_char(int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_signal = 0;
		ft_kill(pid, 1);
		if (g_signal == 0)
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
			g_signal = 0;
			if (((msg[pos] >> bit) & 1) == 0)
				ft_kill(pid, 1);
			if (((msg[pos] >> bit) & 1) == 1)
				ft_kill(pid, 2);
			if (g_signal == 0)
				pause();
			bit--;
		}
		pos++;
	}
	send_null_char(pid);
}

void	handle_signals(int signal)
{
	if (signal == SIGUSR1)
	{
		g_signal = 1;
	}
	if (signal == SIGUSR2)
	{
		g_signal = 2;
		ft_printf("Server received message!\n");
		exit (SUCCESS);
	}
}

void	set_up_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_signals;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit (ERROR);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		exit (ERROR);
}

int	main(int ac, char **av)
{
	int		pid;

	if (ac != 3)
	{
		ft_printf("Not enough arguments provided! Please write ");
		ft_printf("./client <PID> <Message>\n");
		return (ERROR);
	}
	pid = ft_atoi(av[1]);
	if (pid < 2 || ft_strncmp(av[1], ft_itoa(pid), ft_strlen(av[1])) != 0
		|| pid > MAX_PID)
	{
		ft_printf("Wrong PID!\n");
		return (ERROR);
	}
	if (av[2][0] == 0)
	{
		ft_printf("Please provide a message!\n");
		return (ERROR);
	}
	set_up_handler();
	send_message(pid, av[2]);
	return (SUCCESS);
}
