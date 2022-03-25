/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:47:47 by tnard             #+#    #+#             */
/*   Updated: 2022/03/24 20:38:51 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/px_ssh.h"

int	ft_is_done(t_hosts *hosts, unsigned int nb_hosts)
{
	int x;

	x = 0;
	while (x < nb_hosts)
	{
		if (hosts[x].status == 0)
			return (0);
		x++;
	}
	return (1);
}

int	ft_left(t_hosts *hosts, unsigned int nb_hosts)
{
	unsigned int x;
	int	left;

	x = 0;
	left = 0;
	while (x < nb_hosts)
	{
		if (hosts[x].status == 0)
			left++;
		x++;
	}
	return (left);
}

int	ft_count(t_hosts *hosts, unsigned int nb_hosts, int y)
{
	unsigned int x;
	int	count;

	x = 0;
	count = 0;
	while (x < nb_hosts)
	{
		if (hosts[x].status == y)
			count++;
		x++;
	}
	return (count);
}
