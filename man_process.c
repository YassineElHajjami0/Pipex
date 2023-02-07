/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   man_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:23:01 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/02/07 11:42:43 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	paarsing(int ac, char **av, char **env, t_allvar *allvar)
{
	allvar->i = -1;
	if (ac != 5)
		write_error(2);
	check_av(ac, av, env, 1);
	allvar->p = -1;
	while (env[++allvar->i])
	{
		if (!ft_strncmp(env[allvar->i], "PATH=", 5))
			allvar->res = ft_split(env[allvar->i] + 5, ':');
	}
	if (!allvar->res)
		write_error(2);
	join_withslash(allvar);
	allvar->paths = malloc(sizeof(char *) * (ac - 2));
	allvar->z = 2;
	while (++allvar->p < ac - 3)
	{
		allvar->j = 0;
		check_cmd(av[allvar->p + allvar->z], allvar, allvar->p);
		if (allvar->j == 0)
			write_error(2);
	}
	allvar->paths[allvar->p] = 0;
}

void	child_process(t_allvar *allvar, int ac, char **av, char **env)
{
	if (allvar->i == 0)
	{
		if (dup2(allvar->fd1, 0) < 0)
			write_error(2);
	}
	if (allvar->i == ac - 4)
	{
		if (dup2(allvar->fd2, 1) < 0)
			write_error(2);
	}
	else
	{
		if (dup2(allvar->fd[1], 1) < 0)
			write_error(2);
	}
	close(allvar->fd[1]);
	close(allvar->fd[0]);
	if (0 > execve(allvar->paths[allvar->i],
			ft_split(av[allvar->i + 2], ' '), env))
	{
		write(2, "Error\n", 6);
		exit(1);
	}
}

void	protection(t_allvar *allvar, int ac, char **av, char **env)
{
	if (pipe(allvar->fd) < 0)
		write_error(2);
	allvar->id = fork();
	if (allvar->id < 0)
		write_error(2);
	if (allvar->id == 0)
		child_process(allvar, ac, av, env);
	if (dup2(allvar->fd[0], 0) < 0)
		write_error(2);
}

void	free_all(char **res)
{
	int	i;

	i = -1;
	while (res[++i])
		free(res[i]);
	free(res);
}

void	loop_cmds(t_allvar *allvar, int ac, char **av, char **env)
{
	while (++allvar->i < ac - 3)
	{
		protection(allvar, ac, av, env);
		close(allvar->fd[1]);
		close(allvar->fd[0]);
	}
	while (1)
	{
		if (wait(NULL) == -1)
			break ;
	}
}
