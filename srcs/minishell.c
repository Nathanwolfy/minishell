/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:02:07 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/25 16:54:30 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	main(int argc, char *argv[], char *old_envp[])
{
	char	**envp;

	if (argc < 1 || !argv || !old_envp || !(old_envp[0])) //env -i needs to be handled
		return (1); //handle correctly + what to do with argc and envp
	envp = copy_envp(old_envp);
	if (!envp)
		return (1); //define clean error codes
	prompt(envp);
	return (0);
}
