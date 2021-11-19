/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:34:46 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/11/07 21:46:40 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	prep_heredoc(int fd[2], t_run_info *run, t_file_redir *redir)
{
	t_list			*elem;
	t_heredoc_info	*here;

	here = malloc(sizeof(t_heredoc_info));
	if (!here)
		return (FAILURE);
	if (pipe(fd))
	{
		free(here);
		return (FAILURE);
	}
	elem = ft_lstnew(here);
	if (!elem)
	{
		close(fd[0]);
		close(fd[1]);
		free(here);
		return (FAILURE);
	}
	ft_lstadd_back(&run->heredocs, elem);
	here->fd = fd[0];
	here->redir = redir;
	return (SUCCESS);
}

int	get_heredoc_fd(t_list *redir_head, t_run_info *run)
{
	t_list	*heredoc_head;

	heredoc_head = run->heredocs;
	while (heredoc_head)
	{
		if (((t_heredoc_info *)heredoc_head->content)->redir == \
			((t_file_redir *)redir_head->content))
			return (((t_heredoc_info *)heredoc_head->content)->fd);
		heredoc_head = heredoc_head->next;
	}
	return (-1);
}

int	exec_and_clean_heredoc(t_run_info *run, t_exec_info info)
{
	int	res;

	res = exec_heredocs(run, info);
	if (!res)
	{
		clean_exec(*run);
		if (res == 2)
		{
			change_env_dollar_question(1, &info.env);
			return (2);
		}
		else
			return (FAILURE);
	}
	return (SUCCESS);
}
