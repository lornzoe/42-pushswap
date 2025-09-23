/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyanga <lyanga@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:27:12 by lyanga            #+#    #+#             */
/*   Updated: 2025/09/23 09:05:35 by lyanga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

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
		return (0);
	while (ptr != NULL)
	{
		if (text_check(*ptr) == 0 || value_check(*ptr) == 0)
		{
			free_split(split);
			return (0);
		}
		ptr++;
	}
	return (1);
}

int	validate_argv(int argc, char **argv)
{
	int			i;

	if (argc == 2)
		return (validate_string(argv[1]));
	i = 1;
	while (i < argc)
	{
		if (text_check(argv[i]) == 0 || value_check(argv[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
