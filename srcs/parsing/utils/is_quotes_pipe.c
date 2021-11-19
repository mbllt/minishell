/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quotes_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:14:17 by mballet           #+#    #+#             */
/*   Updated: 2021/11/01 17:34:57 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short int	is_quotes_pipe(char c, char **esc_quote, int loc)
{
	int	i;

	if (c == '\'' || c == '\"')
	{
		i = 0;
		if (esc_quote)
		{
			while (esc_quote[i])
			{
				if (!ft_strncmp(ft_itoa(loc), esc_quote[i], \
						ft_strlen(esc_quote[i])))
					return (FAILURE);
				i++;
			}
		}
		return (SUCCESS);
	}
	else if (c == '|')
		return (SUCCESS);
	return (FAILURE);
}
