/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyanga <lyanga@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:58:57 by lyanga            #+#    #+#             */
/*   Updated: 2025/09/18 16:30:18 by lyanga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void sort_three(t_stack **head)
{
	if ((*head)->index == stack_biggest((*head)))
		rotate_a(head);
	else if ((*head)->next->index == stack_biggest((*head)))
		r_rotate_a(head);
	if ((*head)->index > (*head)->next->index)
		swap_a(head);
}

void sort_five(t_stack **a, t_stack **b)
{
	while (stack_size(*a) > 3)
	{
		if ((*a)->index == 0 || (*a)->index == 1)
			push_b(a, b);
		else
			rotate_a(a);
	}
	sort_three(a);
	if ((*b)->index < (*b)->next->index)
		swap_b(b);
	push_a(a, b);
	push_a(a, b);
}

static int get_max_bits(int x)
{
	int	max;

	max = 0;
	while (x > 0)
	{
		x = x >> 1;
		max++;
	}
	return (max);
}

void radix_sort(t_stack **a, t_stack **b)
{
	int size;
	int max_bits;
	int i; // itr for index
	int j; // itr for nums
 
	size = stack_biggest((*a));
	max_bits = get_max_bits(size);
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j <= size)
		{
			if (((*a)->index >> i) & 1)
				push_b(a, b);
			else
				rotate_a(a);
			j++;
		}
		while (stack_size((*b)) > 0)
			push_a(a, b);
		i++;
	}
}
