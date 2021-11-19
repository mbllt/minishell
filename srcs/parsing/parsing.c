/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:32:25 by mballet           #+#    #+#             */
/*   Updated: 2021/11/08 19:44:02 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERROR_SPACE 2

short int	parsing(char **line, t_exec_info *global)
{
	short int	ret;
	char		**esc_quote;

	if (*line && (*line)[0] == 0)
		return (SUCCESS);
	if (!error_multi_line(*line))
		return (ERROR_SPACE);
	ret = trim_space(line);
	if (ret == ERROR_SPACE)
		return (SUCCESS);
	if (!ret)
		return (FAILURE);
	esc_quote = NULL;
	if (!var_env(line, global, &esc_quote))
		return (FAILURE);
	ret = tokenizing(global, *line, esc_quote);
	if (!ret)
		return (FAILURE);
	return (ret);
}
