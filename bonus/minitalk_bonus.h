/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:05:02 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/11 14:52:05 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
#define MINITALK_H


#include <limits.h>
#include <unistd.h>
#include <signal.h>
// #include <sys/types.h>


# define WRONG_PID \
	"Invalid Argument|PID OR the Process dosnt exist\n"
# define DBL_MAX 1.7976931348623157e+308


long	ft_atoi(const char *str);
void	ft_putnbr_fd(int n, int fd);
int get_char_size(unsigned char c);
void	ft_putstr_fd(char *s, int fd);
void	*ft_memset(void *b, int c, size_t len);


#endif