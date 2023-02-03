/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:48:39 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/02/02 15:22:44 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void child (char **env)
{
	int fd[2];
	pipe(fd);
	int id = fork();
	if(id == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close (fd[1]);
		execve("/bin/ls", NULL, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		execve("/bin/cat", NULL, env);
	}
}


void	paarsing(int ac, char **av, char **env, t_allvar *allvar)
{
	int i = -1;
	if (ac != 5)
		write_error(2);
	allvar->p = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			allvar->res = ft_split(env[i] + 5, ':');
	}
	join_withslash(allvar);
	allvar->paths = malloc(sizeof(char *) * (ac - 2));
	allvar->z = 2;
	allvar->k = 3;
	while (++allvar->p < ac - allvar->k)
	{
		allvar->j = 0;
		check_cmd(av[allvar->p + allvar->z], allvar, allvar->p);
		if (allvar->j == 0)
			write_error(2);
	}
	allvar->paths[allvar->p] = 0;
}

void my(void)
{
	system("leaks pipex");
}

int main(int ac, char **av, char **env)
{
	t_allvar	allvar;
	int			id;
	int			fd[2];

	atexit(my);
	allvar.bonus = 0;
	paarsing(ac, av, env, &allvar);
	int	fd1 = open(av[1], O_RDONLY);
	int	fd2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd1 < 0 || fd2 < 0)
		write_error(2);
	int i = -1;
	while (++i < ac - 3)
	{
		
		if (pipe(fd) < 0)
			exit(1);
		id = fork();
		if (id < 0)
			exit(1);
		if (id == 0)
		{
			if (i == 0)
			{
				if (dup2(fd1, 0) < 0)
					exit(1);
			}
			if (i == ac - 4)
			{
				if (dup2(fd2, 1) < 0)
					exit(1);
			}
			else
			{
				if (dup2(fd[1], 1) < 0)
					exit(1);
			}
			close(fd[1]);
			close(fd[0]);
			if(0 > execve(allvar.paths[i], ft_split(av[i + 2], ' '), env))
			{
				write(2, "Errooooor\n", 10);
				exit(1);
			}
		}
		if (dup2(fd[0], 0) < 0)
			exit(1);
		close(fd[1]);
		close(fd[0]);
	}

	while(1)
	{
		if (wait(NULL) == -1)
			break ;
	}
	return 0;
}
