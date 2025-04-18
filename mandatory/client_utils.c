/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:04:12 by aelbour           #+#    #+#             */
/*   Updated: 2025/04/12 12:45:54 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

static void	ft_get_sign_bonus(int *s, long *i, const char *str)
{
	*s = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*s = -1;
		(*i)++;
	}
}

long	ft_atoi(const char *str)
{
	long	i;
	long	t;
	long	oldt;
	int		s;

	t = 0;
	oldt = 0;
	i = 0;
	ft_get_sign_bonus(&s, &i, str);
	if (!str[i])
		return (2147483649);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (2147483649);
		t = (t * 10) + (str[i++] - '0');
		if ((t / 10) != oldt && s < 0)
			return (2147483649);
		else if ((t / 10) != oldt && s > 0)
			return (2147483649);
		oldt = t;
	}
	return (t * s);
}
