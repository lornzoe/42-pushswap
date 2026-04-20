#include "push_swap.h"
#include <limits.h>

#ifndef CHUNK100
    #define CHUNK100 20
#endif
#ifndef CHUNK500
    #define CHUNK500 100
#endif

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

static int find_target_pos(t_stack *a_stack, int b_idx)
{
	int pos = 0;
	int best_pos = -1;
	int best_idx = -1;
	t_stack *cur = a_stack;

	if (!cur)
		return (0);
	while (cur)
	{
		if (cur->index > b_idx)
		{
			if (best_pos == -1 || cur->index < best_idx)
			{
				best_idx = cur->index;
				best_pos = pos;
			}
		}
		cur = cur->next;
		pos++;
	}
	if (best_pos != -1)
		return (best_pos);
	return (pos_of_smallest(a_stack));
}

static void do_rotations(t_stack **a_stack, t_stack **b_stack, int a_moves, int b_moves)
{
	while (a_moves > 0 && b_moves > 0)
	{
		rotate_ab(a_stack, b_stack);
		a_moves--;
		b_moves--;
	}
	while (a_moves < 0 && b_moves < 0)
	{
		r_rotate_ab(a_stack, b_stack);
		a_moves++;
		b_moves++;
	}
	while (a_moves > 0)
	{
		rotate_a(a_stack);
		a_moves--;
	}
	while (a_moves < 0)
	{
		r_rotate_a(a_stack);
		a_moves++;
	}
	while (b_moves > 0)
	{
		rotate_b(b_stack);
		b_moves--;
	}
	while (b_moves < 0)
	{
		r_rotate_b(b_stack);
		b_moves++;
	}
}

void	sort_magic(t_stack **a, t_stack **b)
{
	// int j = 0;
	// int size = (int)stack_size(*a);

	// while (j < size - 2)
	// {
	// 	push_b(a, b);
	// 	j++;
	// }

	
    push_chunks(a, b);
	sort_three(a);
    while (stack_size(*b) > 0)
	{
		int best_cost = INT_MAX;
		int best_a_moves = 0;
		int best_b_moves = 0;
		int b_size = (int)stack_size(*b);
		int a_size = (int)stack_size(*a);

		for (int i = 0; i < b_size; ++i)
		{
			t_stack *tmp = *b;
			int k = 0;
			while (k < i && tmp)
			{
				tmp = tmp->next;
				k++;
			}
			if (!tmp)
				continue;
			int b_idx = tmp->index;
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

			int cost;
			if (a_moves >= 0 && b_moves >= 0)
				cost = (a_moves > b_moves) ? a_moves : b_moves;
			else if (a_moves <= 0 && b_moves <= 0)
				cost = ((-a_moves) > (-b_moves)) ? -a_moves : -b_moves;
			else
				cost = (a_moves >= 0 ? a_moves : -a_moves) + (b_moves >= 0 ? b_moves : -b_moves);

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

	if (stack_size(*a) > 0)
	{
		int min_pos = pos_of_smallest(*a);
		int a_sz = (int)stack_size(*a);
		if (min_pos <= a_sz / 2)
			while (min_pos-- > 0)
				rotate_a(a);
		else
			while (min_pos++ < a_sz)
				r_rotate_a(a);
	}
}