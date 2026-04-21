/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_main_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyanga <lyanga@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 04:37:21 by lyanga            #+#    #+#             */
/*   Updated: 2026/04/22 06:30:10 by lyanga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"
#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>

static t_stack	*parse_string(char *arg, t_stack *prev, t_stack **head)
{
	char	**split;
	int		j;
	t_stack	*curr;

	split = NULL;
	curr = NULL;
	j = 0;
	split = ft_split(arg, ' ');
	while (split[j])
	{
		curr = ft_calloc(1, sizeof(t_stack));
		curr->value = ft_atoi(split[j]);
		if (!*head)
			*head = curr;
		else
			prev->next = curr;
		prev = curr;
		j++;
	}
	j = 0;
	while (split[j])
		free(split[j++]);
	free(split);
	return (prev);
}


static t_stack	*parse_argv(int argc, char **argv)
{
	int		i;
	t_stack	*head;
	t_stack	*prev;

	i = 1;
	head = NULL;
	prev = NULL;
	if (argc == 1 || validate_argv(argc, argv) == 0)
		return (NULL);
	while (i < argc)
	{
		prev = parse_string(argv[i], prev, &head);
		i++;
	}
	return (head);
}

static int	dupe_check(t_stack *head)
{
	t_stack	*i;
	t_stack	*j;
	int		x;

	x = 1;
	i = head;
	while (i != NULL)
	{
		j = i->next;
		while (j != NULL)
		{
			if (i->value == j->value)
				return (0);
			j = j->next;
		}
		i = i->next;
		x++;
	}
	return (1);
}

static void	cleanup(t_stack *a, t_stack *b, char *line)
{
	stack_del(a);
	stack_del(b);
	if (line)
	{
		free(line);
	}
}

int main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	char	*line;

	if (argc == 1)
		return (0);
	b = NULL;
	a = parse_argv(argc, argv);
	if (a != NULL && dupe_check(a))
	{
		while (1)
		{
			line = ft_gnl(STDIN_FILENO);
			if (!line)
				break ;
			if (!process_line(line, a, b))
				return(print_error("Error\n"), cleanup(a, b, NULL), -1);
			free(line);
		}
	}
	else
		return(print_error("Error\n"), cleanup(a, b, NULL), -1);
	// after EOF (ctrl + d i guess)
	if (stack_issorted(a) && stack_size(b) == 0)
		ft_printf("OK\n");
	else
	 	ft_printf("KO\n");
	return (cleanup(a, b, line), 0);
}
