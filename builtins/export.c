/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:13:56 by jingchen          #+#    #+#             */
/*   Updated: 2024/05/10 03:47:45 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

t_env	*sort_env(t_env *env)
{
	char	*aux;
	t_env	*tmp;
	int		i;

	tmp = env;
	while (env->next != NULL)
	{
		i = 0;
		while (env->value[i] && (env->value[i] == env->next->value[i]))
			i++;
		if (env->value[i] > env->next->value[i])
		{
			aux = env->value;
			env->value = env->next->value;
			env->next->value = aux;
			env = tmp;
		}
		else
			env = env->next;
	}
	env = tmp;
	return (env);
}

int	print_export(t_env *env)
{
	t_env	*sorted;
	char	*name;
	char	*value;

	if (!env)
		return (1);
	sorted = sort_env(env);
	while (sorted)
	{
		name = var_name(sorted->value);
		value = envvalue(sorted->value);
		if (empty_value(sorted->value) == 1)
			printf("declare -x %s=\"%s\"\n", name, value);
		else
			printf("declare -x %s\n", name);
		free(name);
		free(value);
		sorted = sorted->next;
	}
	free(sorted);
	return (0);
}

static int	check_argv(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if ((!ft_isalnum(argv[i]) && argv[i] != '_')
			|| (!ft_isalpha(argv[0]) && argv[0] != '_'))
		{
			printf("export : \'%s\' : is invalid identifier\n", argv);
			return (1);
		}
		i++;
	}
	return (0);
}

static	void	ft_invalid_export(char **name, t_env **aux)
{
	free(*name);
	free((*aux)->value);
	free(*aux);
}

t_env	*ft_export(t_env *env, char	*argv, int *exit_status)
{
	t_env	*aux;
	char	*name;
	t_env	*tmp;

	tmp = env;
	if (!env)
		return (NULL);
	name = var_name(argv);
	aux = new_env(argv);
	*exit_status = (check_argv(name));
	if (*exit_status == 1)
	{
		ft_invalid_export(&name, &aux);
		return (env);
	}
	if (is_existing (&tmp, name) == 1)
	{
		ft_unset (&tmp, name);
		addenv_back (&tmp, aux);
	}
	if (!is_existing(&tmp, name) || !tmp)
		addenv_back(&tmp, aux);
	free(name);
	env = tmp;
	return (env);
}
