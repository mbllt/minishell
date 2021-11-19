/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:51:44 by mballet           #+#    #+#             */
/*   Updated: 2021/10/27 14:10:13 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short int	init(t_exec_info *global, char **env)
{
	struct termios	term;

	if (tcgetattr(STDOUT_FILENO, &term))
	{
		ft_fprintf(STDERR_FILENO, "%s: tcgetattr() err", MINISHELL);
		return (FAILURE);
	}
	term.c_lflag = term.c_lflag & ~ECHOCTL;
	if (tcsetattr(STDOUT_FILENO, TCSANOW, &term))
	{
		ft_fprintf(STDERR_FILENO, "%s: tcsetattr() err", MINISHELL);
		return (FAILURE);
	}
	if (signal(SIGINT, sig_int) == SIG_ERR)
		ft_fprintf(STDERR_FILENO, "%s\n", ERR_SIGINT);
	if (signal(SIGQUIT, sig_quit) == SIG_ERR)
		ft_fprintf(STDERR_FILENO, "%s\n", ERR_SIGQUIT);
	global->cmds = NULL;
	global->env = NULL;
	global->env = ft_new_env(env);
	if (!global->env)
		return (FAILURE);
	g_children_running = 0;
	return (change_env_dollar_question(0, &global->env));
}
