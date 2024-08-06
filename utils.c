/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:03:13 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/08/05 18:02:24 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_kill(int pid, int sig)
{
	if (sig == 1)
	{
		if (kill(pid, SIGUSR1) == -1)
			exit (ERROR);
	}
	if (sig == 2)
	{
		if (kill(pid, SIGUSR2) == -1)
			exit (ERROR);
	}
}
