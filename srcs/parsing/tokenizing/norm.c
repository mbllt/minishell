/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:56:31 by mballet           #+#    #+#             */
/*   Updated: 2021/11/02 08:43:40 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_redir(t_token *token, char *line, int *i)
{
	if (token->content.in == _SINGLE)
		token->redir->count = _REDIR_SINGLE;
	else if (token->content.in == _DOUBLE)
		token->redir->count = _REDIR_DOUBLE;
	else if (token->content.out == _SINGLE)
		token->redir->count = _REDIR_SINGLE;
	else if (token->content.out == _DOUBLE)
		token->redir->count = _REDIR_DOUBLE;
	if (line[*i] == ' ')
		(*i)++;
}

void	norm_fill_redir_name(t_token *token, char *line, int *i, \
						char **esc_quote)
{
	int		j;
	char	quote;

	j = 0;
	while (line[*i] && line[*i] != ' ' && line[*i] != '>' && line[*i] != '<')
	{
		if (is_quote_export(line[*i], esc_quote, *i))
		{
			quote = line[(*i)++];
			while (line[*i] && line[*i] != quote)
				token->redir->name[j++] = line[(*i)++];
			(*i)++;
			continue ;
		}
		token->redir->name[j++] = line[(*i)++];
	}
	token->redir->name[j] = 0;
}
