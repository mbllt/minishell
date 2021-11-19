/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:38:44 by mballet           #+#    #+#             */
/*   Updated: 2021/11/08 18:54:36 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static short int	fill_token(t_token *token, char *line, int *i, \
						char **esc_quote)
{
	int	ret;

	ret = SUCCESS;
	if (!token->export && is_export(line + *i))
		token->export = 1;
	else if (token->export)
	{
		token->export = 0;
		if (!export_quote(token, line, i, esc_quote))
			return (FAILURE);
		return (SUCCESS);
	}
	find_token_content(token, line, i);
	ret = find_token(token, line, i, esc_quote);
	if (!ret)
		return (FAILURE);
	return (ret);
}

static short int	fill_cmds(t_cmd *content, t_token token)
{
	t_list	*new;

	if (token.content.arg == 1)
	{
		new = ft_lstnew(token.str);
		if (!new)
			return (FAILURE);
		ft_lstadd_back(&(content->args), new);
	}
	else if (token.content.in != _NOTHING)
	{
		new = ft_lstnew(token.redir);
		if (!new)
			return (FAILURE);
		ft_lstadd_back(&(content->infile), new);
	}
	else if (token.content.out != _NOTHING)
	{
		new = ft_lstnew(token.redir);
		if (!new)
			return (FAILURE);
		ft_lstadd_back(&(content->outfile), new);
	}
	return (SUCCESS);
}

short int	tokenizing(t_exec_info *global, char *line, char **esc_quote)
{
	t_list		*tmp;
	int			i;
	int			j;
	int			ret;
	t_token		token;

	tmp = NULL;
	ret = SUCCESS;
	i = -1;
	while (line[++i] && i < (int)ft_strlen(line) && !is_only_space(line, i))
	{
		init_ret_token(&token, &j, i);
		while (line[i] == ' ')
			i++;
		if (j == 0 || line[i] == '|')
			if (!start(&tmp, line[i], &i))
				return (FAILURE);
		ret = fill_token(&token, line, &i, esc_quote);
		if (!ret || ret == ERR_PARSING)
			return (ret);
		if (!fill_cmds(ft_lstlast(tmp)->content, token))
			return (FAILURE);
	}
	global->cmds = tmp;
	return (ret);
}
