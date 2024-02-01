/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:54:08 by llopes-d          #+#    #+#             */
/*   Updated: 2024/02/01 16:56:29 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler_main);
	if (argc != 1 && argc != 3)
		return (write(1, "wrong arguments\n", 17));
	get_prompt_color(argc, argv);
	if (!get_data()->prompt_color)
		get_data()->prompt_color = ft_strdup(WHITE);
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
}
