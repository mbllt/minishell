/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_separator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:42:29 by mballet           #+#    #+#             */
/*   Updated: 2021/10/25 17:37:44 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int short	is_separator(char c, char **esc_quote, int loc)
{
	if (is_quotes_pipe(c, esc_quote, loc) || c == '<' || c == '>' || c == ' ')
		return (SUCCESS);
	return (FAILURE);
}
