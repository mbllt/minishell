/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:17:09 by mballet           #+#    #+#             */
/*   Updated: 2021/10/12 12:51:04 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmds(t_exec_info global)
{
	t_list	*tmp;
	int		i;

	if (!(global.cmds))
	{
		printf("list cmds empty\n");
		return ;
	}
	i = 0;
	tmp = global.cmds;
	printf("\n");
	printf("\n");
	while (tmp)
	{
		printf("list content->args %d :\033[33m", i);
		print_content_args(tmp->content);
		printf("list content->infile %d :\033[33m", i);
		print_content_infile(tmp->content);
		printf("list content->outfile %d :\033[33m", i);
		print_content_outfile(tmp->content);
		printf("\n");
		tmp = tmp->next;
		i++;
	}
	printf("\n");
}
