/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_multi_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 13:57:00 by mballet           #+#    #+#             */
/*   Updated: 2021/10/12 16:05:24 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define _PIPE 1
#define _MATCH 2

typedef struct s_special {
	short int	s_quote;
	short int	d_quote;
	short int	r_brackets;
	short int	r_brackets_match;
	short int	c_brackets;
	short int	c_brackets_match;
	short int	s_brackets;
	short int	s_brackets_match;
}	t_special;

static void	fill_spe(t_special *spe, char c)
{
	if (c == '\'')
		spe->s_quote++;
	if (c == '\"')
		spe->d_quote++;
	if (c == '(')
		spe->r_brackets++;
	if (c == ')')
		spe->r_brackets_match++;
	if (c == '{')
		spe->c_brackets++;
	if (c == '}')
		spe->c_brackets_match++;
	if (c == '[')
		spe->s_brackets++;
	if (c == ']')
		spe->s_brackets_match++;
}

static void	find_match(t_special *spe, char *line, int *i, char c)
{
	(*i)++;
	while (line[(*i)] && line[(*i)] != c)
		(*i)++;
	if (line[(*i)] == c)
		fill_spe(spe, c);
}

static void	init_spe(t_special *spe)
{
	spe->s_quote = 0;
	spe->d_quote = 0;
	spe->r_brackets = 0;
	spe->r_brackets_match = 0;
	spe->c_brackets = 0;
	spe->c_brackets_match = 0;
	spe->s_brackets = 0;
	spe->s_brackets_match = 0;
}

static short int	ret(t_special spe, int ret)
{
	if (ret == _PIPE)
	{
		write(1, "error : unexpected token at end of line\n", 40);
		return (FAILURE);
	}
	else
	{
		if (spe.s_quote % 2 || spe.d_quote % 2)
		{
			write(1, "error : multiline\n", 18);
			return (FAILURE);
		}
		if ((spe.r_brackets != spe.r_brackets_match) \
			|| (spe.c_brackets != spe.c_brackets_match) \
			|| (spe.s_brackets != spe.s_brackets_match))
		{
			write(1, "error : multiline\n", 18);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

short int	error_multi_line(char *line)
{
	int			i;
	int			j;
	t_special	spe;

	init_spe(&spe);
	i = 0;
	while (line[i])
	{
		if (is_brackets_quote(line[i]))
			fill_spe(&spe, line[i]);
		if (line[i] == '\'' || line[i] == '\"')
			find_match(&spe, line, &i, line[i]);
		else if (line[i] == '|')
		{
			j = i + 1;
			while (line[j] && line[j] == ' ')
				j++;
			if (!(line[j]))
				return (ret(spe, _PIPE));
		}
		if (spe.s_quote % 2 || spe.d_quote % 2)
			break ;
		i++;
	}
	return (ret(spe, _MATCH));
}
