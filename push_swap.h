/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyanga <lyanga@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 05:09:16 by lyanga            #+#    #+#             */
/*   Updated: 2025/09/18 18:52:27 by lyanga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include "ft_printf.h"

// struct
typedef struct s_stack {
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

// stack utils
void	stack_del(t_stack *head);
t_stack	*stack_last(t_stack *head);
size_t	stack_size(t_stack *head);
int		stack_biggest(t_stack *head);
int		stack_issorted(t_stack *head);

// validations
int	validate_argv(int argc, char **argv);
int validate_values(t_stack *head, char **argv);


// instructions
void	swap(t_stack **head);
void	swap_a(t_stack **head);
void	swap_b(t_stack **head);
void	swap_ab(t_stack **stack_a, t_stack **stack_b);

void	push(t_stack **stack_from, t_stack **stack_to);
void	push_a(t_stack **stack_a, t_stack **stack_b);
void	push_b(t_stack **stack_a, t_stack **stack_b);

void	rotate(t_stack **head);
void	rotate_a(t_stack **head);
void	rotate_b(t_stack **head);
void	rotate_ab(t_stack **stack_a, t_stack **stack_b);

void	r_rotate(t_stack **head);
void	r_rotate_a(t_stack **head);
void	r_rotate_b(t_stack **head);
void	r_rotate_ab(t_stack **stack_a, t_stack **stack_b);

// sorts
void sort_three(t_stack **head);
void sort_five(t_stack **a, t_stack **b);
void radix_sort(t_stack **a, t_stack **b);

#endif