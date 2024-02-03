/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehickman <ehickman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:20:57 by ehickman          #+#    #+#             */
/*   Updated: 2024/02/03 10:24:10 by ehickman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static int	count_split(char *old_envp[])
{
	int	k;

	if (!old_envp)
		return (0);
	k = 0;
	while (old_envp[k])
		k++;
	return (k);
}

static int	modify_env_value(char **envp, char *content)
{
	char	*new;
	int		var_name_len;
	int		i;

	var_name_len = 0;
	while (content[var_name_len] && content[var_name_len] != '=')
		var_name_len++;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], content, var_name_len) == 0)
		{
			new = ft_strdup(content);
			if (!new)
				return (-1);
			free(envp[i]);
			envp[i] = new;
			return (0);
		}
		i++;
	}
	return (1);
}

static char	**append_envp(char *old_envp[], char *content)
{
	char	**envp;
	int		ct;
	int		l;

	ct = count_split(old_envp);
	envp = ft_calloc(ct + 2, sizeof(char *));
	if (!envp)
		return (NULL);
	l = 0;
	while (l < ct)
	{
		envp[l] = ft_strdup(old_envp[l]);
		if (!envp[l])
			return (free_split(envp), NULL);
		l++;
	}
	envp[l] = ft_strdup(content);
	if (!envp[l])
		return (free_split(envp), NULL);
	envp[ct + 1] = NULL;
	return (envp);
}

static int	env_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] != '=' && s1[i] == s2[i])
		i++;
	return ((int)s1[i] - (int)s2[i]);
}

static void	sort_env(char **env)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!env)
		return ;
	while (env[i + 1])
	{
		if (env_cmp(env[i], env[i + 1]) > 0)
		{
			tmp = env[i + 1];
			env[i + 1] = env[i];
			env[i] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

static int	print_declare_envp(char **envp)
{
	char	**envp_cpy;
	int		i;
	int		j;

	i = 0;
	envp_cpy = copy_envp(envp);
	if (!envp_cpy)
		return (-1);
	sort_env(envp_cpy);
	while (envp_cpy[i])
	{
		write(1, "declare -x ", 11);
		j = -1;
		while (envp_cpy[i][++j])
		{
			write(1, &envp_cpy[i][j], 1);
			if (envp_cpy[i][j] == '=')
				write(1, "\"", 1);
		}
		write(1, "\"\n", 2);
		i++;
	}
	return (free_split(envp_cpy), 0);
}

static int	check_format(char *content)
{
	int	i;

	i = 0;
	if (!content || (!ft_isalpha(content[i]) && content[i] != '_'))
	{
		printf("minishell: export: `%s': not a valid identifier\n", content);
		return (-1);
	}
	while (content[i])
	{
		if (content[i] == '=')
			return (0);
		if (!ft_isalpha(content[i]) && !ft_isdigit(content[i])
			&& content[i] != '_')
		{
			printf("minishell: export: `%s': not a valid identifier\n", content);
			return (-1);
		}
		i++;
	}
	return (-1);
}

int	builtin_export(t_tree *node, char ***envp)
{
	char	*formated;
	int		r_val;

	if (!node || !envp || !*envp)
		return (-1);
	if (!node->right)
		return (print_declare_envp(*envp));
	formated = format_quote(node->right->content, *envp);
	if (!formated)
		return (-1);
	if (check_format(node->right->content) == -1) // if there is no = just return
		return (0);
	r_val = modify_env_value(*envp, node->right->content);
	if (r_val == -1)
		return (-1);
	else if (r_val == 1)
		*envp = append_envp(*envp, node->right->content);
	if (!*envp)
		return (-1);
	return (0);
}

/*int	main(int argc, char **argv, char **env)
{
	t_tree	*node;
	t_tree	*node1;

	(void)argc;
	node1 = create_node(T_WORD, argv[1], NULL, NULL);
	node = create_node(T_WORD, "export", NULL, node1);
//	builtin_env(env);
//	printf("SADASDADASDASD\n");
	builtin_export(node, &env);
//	printf("SDADSDASDASDASD\n");
//	builtin_env(env);
}*/
