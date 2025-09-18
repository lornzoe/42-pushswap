/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyanga <lyanga@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:27:12 by lyanga            #+#    #+#             */
/*   Updated: 2025/09/18 19:38:21 by lyanga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int validate_argv(int argc, char **argv)
{
	const char	*p;
	int			i;

	i = 1;
	while (i < argc)
	{
		p = argv[i];
		if (*p == '\0' || ft_strlen(p) > 11)
			return (0);
		if ((p[0] == '-' && p[1] == '\0') || (p[0] == '0' && p[1] != '\0'))
			return (0);
		if (*p == '-')
			p++;
		while (*p)
		{
			if (!ft_isdigit((unsigned char)*p))
				return (0);
			p++;
		}
		i++;
	}
	return (1);
}

int validate_values(t_stack *head, char **argv)
{
	t_stack	*i;
	t_stack	*j;
	int		x;

	x = 1;
	i = head;
	while (i != NULL)
	{
		if ((long)i->value != ft_atol(argv[x]))
			return (0);
		j = i->next;
		while (j != NULL)
		{
			if (i->value == j->value)
				return (0);
			j = j->next;
		}
		i = i->next;
		x++;
	}
	return (1);
}
