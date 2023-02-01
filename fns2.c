/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fns2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:19:38 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/02/01 11:14:13 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	join_withslash(t_allvar *allvar)
{
	//char	*p;
	allvar->i = 0;
	allvar->j = 0;
	while(allvar->res[allvar->i])
	{
		//p = ft_strjoin(allvar->res[allvar->i], "/");
		allvar->res[allvar->i] = ft_strjoin(allvar->res[allvar->i], "/");
		allvar->i++;
		//free(p);
	}	
}

void	check_cmd(char *cmd, t_allvar *allvar, int n)
{
	allvar->split_it = ft_split(cmd, ' ');
	allvar->i = -1;
	while (allvar->res[++allvar->i])
	{
		allvar->join = ft_strjoin(allvar->res[allvar->i], allvar->split_it[0]);
		if (access(allvar->join, F_OK) == 0)
		{
			allvar->paths[n] = ft_strjoin(allvar->res[allvar->i], allvar->split_it[0]);
			allvar->j++;
		}
		free(allvar->join);
	}
}