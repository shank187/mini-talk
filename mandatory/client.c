/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:01:09 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/11 12:17:43 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk.h"

void send_char(unsigned char c, int pid)
{
    int i;

    i = 7;
    while(i >= 0)
    {
        if((c >> i) | 0)
            kill(pid, SIGUSR2);
        else
            kill(pid, SIGUSR1);
        usleep(500);
        usleep(500);
        i--;
    }
}


int main(int ac, char ** av)
{
    long pid;
    size_t i;
    
    pid = ft_atoi(av[1]);
    if(ac != 3 || pid > INT_MAX || pid < INT_MIN || kill(pid, 0) == -1)
        return(ft_putnbr_fd(WRONG_PID, 2),0);
    i = -1;
    while(av[3][++i])
        send_char((unsigned char) av[3][i], pid);
    // while(1)
    //     pause();
    return(0);
}
