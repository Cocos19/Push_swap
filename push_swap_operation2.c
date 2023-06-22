/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_lists_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:57:58 by mprofett          #+#    #+#             */
/*   Updated: 2023/01/06 13:57:59 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_stacks *stacks, char *operation)
{
	if (operation[0] == 'r' && stacks->stack_a_len > 1
		&& (operation[1] == 'a' || operation[1] == 'r'))
	{
		stacks->stack_a_last->next = stacks->stack_a;
		stacks->stack_a->previous = stacks->stack_a_last;
		stacks->stack_a_last = stacks->stack_a;
		stacks->stack_a = stacks->stack_a->next;
		stacks->stack_a->previous = NULL;
		stacks->stack_a_last->next = NULL;
	}
	if (operation[0] == 'r' && stacks->stack_a_len > 1
		&& (operation[1] == 'b' || operation[1] == 'r'))
	{
		stacks->stack_b_last->next = stacks->stack_b;
		stacks->stack_b->previous = stacks->stack_b_last;
		stacks->stack_b_last = stacks->stack_b;
		stacks->stack_b = stacks->stack_b->next;
		stacks->stack_b->previous = NULL;
		stacks->stack_b_last->next = NULL;
	}
}

void	reverse_rotate(t_stacks *stacks, char *operation)
{
	if (stacks->stack_a_len > 1 && (operation[2] == 'a' || operation[2] == 'r'))
	{
		stacks->stack_a_last->next = stacks->stack_a;
		stacks->stack_a->previous = stacks->stack_a_last;
		stacks->stack_a_last = stacks->stack_a_last->previous;
		stacks->stack_a = stacks->stack_a_last->next;
		stacks->stack_a->previous = NULL;
		stacks->stack_a_last->next = NULL;
	}
	if (stacks->stack_b_len > 1 && (operation[2] == 'b' || operation[2] == 'r'))
	{
		stacks->stack_b_last->next = stacks->stack_b;
		stacks->stack_b->previous = stacks->stack_b_last;
		stacks->stack_b_last = stacks->stack_b_last->previous;
		stacks->stack_b = stacks->stack_b_last->next;
		stacks->stack_b->previous = NULL;
		stacks->stack_b_last->next = NULL;
	}
}

void	execute_without_recording(t_stacks *stacks, char *operation)
{
	if (operation[0] == 's' && (operation[1] == 'a' || operation[1] == 's')
		&& stacks->stack_a_len > 1)
		swap_a(stacks);
	if (operation[0] == 's' && (operation[1] == 'b' || operation[1] == 's')
		&& stacks->stack_b_len > 1)
		swap_b(stacks);
	if (operation[0] == 'p' && operation[1] == 'a')
		push_a(stacks);
	if (operation[0] == 'p' && operation[1] == 'b')
		push_b(stacks);
	if (operation[0] == 'r' && (operation[2] == '\0' || operation[2] == '\n'))
		rotate(stacks, operation);
	else if (operation[0] == 'r'
		&& (operation[3] == '\0' || operation[3] == '\n'))
		reverse_rotate(stacks, operation);
}

void	execute_double_operations(t_stacks *stacks, t_moves *best)
{
	if (ft_strncmp(best->operation_in_a, best->operation_in_b, 3) == 0)
	{
		while (best->move_nbr_in_a > 0 && best->move_nbr_in_b > 0)
		{
			execute(stacks, best->operation_in_a);
			--best->move_nbr_in_a;
			--best->move_nbr_in_b;
		}
		if (best->move_nbr_in_a > 0)
		{
			if (ft_strncmp(best->operation_in_a, "rr", 3) == 0)
				best->operation_in_a = "ra";
			else
				best->operation_in_a = "rra";
		}
		if (best->move_nbr_in_b > 0)
		{
			if (ft_strncmp(best->operation_in_b, "rr", 3) == 0)
				best->operation_in_b = "rb";
			else
				best->operation_in_b = "rrb";
		}
	}
}

void	execute_last_operations_and_push_b(t_stacks *stacks, t_moves *best)
{
	while (best->move_nbr_in_a > 0)
	{
		execute(stacks, best->operation_in_a);
		--best->move_nbr_in_a;
	}
	while (best->move_nbr_in_b > 0)
	{
		execute(stacks, best->operation_in_b);
		--best->move_nbr_in_b;
	}
	if (stacks->stack_b->nbr < stacks->lowest_nbr)
		stacks->lowest_nbr = stacks->stack_b->nbr;
	else if (stacks->stack_b->nbr > stacks->highest_nbr)
		stacks->highest_nbr = stacks->stack_b->nbr;
	execute(stacks, "pa");
}
