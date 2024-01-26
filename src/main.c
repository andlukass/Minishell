/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:54:08 by llopes-d          #+#    #+#             */
/*   Updated: 2024/01/26 11:30:59 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(char *value, char *message)
{
	write(STDERR_FILENO, value, ft_strlen(value));
	write(STDERR_FILENO, message, ft_strlen(message));
}

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*input;
	char	*prompt;

	get_data()->pid = get_process();
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler_main);
	if (argc != 1)
		return (write(1, "too many arguments\n", 19));
	get_env(env);
	get_data()->exit_status = 0;
	while (1)
	{
		get_data()->interactive = 1;
		prompt = get_prompt();
		input = readline(prompt);
		free(prompt);
		get_data()->interactive = 0;
		if (!input)
			ft_exit(NULL, 0);
		if (*input)
			handle_input(input);
	}
	exit(0);
}
