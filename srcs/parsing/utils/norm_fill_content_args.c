/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_fill_content_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 17:07:51 by mballet           #+#    #+#             */
/*   Updated: 2021/10/26 17:07:57 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short int	norm_fill_content_args(t_cmd *content, t_list *new, char *str)
{
	new = ft_lstnew(str);
	if (!new)
		return (FAILURE);
	ft_lstadd_back(&(content->args), new);
	return (SUCCESS);
}
