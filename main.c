/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyanga <lyanga@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 05:33:07 by lyanga            #+#    #+#             */
/*   Updated: 2025/09/18 20:20:20 by lyanga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void print_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}}

// validate argv, if validation fails return NULL, otherwise put argv into nodes & link them
static t_stack *parse_argv(int argc, char **argv)
{
	int		i;
	t_stack *curr;
	t_stack *prev;
	t_stack	*head;

	if (argc == 1 || !validate_argv(argc, argv))
		return (NULL);
	i = 1;
	head = NULL;
	while (i < argc)
	{
		curr = ft_calloc(1, sizeof(t_stack));
		curr->value = ft_atoi(argv[i]);
		if (i == 1)
			head = curr;
		else
			prev->next = curr;
		prev = curr;
		i++;
	}
	return (head);
}

static void rank_nodes(t_stack *stack)
{
	t_stack	*i;
	t_stack	*j;
	int		rank;

	i = stack;
	while (i != NULL)
	{
		rank = 0;
		j = stack;
		while (j != NULL)
		{
			if (j->value < i->value)
				rank++;
			j = j->next;
		}
		i->index = rank;
		i = i->next;
	}
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	size_t size;

	b = NULL;
	a = parse_argv(argc, argv);
	if (a != NULL && validate_values(a, argv))
	{
		rank_nodes(a);
		size = stack_size(a);
		if (!stack_issorted(a) && size <= 3)
			sort_three(&a);
		else if (!stack_issorted(a) && size <= 5)
			sort_five(&a, &b);
		else if (!stack_issorted(a) && size > 5)
			radix_sort(&a, &b);
	}
	else
		print_error("Error\n");
	stack_del(a);
	stack_del(b);
	return (0);
}
