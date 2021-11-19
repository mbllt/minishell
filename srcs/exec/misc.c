/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:33:47 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/11/08 16:27:53 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**t_list_to_char(t_list *lst)
{
	t_list	*head;
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	head = lst;
	i = 0;
	while (head)
	{
		res[i] = ft_strdup((char *)head->content);
		if (!res[i])
		{
			ft_free_token_list(res);
			return (NULL);
		}
		head = head->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	wait_children_and_set_exit_code(pid_t last_child, t_list **env)
{
	int	stat_loc;

	waitpid(last_child, &stat_loc, 0);
	while (wait(NULL) != -1)
		;
	g_children_running = 0;
	if (WIFEXITED(stat_loc))
		return (change_env_dollar_question(WEXITSTATUS(stat_loc), env));
	if (WIFSIGNALED(stat_loc))
		return (change_env_dollar_question(WTERMSIG(stat_loc) + 128, env));
	return (FAILURE);
}

void	free_and_close(void *ptr)
{
	t_heredoc_info	*here;

	here = (t_heredoc_info *)ptr;
	close(here->fd);
	free(here);
}

int	init_exec(t_run_info *run, t_exec_info info)
{
	char	*tmp;
	int		res;

	run->fd_real_in = dup(0);
	run->fd_real_out = dup(1);
	run->left_pipe[0] = -1;
	run->left_pipe[1] = -1;
	if (run->fd_real_out == -1 || run->fd_real_in == -1)
	{
		perror(ERR_EXEC);
		return (FAILURE);
	}
	res = exec_and_clean_heredoc(run, info);
	if (!res)
		return (res);
	if (((t_cmd *)info.cmds->content)->args == NULL)
		return (SUCCESS);
	tmp = ft_strjoin("_=", \
		ft_lstlast(((t_cmd *)ft_lstlast(info.cmds)->content)->args)->content);
	if (!tmp)
		return (FAILURE);
	res = try_add(tmp, &info.env);
	free(tmp);
	return (res);
}
