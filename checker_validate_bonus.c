/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_validate_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyanga <lyanga@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 04:43:30 by lyanga            #+#    #+#             */
/*   Updated: 2026/04/22 04:43:38 by lyanga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	text_check(char *p)
{
	if (*p == '\0' || ft_strlen(p) > 11
		|| (p[0] == '-' && p[1] == '\0') || (p[0] == '0' && p[1] != '\0'))
		return (0);
	if (*p == '-')
		p++;
	while (*p)
	{
		if (!ft_isdigit((unsigned char)*p))
			return (0);
		p++;
	}
	return (1);
}

static int	value_check(char *str)
{
	long	num;

	num = ft_atol(str);
	if ((num > INT_MAX) || (num < INT_MIN))
		return (0);
	return (1);
}

int	validate_string(char *string)
{
	char	**split;
	char	**ptr;

	split = ft_split(string, ' ');
	ptr = split;
	if (split[0] == NULL)
	{
		free_split(split);
		return (0);
	}
	while (*ptr != NULL)
	{
		if (text_check(*ptr) == 0 || value_check(*ptr) == 0)
		{
			free_split(split);
			return (0);
		}
		ptr++;
	}
	free_split(split);
	return (1);
}

int	validate_argv(int argc, char **argv)
{
	int			i;

	i = 1;
	while (i < argc)
	{
		if (!validate_string(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
