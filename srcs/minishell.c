/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:02:07 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/09 12:33:45 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"


int	main(int argc, char *argv[], char *old_envp[])
{
	char	**envp;
	t_token	*token;
	t_tree	*ast;

	token = NULL;
	ast = NULL;
	if (argc < 1 || !argv) //relaunch minishell with minishell, it can set argc to 0 and argv to NULL
		return (1); //needs to handle signals properly before
	envp = copy_envp(old_envp);
	if (!envp)
		return (ft_perror(), 1);
	envp = check_mandatory_envp(envp);
	if (!envp)
		return (ft_perror(), 1);
	prompt(token, ast, &envp);
	return (0);
}
