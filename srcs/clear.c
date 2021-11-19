/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:09:47 by mballet           #+#    #+#             */
/*   Updated: 2021/11/08 20:01:16 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define _REDIR_IN 0
#define _REDIR_OUT 1

void	ft_lstclear_redir(t_list **lst, void (*del)(void*), short int nb)
{
	t_list	*curr;
	t_list	*next;

	if (!*lst)
		return ;
	curr = *lst;
	while (curr)
	{
		next = curr->next;
		if (nb == _REDIR_IN)
		{
			if (((t_file_redir *)curr->content)->name)
				free(((t_file_redir *)curr->content)->name);
		}
		else if (nb == _REDIR_OUT)
		{
			if (((t_file_redir *)curr->content)->name)
				free(((t_file_redir *)curr->content)->name);
		}
		ft_lstdelone(curr, del);
		curr = next;
	}
	*lst = NULL;
}

void	del(void *content)
{
	if (content)
	{
		if (((t_cmd *)content)->args)
			ft_lstclear(&(((t_cmd *)content)->args), free);
		if (((t_cmd *)content)->infile)
			ft_lstclear_redir(&(((t_cmd *)content)->infile), free, _REDIR_IN);
		if (((t_cmd *)content)->outfile)
			ft_lstclear_redir(&(((t_cmd *)content)->outfile), free, _REDIR_OUT);
		free(content);
	}
}

void	clear_cmds(t_exec_info global)
{
	if (global.cmds)
		ft_lstclear(&(global.cmds), del);
}

short int	clear(t_exec_info global, char *line, int ret)
{
	if ((global.cmds))
	{
		clear_cmds(global);
	}
	if ((global.env))
	{
		ft_lstclear(&(global.env), free);
	}
	if (line)
		free(line);
	return (ret);
}

void	clear_exec_info(t_exec_info info)
{
	if (info.cmds)
		clear_cmds(info);
	ft_lstclear(&info.env, free);
}
