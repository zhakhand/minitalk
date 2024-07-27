/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:49:27 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/07/27 16:10:43 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

volatile sig_atomic_t   g_response = 0;

void	handle_signal(int signal)
{
	if (signal == SIGUSR1)
		g_response = 1;
}

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

void    wait_response(void)
{
    while(1)
    {
        pause();
        if (g_response == 1)
            break ;
    }
	ft_printf("Message received");
}

int	main(int ac, char **av)
{
    struct sigaction    sa;
	char	*msg;
	int		pid;

	if (ac != 3)
	{
		ft_printf("Not enough arguments provided! Please write ");
		ft_printf("./client <PID> <Message>\n");
		return (ERROR);
	}
    sa.sa_handler = handle_signal;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	pid = ft_atoi(av[1]);
	msg = av[2];
	if (!pid || msg[0] == 0)
	{
		if (!pid)
            ft_printf("Wrong PID!\n");
        if (msg[0] == 0)
            ft_printf("Please provide a message!\n");
		return (ERROR);
	}
    send_message(pid, msg);
    send_message(pid, ft_itoa(getpid()));
    wait_response();
	return (SUCCESS);
}
