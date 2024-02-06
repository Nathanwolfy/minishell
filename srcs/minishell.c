/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:02:07 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/06 14:16:00 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/*
0 : nothing
else : error displayed with strerror(errno)
*/

static int	print_error_main(void)
{
	if (errno != 0)
		print_error_from_errno();
	return (errno);
}

int	main(int argc, char *argv[], char *old_envp[])
{
	char	**envp;
	t_token	*token;
	t_tree	*ast;

	token = NULL;
	ast = NULL;
	if (argc < 1 || !argv) //relaunch minishell with minishell, it can set argc to 0 and argv to NULL
		return (1); //needs to handle signals properly before
	if (!old_envp || !(old_envp[0]))
		return (ft_putendl_fd("minishell: envp is empty", STDERR_FILENO), 1); //create envp if it's empty
	else
		envp = copy_envp(old_envp);
	if (!envp)
		return (print_error_main()); //define clean error codes
	prompt(token, ast, envp);
	return (0);
}
