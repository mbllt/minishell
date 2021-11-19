/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokenizing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:29:09 by mballet           #+#    #+#             */
/*   Updated: 2021/10/26 16:49:50 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short int	init_tokenizing(t_norm *norm, char **esc_quote, t_list **tmp, \
				int *ret)
{
	*ret = SUCCESS;
	*tmp = NULL;
	norm->st = _START;
	if (esc_quote)
		norm->esc_quote = ft_strdup_double(esc_quote);
	if (!norm->esc_quote)
		return (FAILURE);
	return (SUCCESS);
}
