/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyanga <lyanga@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 05:33:07 by lyanga            #+#    #+#             */
/*   Updated: 2025/09/23 08:07:27 by lyanga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_stack *parse_string(char *arg, t_stack *prev, t_stack **head)
{
    char    **split;
    int     j;
    t_stack *curr;

    split = NULL;
    curr = NULL;
	j = 0;
    split = ft_split(arg, ' ');
    while (split[j])
    {
        curr = ft_calloc(1, sizeof(t_stack));
        curr->value = ft_atoi(split[j]);
        if (!*head)
            *head = curr;
        else
            prev->next = curr;
        prev = curr;
        j++;
    }
    j = 0;
    while (split[j])
        free(split[j++]);
    free(split);
    return (prev);
}

// validate argv, if validation fails return NULL, otherwise put argv into nodes & link them
static t_stack *parse_argv(int argc, char **argv)
{
    int     i;
    t_stack *head;
    t_stack *prev;

    i = 1;
    head = NULL;
    prev = NULL;

    if (argc == 1)
        return (NULL);
    while (i < argc)
    {
        prev = parse_string(argv[i], prev, &head);
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

static int dupe_check(t_stack *head)
{
	t_stack	*i;
	t_stack	*j;
	int		x;

	x = 1;
	i = head;
	while (i != NULL)
	{
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

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	size_t size;

	b = NULL;
	a = parse_argv(argc, argv);
	if (a != NULL && dupe_check(a))
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
