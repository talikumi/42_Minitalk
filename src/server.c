/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsociety <fsociety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:02:13 by fsociety          #+#    #+#             */
/*   Updated: 2023/01/27 17:45:39 by fsociety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static char	*ft_mkstr(char character, char *string)
{
	char	*tmp;
	char	*tmp2;

	tmp = malloc(2);
	if (tmp == NULL)
		exit(0);
	tmp[0] = character;
	tmp[1] = '\0';
	if (string == NULL)
	{
		string = malloc(2);
		if (string == NULL)
			exit(0);
		ft_strlcpy(string, tmp, 2);
	}
	else
	{
		tmp2 = string;
		string = ft_strjoin(string, tmp);
		if (string == NULL)
			exit(0);
		free(tmp2);
	}
	free(tmp);
	return (string);
}

static void	ft_count(int sign)
{
	static int	count;
	static int	character;
	static char	*string;

	count++;
	if (sign == SIGUSR2)
		character = (character << 1) + 1;
	else
		character = character << 1;
	if (count == 7)
	{
		string = ft_mkstr(character, string);
		if (character == 0)
		{
			ft_putendl_fd(string, 1);
			free(string);
			string = NULL;
		}
		count = 0;
		character = 0;
	}
}

int	main(void)
{
	int		pid;
	char	*cnv_pid;

	pid = getpid();
	cnv_pid = ft_itoa(pid);
	if (cnv_pid == 0)
		exit(0);
	ft_putendl_fd(cnv_pid, 1);
	signal(SIGUSR1, ft_count);
	signal(SIGUSR2, ft_count);
	while (1)
		pause();
}
