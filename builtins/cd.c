/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:28:16 by jingchen          #+#    #+#             */
/*   Updated: 2024/05/10 21:14:24 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_old_path(t_env *env)
{
	char	*curr_path;
	char	*varname;
	char	*oldpwd;

	curr_path = NULL;
	while (env)
	{
		varname = var_name(env->value);
		if (ft_strncmp (varname,
				"PWD", ft_strlen (varname)) == 0)
			curr_path = envvalue (env->value);
		env = env->next;
		free(varname);
	}
	if (curr_path == NULL)
		return (NULL);
	oldpwd = ft_strjoin("OLDPWD=", curr_path, 0);
	free (curr_path);
	return (oldpwd);
}

char	*get_new_path(int *exit_status)
{
	char	buf[1024];
	char	*cwd;
	char	*newpwd;

	cwd = getcwd(buf, sizeof(buf));
	if (cwd == NULL)
	{
		printf("cd: error retrieving current directory: ");
		printf("getcwd: cannot access parent directories: ");
		printf("No such file or directory\n");
		newpwd = NULL;
		*exit_status = 1;
	}
	else
	{
		newpwd = ft_strjoin("PWD=", cwd, 0);
		*exit_status = 0;
	}
	return (newpwd);
}

static int	cd_error(char *argv, int *exit_status)
{
	printf ("cd: %s: no such file or directory\n", argv);
	*exit_status = 1;
	return (1);
}

static char	*cd_option(char *argv, t_env *env, int *exit_status)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	if (!argv)
	{
		name = "$HOME";
		value = var_expansion(name, env, exit_status);
	}
	else if (!ft_strncmp(argv, "-", ft_strlen(argv)))
	{
		name = "$OLDPWD";
		value = var_expansion(name, env, exit_status);
	}
	else
		return (ft_strdup(argv));
	return (value);
}

t_env	*ft_cd(char *argv, t_env *env, int *exit_status)
{
	char	*oldpwd;
	char	*newpwd;
	char	*tmp;
	int		code;

	newpwd = NULL;
	if (!env)
		return (NULL);
	tmp = cd_option(argv, env, exit_status);
	code = chdir(tmp);
	oldpwd = get_old_path(env);
	if (utils2_c(oldpwd, &tmp) == 1)
		return (env);
	if (!code)
	{
		newpwd = get_new_path(exit_status);
		if (utils_c(&oldpwd, newpwd, &tmp) == 1)
			return (env);
		env = ft_export(env, oldpwd, exit_status);
		env = ft_export(env, newpwd, exit_status);
	}
	else
		cd_error(tmp, exit_status);
	free_cd(&oldpwd, &newpwd, &tmp);
	return (env);
}
