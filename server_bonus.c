/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:49:43 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/07/27 16:06:25 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

volatile sig_atomic_t	g_signal_received = 0;

void	handle_signals(int signal)
{
	if (signal == SIGUSR1)
		g_signal_received = 1;
	if (signal == SIGUSR2)
		g_signal_received = 2;
}

void    get_pid(void)
{
    static char	*pid = NULL;
    static char	num = 0;
    static int	bits = 0;
    char		str[2];

    if (!pid)
        pid = ft_strdup("");
    if (!pid)
		exit (ERROR);
    num = (num << 1) | (g_signal_received - 1);
    bits++;
    if	(bits == 8)
    {
        str[0] = num;
        str[1] = '\0';
        pid = ft_strjoin(pid, str);
        if (num == '\0')
        {
            kill(ft_atoi(pid), SIGUSR1);
            usleep(300);
            pid = NULL;
        }
		bits = 0;
		num = 0;
    }
	g_signal_received = 0;
}

void    send_response()
{
    while (1)
    {
        pause();
        if (g_signal_received)
            get_pid();
    }
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
            send_response();
			msg = NULL;
		}
		bits = 0;
		letter = 0;
	}
	g_signal_received = 0;
}

int	main(void)
{
    struct sigaction	sa;

    ft_printf("Welcome to the server! PID: %d\n", getpid());
	sa.sa_handler = handle_signals;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit (ERROR);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		exit (ERROR);
	while (1)
	{
		pause();
		if (g_signal_received)
			decrypt();
	}
	return (SUCCESS);
}
