/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 23:17:26 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/11/07 17:57:51 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	dup_pipes(int pipe_dir, t_run_info *run)
{
	int	*pipe_fd;

	pipe_fd = run->left_pipe;
	if (pipe_dir == 1)
		pipe_fd = run->right_pipe;
	if (pipe_fd[pipe_dir] != -1)
	{
		if (dup2(pipe_fd[pipe_dir], pipe_dir) == -1)
			return (FAILURE);
		if (close(pipe_fd[0]) == -1)
			return (FAILURE);
		if (close(pipe_fd[1]) == -1)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	file_err(char *name)
{
	ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", MINISHELL, name, strerror(ENOENT));
	return (FAILURE);
}

static int	right_redir(t_cmd *cmd, t_run_info *run)
{
	t_list	*redir_head;
	int		fd;
	int		flags;

	if (!dup_pipes(1, run))
		return (FAILURE);
	redir_head = cmd->outfile;
	while (redir_head)
	{
		if (((t_file_redir *)redir_head->content)->count == _REDIR_SINGLE)
			flags = O_CREAT | O_TRUNC | O_WRONLY;
		else
			flags = O_CREAT | O_APPEND | O_WRONLY;
		fd = open(((t_file_redir *)redir_head->content)->name, flags, 0644);
		if (fd < 0)
			return (file_err(((t_file_redir *)redir_head->content)->name));
		if (dup2(fd, 1) == -1)
			return (FAILURE);
		if (close(fd))
			return (FAILURE);
		redir_head = redir_head->next;
	}
	return (SUCCESS);
}

static int	left_redir(t_cmd *cmd, t_run_info *run)
{
	t_list	*redir_head;
	int		fd;

	if (!dup_pipes(0, run))
		return (FAILURE);
	redir_head = cmd->infile;
	while (redir_head)
	{
		if (((t_file_redir *)redir_head->content)->count == _REDIR_DOUBLE)
		{
			if (dup2(get_heredoc_fd(redir_head, run), 0) == -1)
				return (FAILURE);
			redir_head = redir_head->next;
			continue ;
		}
		fd = open(((t_file_redir *)redir_head->content)->name, O_RDONLY);
		if (fd < 0)
			return (file_err(((t_file_redir *)redir_head->content)->name));
		if (dup2(fd, 0) == -1)
			return (FAILURE);
		if (close(fd) == -1)
			return (FAILURE);
		redir_head = redir_head->next;
	}
	return (SUCCESS);
}

int	prepare_redir(t_cmd *cmd, t_run_info *run)
{
	if (!left_redir(cmd, run))
		return (FAILURE);
	if (!right_redir(cmd, run))
		return (FAILURE);
	return (SUCCESS);
}
