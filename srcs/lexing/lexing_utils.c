/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:38:21 by nlederge          #+#    #+#             */
/*   Updated: 2024/01/11 18:41:38 by nlederge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (code);
}