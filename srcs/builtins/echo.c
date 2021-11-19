/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 21:24:49 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/11/07 15:35:19 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	print(int rank, int is_newline, int argc, char **argv)
{
	while (rank < argc - 1)
	{
		printf("%s ", argv[rank]);
		rank++;
	}
	if (argc - rank > 0)
		printf("%s", argv[argc - 1]);
	if (is_newline)
		printf("\n");
	return (PROG_SUCCESS);
}

int	ft_echo(int argc, char **argv, t_list **env)
{
	int	i;
	int	j;
	int	is_newline;
	int	old_is_newline;

	(void)env;
	is_newline = 1;
	i = 1;
	if (argc > 1)
	{
		while (i < argc && !ft_strncmp(argv[i], "-n", 2))
		{
			old_is_newline = is_newline;
			j = 0;
			while (argv[i][++j])
			{
				if (argv[i][j] == 'n')
					is_newline = 0;
				else
					return (print(i, old_is_newline, argc, argv));
			}
			i++;
		}
	}
	return (print(i, is_newline, argc, argv));
}
