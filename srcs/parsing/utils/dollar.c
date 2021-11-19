/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:12:39 by mballet           #+#    #+#             */
/*   Updated: 2021/11/08 16:29:33 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short int	dollar(char *line, int loc)
{
	if (line[loc] == '$' && line[loc + 1] && line[loc + 1])
		return (SUCCESS);
	return (FAILURE);
}
