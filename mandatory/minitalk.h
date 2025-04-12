/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:05:02 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/12 12:46:49 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <limits.h>
# include <unistd.h>
# include <signal.h>

# define WRONG_PID \
	"Invalid Argument|PID OR the Process dosnt exist\n"

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
