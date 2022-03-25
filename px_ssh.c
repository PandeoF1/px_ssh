/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_ssh.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:30:15 by tnard             #+#    #+#             */
/*   Updated: 2022/03/25 22:50:42 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/px_ssh.h"

int ft_usage(void)
{
	printf("Usage: ./px_ssh  <nb_threads (0 - 100)> <hosts file> <combo file> <output files>\n");
	return (-1);
}

int main(int argc, char *argv[])
{
	int	nb_threads;
	int64_t	start;
	unsigned int	nb_hosts;
	unsigned int	nb_combo;
	t_hosts *hosts;
	t_combo *combos;
	t_threads *threads;

	if (argc == 5 && strncmp(argv[0], "./px_ssh", 7) == 0)
	{
		start = get_time();
		printf("Managing data...\n");
		nb_threads = atoi(argv[1]);
		hosts = ft_get_hosts(argv[2]);
		combos = ft_get_combos(argv[3]);
		nb_combo = ft_get_line(argv[3]);
		nb_hosts = ft_get_line(argv[2]) - nb_combo;
		nb_combo -= 3;
		threads = ft_create_thread(nb_threads, hosts, combos, nb_hosts, nb_combo, argv[4]);
		dprintf(1, "\033[2K\r\033[1;32mEstimed time : %u seconds\e[0m\n", ((nb_hosts * nb_combo) / nb_threads) * 5);
		while (1)
		{
			usleep(1000);
			if (ft_count(hosts, nb_hosts, 2) + ft_count(hosts, nb_hosts, 3) == nb_hosts)
			{
				dprintf(1, "\033[2K\r\033[1;32m[+]\033[0m Work finished !\n");
				dprintf(1, "\033[2K\r\033[1;32mFailed : %d, Success : %d, Skipped : %d, Wtf : %d | Elapsed time : %ld\n", ft_count(hosts, nb_hosts, 2), ft_count(hosts, nb_hosts, 3), ft_count(hosts, nb_hosts, 0), ft_count(hosts, nb_hosts, 1), (get_time() - start) / 1000);
				return (0);
			}
			else
				dprintf(1, "\033[2K\r\033[1;32mFailed : %d, Success : %d, Left : %d, Current : %d | Estimed time : %d seconds\e[0m", ft_count(hosts, nb_hosts, 2), ft_count(hosts, nb_hosts, 3), ft_count(hosts, nb_hosts, 0), ft_count(hosts, nb_hosts, 1), (((ft_count(hosts, nb_hosts, 1) + ft_count(hosts, nb_hosts, 0)) * nb_combo) / nb_threads) * 5);
		}
	}
	else
		return(ft_usage());
	return (0);
}