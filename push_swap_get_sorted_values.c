/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_init_lists.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 09:58:39 by mprofett          #+#    #+#             */
/*   Updated: 2023/01/05 09:58:42 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	update_in_best_serie(t_stacks *stacks)
{
	t_int_list	*lst;

	stacks->inc_len = 0;
	lst = stacks->best_inc;
	while (lst)
	{
		lst->in_best_inc_serie = 1;
		++stacks->inc_len;
		lst = lst->best_next_inc_elem;
	}
}

static void	refresh_values(t_stacks *stacks, int list)
{
	t_int_list	*lst;

	lst = stacks->stack_a;
	while (lst)
	{
		if (list == 1)
			lst->in_best_inc_serie = 0;
		else if (list == 0)
		{
			lst->count_inc = 0;
			lst->next_inc_elem = NULL;
		}
		lst = lst->next;
	}
}

static void	flag_best_elems(t_stacks *stacks, int list)
{
	t_int_list	*lst;

	if (list == 1)
	{
		lst = stacks->best_inc;
		refresh_values(stacks, list);
		while (lst)
		{
			lst->in_best_inc_serie = 1;
			lst->best_next_inc_elem = lst->next_inc_elem;
			lst = lst->next_inc_elem;
		}
	}
}

static void	compare_t_int_list(t_stacks *stacks, t_int_list *current)
{
	t_int_list	*lst;

	lst = current->next;
	while (lst)
	{
		if (lst->nbr == current->nbr)
			free_stacks_and_exit(stacks);
		if (lst->count_inc >= current->count_inc && lst->nbr > current->nbr)
		{
			current->count_inc = lst->count_inc + 1;
			current->next_inc_elem = lst;
			if (!stacks->best_inc
				|| current->count_inc > stacks->inc_len)
				stacks->best_inc = current;
		}
		lst = lst->next;
	}
}

void	init_list_values(t_stacks *stacks)
{
	t_int_list	*current;
	int			i;

	i = -1;
	stacks->inc_len = 0;
	while (++i < stacks->size_max)
	{
		current = stacks->stack_a_last->previous;
		while (current)
		{
			compare_t_int_list(stacks, current);
			current = current->previous;
		}
		if (stacks->best_inc->count_inc > stacks->inc_len)
		{
			stacks->inc_len = stacks->stack_a->count_inc;
			flag_best_elems(stacks, 1);
		}
		refresh_values(stacks, 0);
		execute_without_recording(stacks, "ra");
	}
	update_in_best_serie(stacks);
}
