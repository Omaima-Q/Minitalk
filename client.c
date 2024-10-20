/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqaroot <oqaroot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:20:20 by oqaroot           #+#    #+#             */
/*   Updated: 2024/10/17 20:11:53 by oqaroot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	signal_action(int pid, char *str)
{
	int	i;
	int	c;

	i = 0;
	while (*str)
	{
		c = *(str);
		while (i < 8)
		{
			if (c << i & 0b10000000)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			i++;
			usleep(850);
		}
		str++;
		i = 0;
	}
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc != 3)
	{
		ft_putstr("Wrong args\nFormat: [./client <(PID)> <STRING>]\n");
		exit(EXIT_FAILURE);
	}
	if (argv[1] != NULL)
	{
		i = 0;
		while ((argv[1][i]))
		{
			if (ft_isdigit(argv[1][i]) == 0)
			{
				ft_putstr("Pid is dangerous\n");
				exit(EXIT_FAILURE);
			}
			i++;
		}
	}
	if (ft_atoi(argv[1]) <= 0)
		return (write(1, "Pid is dangerous\n", 16), 1);
	else
		signal_action(ft_atoi(argv[1]), argv[2]);
	return (0);
}
