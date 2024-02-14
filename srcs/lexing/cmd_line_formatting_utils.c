/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line_formatting_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:45:56 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/14 16:52:09 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

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

static char	*create_new_cmd_line(char *old, int *flags)
{
	int		len;
	char	*new;

	len = get_flagged_len(old, flags);
	if (len == 0)
		return ((char *)-1);
	new = ft_calloc(len + 1, sizeof(char));
	if (!new && ft_perror())
		return (NULL);
	return (new);
}

static void	copy_and_increment(char *new, char *old, int *j, int i)
{
	new[*j] = old[i];
	*j += 1;
}

char	*copy_flagged(char *old, int *flags, char **envp, int exit_status)
{
	int		i;
	int		j;
	char	*new;

	new = create_new_cmd_line(old, flags);
	if (!new || new == (char *)-1)
		return (new);
	i = -1;
	j = 0;
	while (old[++i])
	{
		if (flags[i] == 1)
			copy_and_increment(new, old, &j, i);
		else if (flags[i] < 0)
		{
			if (old[i + 1] == '?')
				copy_exit_status(new, j, exit_status);
			else
				copy_env_var(old, new, &i, envp);
			j += -flags[i];
		}
	}
	return (new);
}
