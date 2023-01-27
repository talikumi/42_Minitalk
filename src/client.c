/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsociety <fsociety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:43:13 by fsociety          #+#    #+#             */
/*   Updated: 2023/01/27 17:52:32 by fsociety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_check_argv(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		num *= 10;
		num += str[i] - 48;
		i++;
		if (str[i] != 0)
		{
			if ((num == 214748364 && str[i] - 48 > 7) || num > 214748364)
				return (-1);
		}
	}
	return (1);
}

static char	*ft_conv(char ch)
{
	int		i;
	char	*ret;

	i = 6;
	ret = malloc(sizeof(char) * 9);
	if (ret == NULL)
		exit(1);
	while (i >= 0)
	{
		ret[i] = (ch % 2) + 48;
		ch = ch / 2;
		i--;
	}
	ret[8] = '\0';
	return (ret);
}

static void	ft_send_bit(int pid, char bit)
{
	if (bit == '0')
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	usleep(50);
}

static void	ft_send_sig(int pid, char *string)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (string[i])
	{
		j = 0;
		temp = ft_conv(string[i]);
		while (temp[j])
		{
			ft_send_bit(pid, temp[j]);
			j++;
		}
		free(temp);
		i++;
	}
	i = 0;
	while (i <= 6)
	{
		ft_send_bit(pid, '0');
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int		pid;
	char	*string;

	if (argc != 3 || ft_check_argv(argv[1]) < 0)
		exit(0);
	pid = ft_atoi(argv[1]);
	string = argv[2];
	ft_send_sig(pid, string);
	return (0);
}
