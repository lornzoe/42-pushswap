/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyanga <lyanga@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:18:07 by lyanga            #+#    #+#             */
/*   Updated: 2025/09/18 16:19:50 by lyanga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void stack_del(t_stack *head)
{
	t_stack *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

t_stack *stack_last(t_stack *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

size_t stack_size(t_stack *head)
{
	size_t size;

	size = 0;
	while (head)
	{
		size++;
		head = head->next;
	}
	return (size);
}

int stack_biggest(t_stack *head)
{
	int biggest;
	biggest = -1;
	while (head)
	{
		if (head->value > biggest)
			biggest = head->index;
		head = head->next;
	}
	return (biggest);
}

int stack_issorted(t_stack *head)
{
	while (head && head->next)
	{
		if (head->value > head->next->value)
			return (0);
		head = head->next;
	}
	return (1);
}
