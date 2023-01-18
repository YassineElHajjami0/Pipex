/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:48:39 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/01/16 17:03:31 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pipex.h"

//----------------join
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*l;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		j++;
	l = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!l)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		l[++j] = s1[i];
	i = -1;
	while (s2[++i])
		l[++j] = s2[i];
	l[++j] = '\0';
	return (l);
}
//----------------join
//----------------split
static	int	countwords(char *s, char c)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			words++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (words);
}

static	char	*bringarray(char *s1, int cp)
{
	int		i;
	char	*p;

	p = (char *)malloc(sizeof(char) * cp + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (i < cp)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

static	void	freearr(char **pp)
{
	int	i;

	i = 0;
	while (pp[i])
		free(pp[i++]);
	free(pp);
}

static	void	fillarrays(char **pp, char *s, int l, char c)
{
	int	i;
	int	j;
	int	cp;

	i = -1;
	j = 0;
	while (++i < l)
	{
		cp = 0;
		while (s[j] && s[j] == c)
			j++;
		while (s[j] && s[j] != c)
		{
			j++;
			cp++;
		}
		pp[i] = bringarray(&s[j - cp], cp);
		if (!pp[i])
		{
			freearr(pp);
			return ;
		}
		j++;
	}
	pp[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	int		l;
	char	**pp;

	if (!s)
		return (NULL);
	l = countwords((char *)s, c);
	pp = (char **)malloc(sizeof(char *) * (l + 1));
	if (!pp)
		return (NULL);
	fillarrays(pp, (char *)s, l, c);
	return (pp);
}
//----------------split
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

void	write_error(int n)
{
	write(n, "Eroor\n", 6);
	exit(1);
}

void	find_path(char **env, t_allvar *allvar)
{
	allvar->i = 0;
	allvar->j = 0;
	while(env[allvar->i])
	{
		if(env[allvar->i][0] == 'P' && env[allvar->i][1] == 'A'
		&& env[allvar->i][2] == 'T' && env[allvar->i][3] == 'H')
		{
			allvar->str = env[allvar->i];
			return ;
		}
		allvar->i++;
	}
}

void	ft_strchr(t_allvar *allvar)
{
	allvar->i = 0;
	while (allvar->str[allvar->i])
	{
		if(allvar->str[allvar->i] == '=')
		{
			allvar->str = &allvar->str[allvar->i + 1];
			return ;
		}
		allvar->i++;
	}
}

void	join_withslash(t_allvar *allvar)
{
	allvar->i = 0;
	allvar->j = 0;
	while(allvar->res[allvar->i])
	{
		
		allvar->res[allvar->i] = ft_strjoin(allvar->res[allvar->i], "/");
		allvar->i++;
	}	
}

int	check_cmd(char *cmd, t_allvar *allvar, int n)
{
	allvar->split_it = ft_split(cmd, ' ');
	allvar->i = 0;
	allvar->j = 0;
	while (allvar->res[allvar->i])
	{
		if (access(ft_strjoin(allvar->res[allvar->i], allvar->split_it[0]), X_OK) == 0)
		{
			if (n == 2)
			{
				allvar->path1 = allvar->res[allvar->i];
				allvar->cmd1 = ft_strjoin(allvar->path1, allvar->split_it[0]);
			}
			if (n == 3)
			{
				allvar->path2 = allvar->res[allvar->i];
				allvar->cmd2 = ft_strjoin(allvar->path2, allvar->split_it[0]);
			}
			return 1;
		}
		allvar->i++;
	}
	return 0;
}

// void	tba3(char **cmd, t_allvar *allvar)
// {
// 	allvar->i = 0;
// 	allvar->j = 0;
// 	while (cmd[allvar->i])
// 	{
// 		printf("-->%s ", cmd[allvar->i]);
// 		printf("\n");
// 		allvar->i++;
// 	}
// }

void	parsing(int ac, char **av, char **env, t_allvar *allvar)
{
	if (ac != 5)
		write_error(2);
	find_path(env, allvar);
	ft_strchr(allvar);
	allvar->res = ft_split(allvar->str, ':');
	join_withslash(allvar);
	if (!check_cmd(av[2], allvar, 2))
		write_error(2);
	if(!check_cmd(av[3], allvar, 3))
		write_error(2);
	allvar->allcmd1 = ft_split(av[2], ' ');
	allvar->allcmd2 = ft_split(av[3], ' ');
	//	for(int i = 0 ; allvar->res[i] != NULL; i++)
	//		printf("=>%s\n", allvar->res[i]);
	printf("\033[0;32m");
	printf("PARSING DONE ✓✓✓\n");
	printf("\033[0m");
}

void	tba3(char **tab)
{
	int i = 0;
	while (tab[i])
		puts(tab[i++]);
}

int main(int ac, char **av, char **env)
{
	t_allvar	allvar;
	int			id;
	int			fd[2];

	//tba3(env);
	parsing(ac, av, env, &allvar);
	printf("cmd1 => %s\n", allvar.cmd1);
	printf("cmd2 => %s\n", allvar.cmd2);
	pipe(fd);
	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		int f1 = open(av[1], O_RDONLY);
		dup2(f1 ,0);
		dup2(fd[1], 1);
		char *args[] = {allvar.cmd1, *allvar.allcmd1, NULL};
		execve(args[0], &args[1], env);
		close(fd[1]);
		close(f1);
	}
	pid_t id2 = fork();
	if (id2 == 0)
	{
		close(fd[1]);
		int f2 = open(av[4], O_RDWR);
		dup2(f2 ,1);
		dup2(fd[0], 0);
		char *args[] = {allvar.cmd2, *allvar.allcmd2, NULL};
		execve(args[0], &args[1], env);
		close(f2);
		close(fd[0]);
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
	return 0;
}