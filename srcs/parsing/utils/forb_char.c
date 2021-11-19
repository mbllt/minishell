/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forb_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:40:25 by mballet           #+#    #+#             */
/*   Updated: 2021/11/08 19:48:27 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short int	forb_char(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (FAILURE);
	return (SUCCESS);
}
