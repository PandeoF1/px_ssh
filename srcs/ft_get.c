/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:48:44 by tnard             #+#    #+#             */
/*   Updated: 2022/03/24 12:51:56 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/px_ssh.h"

int	ft_intlen(int n)
{
	int		len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_splitlen(char **split)
{
	int	x;

	x = 0;
	while (split[x])
		x++;
	return (x);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

t_combo *ft_get_combos(char *str)
{
	t_combo *combos;
	int		fd;
	int 	x;
	int		y;
	char	*tmp;
	char	**splita;
	char	**splitb;

	fd = open(str, O_RDONLY);
	tmp = ft_get_file(fd, 0, 0);
	close(fd);
	splita = ft_split(tmp, '\n');
	free(tmp);
	x = ft_splitlen(splita);
	combos = malloc(sizeof(t_combo) * x);
	y = 0;
	while (y < x)
	{
		splitb = ft_split(splita[y], ':');
		if (ft_splitlen(splitb) != 2)
		{
			ft_free_split(splitb);
			ft_free_split(splita);
			return (printf("Error: invalid format for combos file\n"), NULL);
		}
		combos[y].user = strdup(splitb[0]);
		combos[y].pass = strdup(splitb[1]);
		ft_free_split(splitb);
		dprintf(1, "\033[2K\r\033[1;32m[+]\033[0m %u combos loaded (%s:%s)\e[0m", y + 1, combos[y].user, combos[y].pass);
		usleep(2500);
		y++;
	}
	ft_free_split(splita);
	printf("\n");
	return (combos);
}

unsigned int	ft_get_line(char *str)
{
	const unsigned MAX_LENGTH = 9000;
	char buffer[MAX_LENGTH];
	FILE *fp = fopen(str, "r");
	unsigned int	line;

	while (fgets(buffer, MAX_LENGTH, fp))
		line++;
	fclose(fp);
	return (line);
}

t_hosts *ft_get_hosts(char *str)
{
	const unsigned MAX_LENGTH = 9000;
	time_t	t;
	unsigned int	count;
	unsigned int	max;
	char buffer[MAX_LENGTH];
	t_hosts *hosts;
	int 	x;
	int		y;
	FILE *fp = fopen(str, "r");

	count = 0;
	srand(time(NULL));
	max = ft_get_line(str);
	hosts = malloc(sizeof(t_hosts) * max + 1);
	while (fgets(buffer, MAX_LENGTH, fp))
	{
		buffer[strlen(buffer) - 1] = '\0';
		hosts[y].status = 0;
		hosts[y].ip = strdup(buffer);
		hosts[y].port = 22;
		if (rand() % 2500 == 5)
			dprintf(1, "\033[2K\r\033[1;32m[+]\033[0m %u hosts loaded (%s:%d)\e[0m", y, hosts[y].ip, hosts[y].port);
		count++;
		y++;
	}
	y--;
	dprintf(1, "\033[2K\r\033[1;32m[+]\033[0m %u hosts loaded (%s:%d)\e[0m", y + 2, hosts[y].ip, hosts[y].port);
	printf("\n");
	fclose(fp);
	return (hosts);
}
