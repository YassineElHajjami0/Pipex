/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fns2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:19:38 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/02/07 11:40:34 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	join_withslash(t_allvar *allvar)
{
	allvar->i = 0;
	allvar->j = 0;
	while (allvar->res[allvar->i])
	{
		free(allvar->res[allvar->i]);
		allvar->res[allvar->i] = ft_strjoinn(allvar->res[allvar->i], "/");
		allvar->i++;
	}
	allvar->i = 0;
	allvar->j = 0;
}

void	check_cmd(char *cmd, t_allvar *allvar, int n)
{
	allvar->split_it = ft_split(cmd, ' ');
	if (allvar->split_it[0][0] == '/' || allvar->split_it[0][0] == '.')
	{
		allvar->paths[n] = (*allvar->split_it);
		allvar->j++;
		return ;
	}
	allvar->i = -1;
	while (allvar->res[++allvar->i])
	{
		allvar->join = ft_strjoinn(allvar->res[allvar->i], allvar->split_it[0]);
		if (access(allvar->join, F_OK) == 0)
		{
			allvar->paths[n] = ft_strjoinn(allvar->res[allvar->i],
					allvar->split_it[0]);
			allvar->j++;
		}
		free(allvar->join);
	}
	free_all(allvar->split_it);
}

void	check_av(int ac, char **av, char **env, int n)
{
	int	i;

	if (!env)
		write_error(2);
	i = 1;
	while (i <= ac - n)
	{
		if (!av[i] || (ft_strlenn(av[i]) == 0))
			write_error(2);
		i++;
	}
}
