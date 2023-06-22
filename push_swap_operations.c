/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:31:54 by mprofett          #+#    #+#             */
/*   Updated: 2023/01/04 11:31:55 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_a(t_stacks *stacks)
{
	t_int_list	*temp;

	stacks->stack_a->next->previous = stacks->stack_a;
	stacks->stack_a->previous = stacks->stack_a->next;
	temp = stacks->stack_a->next;
	if (stacks->stack_a_len > 2)
	{
		stacks->stack_a->next->next->previous = stacks->stack_a;
		stacks->stack_a->next = stacks->stack_a->next->next;
	}
	else
		stacks->stack_a->next = NULL;
	temp->next = stacks->stack_a;
	stacks->stack_a = temp;
	stacks->stack_a->previous = NULL;
	if (stacks->stack_a_len == 2)
		stacks->stack_a_last = stacks->stack_a->next;
}

void	swap_b(t_stacks *stacks)
{
	t_int_list	*temp;

	stacks->stack_b->next->previous = stacks->stack_b;
	stacks->stack_b->previous = stacks->stack_b->next;
	temp = stacks->stack_b->next;
	if (stacks->stack_b_len > 2)
	{
		stacks->stack_b->next->next->previous = stacks->stack_b;
		stacks->stack_b->next = stacks->stack_b->next->next;
	}
	else
		stacks->stack_b->next = NULL;
	temp->next = stacks->stack_b;
	stacks->stack_b = temp;
	stacks->stack_b->previous = NULL;
	if (stacks->stack_b_len == 2)
		stacks->stack_b_last = stacks->stack_b->next;
}

void	push_a(t_stacks *stacks)
{
	t_int_list	*temp;

	temp = NULL;
	if (stacks->stack_b)
	{
		if (!stacks->stack_a)
			stacks->stack_a_last = stacks->stack_b;
		else
		{
			stacks->stack_a->previous = stacks->stack_b;
			temp = stacks->stack_a;
		}
		stacks->stack_a = stacks->stack_b;
		++stacks->stack_a_len;
		--stacks->stack_b_len;
		if (stacks->stack_b_len > 0)
		{
			stacks->stack_b = stacks->stack_b->next;
			stacks->stack_b->previous = NULL;
		}
		else
			stacks->stack_b = NULL;
		stacks->stack_a->next = temp;
		stacks->stack_a->previous = NULL;
	}
}

void	push_b(t_stacks *stacks)
{
	t_int_list	*temp;

	temp = NULL;
	if (stacks->stack_a)
	{
		if (!stacks->stack_b)
			stacks->stack_b_last = stacks->stack_a;
		else
		{
			stacks->stack_b->previous = stacks->stack_a;
			temp = stacks->stack_b;
		}
		stacks->stack_b = stacks->stack_a;
		++stacks->stack_b_len;
		--stacks->stack_a_len;
		if (stacks->stack_a_len > 0)
		{
			stacks->stack_a = stacks->stack_a->next;
			stacks->stack_a->previous = NULL;
		}
		else
			stacks->stack_a = NULL;
		stacks->stack_b->next = temp;
		stacks->stack_b->previous = NULL;
	}
}

void	execute(t_stacks *stacks, char *operation)
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
	if (operation[0] == 'r' && operation[2] == '\0')
		rotate(stacks, operation);
	else if (operation[0] == 'r' && operation[2] != '\0')
		reverse_rotate(stacks, operation);
	ft_printf("%s\n", operation);
}
