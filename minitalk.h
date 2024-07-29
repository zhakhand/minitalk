/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzhakhan <dzhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:04:05 by dzhakhan          #+#    #+#             */
/*   Updated: 2024/07/29 14:31:08 by dzhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "./ft_printf/ft_printf.h"
# include "./libft/libft.h"
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define ERROR 1

void    send_message(int pid, char *msg);
void    send_null_char(int pid);
void    ft_kill(int pid, int sig);

# define SUCCESS 0

#endif
