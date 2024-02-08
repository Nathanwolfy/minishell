/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line_formatting_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:45:56 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/08 16:17:28 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	get_flagged_len(char *old, int *flags)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (old[i])
	{
		if (flags[i] < 0)
			len += -flags[i];
		else
			len += flags[i];
		i++;
	}
	return (len);
}

static void	copy_exit_status(char *new, int j, int exit_status)
{
	int	n;

	n = exit_status;
	if (exit_status == 0)
		new[j] = '0';
	else
	{
		while (exit_status >= 10)
		{
			j++;
			exit_status /= 10;
		}
		while (n > 0)
		{
			new[j] = n % 10 + '0';
			j--;
			n /= 10;
		}
	}
}

char	*copy_flagged(char *old, int *flags, char **envp, int exit_status)
{
	int		len;
	int		i;
	int		j;
	char	*new;

	len = get_flagged_len(old, flags);
	if (len == 0)
		return ((char *)-1);
	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (old[i])
	{
		if (flags[i] == 1)
		{
			new[j] = old[i];
			j++;
		}
		else if (flags[i] < 0)
		{
			if (old[i + 1] == '?')
				copy_exit_status(new, j, exit_status);
			else
				copy_env_var(old, new, &i, envp);
			j += -flags[i];
		}
		i++;
	}
	return (new);
}
