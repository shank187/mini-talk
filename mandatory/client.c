/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:01:09 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/12 12:45:37 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char(unsigned char c, int pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(300);
		usleep(300);
		i--;
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;
	size_t	i;

	if (ac != 3)
		return (ft_putstr_fd("Usage: ./client <PID> <message>\n", 2), 1);
	pid = ft_atoi(av[1]);
	if (pid <= 0 || kill(pid, 0) == -1)
		return (ft_putstr_fd("Invalid PID or process not running.\n", 2), 1);
	i = 0;
	while (av[2][i])
		send_char((unsigned char)av[2][i++], pid);
	send_char('\0', pid);
	return (0);
}
