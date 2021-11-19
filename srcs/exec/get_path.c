/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 01:10:38 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/11/08 15:21:09 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**add_cmd(char **path, int i, char *cmd)
{
	char	*tmp;
	char	*com;

	tmp = ft_strjoin(path[i], "/");
	if (!tmp)
	{
		ft_free_token_list(path);
		return (NULL);
	}
	free(path[i]);
	com = ft_strjoin(tmp, cmd);
	if (!com)
	{
		ft_free_token_list(path);
		free(tmp);
		return (NULL);
	}
	path[i] = com;
	free(tmp);
	return (path);
}

static char	**prepare_absolute_path(char *cmd)
{
	char	**path;

	path = malloc(sizeof(char *) * 2);
	if (!path)
		return (NULL);
	path[0] = ft_strdup(cmd);
	path[1] = NULL;
	return (path);
}

static char	**get_env_path(t_list *env)
{
	char	**path;
	char	*tmp;

	tmp = ft_getenv_value("PATH", env);
	path = ft_split(tmp, ":");
	free(tmp);
	return (path);
}

static char	**prepare_path(char *cmd, t_list *env)
{
	int		i;
	char	**path;

	if (!ft_strncmp(cmd, "/", 1))
		return (prepare_absolute_path(cmd));
	else if (!ft_strncmp(cmd, "./", 2))
	{
		path = malloc(sizeof(char *) * 2);
		if (!path)
			return (NULL);
		path[0] = getcwd(NULL, 0);
		path[1] = NULL;
		cmd += 2 * sizeof(char);
	}
	else
	{
		path = get_env_path(env);
		if (!path)
			return (NULL);
	}
	i = 0;
	while (path[i])
		add_cmd(path, i++, cmd);
	return (path);
}

char	*get_path(char *cmd, t_list *env)
{
	int		i;
	char	*res;
	char	**path;

	path = prepare_path(cmd, env);
	if (!path)
		return (NULL);
	res = NULL;
	i = 0;
	while (path[i])
	{
		if (access(path[i], X_OK) == 0)
		{
			res = ft_strdup(path[i]);
			break ;
		}
		i++;
	}
	ft_free_token_list(path);
	return (res);
}
