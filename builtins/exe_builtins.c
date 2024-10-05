/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:10:22 by jingchen          #+#    #+#             */
/*   Updated: 2024/05/10 02:37:55 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

int	is_builtin(char *command)
{
	if (ft_strncmp(command, "echo", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "cd", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "env", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "export", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "unset", ft_strlen(command)) == 0)
		return (1);
	return (0);
}

static void	exec_builtin_util(char **argv, t_env *env, int *exit_status)
{
	if (ft_strncmp(argv[0], "echo", ft_strlen(argv[0])) == 0)
		*exit_status = ft_echo(argv);
	if ((ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])) == 0))
	{
		*exit_status = ft_pwd();
	}
	if (ft_strncmp(argv[0], "env", ft_strlen(argv[0])) == 0)
		*exit_status = ft_env(env);
	exit(*exit_status);
}

t_env	*exec_builtin(char **argv, t_env *env, int *exit_status)
{
	int	i;

	i = 1;
	if (argv[0] != NULL)
	{
		if (ft_strncmp(argv[0], "export", ft_strlen(argv[0])) == 0)
		{
			if (!argv[1])
				*exit_status = print_export(env);
			while (argv[i])
				env = ft_export(env, argv[i++], exit_status);
		}
		else if (ft_strncmp(argv[0], "unset", ft_strlen(argv[0])) == 0)
		{
			while (argv[i])
				*exit_status = ft_unset(&env, argv[i++]);
		}
		else if (ft_strncmp(argv[0], "cd", ft_strlen(argv[0])) == 0)
			env = ft_cd(argv[1], env, exit_status);
		else if (!ft_strncmp(argv[0], "echo", ft_strlen(argv[0]))
			|| !ft_strncmp(argv[0], "pwd", ft_strlen(argv[0]))
			|| !ft_strncmp(argv[0], "env", ft_strlen(argv[0])))
			exec_builtin_util(argv, env, exit_status);
	}
	return (env);
}
