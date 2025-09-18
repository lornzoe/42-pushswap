/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyanga <lyanga@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 05:33:07 by lyanga            #+#    #+#             */
/*   Updated: 2025/09/18 06:58:31 by lyanga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// make sure all argv are numbers, if fail return 0, else return 1
static int validate_argv(int argc, char **argv)
{
	const char	*p;
	
	for (int i = 1; i < argc; i++)
	{
		p = argv[i];
		if (*p == '\0')
			return (0); //empty argument
		if (p[0] == '0' && p[1] != '\0')
			return (0); // reject leading zeros
		while (*p)
		{
			if (!ft_isdigit((unsigned char)*p))
				return (0);
			p++;
		}
	}
	return (1);
}

// validate argv, if validation fails return NULL, otherwise put argv into nodes & link them
static t_stack *parse_argv(int argc, char **argv)
{
	if (argc == 1)
		return (NULL); // no args
	if (!validate_argv(argc, argv))
		return (NULL);
	// logic - create nodes with argc and argv.

}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	b = NULL;
	a = parse_argv(argc, argv);
	if (a != NULL)
	{
		// logic here
		
		// free a after done
	}
	return (0);
}