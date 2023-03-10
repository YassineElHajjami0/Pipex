/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:55:31 by yel-hajj          #+#    #+#             */
/*   Updated: 2023/02/05 08:05:31 by yel-hajj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

int	main(int ac, char **av, char **env)
{
	t_allvar	allvar;

	parsing(ac, av, env, &allvar);
	some_checks(&allvar, ac, av);
	read_data(&allvar, av);
	loop_on_data(&allvar, ac, av, env);
	free_all(allvar.res);
	free_all(allvar.paths);
	unlink(".temp");
	return (0);
}
