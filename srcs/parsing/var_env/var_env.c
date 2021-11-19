/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 09:46:12 by mballet           #+#    #+#             */
/*   Updated: 2021/11/08 19:53:39 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_norm
{
	int	size;
	int	loc;
}	t_norm;

static short int	get_new_line(char **line, char *val, char ***esc_quote, \
						t_norm n)
{
	char	*str;
	int		i;
	int		j;

	str = ft_strdup(*line);
	if (!str)
		return (FAILURE);
	*line = ft_realloc(*line, (ft_strlen(*line) - n.size + ft_strlen(val) + 1));
	if (!(*line))
		return (FAILURE);
	j = n.loc + 1;
	i = -1;
	while (val[i + 1])
	{
		if (val[i + 1] == '\'' || val[i + 1] == '\"')
			if (!fill_esc_quote(esc_quote, n.loc + 1))
				return (FAILURE);
		(*line)[++(n.loc)] = val[++i];
	}
	j += n.size;
	while (str[j])
		(*line)[++(n.loc)] = str[++j];
	(*line)[++(n.loc)] = 0;
	free(str);
	return (SUCCESS);
}

static char	*get_key(char *line, int loc, char **esc_quote)
{
	int		i;
	char	*str;

	if (line[loc] && line[loc] == '?')
		return (ft_strdup("?"));
	i = 0;
	loc--;
	while (line[++loc] && (line[loc] != ' ') && !is_quotes_pipe(line[loc], \
			esc_quote, loc) && !dollar(line, loc) && !forb_char(line[loc]))
		i++;
	loc -= i;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (line[loc] && (line[loc] != ' ') && !is_quotes_pipe(line[loc], \
			esc_quote, loc) && !dollar(line, loc) && !forb_char(line[loc]))
	{
		str[i] = line[loc];
		loc++;
		i++;
	}
	str[i] = 0;
	return (str);
}

static short int	trim_dollar(t_exec_info *global, char **line, int loc, \
						char ***esc_quote)
{
	char	*key;
	char	*value;
	t_norm	n;

	key = NULL;
	value = NULL;
	key = get_key(*line, loc + 1, *esc_quote);
	if (!key)
		return (FAILURE);
	n.size = ft_strlen(key);
	n.loc = loc - 1;
	value = ft_getenv_value(key, global->env);
	if (!value)
	{
		if (!get_new_line(line, "\0", esc_quote, n))
			return (FAILURE);
	}
	else
	{
		if (!get_new_line(line, value, esc_quote, n))
			return (FAILURE);
		free(value);
	}
	free(key);
	return (SUCCESS);
}

static short int	in_s_quote(char *str, int loc)
{
	int	i;
	int	stock_loc_i;

	i = -1;
	while (str[++i])
	{
		stock_loc_i = -1;
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
		}
		else if (str[i] == '\'')
		{
			stock_loc_i = i;
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (stock_loc_i >= 0 && loc < i && loc > stock_loc_i)
			return (SUCCESS);
	}
	return (FAILURE);
}

short int	var_env(char **line, t_exec_info *global, char ***esc_quote)
{
	int			i;
	short int	ret;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && (*line)[i + 1] && (*line)[i + 1] != ' ' \
			&& !in_s_quote(*line, i))
		{
			ret = trim_dollar(global, line, i, esc_quote);
			if (!ret)
				return (FAILURE);
			i = 0;
		}
		i++;
	}
	return (SUCCESS);
}
