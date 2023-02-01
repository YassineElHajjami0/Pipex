/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:52:59 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/02/01 11:08:05 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct s_allvar
{
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
	char	**allcmd1;
	char	**allcmd2;
	char	**cmds;
	char	**split_it;

}		t_allvar;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void	write_error(int n);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *c);
void	check_cmd(char *cmd, t_allvar *allvar, int n);
void	join_withslash(t_allvar *allvar);

#endif