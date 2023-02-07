/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bns_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:21:18 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/02/05 16:32:06 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

void	some_checks(t_allvar *allvar, int ac, char **av)
{
	if (ft_strncmp(av[1], "here_doc", ft_strlenn(av[1])) == 0)
	{
		allvar->fd1 = open(".temp", O_CREAT | O_WRONLY, 0666);
		allvar->fd2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
	}
	else
	{
		allvar->fd1 = open(av[1], O_RDONLY);
		allvar->fd2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	}
	if (allvar->fd1 < 0 || allvar->fd2 < 0)
		write_error(2);
}

void	read_data(t_allvar *allvar, char **av)
{
	char	*line;
	char	*limit;

	if (ft_strncmp(av[1], "here_doc", ft_strlenn(av[1])) == 0)
	{
		limit = ft_strjoinn(av[2], "\n");
		line = get_next_line(0);
		while (line && ft_strcmp(line, limit))
		{
			ft_putstr_fd(line, allvar->fd1);
			free(line);
			line = get_next_line(0);
		}
		close(allvar->fd1);
		allvar->fd1 = open(".temp", O_RDONLY);
		free(line);
		free(limit);
	}
}

void	the_child_process(t_allvar *allvar, int ac, char **av, char **env)
{
	if (allvar->i == 0)
	{
		if (dup2(allvar->fd1, 0) < 0)
			write_error(2);
	}
	if (allvar->i == ac - (allvar->k + 1))
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
			ft_split(av[allvar->i + allvar->z], ' '), env))
	{
		write(2, "Error\n", 6);
		exit(1);
	}
}

void	protections(t_allvar *allvar, int ac, char **av, char **env)
{
	if (pipe(allvar->fd) < 0)
		write_error(2);
	allvar->id = fork();
	if (allvar->id < 0)
		write_error(2);
	if (allvar->id == 0)
		the_child_process(allvar, ac, av, env);
	if (dup2(allvar->fd[0], 0) < 0)
		write_error(2);
}

void	loop_on_data(t_allvar *allvar, int ac, char **av, char **env)
{
	allvar->i = -1;
	while (++allvar->i < ac - allvar->k)
	{
		protections(allvar, ac, av, env);
		close(allvar->fd[1]);
		close(allvar->fd[0]);
	}
	while (1)
	{
		if (wait(NULL) == -1)
			break ;
	}
}
