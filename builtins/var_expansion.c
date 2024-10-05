/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:14:37 by jingchen          #+#    #+#             */
/*   Updated: 2024/05/10 21:33:37 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

int	find_dolar(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '$')
		{
			return (i);
			break ;
		}
		i++;
	}
	return (0);
}

char	*parsing_doller(char *argv)
{
	int		i;
	int		j;
	char	*valid_name;

	i = find_dolar(argv);
	valid_name = NULL;
	i = i + 1;
	j = i;
	while (argv[i] && ((ft_isalnum(argv[i]) || argv[i] == '_')))
		i++;
	valid_name = ft_substr(argv, j, i - 1);
	return (valid_name);
}

int	is_interogante(char	*argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '$' && argv[i + 1] == '?')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*find_var(char *argv, t_env *env)
{
	char	*name;
	t_env	*aux;
	char	*var_exp;
	char	*value;

	aux = env;
	value = NULL;
	var_exp = parsing_doller(argv);
	while (aux)
	{
		name = var_name(aux->value);
		if ((ft_strlen(name) == ft_strlen(var_exp))
			&& (!(ft_strncmp(name, var_exp, ft_strlen(name)))))
		{
			free(name);
			value = envvalue(aux->value);
			break ;
		}
		free(name);
		aux = aux->next;
	}
	if (var_exp != NULL)
		free(var_exp);
	return (value);
}

char	*var_expansion(char *argv, t_env *env, int *exit_status)
{
	char	*expenssion;
	t_env	*aux;

	aux = env;
	if (is_interogante(argv))
	{
		expenssion = ft_itoa(*exit_status);
		g_exit_status = 0;
	}
	else
		expenssion = find_var(argv, aux);
	return (expenssion);
}
