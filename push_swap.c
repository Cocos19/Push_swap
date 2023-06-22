/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 15:16:25 by mprofett          #+#    #+#             */
/*   Updated: 2022/12/30 15:16:27 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_moves	*init_moves(void)
{
	t_moves	*new_elem;

	new_elem = malloc(sizeof(t_moves));
	if (!new_elem)
		return (NULL);
	new_elem->move_nbr_in_a = 0;
	new_elem->move_nbr_in_b = 0;
	new_elem->min_move_nbr_in_a = 0;
	new_elem->min_move_nbr_in_b = 0;
	new_elem->operation_in_a = "ra";
	new_elem->operation_in_b = "rb";
	new_elem->total_move = -1;
	return (new_elem);
}

void	push_a_most_efficient(t_stacks *stacks, t_moves *current, t_moves *best)
{
	int	i;

	i = -1;
	find_extreme_nbrs(stacks);
	while (++i < stacks->stack_b_len)
	{
		current->move_nbr_in_a = get_ra_to_insert_elem(stacks->stack_a, stacks);
		current->move_nbr_in_b = i;
		get_total_move_for_current(stacks, current);
		check_if_current_is_best_move(current, best);
		execute_without_recording(stacks, "rb");
	}
	execute_double_operations(stacks, best);
	execute_last_operations_and_push_b(stacks, best);
	current->move_nbr_in_a = 0;
	current->move_nbr_in_b = 0;
	current->min_move_nbr_in_a = 0;
	current->min_move_nbr_in_b = 0;
	current->total_move = -1;
	best->move_nbr_in_a = 0;
	best->move_nbr_in_b = 0;
	best->total_move = -1;
}

void	push_b_not_in_best_increasing_serie(t_stacks *stacks)
{
	int	to_push;

	to_push = stacks->stack_a_len - stacks->inc_len;
	while (to_push > 0)
	{
		if (stacks->stack_a->in_best_inc_serie == 0)
			to_push = check_elem_not_in_best_serie(stacks, to_push);
		else
			to_push = check_elem_in_best_serie(stacks, to_push);
	}
}

void	sort_stacks(t_stacks *stacks)
{
	t_moves		*current;
	t_moves		*best;

	current = init_moves();
	if (!current)
		free_stacks_and_exit(stacks);
	best = init_moves();
	if (!best)
	{
		free(current);
		free_stacks_and_exit(stacks);
	}
	push_b_not_in_best_increasing_serie(stacks);
	while (stacks->stack_b)
		push_a_most_efficient(stacks, current, best);
	free(current);
	free(best);
	if (lst_is_sorted(stacks->stack_a) == 0)
		go_to_lowest_number(stacks);
}

int	main(int argc, char **argv)
{
	t_stacks	*stacks;

	if (argc <= 1)
		return (0);
	stacks = malloc(sizeof(t_stacks));
	if (!stacks)
		exit(EXIT_FAILURE);
	get_list(stacks, argc, argv);
	if (stacks->stack_a_len > 1)
	{
		init_list_values(stacks);
		if (stacks->stack_a && stacks->stack_a_len >= 2)
			sort_stacks(stacks);
	}
	free_list(stacks->stack_a);
	free(stacks);
	return (0);
}
