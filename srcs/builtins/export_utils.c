/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaudet- <lgaudet-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 22:40:02 by lgaudet-          #+#    #+#             */
/*   Updated: 2021/11/07 23:30:34 by lgaudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

static void	swap(int i, int j, char **list)
{
	char	*tmp;

	tmp = list[i];
	list[i] = list[j];
	list[j] = tmp;
}

static void	q_sort(int start, int end, char **list)
{
	int		i;
	int		j;

	i = start;
	j = end;
	if (i >= j)
		return ;
	while (i < j)
	{
		while (ft_strcmp(list[i], list[start]) < 0 && i < end)
			i++;
		while (i < j && ft_strcmp(list[j], list[start]) >= 0)
			j--;
		if (i < j)
			swap(i, j, list);
	}
	swap(i, j, list);
	q_sort(start, j, list);
	q_sort(j + 1, end, list);
}

static void	sort(char **list)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	q_sort(0, i - 1, list);
}

int	print_ordered_env(t_list *env)
{
	char	**list;
	int		i;

	list = t_list_to_char(env);
	if (!list)
		return (PROG_FAILURE);
	sort(list);
	i = 0;
	while (list[i])
	{
		if (ft_strncmp("?", list[i], 1))
			if (!printf("%s %s\n", EXPORT_MSG, list[i]))
				return (PROG_FAILURE);
		i++;
	}
	ft_free_token_list(list);
	return (PROG_SUCCESS);
}
