/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:52:59 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/02/04 17:05:54 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_allvar
{
	int		fd[2];
	int		fd1;
	int		fd2;
	int		id;
	int		i;
	int		j;
	int		z;
	int		k;
	int		p;
	int		bonus;
	char	*join;
	char	*str;
	char	**res;
	char	**paths;
	char	**split_it;

}			t_allvar;

char	**ft_split(char const *s, char c);
char	*ft_strjoinn(char const *s1, char const *s2);
void	write_error(int n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlenn(const char *c);
void	check_cmd(char *cmd, t_allvar *allvar, int n);
void	join_withslash(t_allvar *allvar);
int		ft_strcmp(char *s1, char *s2);
void	parsing(int ac, char **av, char **env, t_allvar *allvar);
void	ft_putstr_fd(char *s, int fd);
void	some_checks(t_allvar *allvar, int ac, char **av);
void	read_data(t_allvar *allvar, char **av);
void	protections(t_allvar *allvar);
void	the_child_process(t_allvar *allvar, int ac, char **av, char **env);
void	loop_on_data(t_allvar *allvar, int ac, char **av, char **env);
void	paarsing(int ac, char **av, char **env, t_allvar *allvar);
void	protection(t_allvar *allvar);
void	child_process(t_allvar *allvar, int ac, char **av, char **env);
void	loop_cmds(t_allvar *allvar, int ac, char **av, char **env);
void	free_all(char **res);

#endif