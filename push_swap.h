/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 15:16:47 by mprofett          #+#    #+#             */
/*   Updated: 2022/12/30 15:16:49 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

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

typedef struct s_move_from_b_to_a
{
	int		move_nbr_in_a;
	int		move_nbr_in_b;
	int		min_move_nbr_in_a;
	int		min_move_nbr_in_b;
	int		best_nbr_in_a;
	int		best_nbr_in_b;
	int		total_move;
	char	*operation_in_a;
	char	*operation_in_b;
	char	*min_operation_in_a;
	char	*min_operation_in_b;
	char	*best_operation_in_a;
	char	*best_operation_in_b;
}				t_moves;

int		lst_is_sorted(t_int_list *stack);
int		check_elem_in_best_serie(t_stacks *stacks, int to_push);
int		check_elem_not_in_best_serie(t_stacks *stacks, int to_push);
int		get_ra_to_insert_elem(t_int_list *lst, t_stacks *stacks);
void	free_stacks_and_exit(t_stacks *stacks);
void	free_list(t_int_list *list_to_free);
void	get_list(t_stacks *stacks, int argc, char **argv);
void	init_list_values(t_stacks *stacks);
void	find_extreme_nbrs(t_stacks *stacks);
void	go_to_lowest_number(t_stacks *stacks);
void	get_total_move_for_current(t_stacks *stacks, t_moves *current);
void	check_if_current_is_best_move(t_moves *current, t_moves *best);
void	execute_last_operations_and_push_b(t_stacks *stacks, t_moves *best);
void	execute_double_operations(t_stacks *stacks, t_moves *best);
void	execute_without_recording(t_stacks *stacks, char *operation);
void	execute(t_stacks *stacks, char *operation);
void	swap_a(t_stacks *stacks);
void	swap_b(t_stacks *stacks);
void	push_a(t_stacks *stacks);
void	push_b(t_stacks *stacks);
void	rotate(t_stacks *stacks, char *operation);
void	reverse_rotate(t_stacks *stacks, char *operation);

#endif
