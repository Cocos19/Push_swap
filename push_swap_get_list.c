/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_get_arguments.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:43:01 by mprofett          #+#    #+#             */
/*   Updated: 2023/01/02 13:43:03 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_int_list	*int_lstnew(long long int number)
{
	t_int_list	*new_elem;

	new_elem = malloc(sizeof(t_int_list));
	if (!new_elem)
		return (NULL);
	new_elem->nbr = (int)number;
	new_elem->in_best_inc_serie = 0;
	new_elem->count_inc = 0;
	new_elem->next_inc_elem = NULL;
	new_elem->previous = NULL;
	new_elem->next = NULL;
	return (new_elem);
}

static void	add_back_new_elem_to_list(long long int nbr, t_stacks *stacks)
{
	t_int_list	*new_elem;

	new_elem = int_lstnew(nbr);
	if (!new_elem)
		free_stacks_and_exit(stacks);
	if (stacks->stack_a_last)
		stacks->stack_a_last->next = new_elem;
	else
	{
		stacks->stack_a_last = new_elem;
		stacks->stack_a = new_elem;
		stacks->best_inc = new_elem;
		stacks->size_max = 0;
	}
	++stacks->size_max;
	if (stacks->size_max > 1)
		new_elem->previous = stacks->stack_a_last;
	stacks->stack_a_last = new_elem;
}

static int	get_next_value_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		++i;
	return (i);
}

static void	get_arguments(char *str, t_stacks *stacks)
{
	long long int	nbr_to_check;
	char			*next_value_save;
	char			*next_value;

	while (str && *str)
	{
		while (str && *str && *str == ' ')
			++str;
		next_value_save = malloc(sizeof(char) * (get_next_value_len(str) + 1));
		if (!next_value_save)
			free_stacks_and_exit(stacks);
		next_value = next_value_save;
		while (str && *str && *str != ' ')
			*(next_value++) = *(str++);
		*next_value = '\0';
		nbr_to_check = safe_atoi(next_value_save);
		free (next_value_save);
		if (nbr_to_check > INT_MAX)
			free_stacks_and_exit(stacks);
		add_back_new_elem_to_list(nbr_to_check, stacks);
	}
}

void	get_list(t_stacks *stacks, int argc, char **argv)
{
	stacks->stack_b = NULL;
	stacks->stack_a_last = NULL;
	stacks->stack_b_last = NULL;
	stacks->stack_a = NULL;
	stacks->stack_a_len = 0;
	stacks->size_max = 0;
	while (--argc >= 1)
	{
		get_arguments(*(++argv), stacks);
		if (!(stacks->size_max > stacks->stack_a_len))
			free_stacks_and_exit(stacks);
		stacks->stack_a_len = stacks->size_max;
	}
	stacks->stack_b_len = 0;
}
