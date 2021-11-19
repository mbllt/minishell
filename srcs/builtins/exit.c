/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:07:06 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/11/08 20:05:11 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <unistd.h>

static int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\v' || c == '\f' || \
		c == '\r' || c == ' ')
		return (SUCCESS);
	return (FAILURE);
}

static int	is_num(const char *str)
{
	char	*s;
	int		sign;

	s = (char *)str;
	sign = 0;
	while (*s)
	{
		if (((*s == '-' || *s == '+') && sign))
			return (FAILURE);
		if (*s != '-' && *s != '+' && !ft_isdigit(*s) && !ft_isspace(*s))
			return (FAILURE);
		if (ft_isdigit(*s))
			break ;
		if (*s == '-' || *s == '+')
			sign = 1;
		s++;
	}
	while (*s)
		if (!ft_isdigit(*(s++)))
			break ;
	while (*s)
		if (!ft_isspace(*(s++)))
			return (FAILURE);
	return (SUCCESS);
}

int	ft_exit(int argc, char **argv, t_list **env)
{
	long long int	status;

	(void)env;
	if (!g_children_running)
		ft_fprintf(STDERR_FILENO, "%s\n", EXIT_MSG);
	status = get_exit_code(*env);
	if (argc == 1)
		exit(status);
	status = ft_atoll(argv[1]);
	if ((status == 0 && errno != 0) || !is_num(argv[1]))
	{
		ft_fprintf(STDERR_FILENO, "%s: %s: %s: %s\n", MINISHELL, argv[0], \
			argv[1], ERR_NUM);
		exit(255);
	}
	if (argc > 2)
	{
		ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", MINISHELL, argv[0], \
			ERR_TOO_ARG);
		return (1);
	}
	exit((int)status);
}
