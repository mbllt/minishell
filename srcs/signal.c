/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 18:43:15 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/11/07 22:05:17 by lgaudet-         ###   ########.fr       */
/*   Updated: 2021/11/07 21:32:50 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sig_quit(int signo)
{
	(void)signo;
	if (!g_children_running)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else
		printf("^\\Quit: 3\n");
}

void	sig_int(int signo)
{
	(void)signo;
	if (!g_children_running)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_children_running = 3;
	}
	else if (g_children_running == 2)
		exit(2);
}
