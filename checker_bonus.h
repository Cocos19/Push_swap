/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:04:47 by mprofett          #+#    #+#             */
/*   Updated: 2023/01/30 14:43:19 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include "libft/libft.h"

typedef struct s_int_stack_list
{
	int						nbr;
	int						in_best_inc_serie;
	int						count_inc;
	struct s_int_stack_list	*next_inc_elem;
	struct s_int_stack_list	*best_next_inc_elem;
	struct s_int_stack_list	*previous;
	struct s_int_stack_list	*next;
}				t_int_list;

typedef struct s_int_stacks
{
	int			size_max;
	int			stack_a_len;
	int			stack_b_len;
	int			inc_len;
	int			lowest_nbr;
	int			highest_nbr;
	t_int_list	*stack_a;
	t_int_list	*stack_b;
	t_int_list	*stack_a_last;
	t_int_list	*stack_b_last;
	t_int_list	*best_inc;
}				t_stacks;

void	get_list(t_stacks *stacks, int argc, char **argv);
void	init_list_values(t_stacks *stacks);
void	free_stacks_and_exit(t_stacks *stacks);
void	free_list(t_int_list *list_to_free);
void	execute_without_recording(t_stacks *stacks, char *operation);
void	swap_a(t_stacks *stacks);
void	swap_b(t_stacks *stacks);
void	push_a(t_stacks *stacks);
void	push_b(t_stacks *stacks);
int		lst_is_sorted(t_int_list *stack);

#endif
