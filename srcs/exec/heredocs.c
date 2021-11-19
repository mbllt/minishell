/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:59:40 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/11/08 18:08:14 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_putstr_fd_list(t_list *list, int fd)
{
	t_list	*head;

	head = list;
	while (head)
	{
		ft_putstr_fd((char *)head->content, fd);
		ft_putstr_fd("\n", fd);
		head = head->next;
	}
	ft_lstclear(&list, free);
}

static int	ft_lstadd_back_char(char *str, t_list **list)
{
	t_list	*elem;

	elem = ft_lstnew(str);
	if (!elem)
	{
		ft_lstclear(list, free);
		return (FAILURE);
	}
	ft_lstadd_back(list, elem);
	return (SUCCESS);
}

static void	heredoc_parsing(int fd, char *str)
{
	char	*line;
	t_list	*list;

	list = NULL;
	while (1)
	{
		line = readline(HEREDOC_PROMPT);
		if (line)
		{
			if (!ft_strncmp(line, str, ft_strlen(str)))
			{
				free(line);
				ft_putstr_fd_list(list, fd);
				return ;
			}
			if (!ft_lstadd_back_char(line, &list))
				return ;
		}
		else
		{
			free(line);
			ft_putstr_fd_list(list, fd);
			return ;
		}
	}
}

static int	heredoc(t_run_info *run, t_file_redir *redir)
{
	int				fd[2];
	int				stat_loc;
	pid_t			pid;

	if (!prep_heredoc(fd, run, redir))
		return (FAILURE);
	g_children_running = 1;
	pid = fork();
	if (pid == 0)
	{
		g_children_running = 2;
		heredoc_parsing(fd[1], redir->name);
		close(fd[0]);
		close(fd[1]);
		exit(0);
	}
	if (pid < 0)
		return (FAILURE);
	close(fd[1]);
	waitpid(pid, &stat_loc, 0);
	g_children_running = 0;
	if (WIFEXITED(stat_loc))
		if (WEXITSTATUS(stat_loc) == 2)
			return (2);
	return (SUCCESS);
}

int	exec_heredocs(t_run_info *run, t_exec_info info)
{
	t_list	*cmd_head;
	t_list	*redir_head;
	int		res;

	(void)res;
	cmd_head = info.cmds;
	run->heredocs = NULL;
	while (cmd_head)
	{
		redir_head = ((t_cmd *)cmd_head->content)->infile;
		while (redir_head)
		{
			if (((t_file_redir *)redir_head->content)->count == _REDIR_DOUBLE)
			{
				res = heredoc(run, (t_file_redir *)redir_head->content);
				if (res == 2)
					return (2);
				else if (!res)
					return (FAILURE);
			}
			redir_head = redir_head->next;
		}
		cmd_head = cmd_head->next;
	}
	return (SUCCESS);
}
