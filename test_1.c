#include "push_swap.h"
#include <stdio.h>

void push_chunks(t_stack **a, t_stack **b)
{
	int i;
	int size;
	int range;

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

static int pos_of_smallest(t_stack *s)
{
	int best_pos = 0;
	int best_idx;
	int i = 0;

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

static int find_target_pos(t_stack *a, int b_index)
{
	int pos;
	int best_pos;
	int best_index;
	t_stack *curr;

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

static void do_rotations(t_stack **a, t_stack **b, int a_moves, int b_moves)
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
static void	rotate_till_ordered(t_stack **a)
{
	int min_pos;
	int size;

	min_pos = pos_of_smallest(*a);
	size = (int)stack_size(*a);
	if (stack_size(*a) > 0)
	{
		if (min_pos <= size / 2)
			while (min_pos-- > 0)
				rotate_a(a);
		else
			while (min_pos++ < size)
				r_rotate_a(a);
	}
}

static int	calculate_cost(int a_mv, int b_mv)
{
	int	abs_a;
	int	abs_b;

	if (a_mv >= 0 && b_mv >= 0)
	{
		if (a_mv > b_mv)
			return (a_mv);
		return (b_mv);
	}
	if (a_mv <= 0 && b_mv <= 0)
	{
		if (a_mv < b_mv)
			return (-a_mv);
		return (-b_mv);
	}
	abs_a = a_mv;
	if (abs_a < 0)
		abs_a = -a_mv;
	abs_b = b_mv;
	if (abs_b < 0)
		abs_b = -b_mv;
	return (abs_a + abs_b);
}

static t_stack	*get_nth_node(t_stack **s, int n)
{
	t_stack *tmp;
	int i = 0;

	tmp = *s;
	while (i < n && tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

static void get_best_moves(t_stack **a, t_stack **b, int *best_a, int *best_b)
{
	int i;
	int target_pos;
	int best_cost;
	int size[2];
	int cost;
	
	i = 0;
	while (i < stack_size(*b))
	{
		target_pos = find_target_pos(*a, get_nth_node(b, i)->index);
		int a_moves = 0;
		if (target_pos <= a_size / 2)
			a_moves = target_pos;
		else
			a_moves = target_pos - a_size;
		int b_moves = 0;
		if (i <= b_size / 2)
			b_moves = i;
		else
			b_moves = i - b_size;
		int cost = calculate_cost(a_moves, b_moves);
		if (cost < best_cost)
		{
			best_cost = cost;
			*best_a = a_moves;
			*best_b = b_moves;
		}
		i++;
	}
}
void	sort_magic(t_stack **a, t_stack **b)
{
	int best_cost;
	int best_a_moves;
	int best_b_moves;
	int b_size;
	int a_size;

	push_chunks(a, b);
	sort_three(a);
	while (stack_size(*b) > 0)
	{
		best_cost = INT_MAX;
		best_a_moves = 0;
		best_b_moves = 0;
		b_size = (int)stack_size(*b);
		a_size = (int)stack_size(*a);
		for (int i = 0; i < b_size; ++i)
		{
			int b_idx = get_nth_node(b, i)->index;
			int target_pos = find_target_pos(*a, b_idx);

			int a_moves = 0;
			if (target_pos <= a_size / 2)
				a_moves = target_pos;
			else
				a_moves = target_pos - a_size;
			int b_moves = 0;
			if (i <= b_size / 2)
				b_moves = i;
			else
				b_moves = i - b_size;
			int cost = calculate_cost(a_moves, b_moves);
			if (cost < best_cost)
			{
				best_cost = cost;
				best_a_moves = a_moves;
				best_b_moves = b_moves;
			}
		}
		do_rotations(a, b, best_a_moves, best_b_moves);
		push_a(a, b);
	}
	rotate_till_ordered(a);
}
