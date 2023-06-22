/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_algo_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:33:05 by mprofett          #+#    #+#             */
/*   Updated: 2023/01/26 12:33:15 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	find_extreme_nbrs(t_stacks *stacks)
{
	t_int_list	*lst;
	int			lowest;
	int			highest;

	lst = stacks->stack_a;
	lowest = stacks->stack_a->nbr;
	highest = stacks->stack_a->nbr;
	while (lst)
	{
		if (lst->nbr < lowest)
			lowest = lst->nbr;
		if (lst->nbr > highest)
			highest = lst->nbr;
		lst = lst->next;
	}
	stacks->lowest_nbr = lowest;
	stacks->highest_nbr = highest;
}

void	go_to_lowest_number(t_stacks *stacks)
{
	t_int_list	*lst;
	char		*operation;
	int			i;

	find_extreme_nbrs(stacks);
	lst = stacks->stack_a;
	i = -1;
	while (lst)
	{
		++i;
		if (lst->nbr == stacks->lowest_nbr)
			lst = NULL;
		else
			lst = lst->next;
	}
	if (i < stacks->stack_a_len - i)
		operation = "ra";
	else
	{
		i = stacks->stack_a_len - i;
		operation = "rra";
	}
	while (--i >= 0)
		execute(stacks, operation);
}

int	lst_is_sorted(t_int_list *stack)
{
	t_int_list	*lst;

	lst = stack;
	while (lst)
	{
		if (lst->next && lst->next->nbr < lst->nbr)
			return (0);
		else
			lst = lst->next;
	}
	return (1);
}

void	free_list(t_int_list *list_to_free)
{
	t_int_list	*temp;

	temp = list_to_free->next;
	while (temp)
	{
		free(list_to_free);
		list_to_free = temp;
		temp = list_to_free->next;
	}
}

void	free_stacks_and_exit(t_stacks *stacks)
{
	if (stacks->stack_a)
		free_list(stacks->stack_a);
	if (stacks->stack_b)
		free_list(stacks->stack_b);
	free(stacks);
	ft_putstr_fd("Error\n", 2);
	exit (EXIT_FAILURE);
}
