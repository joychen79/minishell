/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:16:59 by rrimonte          #+#    #+#             */
/*   Updated: 2024/05/10 03:55:24 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	*init_pid(t_data *g_data, int *pid)
{
	signal(SIGINT, signal_father);
	signal(SIGQUIT, SIG_IGN);
	if (g_data->cmd_count != 0)
	{
		pid = (int *)malloc (sizeof(int) * g_data->cmd_count);
		if (pid == NULL)
			exit(0);
	}
	return (pid);
}

t_env	*create_pipes(t_data *g_data, t_env	*envp)
{
	int	*pid;

	pid = NULL;
	pid = init_pid(g_data, pid);
	ft_init_here_docs(g_data);
	ft_backward_node(g_data);
	if (g_data->status == 2)
		return (envp);
	g_data->i = 0;
	g_data->z = -1;
	g_data->cmd_total = g_data->cmd_count;
	while (g_data->i <= g_data->total_count - 1)
	{
		envp = create_pipes1(g_data, envp);
		if (g_data->bexit == 1)
			break ;
		create_pipes2(g_data);
		pid = new_pipe(g_data, pid);
		pid = create_pipes3(g_data, envp, pid);
	}
	create_pipes_end(g_data, pid, 0);
	if (pid != NULL)
		free(pid);
	return (envp);
}

int	ft_exit(t_data *g_data, int *pid, int child_pid)
{
	int	x;

	x = 0;
	g_data->total_count--;
	while (g_data->total_count > 0)
	{
		child_pid = waitpid(pid[x], &g_data->status, 0);
		if (child_pid == -1)
		{
			perror("Error waiting child process");
			exit(EXIT_FAILURE);
		}
		x++;
		g_data->total_count--;
	}
	return (g_data->exit_status);
}
