/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:05:02 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/12 12:38:51 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <limits.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

# define WRONG_PID \
	"\nInvalid Argument|PID OR the Process dosnt exist\n"
# define CONFIRMATION \
	"\nThe server has received full Message successfully :)\n"

typedef struct s_message
{
	unsigned char	b[4];
	pid_t			pid;
	int				bit_count;
	int				target;
}	t_message;

long	ft_atoi(const char *str);
void	ft_putnbr_fd(int n, int fd);
int		get_char_size(unsigned char c);
void	ft_putstr_fd(char *s, int fd);
void	*ft_memset(void *b, int c, size_t len);
size_t	ft_strlen(char *s);

#endif