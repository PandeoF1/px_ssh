/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_ssh.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:30:18 by tnard             #+#    #+#             */
/*   Updated: 2022/03/24 12:30:18 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_SSH_H
# define PX_SSH_H
# include <libssh/libssh.h>
# include <stdlib.h>
# include <stdio.h> 
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <time.h>
# include <pthread.h>
# include <sys/time.h>

# include "../libft/libft.h"

# define COL_YELLOW "\x1b[33m"
# define COL_RESET "\x1b[0m"

# define SHELL_COLOR_ESCAPE_SEQ(X) "\x1b["X"m"

typedef struct s_hosts
{
	char *ip;
	int port;
	int status;
}				t_hosts;

typedef struct s_combo
{
	char *user;
	char *pass;
}				t_combo;

typedef struct s_threads
{
	int	id;
	char *output;
	int	nb_threads;
	int	nb_hosts;
	int	nb_combo;
	t_hosts *hosts;
	t_combo *combos;
	pthread_t			thread;
	ssh_session ssh;
	
}				t_threads;

void 			ft_thread(void *content);
t_threads 	*ft_create_thread(int nb_threads, t_hosts *hosts, t_combo *combos, unsigned int nb_hosts, unsigned int nb_combo, char *output);
int64_t		get_time(void);
int			ft_is_done(t_hosts *hosts, unsigned int nb_hosts);
int			ft_count(t_hosts *hosts, unsigned int nb_hosts, int y);
int			ft_left(t_hosts *hosts, unsigned int nb_hosts);
int			ft_intlen(int n);
int			ft_splitlen(char **split);
void			ft_free_split(char **split);
t_combo 		*ft_get_combos(char *str);
unsigned int	ft_get_line(char *str);
t_hosts		*ft_get_hosts(char *str);
char			*ft_get_file(int fd, int size, int len);

#endif