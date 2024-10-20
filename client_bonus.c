/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqaroot <oqaroot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:20:47 by oqaroot           #+#    #+#             */
/*   Updated: 2024/10/17 20:15:14 by oqaroot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_action(int pid, char *str)
{
	int	i;
	int	p;

	p = 0;
	i = 0;
	while (*str)
	{
		while (i < 8)
		{
			if (*str << i & 0b10000000)
				p = kill(pid, SIGUSR1);
			else
				p = kill(pid, SIGUSR2);
			i++;
			usleep(12003);
		}
		if (p == -1)
		{
			ft_putstr("Unable to find PID\n");
			exit(1);
		}
		str++;
		i = 0;
	}
}

void	handler(int sig)
{
	static int	message_printed = 0;

	if (!message_printed)
	{
		if (sig == SIGUSR1)
		{
			ft_putstr("The signal was received successfully.\n");
			message_printed = 1;
		}
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa_sig;
	int					i;

	i = 0;
	if (argc != 3)
	{
		ft_putstr("Number of arguments invalid or the message is empty.\n");
		ft_putstr("Try again.\n");
		exit(1);
	}
	if (ft_atoi(argv[1]) <= 0)
		return (write(1, "Pid is dangerous\n", 16), 1);
	else
	{
		sa_sig.sa_handler = &handler;
		sa_sig.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, &sa_sig, NULL);
		sigaction(SIGUSR2, &sa_sig, NULL);
		signal_action(ft_atoi(argv[1]), argv[2]);
	}
	return (EXIT_SUCCESS);
}
