/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 22:18:37 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/10/25 19:30:02 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	free_and_return(char *str, int ret)
{
	free(str);
	return (ret);
}

static int	change_pwd(t_list **env)
{
	char	*env_entry;
	char	*dir;
	int		res;

	dir = getcwd(NULL, 0);
	if (!dir)
		return (FAILURE);
	env_entry = ft_strjoin(PWD, dir);
	free(dir);
	if (!env_entry)
		return (FAILURE);
	dir = ft_getenv_value(PWD2, *env);
	res = try_add(env_entry, env);
	free(env_entry);
	if (!res)
		free_and_return(dir, FAILURE);
	env_entry = ft_strjoin(OLDPWD, dir);
	free(dir);
	if (!env_entry)
		return (FAILURE);
	res = try_add(env_entry, env);
	free(env_entry);
	return (res);
}

static char	*set_target_dir(int argc, char **argv, t_list **env)
{
	char	*target_dir;

	if (argc == 1)
	{
		target_dir = ft_getenv_value(HOME, *env);
		if (!target_dir)
			ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", MINISHELL, argv[0], \
					ERR_HOME);
	}
	else
	{
		target_dir = ft_strdup(argv[1]);
		if (!target_dir)
			ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", MINISHELL, argv[0], \
					ERR_MEM);
	}
	return (target_dir);
}

int	ft_cd(int argc, char **argv, t_list **env)
{
	char	*target_dir;
	int		res;

	target_dir = set_target_dir(argc, argv, env);
	if (!target_dir)
		return (PROG_FAILURE);
	if (chdir(target_dir))
	{
		perror(ERR_MSG_CD);
		free(target_dir);
		return (PROG_FAILURE);
	}
	res = change_pwd(env);
	free(target_dir);
	return (!res);
}

int	ft_pwd(int argc, char **argv, t_list **env)
{
	char	*dir_path;

	(void)argc;
	(void)argv;
	(void)env;
	dir_path = getcwd(NULL, 0);
	if (!dir_path)
	{
		perror(MINISHELL);
		return (PROG_FAILURE);
	}
	printf("%s\n", dir_path);
	free(dir_path);
	return (PROG_SUCCESS);
}
