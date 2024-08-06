/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:16:05 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/08/06 13:28:09 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_pain	g_u;

void	decrypt(int pid)
{
	g_u.msg[g_u.pos] = (g_u.msg[g_u.pos] << 1) | (g_u.signal - 1);
	g_u.bits++;
	if (g_u.bits == 8)
	{
		g_u.pos++;
		if (g_u.msg[g_u.pos - 1] == 0)
		{
			ft_printf("%s\n", g_u.msg);
			g_u.pos = 0;
			ft_bzero(g_u.msg, BUFFER);
			ft_kill(pid, 2);
		}
		g_u.bits = 0;
	}
	g_u.signal = 0;
}

void	handle_signals(int signal, siginfo_t *info, void *data)
{
	(void)data;
	if (signal == SIGUSR1)
		g_u.signal = 1;
	if (signal == SIGUSR2)
		g_u.signal = 2;
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
