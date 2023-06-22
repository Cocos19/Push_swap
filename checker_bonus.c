/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 15:16:34 by mprofett          #+#    #+#             */
/*   Updated: 2023/01/30 14:59:54 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

int	check_if_instruction_is_valid(char *str, int str_len)
{
	if (!str)
		return (0);
	if (str_len == 3)
	{
		if (str[0] == 'p' && (str[1] == 'a' || str[1] == 'b')
			&& (str[2] == '\n' && str[3] == '\0'))
			return (1);
		if (str[0] == 's' && (str[1] == 'a' || str[1] == 'b' || str[1] == 's')
			&& str[2] == '\n' && str[3] == '\0')
			return (1);
		if (str[0] == 'r' && (str[1] == 'a' || str[1] == 'b' || str[1] == 'r')
			&& (str[2] == '\n' && str[3] == '\0'))
			return (1);
	}
	if (str_len == 4 && str[0] == 'r' && str[1] == 'r'
		&& (str[2] == 'a' || str[2] == 'b' || str[2] == 'r')
		&& (str[3] == '\n' && str[4] == '\0'))
		return (1);
	return (0);
}

char	*check_if_end_of_instructions(char *str, int str_len)
{
	if (!str)
		return (NULL);
	else if (str_len == 1 && str[0] == '\n')
	{
		free(str);
		str = NULL;
	}
	return (str);
}

void	execute_instructions(t_stacks *stacks)
{
	char	*str;
	int		str_len;

	str = get_next_line(0, 4);
	if (str)
	{
		str_len = ft_strlen(str);
		str = check_if_end_of_instructions(str, str_len);
	}
	while (str && *str)
	{
		if (!check_if_instruction_is_valid(str, str_len))
		{
			free(str);
			free_stacks_and_exit(stacks);
		}
		if (stacks->stack_a_len > 1 || (str[0] == 'p'
				&& str[1] == 'b' && str[2] == '\n' && str[3] == '\0'))
			execute_without_recording(stacks, str);
		free(str);
		str = get_next_line(0, 4);
		if (str)
			str_len = ft_strlen(str);
		str = check_if_end_of_instructions(str, str_len);
	}
}

int	main(int argc, char **argv)
{
	t_stacks	*stacks;

	if (argc <= 1)
		return (0);
	stacks = malloc(sizeof(t_stacks));
	if (!stacks)
		exit (EXIT_FAILURE);
	get_list(stacks, argc, argv);
	if (stacks->stack_a_len > 1)
		init_list_values(stacks);
	execute_instructions(stacks);
	if (!stacks->stack_b && lst_is_sorted(stacks->stack_a) == 1)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	if (stacks->stack_a)
		free_list(stacks->stack_a);
	if (stacks->stack_b)
		free_list(stacks->stack_b);
	free(stacks);
	return (0);
}
