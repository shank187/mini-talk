/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:22:55 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/12 12:44:50 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

t_message	g_msg;

int	get_char_size(unsigned char c)
{
	if ((c & 0x80) == 0x00)
		return (8);
	else if ((c & 0xE0) == 0xC0)
		return (16);
	else if ((c & 0xF0) == 0xE0)
		return (24);
	else if ((c & 0xF8) == 0xF0)
		return (32);
	return (-1);
}

void	manage_buffer(int i, int pid)
{
	int	index;

	index = g_msg.bit_count / 8;
	g_msg.b[index] = g_msg.b[index] << 1;
	g_msg.b[index] |= i;
	g_msg.bit_count++;
	if (g_msg.bit_count == 8)
		g_msg.target = get_char_size(g_msg.b[0]);
	if (g_msg.bit_count == 8 && g_msg.b[0] == '\0')
	{
		ft_memset(g_msg.b, 0, 4);
		g_msg.bit_count = 0;
		g_msg.target = 0;
		kill(pid, SIGUSR2);
		return ;
	}
	if (g_msg.target > 0 && g_msg.bit_count == g_msg.target)
	{
		write(1, g_msg.b, g_msg.target / 8);
		ft_memset(g_msg.b, 0, 4);
		g_msg.bit_count = 0;
		g_msg.target = 0;
	}
}

void	handle_signal(int signal, siginfo_t *info, void *p)
{
	(void)p;
	if (info->si_pid != g_msg.pid)
	{
		g_msg = (t_message){0};
		g_msg.pid = info->si_pid;
	}
	if (signal == SIGUSR2)
		manage_buffer(1, g_msg.pid);
	else if (signal == SIGUSR1)
		manage_buffer(0, g_msg.pid);
}

void	setup_sigaction(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &handle_signal;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	write(1, "the server pid id > ", 20);
	ft_putnbr_fd(pid, 1);
	write(1, " <\n", 3);
	setup_sigaction();
	while (1)
		pause();
}
