/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:01:42 by mballet           #+#    #+#             */
/*   Updated: 2021/11/08 17:09:00 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static short int	find_token_str(t_token *token, char *line, int *i, \
						char **esc_quote)
{
	int		j;
	char	quote;

	token->str = malloc(sizeof(char) * size_token(line, *i, esc_quote) + 1);
	if (!token->str)
		return (FAILURE);
	j = 0;
	while (line[*i] && !is_redir_space(line[*i]) && line[*i] != '|')
	{
		if (is_quote_export(line[*i], esc_quote, *i))
		{
			quote = line[(*i)++];
			while (line[*i] && line[*i] != quote)
			{
				token->str[j++] = line[(*i)++];
			}
			(*i)++;
			continue ;
		}
		token->str[j++] = line[(*i)++];
	}
	token->str[j] = 0;
	(*i)--;
	return (SUCCESS);
}

static short int	find_token_redir(t_token *token, char *line, int *i, \
						char **esc_quote)
{
	int		size;

	token->redir = malloc(sizeof(t_file_redir));
	if (!token->redir)
		return (FAILURE);
	fill_redir(token, line, i);
	size = size_token(line, *i, esc_quote);
	if (!size)
		return (ERR_PARSING);
	token->redir->name = malloc(sizeof(char) * size + 1);
	if (!token->redir->name)
		return (FAILURE);
	norm_fill_redir_name(token, line, i, esc_quote);
	(*i)--;
	return (SUCCESS);
}

short int	find_token(t_token *token, char *line, int *i, \
						char **esc_quote)
{
	int	ret;

	ret = SUCCESS;
	if (token->content.arg == 1)
	{
		if (!find_token_str(token, line, i, esc_quote))
			return (FAILURE);
	}
	else if (token->content.in != _NOTHING || token->content.out != _NOTHING)
	{
		ret = find_token_redir(token, line, i, esc_quote);
		if (!ret)
			return (FAILURE);
		if (ret == ERR_PARSING)
		{
			ft_fprintf(1, "%s", PROMPT);
			ft_fprintf(1, "syntax error near unexpected token `newline'\n");
			free(token->redir);
		}
	}
	return (ret);
}
