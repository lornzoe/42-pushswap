/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyanga <lyanga@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 17:52:15 by lyanga            #+#    #+#             */
/*   Updated: 2026/04/21 20:09:34 by lyanga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	pos_of_smallest(t_stack *s)
{
	int	best_pos;
	int	best_idx;
	int	i;

	best_pos = 0;
	i = 0;
	if (!s)
		return (0);
	best_idx = s->index;
	while (s)
	{
		if (s->index < best_idx)
		{
			best_idx = s->index;
			best_pos = i;
		}
		s = s->next;
		i++;
	}
	return (best_pos);
}

static int	find_target_pos(t_stack *a, int b_index)
{
	int		pos;
	int		best_pos;
	int		best_index;
	t_stack	*curr;

	pos = 0;
	best_pos = -1;
	best_index = -1;
	curr = a;
	while (curr)
	{
		if (curr->index > b_index)
		{
			if (best_pos == -1 || curr->index < best_index)
			{
				best_index = curr->index;
				best_pos = pos;
			}
		}
		curr = curr->next;
		pos++;
	}
	if (best_pos != -1)
		return (best_pos);
	return (pos_of_smallest(a));
}

static void	rotate_till_ordered(t_stack **s)
{
	int	min_pos;
	int	size;

	min_pos = pos_of_smallest(*s);
	size = (int)stack_size(*s);
	if (stack_size(*s) > 0)
	{
		if (min_pos <= size / 2)
			while (min_pos-- > 0)
				rotate_a(s);
		else
			while (min_pos++ < size)
				r_rotate_a(s);
	}
}

static void	get_best_move(t_stack **a, t_stack **b, int *best_a, int *best_b)
{
	int		i;
	int		moves[2];
	int		best_cost;
	t_stack	*curr_b;

	i = 0;
	best_cost = INT_MAX;
	curr_b = *b;
	while (curr_b)
	{
		moves[0] = find_target_pos(*a, curr_b->index);
		if (moves[0] > (int)stack_size(*a) / 2)
			moves[0] -= (int)stack_size(*a);
		moves[1] = i;
		if (i > (int)stack_size(*b) / 2)
			moves[1] -= (int)stack_size(*b);
		if (calculate_cost(moves[0], moves[1]) < best_cost)
		{
			best_cost = calculate_cost(moves[0], moves[1]);
			*best_a = moves[0];
			*best_b = moves[1];
		}
		curr_b = curr_b->next;
		i++;
	}
}

void	sort_large(t_stack **a, t_stack **b)
{
	int	best_a_moves;
	int	best_b_moves;

	push_chunks(a, b);
	sort_three(a);
	while (stack_size(*b) > 0)
	{
		best_a_moves = 0;
		best_b_moves = 0;
		get_best_move(a, b, &best_a_moves, &best_b_moves);
		do_rotations(a, b, best_a_moves, best_b_moves);
		push_a(a, b);
	}
	rotate_till_ordered(a);
}
