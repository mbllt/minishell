/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:40:04 by mballet           #+#    #+#             */
/*   Updated: 2021/10/26 16:40:19 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short int	norm_free(char **esc_quote, t_norm norm, int ret)
{
	if (esc_quote)
		free(norm.esc_quote);
	return (ret);
}
