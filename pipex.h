/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:52:59 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/01/29 16:07:43 by yel-hajj         ###   ########.fr       */
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
	char	*str;
	char	**res;
	char	**paths;
	char	**allcmd1;
	char	**allcmd2;
	char	**cmds;
	char	**split_it;

}		t_allvar;

char	**ft_split(char const *s, char c);

#endif