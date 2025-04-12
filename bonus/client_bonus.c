/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:01:09 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/12 12:38:16 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

pid_t	g_server_pid;

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

void	handle_confirmation_signal(int signal, siginfo_t *info, void *p)
{
	(void)p;
	if (signal == SIGUSR2 && info-> si_pid == g_server_pid)
	{
		ft_putstr_fd(CONFIRMATION, 1);
		exit(0);
	}
}

void	setup_client_sigaction(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &handle_confirmation_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigaction(SIGUSR2, &sa, NULL);
}

int	main(int ac, char **av)
{
	pid_t	pid;
	size_t	i;

	setup_client_sigaction();
	if (ac != 3)
		return (ft_putstr_fd("Usage: ./client <PID> <message>\n", 2), 1);
	pid = ft_atoi(av[1]);
	if (pid <= 0 || kill(pid, 0) == -1)
		return (ft_putstr_fd("Invalid PID or process not running.\n", 2), 1);
	i = 0;
	g_server_pid = pid;
	while (av[2][i])
		send_char((unsigned char)av[2][i++], pid);
	send_char('\0', pid);
	pause();
	return (0);
}
