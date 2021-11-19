/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:50:27 by mballet           #+#    #+#             */
/*   Updated: 2021/10/26 16:52:37 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	starting(t_list **tmp, t_states *st)
{
	t_list	*new;

	new = init_content();
	if (!new)
		return (FAILURE);
	ft_lstadd_back(tmp, new);
	*st = _DEFAULT;
	return (SUCCESS);
}

static int	restarting(char *line, t_list **tmp, int *i)
{
	t_list	*new;

	new = init_content();
	if (!new)
		return (FAILURE);
	ft_lstadd_back(tmp, new);
	(*i)++;
	if (line[(*i)] == ' ')
		(*i)++;
	return (SUCCESS);
}

short int	token_start(t_norm *norm, t_list **tmp, char *line, int *i)
{
	if (norm->st == _START)
	{
		if (!starting(tmp, &(norm->st)))
			return (FAILURE);
	}
	else if (line[*i] == '|')
		if (!restarting(line, tmp, i))
			return (FAILURE);
	return (SUCCESS);
}
