/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_algo_push_a_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:18:56 by mprofett          #+#    #+#             */
/*   Updated: 2023/01/26 13:23:21 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_ra_to_insert_elem(t_int_list *lst, t_stacks *stacks)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (stacks->stack_b->nbr < stacks->lowest_nbr
			&& lst->nbr == stacks->lowest_nbr)
			return (i);
		if (stacks->stack_b->nbr > stacks->highest_nbr
			&& lst->nbr == stacks->highest_nbr)
			return (++i);
		if (stacks->stack_b->nbr < lst->nbr
			&& !(stacks->stack_b->nbr < stacks->lowest_nbr)
			&& ((lst->previous && lst->previous->nbr < stacks->stack_b->nbr)
				|| (!lst->previous
					&& stacks->stack_a_last->nbr < stacks->stack_b->nbr)))
			return (i);
		else
		{
			lst = lst->next;
			++i;
		}
	}
	return (i);
}

void	check_if_min_moves_is_best(t_moves *current, t_stacks *stacks)
{
	if (current->move_nbr_in_a > stacks->stack_a_len - current->move_nbr_in_a)
	{
		current->min_move_nbr_in_a
			= stacks->stack_a_len - current->move_nbr_in_a;
		current->min_operation_in_a = "rra";
	}
	if (current->move_nbr_in_b > stacks->stack_b_len - current->move_nbr_in_b)
	{
		current->min_move_nbr_in_b
			= stacks->stack_b_len - current->move_nbr_in_b;
		current->min_operation_in_b = "rrb";
	}
	if (current->min_move_nbr_in_a + current->min_move_nbr_in_b
		<= current->total_move)
	{
		current->total_move
			= current->min_move_nbr_in_a + current->min_move_nbr_in_b;
		current->best_nbr_in_a = current->min_move_nbr_in_a;
		current->best_nbr_in_b = current->min_move_nbr_in_b;
		current->best_operation_in_a = current->min_operation_in_a;
		current->best_operation_in_b = current->min_operation_in_b;
	}
}

void	init_current_values(t_moves *current)
{
	current->operation_in_a = "rr";
	current->operation_in_b = "rr";
	current->min_move_nbr_in_a = current->move_nbr_in_a;
	current->min_move_nbr_in_b = current->move_nbr_in_b;
	current->min_operation_in_a = "ra";
	current->min_operation_in_b = "rb";
	current->best_nbr_in_a = current->move_nbr_in_a;
	current->best_nbr_in_b = current->move_nbr_in_b;
	current->best_operation_in_a = "rr";
	current->best_operation_in_b = "rr";
}

void	get_total_move_for_current(t_stacks *stacks, t_moves *current)
{
	int	total_move_temp;

	init_current_values(current);
	if (current->move_nbr_in_a > current->move_nbr_in_b)
		current->total_move = current->move_nbr_in_a;
	else
		current->total_move = current->move_nbr_in_b;
	if (stacks->stack_a_len - current->move_nbr_in_a
		> stacks->stack_b_len - current->move_nbr_in_b)
		total_move_temp = stacks->stack_a_len - current->move_nbr_in_a;
	else
		total_move_temp = stacks->stack_b_len - current->move_nbr_in_b;
	if (total_move_temp < current->total_move)
	{
		current->total_move = total_move_temp;
		current->best_nbr_in_a = stacks->stack_a_len - current->move_nbr_in_a;
		current->best_nbr_in_b = stacks->stack_b_len - current->move_nbr_in_b;
		current->best_operation_in_a = "rrr";
		current->best_operation_in_b = "rrr";
	}
	check_if_min_moves_is_best(current, stacks);
	current->move_nbr_in_a = current->best_nbr_in_a;
	current->move_nbr_in_b = current->best_nbr_in_b;
	current->operation_in_a = current->best_operation_in_a;
	current->operation_in_b = current->best_operation_in_b;
}

void	check_if_current_is_best_move(t_moves *current, t_moves *best)
{
	if (best->total_move == -1 || current->total_move < best->total_move)
	{
		best->total_move = current->total_move;
		best->move_nbr_in_a = current->move_nbr_in_a;
		best->move_nbr_in_b = current->move_nbr_in_b;
		best->operation_in_a = current->operation_in_a;
		best->operation_in_b = current->operation_in_b;
	}
}
