/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mballet <mballet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:27:44 by mballet           #+#    #+#             */
/*   Updated: 2021/10/26 17:08:45 by mballet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static short int	fill_in_new(char ***new, char **str, int size)
{
	size_t	size_bis;
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < (size_t)size)
	{
		size_bis = 0;
		j = -1;
		while (str[i][++j])
			size_bis++;
		(*new)[i] = malloc(sizeof(char) * size_bis + 1);
		if (!(*new)[i])
		{
			free_double((*new));
			return (FAILURE);
		}
		j = -1;
		while (str[i][++j])
			(*new)[i][j] = str[i][j];
		(*new)[i][j] = 0;
	}
	(*new)[i] = 0;
	return (SUCCESS);
}

char	**ft_strdup_double(char **str)
{
	char	**new;
	size_t	size;

	if (!str)
		return (NULL);
	size = 0;
	while (str[size])
		size++;
	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	if (!fill_in_new(&new, str, size))
		return (FAILURE);
	return (new);
}
