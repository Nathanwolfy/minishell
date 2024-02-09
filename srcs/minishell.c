/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:02:07 by nlederge          #+#    #+#             */
/*   Updated: 2024/02/09 15:20:37 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"


int	main(int argc, char *argv[], char *old_envp[])
{
	char	**envp;
	t_token	*token;
	t_tree	*ast;

	(void)argc;
	(void)argv;
	token = NULL;
	ast = NULL;
	envp = copy_envp(old_envp);
	if (!envp)
		return (ft_perror(), 1);
	envp = check_mandatory_envp(envp);
	if (!envp)
		return (ft_perror(), 1);
	prompt(token, ast, &envp);
	return (0);
}
