/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 20:08:46 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/11/08 13:51:15 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_add_to_env(const char *val, t_list **env)
{
	t_list	*new_elem;

	if (!val)
		return (SUCCESS);
	new_elem = ft_lstnew(ft_strdup(val));
	if (!new_elem)
		return (FAILURE);
	ft_lstadd_back(env, new_elem);
	return (SUCCESS);
}

int	try_add(const char *str, t_list **env)
{
	char	*key;
	char	*val;
	char	**env_entry;
	int		res;

	key = ft_strdup(str);
	val = ft_strchr(key, '=');
	if (val)
		*val = '\0';
	env_entry = ft_getenv_entry(key, *env);
	if (env_entry != NULL)
	{
		res = SUCCESS;
		if (val)
		{
			free(*env_entry);
			*env_entry = ft_strdup(str);
			res = *env_entry != NULL;
		}
	}
	else
		res = ft_add_to_env(str, env);
	free(key);
	return (res);
}

char	*ft_getenv_value(char *key, t_list *env)
{
	char	**env_entry;
	char	*res;

	env_entry = ft_getenv_entry(key, env);
	if (!env_entry)
		return (NULL);
	res = ft_strchr(*env_entry, '=') + sizeof(char);
	if (!res)
		return (NULL);
	res = ft_strdup(res);
	return (res);
}

int	change_env_dollar_question(int n, t_list **env)
{
	char	*tmp;
	char	*str;
	int		res;

	tmp = ft_itoa(n);
	if (!tmp)
		return (FAILURE);
	str = ft_strjoin("?=", tmp);
	free(tmp);
	if (!str)
		return (FAILURE);
	res = try_add(str, env);
	free(str);
	return (res);
}

int	get_exit_code(t_list *env)
{
	char	*tmp;
	int		status;

	tmp = ft_getenv_value("?", env);
	status = ft_atoi(tmp);
	free(tmp);
	return (status);
}
