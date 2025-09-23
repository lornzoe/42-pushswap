/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyanga <lyanga@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:58:57 by lyanga            #+#    #+#             */
/*   Updated: 2025/09/23 08:34:59 by lyanga           ###   ########.fr       */
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
    int to_push;

    to_push = stack_size(*a) - 3;
    while (stack_size(*a) > 3)
    {
        if ((*a)->index < to_push)
            push_b(a, b);
        else
            rotate_a(a);
    }
    sort_three(a);
    if (stack_size(*b) == 2 && (*b)->index < (*b)->next->index)
        swap_b(b);
    while (stack_size(*b) > 0)
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
	int i; // itr for bit
	int j; // itr for node
	

	size = stack_size((*a));
	max_bits = get_max_bits(size - 1);
	i = -1;
	while (++i < max_bits && !stack_issorted(*a))
	{
		j = 0;
		size = stack_size(*a);
		while (j < size)
		{
			if (((*a)->index >> i) & 1)
				rotate_a(a);
			else
				push_b(a, b);
			j++;
		}
		while (stack_size((*b)) > 0)
			push_a(a, b);
	}
}

// void radix_sort(t_stack **a, t_stack **b)
// {
//     int size = stack_size(*a);
//     int max_bits = get_max_bits(size - 1);
//     int i = -1;
    
//     while (++i < max_bits && !stack_issorted(*a))
//     {
//         // Skip useless bits (optional optimization)
//         int ones = 0, zeros = 0;
//         t_stack *temp = *a;
//         while (temp)
//         {
//             if ((temp->index >> i) & 1)
//                 ones++;
//             else
//                 zeros++;
//             temp = temp->next;
//         }
        
//         // Skip if all elements have same bit value
//         if (ones == 0 || zeros == 0)
//             continue;
        
//         // Process the bit
//         //int rotations_needed = ones;  // We need to rotate past all the 1s
//         int pushes_needed = zeros;    // We need to push all the 0s
        
//         int rotations_done = 0;
//         int pushes_done = 0;
        
//         while (pushes_done < pushes_needed)
//         {
//             if (((*a)->index >> i) & 1)
//             {
//                 rotate_a(a);
//                 rotations_done++;
//             }
//             else
//             {
//                 push_b(a, b);
//                 pushes_done++;
//             }
//         }
        
//         // Push everything back from B to A
//         while (stack_size(*b) > 0)
//             push_a(a, b);
//     }
// }
