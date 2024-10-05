/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:00:05 by rrimonte          #+#    #+#             */
/*   Updated: 2024/05/10 23:06:27 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	ft_compare_marks(t_data *g_data, int i)
{
	if (g_data->cmd_lst->cmdaux[i] == '"')
		check_marks(g_data, 0);
	if (g_data->cmd_lst->cmdaux[i] == '\'')
		check_marks(g_data, 1);
}

void	splitcommands(char *input, t_data *g_data, t_env	*envp)
{
	char	*start;
	char	*end;

	start = input;
	end = 0;
	ft_init_var(g_data);
	ft_check_semicolon(start, g_data, envp);
	start = input;
	while (*start != '\0')
	{
		inicialize_list(g_data);
		start = skip_delimiters(start, g_data, envp);
		end = start;
		g_data->bspaces = 0;
		end = count_quotes(g_data, end);
		check_tag(g_data, end);
		ft_catch_cmd(g_data, end, start, envp);
		start = check_if_pipe(g_data, start, end);
	}
	ft_order(g_data, envp);
	ft_backward_node(g_data);
}

int	main(int argc, char **argv, char **env)
{
	t_data		*g_data;
	t_env		*envp;

	if (argc != 1)
	{
		perror("error, don't add parameters");
		exit(1);
	}
	(void)argv;
	g_data = malloc(sizeof(t_data));
	if (g_data == NULL)
		return (0);
	ft_init_main(g_data, env);
	envp = NULL;
	envp = get_env(env, &g_data->exit_status);
	increment_shlv(envp, &g_data->exit_status);
	ft_actualize_env(g_data, envp);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	ft_loop_input(g_data, envp);
	return (0);
}
//uuu