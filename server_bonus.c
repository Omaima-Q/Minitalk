/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqaroot <oqaroot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:21:15 by oqaroot           #+#    #+#             */
/*   Updated: 2024/10/17 17:21:17 by oqaroot          ###   ########.fr       */
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

void	print_intro(int pid)
{
	ft_putstr("\n\033[1;33m");
	ft_putstr("███████╗███████╗██████╗ ██╗   ██╗███████╗██████╗ \n");
	ft_putstr("██╔════╝██╔════╝██╔══██╗██║   ██║██╔════╝██╔══██╗\n");
	ft_putstr("███████╗█████╗  ██████╔╝██║   ██║█████╗  ██████╔╝\n");
	ft_putstr("╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝██╔══╝  ██╔══██╗\n");
	ft_putstr("███████║███████╗██║  ██║ ╚████╔╝ ███████╗██║  ██║\n");
	ft_putstr("╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝  ╚══════╝╚═╝  ╚═╝\n");
	ft_putstr("Process ID: \033[1;34m");
	ft_putnbr(pid);
	ft_putstr("\033[0m\t\n");
}

void	handler(int sig, siginfo_t *info, void *content)
{
	static int				i = 0;
	static unsigned char	c = 0;

	(void)content;
	if (sig == SIGUSR2)
		c = c << 1;
	else if (sig == SIGUSR1)
		c = (c << 1) | 0b00000001;
	i++;
	if (i == 8)
	{
		ft_putchar(c);
		i = 0;
		c = 0;
		if (kill(info->si_pid, SIGUSR1) == -1)
			ft_putstr_fd("Unable to send SIGUSR1\n", 2);
		return ;
	}
	if (kill(info->si_pid, SIGUSR2) == -1)
		ft_putstr_fd("Unable to send SIGUSR2\n", 2);
}

int	main(void)
{
	struct sigaction	sa_sig;

	print_intro(getpid());
	while (1)
	{
		sa_sig.sa_sigaction = &handler;
		sa_sig.sa_flags = SA_SIGINFO;
		if (sigaction(SIGUSR1, &sa_sig, NULL) == -1)
			ft_putstr_fd("Unable to send SIGUSR1\n", 2);
		if (sigaction(SIGUSR2, &sa_sig, NULL) == -1)
			ft_putstr_fd("Unable to send SIGUSR2\n", 2);
	}
	return (0);
}
