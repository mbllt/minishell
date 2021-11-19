/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_only_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:18:15 by mballet           #+#    #+#             */
/*   Updated: 2021/11/03 10:18:57 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short int	is_only_space(char *str, int i)
{
	while (str[i])
	{
		if (str[i] != ' ')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
