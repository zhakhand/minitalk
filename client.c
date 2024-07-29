/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:16:01 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/07/29 14:44:32 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_signal = 0;

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
	if (pid < 2)
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
