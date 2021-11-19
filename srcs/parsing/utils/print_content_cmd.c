/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_content_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:36:37 by mballet           #+#    #+#             */
/*   Updated: 2021/10/12 16:16:49 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_content_infile(t_cmd *content)
{
	t_list	*tmp;

	tmp = content->infile;
	while (tmp)
	{
		if ((((t_file_redir *)tmp->content)->count) == _REDIR_SINGLE)
			printf("(single | ");
		else if ((((t_file_redir *)tmp->content)->count) ==_REDIR_DOUBLE)
			printf("(double | ");
		printf("%s) ", ((t_file_redir *)tmp->content)->name);
		tmp = tmp->next;
	}
	printf("\n\033[0m");
}

void	print_content_outfile(t_cmd *content)
{
	t_list	*tmp;

	tmp = content->outfile;
	while (tmp)
	{
		if ((((t_file_redir *)tmp->content)->count) == _REDIR_SINGLE)
			printf(" (single | ");
		else if ((((t_file_redir *)tmp->content)->count) ==_REDIR_DOUBLE)
			printf(" (double | ");
		printf("%s) ", ((t_file_redir *)tmp->content)->name);
		tmp = tmp->next;
	}
	printf("\n\033[0m");
}

void	print_content_args(t_cmd *content)
{
	t_list	*tmp;

	tmp = content->args;
	while (tmp)
	{
		printf(" (%s)", tmp->content);
		tmp = tmp->next;
	}
	printf("\n\033[0m");
}
