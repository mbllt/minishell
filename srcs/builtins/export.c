/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:09:29 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/11/08 18:50:12 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_valid_name(char *str)
{
	int	i;

	if (!str)
		return (FAILURE);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (FAILURE);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	ft_export(int argc, char **argv, t_list **env)
{
	int	i;

	if (argc == 1)
		return (print_ordered_env(*env));
	i = 0;
	while (i < argc - 1)
	{
		if (!is_valid_name(argv[i + 1]))
		{
			ft_fprintf(STDERR_FILENO, "%s: %s: \"%s\": %s\n", MINISHELL, argv[0], \
			argv[i + 1], ERR_IDENT);
			return (PROG_FAILURE);
		}
		if (!try_add(argv[i + 1], env))
			return (PROG_FAILURE);
		i++;
	}
	return (PROG_SUCCESS);
}

int	ft_unset(int argc, char **argv, t_list **env)
{
	int		i;

	i = 0;
	while (i < argc - 1)
	{
		if (!argv[i + 1])
		{
			i++;
			continue ;
		}
		if (!is_valid_name(argv[i + 1]))
		{
			ft_fprintf(STDERR_FILENO, "%s: %s: %s: %s\n", MINISHELL, argv[0], \
			argv[i + 1], ERR_IDENT);
			return (PROG_FAILURE);
		}
		ft_remove_from_env(argv[i + 1], env);
		i++;
	}
	return (PROG_SUCCESS);
}

int	ft_env(int argc, char **argv, t_list **env)
{
	t_list	*head;

	(void)argc;
	(void)argv;
	head = *env;
	while (head)
	{
		if (ft_strncmp("?", (char *)head->content, 1) && \
			ft_strchr((char *)head->content, '='))
			if (!printf("%s\n", (char *)head->content))
				return (PROG_FAILURE);
		head = head->next;
	}
	return (PROG_SUCCESS);
}
