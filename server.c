/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:16:05 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/07/26 15:45:57 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	signal_received = 0;

void	handle_signal(int signal)
{
	if (signal == SIGUSR1)
		signal_received = 1;
	else if (signal == SIGUSR2)
		signal_received = 2;
}

void	setup_sig_handlers(void)
{
	struct sigaction sa;
	sa.sa_handler = handle_signal;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit (ERROR);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		exit (ERROR);
}

void	receive_msg(void)
{
	char	msg[100];
	int		bits;
	int		i;

	bits = 0;
	i = 0;
	msg[i] = 0;
	while (1)
	{
		pause();
		if (signal_received)
		{
			if (signal_received == 1)
				msg[i] |= (1 << bits);
			bits++;
			if (bits == 8)
			{
				bits = 0;
				i++;
				if (i > 100)
					exit(ERROR);
			}
			signal_received = 0;
		}
		if (bits == 0 && msg[i] == '\0')
		{
			ft_printf("%s", msg);
			i = 0;
			msg[i] = 0;
		}
	}
}

int	main(void)
{
	setup_sig_handlers();
	ft_printf("Welcome! PID: %d\n", getpid());
	receive_msg();
	return (SUCCESS);
}