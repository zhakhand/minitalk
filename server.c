/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:16:05 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/07/29 14:51:51 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_signal_received = 0;

void	decrypt(int pid)
{
	static char	*msg = NULL;
	static int	bits = 0;
	static char	letter[2] = {0, 0};

	if (!msg)
		msg = ft_strdup("");
	if (!msg)
		exit (ERROR);
	letter[0] = (letter[0] << 1) | (g_signal_received - 1);
	bits++;
	if (bits == 8)
	{
		msg = ft_strjoin(msg, letter);
		if (letter[0] == 0)
		{
			ft_printf("%s\n", msg);
			ft_free(&msg);
			ft_kill(pid, 2);
		}
		bits = 0;
		letter[0] = 0;
	}
	g_signal_received = 0;
}

void	handle_signals(int signal, siginfo_t *info, void *data)
{
	(void)data;
	if (signal == SIGUSR1)
		g_signal_received = 1;
	if (signal == SIGUSR2)
		g_signal_received = 2;
	decrypt(info->si_pid);
	ft_kill(info->si_pid, 1);
}

void	set_up_handler(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signals;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit (ERROR);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		exit (ERROR);
}

int	main(void)
{
	ft_printf("Welcome to the server! PID: %d\n", getpid());
	set_up_handler();
	while (1)
	{
		pause();
	}
	return (SUCCESS);
}
