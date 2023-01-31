/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:48:39 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/01/30 16:44:31 by yel-hajj         ###   ########.fr       */
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

void	check_cmd(char *cmd, t_allvar *allvar, int n, int *cp)
{
	allvar->split_it = ft_split(cmd, ' ');
	allvar->i = -1;
	while (allvar->res[++allvar->i])
	{
		if (access(ft_strjoin(allvar->res[allvar->i], allvar->split_it[0]), F_OK) == 0)
		{
			allvar->paths[n] = ft_strjoin(allvar->res[allvar->i], allvar->split_it[0]);
			(*cp)++;
		}
	}
}

void	parsing(int ac, char **av, char **env, t_allvar *allvar)
{
	// if (ac != 5)
	// 	write_error(2);
	find_path(env, allvar);
	ft_strchr(allvar);
	allvar->res = ft_split(allvar->str, ':');
	join_withslash(allvar);
	allvar->paths = malloc(sizeof(char *) * (ac - 2));
	int i = -1;
	int	cp;
	while (++i < ac - 3)
	{
		cp = 0;
		check_cmd(av[i + 2], allvar, i, &cp);
		if (cp == 0)
			write_error(2);
	}
	allvar->paths[i] = 0;
	// allvar->allcmd1 = ft_split(av[2], ' ');
	// allvar->allcmd2 = ft_split(av[3], ' ');
	//	for(int i = 0 ; allvar->res[i] != NULL; i++)
	//		printf("=>%s\n", allvar->res[i]);
	// printf("\033[0;32m");
	// printf("PARSING DONE ✓✓✓\n");
	// // printf("\033[0m");
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

	parsing(ac, av, env, &allvar);
	
	int	fd1 = open(av[1], O_RDONLY);
	int	fd2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
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

	

	// 	tba3(allvar.allcmd1);
	// pipe(fd);
	// id = fork();
	// if (id == 0)
	// {
	// 	int f1 = open(av[1], O_RDONLY);
	// 	dup2(f1 ,0);
	// 	dup2(fd[1], 1);
	// 	close(fd[1]);
	// 	close(fd[0]);
	// 	execve(allvar.cmd1, allvar.allcmd1, env);
	// }
	// dup2(fd[0], 0);
	// pid_t id2 = fork();
	// if (id2 == 0)
	// {
	// 	int f2 = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	// 	// dup2(fd[1], 1);
	// 	dup2(f2 ,1);
	// 	close(fd[1]);
	// 	close(fd[0]);
	// 	execve(allvar.cmd2, allvar.allcmd2, env);
	// }
	// dup2(fd[0], 0);
	// close(fd[0]);
	// close(fd[1]);
	while(1)
	{
		if (wait(NULL) == -1)
			break ;
	}
	return 0;
}

// paths of all cmds
// ./pipex_bonus here_doc limiter + \n
// if here_doc open file .tmp
// at9ra mn 0 otktb fih (.tmp)