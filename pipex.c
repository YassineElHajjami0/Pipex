/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:48:39 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/02/04 15:22:38 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	my(void)
{
	system("leaks pipex");
}

int	main(int ac, char **av, char **env)
{
	t_allvar	allvar;

	allvar.bonus = 0;
	paarsing(ac, av, env, &allvar);
	allvar.fd1 = open(av[1], O_RDONLY);
	allvar.fd2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (allvar.fd1 < 0 || allvar.fd2 < 0)
		write_error(2);
	allvar.i = -1;
	loop_cmds(&allvar, ac, av, env);
	return (0);
}
