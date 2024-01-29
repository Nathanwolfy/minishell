/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:38:21 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/29 15:05:35 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int	unclosed_quotes_code(int sq, int dq)
{
	if (sq)
		return (-2);
	else if (dq)
		return (-3);
	return (-4);
}

int	print_error_lexing_code(int code)
{
	//Add error code message
	return (code);
}

static int	check_content_quotes(t_token *node)
{
	char	*word;

	if (!(node->content) || node->type != T_WORD)
		return (0);
	word = node->content; 
	if (word[0] == '\'' && word[ft_strlen(word) - 1] == '\'')
		return (1);
	if (word[0] == '\"' && word[ft_strlen(word) - 1] == '\"')
		return (2);
	return (0);
}

int	check_token_quotes(t_token **token)
{
	t_token	*node;
	char	*temp;
	int		res;

	if (!token)
		return (-1); //define clear malloc codes
	node = *token;
	while (node)
	{
		res = check_content_quotes(node);
		if (res > 0)
		{
			temp = ft_substr(node->content, 1, ft_strlen(node->content) - 2);
			if (!temp)
				return (-1);
			free(node->content);
			node->content = temp;
		}
		node = node->next;
	}
	return (0);
}