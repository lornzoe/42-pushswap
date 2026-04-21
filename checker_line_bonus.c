/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_line_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyanga <lyanga@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 05:17:52 by lyanga            #+#    #+#             */
/*   Updated: 2026/04/22 07:41:05 by lyanga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"
#include "libft.h"
#include <unistd.h>

static int	process_swap(t_stack **a, t_stack **b, char *line)
{
	if (ft_strncmp(line, "sa\n", 4) == 0)
		swap(a);
	else if (ft_strncmp(line, "sb\n", 4) == 0)
		swap(b);
	else if (ft_strncmp(line, "ss\n", 4) == 0)
	{
		swap(a);
		swap(b);
	}
	else
		return (0);
	return (1);
}

static int	process_push(t_stack **a, t_stack **b, char *line)
{
	if (ft_strncmp(line, "pa\n", 4) == 0)
		push(b, a);
	else if (ft_strncmp(line, "pb\n", 4) == 0)
		push(a, b);
	else
		return (0);
	return (1);
}

static int	process_rotate(t_stack **a, t_stack **b, char *line)
{
	if (ft_strncmp(line, "ra\n", 4) == 0)
		rotate(a);
	else if (ft_strncmp(line, "rb\n", 4) == 0)
		rotate(b);
	else if (ft_strncmp(line, "rr\n", 4) == 0)
	{
		rotate(a);
		rotate(b);
	}
	else if (ft_strncmp(line, "rra\n", 5) == 0)
		r_rotate(a);
	else if (ft_strncmp(line, "rrb\n", 5) == 0)
		r_rotate(b);
	else if (ft_strncmp(line, "rrr\n", 5) == 0)
	{
		r_rotate(a);
		r_rotate(b);
	}
	else
		return (0);
	return (1);
}

int	process_lines(t_stack *a, t_stack *b)
{
	char	*line;
	int		flag;

	flag = 1;
	while (flag)
	{
		line = ft_gnl(STDIN_FILENO);
		if (!line)
			break ;
		if (process_swap(&a, &b, line))
			flag = 1;
		else if (process_push(&a, &b, line))
			flag = 1;
		else if (process_rotate(&a, &b, line))
			flag = 1;
		else
			flag = 0;
		free(line);
		line = NULL;
	}
	return (flag);
}
