/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyanga <lyanga@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 04:21:22 by lyanga            #+#    #+#             */
/*   Updated: 2026/04/22 07:30:44 by lyanga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include "libft.h"
# include "ft_printf.h"
# include "ft_gnl.h"

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

// argv validation
int		validate_argv(int argc, char **argv);

// move instructions
void	swap(t_stack **head);
void	push(t_stack **stack_from, t_stack **stack_to);
void	rotate(t_stack **head);
void	r_rotate(t_stack **head);

// line processing
int		process_lines(t_stack *a, t_stack *b);

// stack utils
void	stack_del(t_stack *head);
t_stack	*stack_last(t_stack *head);
size_t	stack_size(t_stack *head);
int		stack_biggest(t_stack *head);
int		stack_issorted(t_stack *head);

// utils
void	print_error(char *str);

#endif