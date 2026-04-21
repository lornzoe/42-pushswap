/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyanga <lyanga@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 19:58:57 by lyanga            #+#    #+#             */
/*   Updated: 2026/04/21 20:11:22 by lyanga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_rotations(t_stack **a, t_stack **b, int a_moves, int b_moves)
{
	while (a_moves > 0 && b_moves > 0 && a_moves-- && b_moves--)
		rotate_ab(a, b);
	while (a_moves < 0 && b_moves < 0 && a_moves++ && b_moves++)
		r_rotate_ab(a, b);
	while (a_moves > 0 && a_moves--)
		rotate_a(a);
	while (a_moves < 0 && a_moves++)
		r_rotate_a(a);
	while (b_moves > 0 && b_moves--)
		rotate_b(b);
	while (b_moves < 0 && b_moves++)
		r_rotate_b(b);
}

void	push_chunks(t_stack **a, t_stack **b)
{
	int	i;
	int	size;
	int	range;

	i = 0;
	size = stack_size(*a);
	range = CHUNK100;
	if (size > 100)
		range = CHUNK500;
	while (stack_size(*a) > 3)
	{
		if ((*a)->index <= i)
		{
			push_b(a, b);
			i++;
		}
		else if ((*a)->index <= (i + range))
		{
			push_b(a, b);
			rotate_b(b);
			i++;
		}
		else
			rotate_a(a);
	}
}

int	calculate_cost(int a_moves, int b_moves)
{
	int	abs_a;
	int	abs_b;

	if (a_moves >= 0 && b_moves >= 0)
	{
		if (a_moves > b_moves)
			return (a_moves);
		return (b_moves);
	}
	if (a_moves <= 0 && b_moves <= 0)
	{
		if (a_moves < b_moves)
			return (-a_moves);
		return (-b_moves);
	}
	abs_a = a_moves;
	if (abs_a < 0)
		abs_a = -a_moves;
	abs_b = b_moves;
	if (abs_b < 0)
		abs_b = -b_moves;
	return (abs_a + abs_b);
}
