/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:22:55 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/11 18:11:59 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

typedef struct s_message
{
	unsigned char b[4];
	pid_t pid;
	int bit_count;
	int target;
} t_message;

t_message msg;

void manage_buffer(int i, int pid)
{
    int index;
    int bit_index;

    index = msg.bit_count / 8;
    msg.b[index] = msg.b[index] << 1;
	msg.b[index] = msg.b[index] | i;
	if(!msg.b[index])
	{
		kill(pid, SIGUSR2);
		return;
	}
	msg.bit_count++;
	if (msg.bit_count == 8)
		msg.target = get_char_size(msg.b[0]);
	else if (msg.bit_count == msg.target)
    {
        write(1, msg.b, msg.target / 8);
        ft_memset(msg.b, 0, 4);
        msg.bit_count = 0;
        msg.target= 0;
    }
}

int handle_signal(int signal, siginfo_t *info, void *p)
{
	if(info->si_pid != msg.pid)
	{
		msg = (t_message){0};
		msg.pid = info->si_pid;
	}
	if(signal == SIGUSR2)
		manage_buffer(1, info->si_pid);
	else if(signal == SIGUSR1)
		manage_buffer(0, info->si_pid);
}

void setup_sigaction(void)
{
	struct sigaction sa;

	sa.sa_sigaction = &handle_signal;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);          // no signals blocked during handler
	sa.sa_flags = SA_RESTART;          // restart interrupted syscalls (like pause)
	sigaction(SIGUSR1, &sa, NULL);     // bind SIGUSR1
	sigaction(SIGUSR2, &sa, NULL);     // bind SIGUSR2
}

int main(void)
{
	pid_t pid;

	pid = getpid();
	write(1, "the server pid id > ", 20);	
	ft_putnbr_fd(pid, 1);
	write(1, " <\n", 3);
	while(1)
		pause();
}
