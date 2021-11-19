/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:56:23 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/11/07 22:24:25 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	child(t_cmd *cmd, t_run_info *run, t_exec_info info)
{
	if (!prepare_redir(cmd, run))
	{
		change_env_dollar_question(1, &info.env);
		return (FAILURE);
	}
	if (!launch_prog(cmd, info))
		return (FAILURE);
	if (!restore_io(run))
	{
		perror(ERR_REDIR);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	launch_prog(t_cmd *cmd, t_exec_info info)
{
	char		**argv;
	int			res;
	t_built_fun	fun;

	if ((char *)cmd->args == NULL)
		return (change_env_dollar_question(0, &info.env));
	argv = t_list_to_char(cmd->args);
	if (!argv)
	{
		ft_fprintf(STDERR_FILENO, "%s: %s\n", MINISHELL, ERR_MEM);
		change_env_dollar_question(127, &info.env);
		return (FAILURE);
	}
	fun = builtin_get_fun_ptr((char *)cmd->args->content);
	if (fun)
	{
		res = (fun)(ft_lstsize(cmd->args), argv, &info.env);
		ft_free_token_list(argv);
		return (change_env_dollar_question(res, &info.env));
	}
	return (!call_execve(argv, cmd, info));
}

int	call_execve(char **argv, t_cmd *cmd, t_exec_info info)
{
	char	*path;
	char	**env;

	if (!prepare_execve(&path, &env, (char *)cmd->args->content, info))
	{
		ft_free_token_list(argv);
		return (FAILURE);
	}
	if (execve(path, argv, env))
	{
		free(path);
		ft_free_token_list(argv);
		ft_free_token_list(env);
	}
	change_env_dollar_question(errno, &info.env);
	perror(MINISHELL);
	return (FAILURE);
}

int	prepare_execve(char **path, char ***env, char *cmd_name, t_exec_info info)
{
	*path = get_path(cmd_name, info.env);
	if (!*path)
	{
		ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", MINISHELL, cmd_name, \
		ERR_COMM_NOT_FOUND);
		change_env_dollar_question(127, &info.env);
		return (FAILURE);
	}
	*env = ft_getenv(info.env);
	if (!*env)
	{
		ft_fprintf(STDERR_FILENO, "%s: %s\n", MINISHELL, ERR_MEM);
		change_env_dollar_question(127, &info.env);
		free(*path);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	restore_io(t_run_info *run)
{
	if (dup2(0, run->fd_real_in) == -1)
		return (FAILURE);
	if (dup2(1, run->fd_real_out) == -1)
		return (FAILURE);
	return (SUCCESS);
}
