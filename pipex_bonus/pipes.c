/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:45:08 by rrimonte          #+#    #+#             */
/*   Updated: 2024/05/10 21:35:15 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	create_pipes_end(t_data *g_data, int *pid, int child_pid)
{
	dup2(g_data->in_std, STDIN_FILENO);
	close(g_data->in_std);
	g_data->bclose = 1;
	ft_backward_node(g_data);
	ft_forward_node(g_data);
	if (g_data->bexit == 0)
	{
		g_data->i = 0;
		while (g_data->i < g_data->cmd_count)
		{
			child_pid = waitpid(pid[g_data->i], &g_data->status, 0);
			if (child_pid == -1)
			{
				perror("Error waiting the child process");
				exit(EXIT_FAILURE);
			}
			g_data->exit_status = (g_data->status >> 8) & 0xFF;
			if (g_exit_status == 130)
				g_data->exit_status = 130;
			g_exit_status = 0;
			g_data->i++;
		}
	}
	else
		ft_exit(g_data, pid, child_pid);
}

t_env	*create_pipes1(t_data *g_data, t_env *envp)
{
	ft_check_infiles(g_data);
	if (1 == g_data->ncmd && g_data->cmd_lst->infile_tag == 0
		&& g_data->cmd_lst->outfile_tag == 0)
	{
		if (1 == exec_exit_father(g_data))
			return (envp);
		else
			envp = exec_builtins_father(g_data, envp);
	}
	return (envp);
}

void	create_pipes2(t_data *g_data)
{
	while ((g_data->cmd_lst->outfile_tag == 1
			|| g_data->cmd_lst->outfile_tag == 2)
		&& g_data->total_count > 0)
	{
		if (g_data->cmd_lst->outfile_tag == 2)
			g_data->outfl = open(g_data->cmd_lst->cmdaux,
					O_CREAT | O_RDWR | O_APPEND, 0664);
		else
			g_data->outfl = open(g_data->cmd_lst->cmdaux,
					O_TRUNC | O_RDWR | O_CREAT, 0664);
		g_data->total_count--;
		if (g_data->cmd_lst->next != 0)
			g_data->cmd_lst = g_data->cmd_lst->next;
		ft_check_infiles(g_data);
	}
	if (g_data->cmd_lst->infile_tag == 2)
	{
		g_data->total_count = g_data->total_count - 1;
		if (g_data->cmd_lst->next != 0)
			g_data->cmd_lst = g_data->cmd_lst->next;
		ft_check_infiles(g_data);
	}
}

int	*create_pipes3(t_data *g_data, t_env *envp, int *pid)
{
	if (g_data->cmd_lst->infile_tag == 0
		&& g_data->cmd_lst->outfile_tag == 0
		&& g_data->i <= g_data->total_count
		&& pid[g_data->z] == 0 && g_data->cmd_lst->bexport == 0)
		child(g_data, envp);
	else
	{
		if (g_data->cmd_lst->previous != NULL
			&& g_data->cmd_lst->previous->infile_tag == 2)
			close(g_data->cmd_lst->previous->fd[WRITE_O]);
		close(g_data->cmd_lst->fd[WRITE_O]);
		if (g_data->i < g_data->total_count - 1
			&& g_data->cmd_lst->next != 0)
			g_data->cmd_lst = g_data->cmd_lst->next;
		if (g_data->cmd_lst->outfile_tag == 1
			|| g_data->cmd_lst->outfile_tag == 2)
			g_data->total_count = g_data->total_count - 1;
		g_data->i++;
	}
	return (pid);
}

int	*new_pipe(t_data *g_data, int *pid)
{
	if (g_data->cmd_lst->infile_tag == 0
		&& g_data->cmd_lst->outfile_tag == 0
		&& g_data->i <= g_data->total_count
		&& g_data->cmd_lst->bexport == 0)
	{
		g_data->cmd_total--;
		g_data->z++;
		pipe(g_data->cmd_lst->fd);
		pid[g_data->z] = fork();
	}
	return (pid);
}
