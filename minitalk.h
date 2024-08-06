/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:04:05 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/08/06 14:04:28 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define BUFFER 500000
# define MAX_PID 4194304

# include <signal.h>
# include "./ft_printf/ft_printf.h"
# include "./libft/libft.h"
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define ERROR 1

void	ft_kill(int pid, int sig);

typedef struct s_pain
{
	char	msg[BUFFER];
	int		bits;
	int		pos;
	int		signal;
}				t_pain;

# define SUCCESS 0

#endif
