/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_algo_push_b_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:04:12 by mprofett          #+#    #+#             */
/*   Updated: 2023/01/26 13:12:23 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_int_list	*get_next_elem_in_best_serie(t_stacks *stacks)
{
	t_int_list	*lst;

	lst = stacks->stack_a;
	while (lst)
	{
		if (lst->next && lst->next->in_best_inc_serie == 1)
			return (lst->next);
		else
			lst = lst->next;
	}
	return (NULL);
}

static t_int_list	*get_previous_elem_in_best_serie(t_stacks *stacks)
{
	t_int_list	*lst;

	lst = stacks->stack_a_last;
	while (lst)
	{
		if (lst->in_best_inc_serie == 1)
			return (lst);
		else if (lst->previous)
			lst = lst->previous;
	}
	return (NULL);
}

static int	check_if_next_elem_go_in_best_serie(t_stacks *stacks, int to_push)
{
	t_int_list	*temp;

	temp = get_previous_elem_in_best_serie(stacks);
	if (stacks->stack_a->nbr > stacks->stack_a->next->nbr
		&& (stacks->stack_a->nbr == stacks->best_inc->nbr
			|| stacks->stack_a->next->nbr > temp->nbr))
	{
		if (stacks->stack_a != stacks->best_inc)
			temp->best_next_inc_elem = stacks->stack_a->next;
		else
			stacks->best_inc = stacks->stack_a->next;
		stacks->stack_a->next->best_next_inc_elem = stacks->stack_a;
		stacks->stack_a->next->in_best_inc_serie = 1;
		execute(stacks, "sa");
		--to_push;
	}
	else
		execute(stacks, "ra");
	return (to_push);
}

int	check_elem_not_in_best_serie(t_stacks *stacks, int to_push)
{
	if (stacks->stack_a->next->in_best_inc_serie == 0
		&& stacks->stack_a->next->nbr < stacks->stack_a->nbr
		&& (get_next_elem_in_best_serie(stacks) == stacks->best_inc
			&& stacks->best_inc->nbr > stacks->stack_a->next->nbr
			&& stacks->best_inc->nbr > stacks->stack_a->nbr))
	{
		execute(stacks, "sa");
		stacks->stack_a->in_best_inc_serie = 1;
		stacks->stack_a->next->in_best_inc_serie = 1;
		stacks->stack_a->best_next_inc_elem = stacks->stack_a->next;
		stacks->stack_a->next->best_next_inc_elem = stacks->best_inc;
		stacks->best_inc = stacks->stack_a;
		--to_push;
	}
	else
		execute(stacks, "pb");
	--to_push;
	return (to_push);
}

int	check_elem_in_best_serie(t_stacks *stacks, int to_push)
{
	if (stacks->stack_a->next && stacks->stack_a->next->in_best_inc_serie == 0)
		to_push = check_if_next_elem_go_in_best_serie(stacks, to_push);
	else if (stacks->stack_a->next
		&& stacks->stack_a->next->in_best_inc_serie == 1
		&& stacks->stack_a->next->nbr < stacks->stack_a->nbr
		&& stacks->stack_a->next->best_next_inc_elem == stacks->stack_a)
	{
		execute(stacks, "sa");
		if (stacks->stack_a_len == 3
			&& stacks->stack_a_last->nbr < stacks->stack_a->nbr)
			to_push = 0;
	}
	else
		execute(stacks, "ra");
	return (to_push);
}
