/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:29:39 by rrimonte          #+#    #+#             */
/*   Updated: 2024/05/10 04:07:11 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_give_exit_value(t_data *g_data)
{
	if (g_data->cmd_lst->cmd[1][0] == '-')
	{
		if (ft_strlen(g_data->cmd_lst->cmd[1])
			< ft_strlen("-9223372036854775808"))
			return (1);
		else if (ft_strlen(g_data->cmd_lst->cmd[1])
			> ft_strlen("-9223372036854775808"))
			return (0);
		else if (ft_strcmp(g_data->cmd_lst->cmd[1], "-9223372036854775808")
			<= 0)
			return (1);
		else if (ft_strcmp(g_data->cmd_lst->cmd[1], "-9223372036854775808") > 0)
			return (0);
	}
	if (ft_strlen(g_data->cmd_lst->cmd[1]) < ft_strlen("9223372036854775807"))
		return (1);
	else if (ft_strlen(g_data->cmd_lst->cmd[1])
		> ft_strlen("9223372036854775807"))
		return (0);
	else if (ft_strcmp(g_data->cmd_lst->cmd[1], "9223372036854775807") <= 0)
		return (1);
	else if (ft_strcmp(g_data->cmd_lst->cmd[1], "9223372036854775807") > 0)
		return (0);
	return (1);
}

void	exec_exit_father2(t_data *g_data)
{
	if (!ft_str_isdigit(g_data->cmd_lst->cmd[1]))
	{
		perror("numeric argument required");
		g_data->exit_status = 2;
	}
	else if (g_data->cmd_lst->cmd[2] != NULL)
	{
		g_data->bexit = 0;
		perror("to many arguments");
		g_data->exit_status = 1;
		g_data->cmd_lst->infile_tag = 4;
	}
	else
	{
		if (ft_give_exit_value(g_data) == 1)
			g_data->exit_status = ft_atoi(g_data->cmd_lst->cmd[1]);
		else
		{
			perror("numeric argument required");
			g_data->exit_status = 2;
		}
	}
}

int	exec_exit_father(t_data *g_data)
{
	if (g_data->cmd_lst->cmd[0] != NULL)
	{
		if (g_data->cmd_lst->cmd != NULL
			&& ft_strncmp(g_data->cmd_lst->cmd[0]
				, "exit", ft_strlen(g_data->cmd_lst->cmd[0]) + 1) == 0)
		{
			g_data->total_count--;
			g_data->cmd_count--;
			g_data->bexit = 1;
			if (g_data->cmd_lst->cmd[1] != NULL)
				exec_exit_father2(g_data);
			return (1);
		}
	}
	return (0);
}

t_env	*exec_builtins_father(t_data *g_data, t_env *envp)
{
	if (g_data->cmd_lst->cmd[0] != NULL)
	{
		if (g_data->cmd_lst->cmd != NULL
			&& (ft_strncmp(g_data->cmd_lst->cmd[0], "export",
					ft_strlen(g_data->cmd_lst->cmd[0]) + 1) == 0
				|| ft_strncmp(g_data->cmd_lst->cmd[0], "unset",
					ft_strlen(g_data->cmd_lst->cmd[0]) + 1) == 0
				|| ft_strncmp(g_data->cmd_lst->cmd[0], "cd",
					ft_strlen(g_data->cmd_lst->cmd[0]) + 1) == 0))
		{
			envp = exec_builtin(g_data->cmd_lst->cmd, envp,
					&g_data->exit_status);
			ft_actualize_env(g_data, envp);
			g_data->total_count--;
			g_data->cmd_count--;
			g_data->cmd_lst->infile_tag = 4;
		}
	}
	return (envp);
}
