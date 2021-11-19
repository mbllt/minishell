/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:00:51 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/11/08 15:59:42 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec(t_exec_info info)
{
	t_list		*head;
	t_run_info	run;
	pid_t		last_pid;
	int			rank;

	if (info.cmds == NULL)
		return (SUCCESS);
	rank = init_exec(&run, info);
	if (!rank)
		return (rank == 2);
	head = info.cmds;
	rank = 0;
	while (head)
	{
		last_pid = launch_cmd(rank++, head, &run, info);
		if (last_pid == -1)
			return (SUCCESS);
		if (last_pid == -2)
			return (clean_exec(run));
		head = head->next;
	}
	clean_exec(run);
	return (wait_children_and_set_exit_code(last_pid, &info.env));
}

pid_t	launch_cmd(int i, t_list *cmd, t_run_info *run, t_exec_info info)
{
	int		res;
	pid_t	pid;

	pid = prepare_fork_pipe(i, cmd, run);
	if (pid == -2)
	{
		child((t_cmd *)cmd->content, run, info);
		return (-1);
	}
	else if (pid == 0)
	{
		child((t_cmd *)cmd->content, run, info);
		res = get_exit_code(info.env);
		clear_exec_info(info);
		exit(res);
	}
	else if (pid > 0)
		parent(i, run);
	else
	{
		perror(ERR_EXEC);
		clear_exec_info(info);
		return (-2);
	}
	return (pid);
}

int	parent(int rank, t_run_info *run)
{
	if (rank != 0)
	{
		close(run->left_pipe[0]);
		close(run->left_pipe[1]);
	}
	run->left_pipe[0] = run->right_pipe[0];
	run->left_pipe[1] = run->right_pipe[1];
	return (SUCCESS);
}

int	clean_exec(t_run_info run)
{
	close(run.fd_real_in);
	close(run.fd_real_out);
	if (run.heredocs)
		ft_lstclear(&run.heredocs, free_and_close);
	return (FAILURE);
}

pid_t	prepare_fork_pipe(int rank, t_list *head, t_run_info *run)
{
	if (head->next != NULL)
	{
		if (pipe(run->right_pipe))
			return (-1);
	}
	else
		run->right_pipe[1] = -1;
	if (((t_cmd *)head->content)->args != NULL && head->next == NULL && \
		rank == 0 && !builtin_get_default_fork((char *) \
		((t_cmd *)head->content)->args->content))
		return (-2);
	g_children_running = 1;
	return (fork());
}
