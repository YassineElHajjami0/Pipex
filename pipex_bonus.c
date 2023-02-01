/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:55:31 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/02/01 11:06:24 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parsing(int ac, char **av, char **env, t_allvar *allvar)
{
	int i = -1;
	if (ac < 5 || (ac != 6  && (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0))
	||  (ac != 6  && (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) != 0) && ac < 5))
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
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
	{
		allvar->z = 3;
		allvar->k = 4;	
	}
	while (++allvar->p < ac - allvar->k)
	{
		allvar->j = 0;
		check_cmd(av[allvar->p + allvar->z], allvar, allvar->p);
		if (allvar->j == 0)
			write_error(2);
	}
	allvar->paths[allvar->p] = 0;
}

int main(int ac, char **av, char **env)
{
	t_allvar	allvar;
	int			id;
	int			fd[2];
	int	fd1;
	int	fd2;
	allvar.bonus = 1;
	parsing(ac, av, env, &allvar);
	allvar.k = 3;
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
	{
		allvar.k = 4;
		fd1 = open(".temp", O_CREAT | O_WRONLY, 0666);
		fd2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
	}
	else
	{
		fd1 = open(av[1], O_RDONLY);
		fd2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	}
	if (fd1 < 0 || fd2 < 0)
		write_error(2);
	int i = -1;
	printf("hamdulah\n");
	while (++i < ac - allvar.k)
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
			if (i == ac - (allvar.k + 1))
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
	while(1){}
	return 0;
}