/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:16:05 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/07/27 14:42:48 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_signal_received = 0;

void	handle_signals(int signal)
{
	if (signal == SIGUSR1)
		g_signal_received = 1;
	if (signal == SIGUSR2)
		g_signal_received = 2;
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

void	decrypt(void)
{
	static char	*msg = NULL;
	static int	bits = 0;
	static char	letter = 0;
	char		str[2];

	if (!msg)
		msg = ft_strdup("");
	if (!msg)
		exit (ERROR);
	letter = (letter << 1) | (g_signal_received - 1);
	bits++;
	if (bits == 8)
	{
		str[0] = letter;
		str[1] = '\0';
		msg = ft_strjoin(msg, str);
		if (letter == 0)
		{
			ft_printf("%s\n", msg);
			msg = NULL;
		}
		bits = 0;
		letter = 0;
	}
	g_signal_received = 0;
}

int	main(void)
{
	ft_printf("Welcome to the server! PID: %d\n", getpid());
	set_up_handler();
	while (1)
	{
		pause();
		if (g_signal_received)
			decrypt();
	}
	return (SUCCESS);
}
