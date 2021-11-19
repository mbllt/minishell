/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:32:24 by mballet           #+#    #+#             */
/*   Updated: 2021/11/02 11:25:56 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERROR_SPACE 2

static short int	is_space_(char *str)
{
	int	i;

	i = -1;
	if (str[i + 1] && str[i + 1] == ' ')
		return (SUCCESS);
	while (str[++i])
	{
		if (str[i] && str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (str[i] && str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
		}
		if (str[i] && str[i] == ' ' && str[i + 1] && str[i + 1] == ' ')
			return (SUCCESS);
	}
	return (FAILURE);
}

static short int	only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
	{
		i++;
	}
	if (!str[i])
		return (SUCCESS);
	return (FAILURE);
}

static int	find_size(char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (i == 0)
			while (str[i] && str[i] == ' ')
				i++;
		while (str[i] && str[i] == ' ' && str[i + 1] && str[i + 1] == ' ')
			i++;
		if (is_quote(str[i]))
		{
			quote = str[i];
			norm(&i, &j);
			while (str[i] && str[i] != quote)
			{
				norm(&i, &j);
			}
		}
		norm(&i, &j);
	}
	return (j);
}

static char	*new_str(char *new, char **str, short int s, short int d)
{
	int		i;
	int		j;
	int		size;

	size = find_size(new);
	i = 0;
	j = 0;
	while (new[i] && j < size)
	{
		if (i == 0)
			while (new[i] == ' ')
				i++;
		if (new[i] == '\'')
			s++;
		if (new[i] == '\"')
			d++;
		while (!(s % 2) && !(d % 2) && is_space_and_next(new, i, ' '))
			i++;
		(*str)[j] = new[i];
		i++;
		j++;
	}
	(*str)[j] = 0;
	return (new);
}

short int	trim_space(char **str)
{
	char		*new;
	int			size;
	short int	s_quote;
	short int	d_quote;

	s_quote = 0;
	d_quote = 0;
	if (is_space_(*str))
	{
		if (only_space(*str))
			return (ERROR_SPACE);
		new = ft_strdup(*str);
		if (!new)
			return (FAILURE);
		size = find_size(new);
		*str = ft_realloc(*str, size + 1);
		if (!(*str))
			return (FAILURE);
		if (!new_str(new, str, s_quote, d_quote))
			return (FAILURE);
		free(new);
	}
	return (SUCCESS);
}
