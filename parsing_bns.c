/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:15:04 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/02/04 15:21:53 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	help_parsing(t_allvar *allvar, int ac, char **av)
{
	if (ft_strncmp(av[1], "here_doc", ft_strlenn(av[1])) == 0)
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

void	parsing(int ac, char **av, char **env, t_allvar *allvar)
{
	int	i;

	i = -1;
	if (ac < 5 || (ac != 6
			&& (ft_strncmp(av[1], "here_doc", ft_strlenn(av[1])) == 0))
		|| (ac != 6 && (ft_strncmp(av[1], "here_doc", ft_strlenn(av[1])) != 0)
			&& ac < 5))
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
	help_parsing(allvar, ac, av);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (fd < 0 || !s)
		return ;
	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
}
